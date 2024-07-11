#include "ventana_mariano.h"
#include "./ui_ventana_Mariano.h"
#include "persona.h"

ventana_Mariano::ventana_Mariano(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ventana_Mariano)
{
    ui->setupUi(this);

    //se esconden labels y botones al iniciar el programa
    ui->label->hide();
    ui->pasa->hide();
    ui->nopasa->hide();
    ui->tabienono->hide();
    ui->pasarDia->hide();

    //esto se del reloj
    tiempoInicio = QTime(13, 0);  //inicia a las 13
    horaFin = QTime(22, 0);       //termina a las 22
    iniciarCronometro();          //el reloj comienza cuando arranca el programa

    connect(ui->pushButton_2, &QPushButton::clicked, this, &ventana_Mariano::actualizarLabelConPersona); //boton de generar npc
    connect(ui->pasa, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->nopasa, SIGNAL(clicked()), this, SLOT(noPasa()));
    connect(ui->pasarDia, SIGNAL(clicked()), SLOT(pasarDia()));
}

ventana_Mariano::~ventana_Mariano()
{
    delete ui;
}


void ventana_Mariano::actualizarLabelConPersona() //esta funcion muestra los datos cuando se presiona un boton
{
    Persona.generarFecha();
    Persona.generarNacionalidad();
    Persona.generarNombres();
    Persona.generarVisa();
    Persona.generar_Estado_civil();
    Persona.generar_Estancia();

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


    ui->label->setText(datosPersona); // Asegurarse de tener un QLabel llamado 'label' en el diseño.

    //manejo de labels y botones
    ui->label->show();
    ui->tabienono->hide();
    ui->pasa->show();
    ui->nopasa->show();
    ui->pasa->setEnabled(true);
    ui->nopasa->setEnabled(true);
    ui->pushButton_2->setDisabled(true);
}



//aca se determina si la decision del jugador esta bien o no dependiendo de que eligiera
void ventana_Mariano::siPasa()
{
    int p1 = Persona.obtenerPop();
    if (p1 == 1)
    {
        ui->tabienono->setText("re mal loco"); //en este caso se debe restar puntos
    }
    else
    {
        ui->tabienono->setText("de diez mi loco"); //en este caso se deben sumar puntos
    }
    Persona.retPop();

    //manejo de labels y botones
    ui->label->hide();
    ui->tabienono->show();
    ui->pasa->setDisabled(true);
    ui->nopasa->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
}

void ventana_Mariano::noPasa()
{
    int p1 = Persona.obtenerPop();
    if (p1 == 0)
    {
        ui->tabienono->setText("re mal loco"); //en este caso se debe restar puntos
    }
    else
    {
        ui->tabienono->setText("de diez mi loco"); //en este caso se deben sumar puntos
    }
    Persona.retPop();

    //manejo de labels y botones
    ui->label->hide();
    ui->tabienono->show();
    ui->pasa->setDisabled(true);
    ui->nopasa->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
}

void ventana_Mariano::eventoCerrar(QCloseEvent *event)
{
    emit seCerro(); //emite una señal cuando la ventana se cierra
}

void ventana_Mariano::iniciarCronometro() //funcion de inicio del reloj
{
    cronometro = new QTimer(this);
    connect(cronometro, &QTimer::timeout, this, &ventana_Mariano::actualizarCronometro);
    cronometro->start(1000); // Emitir la señal timeout cada 1 segundo
    tiempoActual = tiempoInicio;
}

void ventana_Mariano::detenerCronometro()
{
    cronometro->stop();
    delete cronometro;
}

//en esta funcion se actualiza el reloj y permite que el mismo avance 10 minutos en 1 segundo (despues lo cambio a 5 min por segundo para que no sea tan rapido)
void ventana_Mariano::actualizarCronometro()
{
    tiempoActual = tiempoActual.addSecs(600);

    // Verificar si ha llegado a la hora de fin
    if (tiempoActual >= horaFin)
    {
        detenerCronometro(); //cuando el tiempo se cumlpe detiene el reloj

        //cuando el tiempo acaba se muestra el boton de pasar de dia y se ocultan el resto de cosas
        ui->pasarDia->show();
        ui->label->hide();
        ui->nopasa->hide();
        ui->pasa->hide();
        ui->pushButton_2->hide();
        ui->tabienono->hide();
        ui->time->hide();
        return;
    }

    ui->time->setText(tiempoActual.toString("hh:mm:ss"));
}


//en esta funcion se debe conectar en cambio de ventana
void ventana_Mariano::pasarDia()
{

}


