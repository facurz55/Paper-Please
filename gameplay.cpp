#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay)
{
    condicion = new condiciones();

    ui->setupUi(this);
    /*ui->Boton_ReiniciarNivel->setVisible(false);
    ui->Boton_SiguienteDia->setVisible(false);
    ui->labelMultas->setVisible(false);
    ui->labelPerdiste->setVisible(false);
    ui->labelPuntos->setVisible(false);*/

    ui->botonFinalizarTurno->hide();
    ui->documento->hide();
    ui->visa->hide();
    ui->visaD->hide();
    ui->cerrar->hide();
    ui->datos->hide();
    ui->Siguiente_NPC->setDisabled(true);
    //ui->aceptar->setDisabled(true);
    //ui->denegar->setDisabled(true);
    //ui->mostrar_req->setDisabled(true);
    //ui->papeles->setDisabled(true);

    //esto se del reloj
    tiempoInicio = QTime(13, 0);  //inicia a las 13
    horaFin = QTime(22, 0);       //termina a las 22
    iniciarCronometro();          //el reloj comienza cuando arranca el programa


    connect(ui->documento, &QPushButton::clicked, this, &gameplay::actualizarLabelConPersona); //boton de generar npc
    connect(ui->visa, SIGNAL(clicked()), this, SLOT(mostrarVisa()));
    connect(ui->aceptar, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->denegar, SIGNAL(clicked()), this, SLOT(noPasa()));
    connect(ui->cerrar, SIGNAL(clicked()), this, SLOT(cerrarDatos()));
    connect(ui->Siguiente_NPC, SIGNAL(clicked()), this, SLOT(vivaPeron()));
    connect(ui->papeles, SIGNAL(clicked()), this, SLOT(mostrarD()));
    //connect(ui->pensar, SIGNAL(clicked()), SLOT(preguntar()));

    // Crea una animación de propiedad para el QLabel, animando su geometría
    animacionEntrada = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacion();

    animacionSalida = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacionSalida();

    connect(animacionSalida, &QAbstractAnimation::finished, this, &gameplay::emitSalioNPC);
    MostrarCondiciones();
}

gameplay::~gameplay()
{
    delete ui;
}


QPushButton* gameplay::getBotonVolver(){
    return ui->BotonVolver;
}

QPushButton* gameplay::getBotonCondiciones(){
    return ui->mostrar_req;
}

//TODA FUNCION QUE EMPIECE CON GET EN ESTA HOJA ES PARA USARLA EN LA CLASE MAINWINDOW
QPushButton* gameplay::getReiniciarDia(){//<-MW
    return ui->Boton_ReiniciarNivel;
}

QPushButton* gameplay::getBotonSiguienteDia(){//<-MW
    return ui->Boton_SiguienteDia;
}

QPushButton* gameplay::getFinalizarTurno(){//<-MW
    return ui->botonFinalizarTurno;
}

QPushButton* gameplay::getBotonSiguiente_NPC(){//<-MW
    return ui->Siguiente_NPC;
}

QLabel *gameplay::getLabelNPC(){//<-MW
    return ui->Label_NPC;
}
//esto hay que verlo en lo del nivel 1 del boton terminar jornada
/*void gameplay::Boton_condiciones() {//esto para verificar si perdiste, en caso que no se muestran los puntos y multas
    if ((multas > 4) || (puntos < 0)) {
        ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
        ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
        ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
        ui->labelMultas->setVisible(false);
        ui->Boton_SiguienteDia->setVisible(false);
    } else {//en caso de que se siga el juego se muestra lo siguiente
        ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
        ui->Boton_ReiniciarNivel->setVisible(false);
        ui->labelPuntos->setText(QString("Puntos: %1").arg(puntos));//se muestran los puntos (arg es paraa mostrar los puntos
        ui->labelPuntos->setVisible(true);//se abre el label de puntos
        ui->labelMultas->setText(QString("Multas: %1").arg(multas));//lo mismo para multas
        ui->labelMultas->setVisible(true);
        ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
    }
}
void gameplay::on_Boton_ReiniciarNivel_clicked() {//ver como configurarlo
    resetear_nivel();
}
void gameplay::on_Boton_SiguienteDia_clicked() {//ver como configurarlo

}
*/

void gameplay::cambiarSkinNPC(){
    condicion1 = Persona.obtenerNpc();

    if(condicion1=="aldeano"){
        ui->Label_NPC->setStyleSheet(ALDEANO);
    }else if(condicion1=="refugiado politico"){
        ui->Label_NPC->setStyleSheet(REFUGIADOPOLITICO);
    }else if(condicion1=="diplomatico"){
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
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 35;

    animacionEntrada->setStartValue(QPoint(-(ui->Label_NPC->width()),centerY));
    animacionEntrada->setEndValue(QPoint(centerX, centerY));

    animacionEntrada->start();
}

void gameplay::SalirNPC()
{
    // Calcula la coordenada X central para el labelNPC
    int centerX = (width() - ui->Label_NPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 35;

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

void gameplay::emitSalioNPC()
{
    emit SalioElNPC();
}






void gameplay::vivaPeron()
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
}

void gameplay::mostrarD()
{
    ui->papeles->setDisabled(true);
    ui->documento->show();
    ui->visa->show();
    ui->cerrar->show();
}

void gameplay::actualizarLabelConPersona() //esta funcion muestra los datos cuando se presiona un boton
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


void gameplay::mostrarVisa()
{

    QString datosMostrarVisa = QString("Tipo de visa\n%1\n\nDuracion de la estancia\n%2\n\n Estado civil\n%3\n\n\n\n\n\n")
                                .arg(Persona.getPersonaVisa())
                                .arg(Persona.obtenerEstancia())
                                .arg(Persona.getPersonaEstCivil());

    ui->visaD->setText(datosMostrarVisa);

    ui->datos->hide();
    ui->visaD->show();
}

void gameplay::cerrarDatos()
{
    ui->papeles->setEnabled(true);

    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();
    ui->documento->hide();
    ui->visaD->hide();
}


//aca se determina si la decision del jugador esta bien o no dependiendo de que eligiera
void gameplay::siPasa()
{
    int p1 = Persona.obtenerPop();
    QString tipo = Persona.obtenerNpc();
    if (p1 == 1)
    {
        //en este caso se debe restar puntos
        puntos.puntaje(tipo);
        ui->informarerror->setText(QString ("Esta mal"));
    }
    else
    {
        //en este caso se deben sumar puntos
        puntos.puntaje2(tipo);
    }
    Persona.retPop();


    //en este caso se debe restar puntos
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
    int p1 = Persona.obtenerPop();
    QString tipo = Persona.obtenerNpc();
    if (p1 == 0)
    {
        //en este caso se debe restar puntos
        puntos.puntaje(tipo);
    }
    else
    {
        //en este caso se deben sumar puntos
        puntos.puntaje2(tipo);
    }
    Persona.retPop();

    //manejo de labels y botones
    ui->documento->hide();
    ui->datos->hide();
    ui->cerrar->hide();
    ui->visa->hide();

    ui->aceptar->setDisabled(true);
    ui->denegar->setDisabled(true);
    ui->papeles->setDisabled(true);
    ui->mostrar_req->setDisabled(true);
    ui->Siguiente_NPC->setEnabled(true);
}


void gameplay::iniciarCronometro() //funcion de inicio del reloj
{
    cronometro = new QTimer(this);
    connect(cronometro, &QTimer::timeout, this, &gameplay::actualizarCronometro);
    cronometro->start(1000); // Emitir la señal timeout cada 1 segundo
    tiempoActual = tiempoInicio;
}

void gameplay::detenerCronometro()
{
    cronometro->stop();
    delete cronometro;
}

//en esta funcion se actualiza el reloj y permite que el mismo avance 10 minutos en 1 segundo (despues lo cambio a 5 min por segundo para que no sea tan rapido)
void gameplay::actualizarCronometro()
{
    tiempoActual = tiempoActual.addSecs(600);

    // Verificar si ha llegado a la hora de fin
    if (tiempoActual >= horaFin)
    {
        detenerCronometro(); //cuando el tiempo se cumlpe detiene el reloj

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


//en esta funcion se debe conectar en cambio de ventana
void gameplay::pasarDia()
{

}

void gameplay::preguntar()
{
    QString per = Persona.obtenerPensamientos();
}


void gameplay::MostrarCondiciones(){
    ui->RNacionalidad->setText(condicion->obtenerNacionalidad());
    ui->REstancia->setText(condicion->obtenerEstancia());
    ui->REstCivil->setText(condicion->obtenerEstCivil());
    ui->RFecha->setText(condicion->obtenerFecha());
    ui->RTipoVisita->setText(condicion->obtenerTipoVisita());
}
