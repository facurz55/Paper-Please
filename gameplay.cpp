#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay)
{
    ui->setupUi(this);

    ui->pasarDia->hide();
    ui->documento->hide();
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
    connect(ui->aceptar, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->denegar, SIGNAL(clicked()), this, SLOT(noPasa()));
    connect(ui->cerrar, SIGNAL(clicked()), this, SLOT(cerrarDatos()));
    connect(ui->Siguiente_NPC, SIGNAL(clicked()), this, SLOT(vivaPeron()));
    connect(ui->papeles, SIGNAL(clicked()), this, SLOT(mostrarD()));
    //connect(ui->pasarDia, SIGNAL(clicked()), this, SLOT(pasarDia()));
    //connect(ui->pensar, SIGNAL(clicked()), SLOT(preguntar()));

}

gameplay::~gameplay()
{
    delete ui;
}

QLabel* gameplay::getLabelNPC(){
    return ui->Label_NPC;
}

QPushButton* gameplay::getBotonSiguiente_NPC(){
    return ui->Siguiente_NPC;
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
    ui->documento->show();
}



void gameplay::actualizarLabelConPersona() //esta funcion muestra los datos cuando se presiona un boton
{


    QString datosPersona = QString("Genero: %1\nNombre: %2\nApellido: %3\nFecha de Nacimiento: %4\nNacionalidad: %5\nTipo de Visa: %6\nDuracion de la estancis: %7\nEstado Civil: %8")
                               .arg(Persona.obtenerGenero())
                               .arg(Persona.obtenerNombre())
                               .arg(Persona.obtenerApellido())
                               .arg(Persona.obtenerFecha())
                               .arg(Persona.obtenerNacionalidad())
                               .arg(Persona.getPersonaVisa())
                               .arg(Persona.obtenerEstancia())
                               .arg(Persona.getPersonaEstCivil());
    //                                      <---- Aca pone lo que te di como ejemplo en ds Thiago.
    //Los marcadores %1, %2, %3, etc., son marcadores de posición utilizados en una cadena QString en Qt.
    //Estos marcadores se reemplazan por valores específicos cuando llamas al método arg().


    ui->datos->setText(datosPersona); // Asegurarse de tener un QLabel llamado 'label' en el diseño.

    //manejo de labels y botones
    ui->datos->show();
    ui->cerrar->show();
    ui->documento->hide();
}

void gameplay::cerrarDatos()
{
    ui->datos->hide();
    ui->cerrar->hide();
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
        ui->pasarDia->show();
        ui->aceptar->hide();
        ui->denegar->hide();
        ui->mostrar_req->hide();
        ui->papeles->hide();
        ui->documento->hide();
        ui->timer->hide();
        ui->datos->hide();
        ui->Siguiente_NPC->hide();
        ui->cerrar->hide();
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
