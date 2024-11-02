    #include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay), Reloj(this)
{
    ui->setupUi(this);
    Puntos.setUpMultas(&multa);

    //MURMULLO DEL GAMEPLAY (CON EASTER EGG MARIANO =O)
    MusicaGameplay = new QMediaPlayer(this);
    audioOutputGameplay = new QAudioOutput(this);
    MusicaGameplay->setAudioOutput(audioOutputGameplay);
    MusicaGameplay->setSource(QUrl("qrc:/murmullomarianito.wav"));
    audioOutputGameplay->setVolume(0.8); // Ajusta el volumen según sea necesario
    MusicaGameplay->setLoops(QMediaPlayer::Infinite);

    //SONIDO AL DENEGAR PASO
    SonidoDenegar = new QMediaPlayer(this);
    audioOutputDenegar = new QAudioOutput(this);
    SonidoDenegar->setAudioOutput(audioOutputDenegar);
    SonidoDenegar->setSource(QUrl("qrc:/denegado.wav"));
    audioOutputDenegar->setVolume(0.3);
    // Conectar el botón denegar al slot
    connect(ui->denegar, &QPushButton::clicked, this, &gameplay::noPasa);

    //SONIDO AL PERMITIR PASO
    SonidoAceptar = new QMediaPlayer(this);
    audioOutputAceptar = new QAudioOutput(this);
    SonidoAceptar->setAudioOutput(audioOutputAceptar);
    SonidoAceptar->setSource(QUrl("qrc:/checki.wav"));
    audioOutputAceptar->setVolume(0.3);
    connect(ui->aceptar, &QPushButton::clicked, this, &gameplay::siPasa);

    //SONIDO AL PEDIR PAPELES
    SonidoPapel = new QMediaPlayer(this);
    audioOutputPapel = new QAudioOutput(this);
    SonidoPapel->setAudioOutput(audioOutputPapel);
    SonidoPapel->setSource(QUrl("qrc:/papelsound.wav"));
    connect(ui->papeles, &QPushButton::clicked, this, &gameplay::mostrarDocumentos);

    //WIDGET DE LA PANTALLA
    ui->botonFinalizarTurno->hide();
    ui->documento->hide();
    ui->visa->hide();
    ui->visaD->hide();
    ui->cerrar->hide();
    ui->datos->hide();
    ui->Siguiente_NPC->setDisabled(true);
    ui->confirmar->hide();
    ui->cancelar->hide();
    ui->nombrePartida->hide();
    ui->mensajePG->hide();
    ui->volverAlMenu->hide();

    //TIMER
    tiempoInicio = QTime(13, 0);  //inicia a las 13
    horaFin = QTime(13.2, 0);       //termina a las 22

    // Conexiones de botones
    connect(ui->Boton_SiguienteDia, &QPushButton::clicked,  this, &gameplay::ComenzarSiguienteDia);
    connect(ui->documento, &QPushButton::clicked,  this, &gameplay::actualizarLabelDocumento); //boton de generar npc
    connect(ui->Boton_ReiniciarNivel, &QPushButton::clicked,  this, &gameplay::ReiniciarNivel);
    connect(ui->botonFinalizarTurno, &QPushButton::clicked,  this, &gameplay::DatosFinalizar);
    connect(ui->mostrar_req, &QPushButton::clicked,  this, &gameplay::CondicionesNivel);
    connect(ui->BotonVolver, &QPushButton::clicked,  this, &gameplay::VolverMesa);
    connect(ui->guardarPartida, &QPushButton::clicked, this, &gameplay::clikedGuardarPartida);
    connect(ui->cancelar, &QPushButton::clicked, this, &gameplay::clikedCancelarGuardar);
    connect(ui->confirmar, &QPushButton::clicked, this, &gameplay::clikedConfirmarGuardar);
    connect(ui->volverAlMenu, &QPushButton::clicked, this, &gameplay::volverAlMenuClicked);
    connect(ui->visa, SIGNAL(clicked()), this, SLOT(actualizarLabelVisa()));
    connect(ui->aceptar, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->denegar, SIGNAL(clicked()), this, SLOT(noPasa()));
    connect(ui->cerrar, SIGNAL(clicked()), this, SLOT(cerrarDocumentos()));
    connect(ui->papeles, SIGNAL(clicked()), this, SLOT(mostrarDocumentos()));

    //ANIMACIONES
    animacionEntrada = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacion();

    animacionSalida = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacionSalida();

    //CONEXIONES de NPC
    connect(ui->Siguiente_NPC, SIGNAL(clicked()), this, SLOT(generarNpc()));
    connect(animacionSalida, &QAbstractAnimation::finished, this, &gameplay::EntrarNPC);

    connect(&Reloj, &QTimer::timeout, this, &gameplay::actualizarReloj);

    //FUNCIONES

    // Seteamos como widget principal donde se mostrara el juego:
    ui->stackedWidget->setCurrentWidget(ui->game);
}

void gameplay::clikedGuardarPartida(){
    ui->nombrePartida->show();
    ui->confirmar->show();
    ui->cancelar->show();
    ui->guardarPartida->hide();
}

void gameplay::clikedCancelarGuardar(){
    ui->nombrePartida->clear();
    ui->nombrePartida->hide();
    ui->confirmar->hide();
    ui->cancelar->hide();
    ui->guardarPartida->show();
}

void gameplay::clikedConfirmarGuardar(){
    // Obtener el texto del QLineEdit
    QString texto = ui->nombrePartida->text();

    emit nombrePartidaActualizado(texto);

    // Convertir el QString a un QByteArray
    QByteArray byteArray = texto.toLatin1(); // o .toUtf8() si necesitas UTF-8

    // Copiar el contenido a 'nombrePartida', asegurando que no exceda el tamaño
    strncpy(nombrePartida, byteArray.data(), sizeof(nombrePartida) - 1);

    // Asegurarse de que la cadena esté terminada en nulo
    nombrePartida[sizeof(nombrePartida) - 1] = '\0';

    qDebug() << nombrePartida;
    // Ahora tienes el texto del QLineEdit en nombrePartida como char[]



    ui->mensajePG->show();
    ui->guardarPartida->hide();
    ui->confirmar->hide();
    ui->cancelar->hide();
    ui->nombrePartida->hide();
    ui->volverAlMenu->show();
}

char* gameplay::getNombrePartida(){
    return nombrePartida;
}

void gameplay::Empezar(int Dificultad)
{
    Nivel = 1;
    MusicaGameplay->play();
    setUpPuntos(Dificultad);
    iniciarReloj(); //el reloj comienza cuando se produse el cambio de ventana
    EntrarNPC();
}

void gameplay::Empezar(DatosJugador datos)
{
    Nivel = datos.nivel;
    Puntos.setPunto(datos.puntuacion);


}

void gameplay::setUpPuntos(int Dificultad)
{
    switch (Dificultad){
    case 0: Puntos.puntuacion_asignada1();
        break;
    case 1: Puntos.puntuacion2_asignada2();
        break;
    default: Puntos.puntuacion3_asignada3();
        break;
    }

    qDebug() << Puntos.obtener_puntos();
}

gameplay::~gameplay()
{
    delete ui;
}

//TODA FUNCION QUE EMPIECE CON GET EN ESTA HOJA ES PARA USARLA EN LA CLASE MAINWINDOW
QPushButton* gameplay::getBotonSiguiente_NPC(){//<-MW
    return ui->Siguiente_NPC;
}

QLabel *gameplay::getLabelNPC(){//<-MW
    return ui->Label_NPC;
}

void gameplay::DatosFinalizar() {//esto para verificar si perdiste, en caso que no se muestran los puntos y mupunt
    int puntaje = Puntos.obtener_puntos();
    int multaa = multa.obtenerMultas();
    MusicaGameplay->stop();

    if ((multaa > 4) || (puntaje < 0)) {
        ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
        ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
        ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
        ui->labelMultas->setVisible(false);
        ui->Boton_SiguienteDia->setVisible(false);

        DatosJugador jugador;
        jugador.multas = multaa; jugador.puntuacion = puntaje;
        jugador.nivel = Nivel;
        emit (jugador);
    } else {//en caso de que se siga el juego se muestra lo siguiente
        ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
        ui->Boton_ReiniciarNivel->setVisible(false);
        ui->labelPuntos->setText(QString("Puntos: %1").arg(puntaje));//se muestran los puntos (arg es paraa mostrar los puntos
        ui->labelPuntos->setVisible(true);//se abre el label de puntos
        ui->labelMultas->setText(QString("Multas: %1").arg(multaa));//lo mismo para multas
        ui->labelMultas->setVisible(true);
        ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
    }

    // Mostramos la pantalla de puntuacion
    ui->stackedWidget->setCurrentWidget(ui->PantallaPuntuacion);
    emit clickedFinalizar();
}

void gameplay::cambiarSkinNPC(){
    condicion1 = Persona.obtenerNpc();

    if(condicion1=="aldeano"){
        ui->Label_NPC->setStyleSheet(ALDEANO);
    }else if(condicion1=="refugiado político"){
        ui->Label_NPC->setStyleSheet(REFUGIADOPOLITICO);
    }else if(condicion1=="diplomático"){
        ui->Label_NPC->setStyleSheet(DIPLOMATICO);
    }else if(condicion1=="revolucionario"){
        ui->Label_NPC->setStyleSheet(REVOLUCIONARIO);
    }
}

void gameplay::EntrarNPC()
{
    cambiarSkinNPC();
    // Calcula la coordenada X central para el labelNPC
    int centerX = (width() - ui->Label_NPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 60;

    animacionEntrada->setStartValue(QPoint(-(ui->Label_NPC->width()),centerY));
    animacionEntrada->setEndValue(QPoint(centerX, centerY));

    animacionEntrada->start();
}

void gameplay::SalirNPC()
{
    // Calcula la coordenada X central para el labelNPC
    int centerX = (width() - ui->Label_NPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 60;

    animacionSalida->setStartValue(QPoint(centerX, centerY));
    animacionSalida->setEndValue(QPoint(width() + ui->Label_NPC->height(), centerY));

    animacionSalida->start();
}

void gameplay::PrepararAnimacion()
{
    // Establece la duración de la animación en milisegundos
    animacionEntrada->setDuration(1500);

    // Establece la curva de animación para que sea suave y desacelerada al final
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
}

void gameplay::PrepararAnimacionSalida()
{
    // Establece la duración de la animación en milisegundos
    animacionSalida->setDuration(1500);

    // Establece la curva de animación para que sea suave y desacelerada al final
    animacionSalida->setEasingCurve(QEasingCurve::InExpo);
}

void gameplay::generarNpc()
{
    Persona.generarFecha();
    Persona.generarNacionalidad();
    Persona.generarNombres();
    Persona.generarVisa();
    Persona.generar_Estado_civil();
    Persona.generar_Estancia();
    Persona.pensamientos();

    ui->aceptar->setEnabled(true);
    ui->denegar->setEnabled(true);
    ui->papeles->setEnabled(true);
    ui->mostrar_req->setEnabled(true);
    ui->Siguiente_NPC->setDisabled(true);

    SalirNPC();
}

void gameplay::mostrarDocumentos()
{
    SonidoPapel->play();
    ui->papeles->setDisabled(true);
    ui->documento->show();
    ui->visa->show();
    ui->cerrar->show();
}

void gameplay::actualizarLabelDocumento() //esta funcion muestra los datos cuando se presiona un boton
{
    QString datosMostrar = QString("\n\n\n      Genero:                          %1\n\n      Nombre:                         %2\n\n      Apellido:                         %3\n\n      Nacido/a el:                   %4\n\n      Nacionalidad:                 %5\n\n")
                            .arg(Persona.obtenerGenero())
                            .arg(Persona.obtenerNombre())
                            .arg(Persona.obtenerApellido())
                            .arg(Persona.obtenerFecha())
                            .arg(Persona.obtenerNacionalidad());

    ui->datos->setText(datosMostrar);
    ui->datos->show();
    ui->visaD->hide();
}


void gameplay::actualizarLabelVisa()
{

    QString datosMostrarVisa = QString("Tipo de visa\n%1\n\nDuracion de la estancia\n%2\n\n Estado civil\n%3\n\n\n\n\n\n")
                                .arg(Persona.getPersonaVisa())
                                .arg(Persona.obtenerEstancia())
                                .arg(Persona.getPersonaEstCivil());

    ui->visaD->setText(datosMostrarVisa);

    ui->datos->hide();
    ui->visaD->show();
}

void gameplay::cerrarDocumentos()
{
    ui->papeles->setEnabled(true);

    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->documento->hide();
    ui->visaD->hide();
}


//aca se determina si la decision del jugador esta bien o no dependiendo de lo que elija
void gameplay::siPasa()
{
    SonidoAceptar->play();
    int p1 = Persona.obtenerPop();
    QString tipo = Persona.obtenerNpc();
    if (p1 == 1)
    {
        Puntos.puntaje(tipo);
    }
    else
    {
        Puntos.puntaje2(tipo);
    }
    Persona.retPop();

    ui->documento->hide();
    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->visaD->hide();

    ui->aceptar->setDisabled(true);
    ui->denegar->setDisabled(true);
    ui->papeles->setDisabled(true);
    ui->mostrar_req->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
}


void gameplay::noPasa()
{
    SonidoDenegar->play();
    int p1 = Persona.obtenerPop();
    QString tipo = Persona.obtenerNpc();
    if (p1 == 0)
    {
        Puntos.puntaje(tipo);
    }
    else
    {
        Puntos.puntaje2(tipo);
    }
    Persona.retPop();

    ui->documento->hide();
    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->visaD->hide();

    ui->aceptar->setDisabled(true);
    ui->denegar->setDisabled(true);
    ui->papeles->setDisabled(true);
    ui->mostrar_req->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
}


void gameplay::iniciarReloj() //funcion de inicio del reloj
{
    Reloj.start(1000); // Emitir la señal timeout cada 1 segundor
    tiempoActual = tiempoInicio;
}

void gameplay::ReiniciarNivel()
{
    emit clickedReiniciar();
    ui->stackedWidget->setCurrentWidget(ui->game);
    iniciarReloj();
    EntrarNPC();

}

void gameplay::CondicionesNivel()
{
    emit clickedCondiciones();
    ui->stackedWidget->setCurrentWidget(ui->game_3);
}

void gameplay::VolverMesa()
{
    ui->stackedWidget->setCurrentWidget(ui->game);
    emit clickedVolverMesa();
}

void gameplay::ComenzarSiguienteDia()
{
    iniciarReloj();
    ui->stackedWidget->setCurrentWidget(ui->game);

    iniciarReloj();

    emit clickedSiguienteDia();
}

void gameplay::actualizarReloj()
{
    tiempoActual = tiempoActual.addSecs(150);

    // Verificar si ha llegado a la hora de finalizar el turno 22:00
    if (tiempoActual >= horaFin)
    {
        Reloj.stop(); //cuando el tiempo se cumlpe detiene el reloj

        //cuando el tiempo acaba se muestra el boton de pasar de dia y se ocultan el resto de cosas
        ui->aceptar->hide();
        ui->denegar->hide();
        ui->mostrar_req->hide();
        ui->papeles->hide();
        ui->documento->hide();
        ui->timer->hide();
        ui->datos->hide();
        ui->Siguiente_NPC->hide();
        ui->cerrar->hide();

        ui->visa->hide();
        ui->visaD->hide();

        ui->botonFinalizarTurno->show();

        return;
    }

    ui->timer->setText(tiempoActual.toString("hh:mm:ss"));
}


void gameplay::preguntar()
{
    QString per = Persona.obtenerPensamientos();
}


void gameplay::MostrarCondiciones(){
    ui->RNacionalidad->setText(condicion.obtenerNacionalidad());
    ui->REstancia->setText(condicion.obtenerEstancia());
    ui->REstCivil->setText(condicion.obtenerEstCivil());
    ui->RFecha->setText(condicion.obtenerFecha());
    ui->RTipoVisita->setText(condicion.obtenerTipoVisita());
}
