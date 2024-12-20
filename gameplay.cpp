#include "gameplay.h"
#include "ui_gameplay.h"
#include <qdebug.h>

gameplay::gameplay(Logs * logs, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay), Reloj(this), log(logs)
{
    ui->setupUi(this);
    Puntos.setUpMultas(&multa);
    //
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

    //SONIDO GAME OVER
    SonidoGameOver = new QMediaPlayer(this);
    audioOutputGameOver = new QAudioOutput(this);
    SonidoGameOver->setAudioOutput(audioOutputGameOver);
    SonidoGameOver->setSource(QUrl("qrc:/game_over.wav"));
    audioOutputGameOver->setVolume(0.3);

    //SONIDO VICTORIA
    SonidoVictoria = new QMediaPlayer(this);
    audioOutputVictoria = new QAudioOutput(this);
    SonidoVictoria->setAudioOutput(audioOutputVictoria);
    SonidoVictoria->setSource(QUrl("qrc:/victoria_sound.wav"));
    audioOutputVictoria->setVolume(0.3);


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
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->ocupacion->hide();
    ui->proposito->hide();
    ui->residencia->hide();
    ui->nivel2_reglas_2->hide();
    ui->nivel3_reglas_2->hide();
    ui->nivel4->hide();
    ui->regNiv1->hide();
    ui->nivel->hide();

    ui->mensajePG_2->hide();
    ui->SLOT1->hide();
    ui->SLOT2->hide();
    ui->SLOT3->hide();

    //TIMER
    tiempoInicio = QTime(13, 0);  //inicia a las 13
    horaFin = QTime(22, 0);       //termina a las 22

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
    connect(ui->SLOT1, &QPushButton::clicked, this, &gameplay::setIndexSlot1);
    connect(ui->SLOT2, &QPushButton::clicked, this, &gameplay::setIndexSlot2);
    connect(ui->SLOT3, &QPushButton::clicked, this, &gameplay::setIndexSlot3);
    connect(ui->visa, SIGNAL(clicked()), this, SLOT(actualizarLabelVisa()));
    connect(ui->proposito, SIGNAL(clicked()), this, SLOT(actualizarResidencia()));
    connect(ui->aceptar, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->denegar, SIGNAL(clicked()), this, SLOT(noPasa()));
    connect(ui->cerrar, SIGNAL(clicked()), this, SLOT(cerrarDocumentos()));
    connect(ui->papeles, SIGNAL(clicked()), this, SLOT(mostrarDocumentos()));

    connect(ui->regNiv1, SIGNAL(clicked()), this, SLOT(botonReglas1()));
    connect(ui->regNiv2, SIGNAL(clicked()), this, SLOT(botonReglas2()));

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
    MostrarCondiciones();

    // Seteamos como widget principal donde se mostrara el juego:
    ui->stackedWidget->setCurrentWidget(ui->game);

}

void gameplay::setIndexSlot1(){
    indexSLOT = 0;
    emit emitirIndexSlot(indexSLOT);
}
void gameplay::setIndexSlot2(){
    indexSLOT = 1;
    emit emitirIndexSlot(indexSLOT);
}
void gameplay::setIndexSlot3(){
    indexSLOT = 2;
    emit emitirIndexSlot(indexSLOT);
}

void gameplay::iniciarMusicaGameplay() {
    MusicaGameplay->play();
}

void gameplay::detenerMusicaGameplay() {
    MusicaGameplay->stop();
}

void gameplay::cargarJugardor(DatosJugador jugador){
    log->setText("Jugador pulso paraa cargar partida.");
    Puntos.setPunto(jugador.puntuacion);
    multa.setMultas(jugador.multas);
    Nivel = jugador.nivel;
    EmpezarJuegoSlot(jugador);
    iniciarReloj();
}

void gameplay::clikedGuardarPartida(){
    log->setText("Jugador guardo la partida.");
    ui->nombrePartida->show();
    ui->confirmar->show();
    ui->cancelar->show();
    ui->guardarPartida->hide();
    ui->SLOT1->show();
     ui->SLOT2->show();
     ui->SLOT3->show();
}

void gameplay::clikedCancelarGuardar(){
    log->setText("Jugador cancelo el guarddo.");
    ui->nombrePartida->clear();
    ui->nombrePartida->hide();
    ui->confirmar->hide();
    ui->cancelar->hide();
    ui->guardarPartida->show();
}

void gameplay::clikedConfirmarGuardar(){

    if(indexSLOT == -1){
        ui->mensajePG_2->show();
        return;
    }

    ui->mensajePG_2->hide();
    ui->SLOT1->hide();
    ui->SLOT2->hide();
    ui->SLOT3->hide();

    // Obtener el texto del QLineEdit
    QString texto = ui->nombrePartida->text();

    emit nombrePartidaActualizado(texto);

    // Convertir el QString a un QByteArray
    QByteArray byteArray = texto.toLatin1(); // o .toUtf8() si necesitas UTF-8

    // Copiar el contenido a 'nombrePartida', asegurando que no exceda el tamaño
    strncpy(nombrePartida, byteArray.data(), sizeof(nombrePartida) - 1);

    // Asegurarse de que la cadena esté terminada en nulo
    nombrePartida[sizeof(nombrePartida) - 1] = '\0';

    // Ahora tienes el texto del QLineEdit en nombrePartida como char[]

    DatosJugador aux;
    for (int i = 0; i < 50; i++)
        aux.nombre[i] = nombrePartida[i];
    aux.multas = this->multa.obtenerMultas();
    aux.nivel = this->Nivel;
    aux.puntuacion = this->Puntos.obtener_puntos();

    emit GuardarDatos(aux, indexSLOT);

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
    iniciarMusicaGameplay();
    Nivel;
    setUpPuntos(Dificultad);
    mostrarNivel(); //prueba
    iniciarReloj(); //el reloj comienza cuando se produse el cambio de ventana
    EntrarNPC();
    ui->SLOT1->hide();
    ui->SLOT2->hide();
    ui->SLOT3->hide();
    ui->mensajePG->hide();
    ui->mensajePG->hide();
    ui->guardarPartida->show();
    ui->volverAlMenu->show();

}

void gameplay::EmpezarJuegoSlot(DatosJugador datos)
{
    Nivel = datos.nivel;
    Puntos.setPunto(datos.puntuacion);
    iniciarReloj();
    EntrarNPC();
    ui->stackedWidget->setCurrentIndex(0);
    qDebug()<<"hola";
}

void gameplay::setUpPuntos(int Dificultad)
{
    switch (Dificultad){
    case 0: Puntos.puntuacion_asignada1();
        Nivel=1;
        break;
    case 1: Puntos.puntuacion2_asignada2();
        Nivel=1;
        break;
    case 2: Puntos.puntuacion3_asignada3();
        Nivel=1;
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
    log->setText("Jugador finalizo el nivel.");
    int puntaje = Puntos.obtener_puntos();
    int multaa = multa.obtenerMultas();
    detenerMusicaGameplay();
    int niv = Nivel;
    if(niv==1){
    if ((multaa > 4) || (puntaje < 0)) {
            log->setText("Jugador perdio al nivel 1.");
        ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
        ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
        ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
        ui->labelMultas->setVisible(false);
        ui->Boton_SiguienteDia->setVisible(false);
        SonidoGameOver -> play();

    } else {//en caso de que se siga el juego se muestra lo siguiente
        log->setText("Jugador gano el nivel 1.");
        ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
        ui->Boton_ReiniciarNivel->setVisible(false);
        ui->labelPuntos->setText(QString("Puntos: %1").arg(puntaje));//se muestran los puntos (arg es paraa mostrar los puntos
        ui->labelPuntos->setVisible(true);//se abre el label de puntos
        ui->labelMultas->setText(QString("Multas: %1").arg(multaa));//lo mismo para multas
        ui->labelMultas->setVisible(true);
        ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
        SonidoVictoria -> play();
        Nivel++;
        }
    }
    if(niv==2){
        if ((multaa > 4) || (puntaje < 50)) {
            log->setText("Jugador perdio al nivel 2.");
            ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
            ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
            ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
            ui->labelMultas->setVisible(false);
            ui->Boton_SiguienteDia->setVisible(false);
            SonidoGameOver -> play();
        } else {//en caso de que se siga el juego se muestra lo siguiente
            log->setText("Jugador gano el nivel 2.");
            ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
            ui->Boton_ReiniciarNivel->setVisible(false);
            ui->labelPuntos->setText(QString("Puntos: %1").arg(puntaje));//se muestran los puntos (arg es paraa mostrar los puntos
            ui->labelPuntos->setVisible(true);//se abre el label de puntos
            ui->labelMultas->setText(QString("Multas: %1").arg(multaa));//lo mismo para multas
            ui->labelMultas->setVisible(true);
            ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
            SonidoVictoria -> play();
            Nivel++;
        }
    }
    if(niv==3){
        if ((multaa > 4) || (puntaje < 100)) {
            log->setText("Jugador perdio al nivel 3.");
            ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
            ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
            ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
            ui->labelMultas->setVisible(false);
            ui->Boton_SiguienteDia->setVisible(false);
            SonidoGameOver -> play();
        } else {//en caso de que se siga el juego se muestra lo siguiente
            log->setText("Jugador gano el nivel 3.");
            ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
            ui->Boton_ReiniciarNivel->setVisible(false);
            ui->labelPuntos->setText(QString("Puntos: %1").arg(puntaje));//se muestran los puntos (arg es paraa mostrar los puntos
            ui->labelPuntos->setVisible(true);//se abre el label de puntos
            ui->labelMultas->setText(QString("Multas: %1").arg(multaa));//lo mismo para multas
            ui->labelMultas->setVisible(true);
            ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
            SonidoVictoria -> play();
            Nivel++;
        }
    }
    if(niv==4){
        if ((multaa > 4) || (puntaje < 150)) {
            log->setText("Jugador perdio al nivel 4.");
            ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
            ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
            ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
            ui->labelMultas->setVisible(false);
            ui->Boton_SiguienteDia->setVisible(false);
            SonidoGameOver -> play();
        } else {//en caso de que se siga el juego se muestra lo siguiente
            log->setText("Jugador gano el nivel 4.");
            ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
            ui->Boton_ReiniciarNivel->setVisible(false);
            ui->labelPuntos->setText(QString("Puntos: %1").arg(puntaje));//se muestran los puntos (arg es paraa mostrar los puntos
            ui->labelPuntos->setVisible(true);//se abre el label de puntos
            ui->labelMultas->setText(QString("Multas: %1").arg(multaa));//lo mismo para multas
            ui->labelMultas->setVisible(true);
            ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
            SonidoVictoria -> play();
            Nivel++;
        }
    }


    mostrarNivel();//prueba
    // Mostramos la pantalla de puntuacion
    multa.reiniciar();
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
    //Persona.pensamientos();
    if (Nivel >= 2){
        Persona.generarResidencia();
        Persona.generarProposito();
        if (Nivel >= 3){
            Persona.generarCompania();
            if (Nivel == 4){
                Persona.generarPesoMaleta();
                if (Persona.getPersonaVisa() == "Trabajo" || Persona.getPersonaVisa() == "diplomatico"){
                    Persona.generarOcupacion();
                }
            }
        }
    }


    /*Persona.generarResidencia();
    Persona.generarProposito();
    Persona.generarPesoMaleta();  //sacara esto despues
    Persona.generarCompania();
    Persona.generarOcupacion();*/

    mostrarNivel();

    ui->aceptar->setEnabled(true);
    ui->denegar->setEnabled(true);
    ui->papeles->setEnabled(true);
    ui->mostrar_req->setEnabled(true);
    ui->Siguiente_NPC->setDisabled(true);

    SalirNPC();
}

void gameplay::mostrarDocumentos()
{
    log->setText("Jugador solcito ver los documentos.");
    SonidoPapel->play();
    ui->papeles->setDisabled(true);
    ui->documento->show();
    ui->visa->show();
    ui->cerrar->show();
    if (Nivel >= 2){ui->proposito->show();}
    //ui->proposito->show(); //sacar
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
    if (Nivel == 4){actualizarMaleta();}
    if (Persona.getBoolComp() && Nivel >= 3){actualizarCompania();}
    ui->datos->show();
    ui->visaD->hide();
    ui->ocupacion->hide();
    ui->residencia->hide();
}


void gameplay::actualizarLabelVisa()
{

    QString datosMostrarVisa = QString("Tipo de visa\n%1\n\nDuracion de la estancia\n%2\n\n Estado civil\n%3\n\n\n\n\n\n")
                                .arg(Persona.getPersonaVisa())
                                .arg(Persona.obtenerEstancia())
                                .arg(Persona.getPersonaEstCivil());

    ui->visaD->setText(datosMostrarVisa);
    if (Nivel == 4){if (Persona.getPersonaVisa() == "Trabajo" || Persona.getPersonaVisa() == "diplomatico"){actualizarOcupacion();}}

    ui->datos->hide();
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->residencia->hide();
    ui->visaD->show();
}
void gameplay::actualizarResidencia(){
    QString resi = QString("\nPais de residencia\n%1\n-----------------------\nProposito del viaje\n%2")
                            .arg(Persona.getResidencia())
                            .arg(Persona.getProposito());

    ui->residencia->setText(resi);
    ui->residencia->show();
    ui->datos->hide();
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->visaD->hide();
    ui->ocupacion->hide();
}


void gameplay::actualizarCompania(){
    QString copm = QString("  Autorizacion de\n  %1 %2\n\n  Acompaniantes: %3")
                            .arg(Persona.obtenerNombre())
                            .arg(Persona.obtenerApellido())
                            .arg(Persona.getCompania());

    ui->compania->setText(copm);
    ui->compania->show();
}

void gameplay::actualizarMaleta(){
    QString datosMaletas = QString("Tipo de equipaje\n%1\n\nPeso: %2kg\n")
    .arg(Persona.getTipoMaleta())
        .arg(Persona.getMaleta());

    ui->MaletaPeso->setText(datosMaletas);
    ui->MaletaPeso->show();
}

void gameplay::actualizarOcupacion(){
    QString ocupa = QString("%1 %2\n\nOcupacion\n%3")
                            .arg(Persona.obtenerNombre())
                            .arg(Persona.obtenerApellido())
                            .arg(Persona.getOcupacion());

    ui->ocupacion->setText(ocupa);
    ui->ocupacion->show();
}

void gameplay::mostrarNivel(){
    QString niv = QString("   Nivel %1")
                      .arg(Nivel);
    ui->nivel->setText(niv);
    ui->nivel->show();
}

void gameplay::cerrarDocumentos()
{
    log->setText("Jugador acepto la persona.");
    ui->papeles->setEnabled(true);

    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->documento->hide();
    ui->visaD->hide();
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->ocupacion->hide();
    ui->proposito->hide();
    ui->residencia->hide();

}





//aca se determina si la decision del jugador esta bien o no dependiendo de lo que elija
void gameplay::siPasa()
{
    log->setText("Jugador acepto la persona.");
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

    if(Nivel>=2){
        Puntos.fallo_nivel_2(Persona.getResidencia(),Persona.obtenerNacionalidad(),Persona.obtenerNpc(),Persona.getProposito());
    }
    if((Nivel>=3) && (Persona.getBoolComp())){
        Puntos.fallo_nivel_3(Persona.getCompania(),Persona.obtenerNpc(),Persona.obtenerNacionalidad());
    }
    if(Nivel>=4){
        Puntos.fallo_nivel_4(Persona.getMaleta(),Persona.getTipoMaleta(),Persona.getOcupacion(),Persona.obtenerNpc(),Persona.getResidencia());
    }

    ui->documento->hide();
    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->visaD->hide();
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->ocupacion->hide();
    ui->proposito->hide();
    ui->residencia->hide();

    ui->aceptar->setDisabled(true);
    ui->denegar->setDisabled(true);
    ui->papeles->setDisabled(true);
    ui->mostrar_req->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
}


void gameplay::noPasa()
{
    log->setText("Jugador rechazo la persona.");
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

    /*if(Nivel>=2){
        Puntos.fallo_nivel_2(Persona.getResidencia(),Persona.obtenerNacionalidad(),Persona.obtenerNpc(),Persona.getProposito());
    }
    if((Nivel>=3) && (Persona.getBoolComp())){
        Puntos.fallo_nivel_3(Persona.getCompania(),Persona.obtenerNpc(),Persona.obtenerNacionalidad());
    }
    if(Nivel>=4){
        Puntos.fallo_nivel_4(Persona.getMaleta(),Persona.getTipoMaleta(),Persona.getOcupacion(),Persona.obtenerNpc(),Persona.getResidencia());
    }*/

    ui->documento->hide();
    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->visaD->hide();
    ui->MaletaPeso->hide();
    ui->compania->hide();
    ui->ocupacion->hide();
    ui->proposito->hide();
    ui->residencia->hide();

    ui->aceptar->setDisabled(true);
    ui->denegar->setDisabled(true);
    ui->papeles->setDisabled(true);
    ui->mostrar_req->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
}

void gameplay::iniciarReloj() //funcion de inicio del reloj
{
    tiempoActual = tiempoInicio;
    Reloj.start(1000); // Emitir la señal timeout cada 1 segundor
}

void gameplay::ReiniciarNivel()
{
    log->setText("Jugador perdio el nivel y reinicio.");

    emit clickedReiniciar();
    ui->stackedWidget->setCurrentWidget(ui->game);
    iniciarMusicaGameplay();
    EntrarNPC();
    ui->aceptar->show();
    ui->denegar->show();
    ui->mostrar_req->show();
    ui->papeles->show();
    iniciarReloj();
    ui->timer->show();

    ui->Siguiente_NPC->show();

    mostrarNivel();


    ui->botonFinalizarTurno->hide();
}

void gameplay::CondicionesNivel()
{
    log->setText("Jugador solicito las condiciones.");
    emit clickedCondiciones();
    ui->stackedWidget->setCurrentWidget(ui->game_3);
    if (Nivel >= 2){
        ui->regNiv1->show();
    } //bottonnnnnnn
}

void gameplay::botonReglas1(){
    log->setText("Jugador cambio a la segunda pagina.");
    ui->stackedWidget->setCurrentWidget(ui->pantalla_reglas);
    ui->nivel2_reglas_2->show();
    if(Nivel>=3){
        ui->nivel3_reglas_2->show();
    }
    if(Nivel>=4){
        ui->nivel4->show();
    }
}
void gameplay::botonReglas2(){
    log->setText("Jugador cambio a la primer pagina.");
    ui->stackedWidget->setCurrentWidget(ui->game_3);
}

void gameplay::VolverMesa()
{
    log->setText("Jugador volvio a la mesa.");
    ui->stackedWidget->setCurrentWidget(ui->game);
    emit clickedVolverMesa();
}

void gameplay::ComenzarSiguienteDia()
{
    log->setText("Jugador Paso al siguiente nivel.");
    ui->stackedWidget->setCurrentWidget(ui->game);
    iniciarMusicaGameplay();
    iniciarReloj();
    EntrarNPC();
    emit clickedSiguienteDia();
    ui->aceptar->show();
    ui->denegar->show();
    ui->mostrar_req->show();
    ui->papeles->show();
    ui->SLOT1->hide();
    ui->SLOT2->hide();
    ui->SLOT3->hide();
    ui->mensajePG->hide();
    ui->mensajePG->hide();
    ui->guardarPartida->show();
    ui->volverAlMenu->show();
    ui->timer->show();
    ui->mostrar_req->setDisabled(false);
    ui->papeles->setDisabled(false);
    ui->aceptar->setDisabled(false);
    ui->denegar->setDisabled(false);
    ui->Siguiente_NPC->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
    ui->Siguiente_NPC->show();

    qDebug()<<Nivel;

    ui->botonFinalizarTurno->hide();
}

void gameplay::actualizarReloj()
{
    tiempoActual = tiempoActual.addSecs(300);

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
        ui->MaletaPeso->hide();
        ui->compania->hide();
        ui->ocupacion->hide();
        ui->proposito->hide();
        ui->residencia->hide();

        ui->nivel->hide();


        ui->visa->hide();
        ui->visaD->hide();

        ui->botonFinalizarTurno->show();

        return;
    }

    ui->timer->setText(tiempoActual.toString("  hh:mm:ss"));
}

void gameplay::preguntar()
{
    QString per = Persona.obtenerPensamientos();
}


void gameplay::MostrarCondiciones(){
    log->setText("Jugador solicito las condiciones.");
    ui->RNacionalidad->setText(condicion.obtenerNacionalidad());
    ui->REstancia->setText(condicion.obtenerEstancia());
    ui->REstCivil->setText(condicion.obtenerEstCivil());
    ui->RFecha->setText(condicion.obtenerFecha());
    ui->RTipoVisita->setText(condicion.obtenerTipoVisita());
}

void gameplay::on_volverAlMenu_clicked()
{
     log->setText("Jugador pulso el boton de volver.");
    ui->stackedWidget->setCurrentWidget(ui->game);
    ui->aceptar->show();
    ui->denegar->show();
    ui->mostrar_req->show();
    ui->papeles->show();

    ui->timer->show();

    ui->Siguiente_NPC->show();




    ui->botonFinalizarTurno->hide();
}

