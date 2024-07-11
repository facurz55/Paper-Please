#include "ventana_mariano.h"
#include "./ui_ventana_Mariano.h"
#include "persona.h"

ventana_Mariano::ventana_Mariano(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ventana_Mariano)
{
    ui->setupUi(this);
    ui->label->hide();
    ui->pasa->hide();
    ui->nopasa->hide();
    ui->tabienono->hide();



    tiempoInicio = QTime(13, 0);
    horaFin = QTime(22, 0);
    iniciarCronometro();

    connect(ui->pushButton_2, &QPushButton::clicked, this, &ventana_Mariano::actualizarLabelConPersona);
    connect(ui->pasa, SIGNAL(clicked()), this, SLOT(siPasa()));
    connect(ui->nopasa, SIGNAL(clicked()), this, SLOT(noPasa()));
}

ventana_Mariano::~ventana_Mariano()
{
    delete ui;
}


void ventana_Mariano::actualizarLabelConPersona()
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
    ui->label->show();
    ui->tabienono->hide();
    ui->pasa->show();
    ui->nopasa->show();
    ui->pasa->setEnabled(true);
    ui->nopasa->setEnabled(true);
    ui->pushButton_2->setDisabled(true);
}

void ventana_Mariano::siPasa()
{
    int p1 = Persona.obtenerPop();
    if (p1 == 1)
    {
        ui->tabienono->setText("re mal loco");
    }
    else
    {
        ui->tabienono->setText("de diez mi loco");
    }
    Persona.retPop();
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
        ui->tabienono->setText("re mal loco");
    }
    else
    {
        ui->tabienono->setText("de diez mi loco");
    }
    Persona.retPop();
    ui->label->hide();
    ui->tabienono->show();
    ui->pasa->setDisabled(true);
    ui->nopasa->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
}

void ventana_Mariano::eventoCerrar(QCloseEvent *event)
{
    emit seCerro();
}

void ventana_Mariano::iniciarCronometro()
{
    // Iniciar el QTimer para actualizar el cronómetro
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

void ventana_Mariano::actualizarCronometro()
{
    tiempoActual = tiempoActual.addSecs(600);

    // Verificar si ha llegado a la hora de fin
    if (tiempoActual >= horaFin)
    {
        detenerCronometro();
        ui->time->setText("00:00:00");
        return;
    }

    // Mostrar el tiempo transcurrido formateado en el label
    ui->time->setText(tiempoActual.toString("hh:mm:ss"));
}
