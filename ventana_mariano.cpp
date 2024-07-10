#include "ventana_mariano.h"
#include "./ui_ventana_Mariano.h"
#include "persona.h"

ventana_Mariano::ventana_Mariano(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ventana_Mariano)
{
    ui->setupUi(this);
    ui->pasa->hide();
    ui->nopasa->hide();
    ui->tabienono->hide();
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

    QString datosPersona = QString("Genero: %1\nNombre: %2\nApellido: %3\nFecha de Nacimiento: %4\nNacionalidad: %5\nTipo de Visa: %6\nEstado Civil: %7")
                               .arg(Persona.obtenerGenero())
                               .arg(Persona.obtenerNombre())
                               .arg(Persona.obtenerApellido())
                               .arg(Persona.obtenerFecha())
                               .arg(Persona.obtenerNacionalidad())
                               .arg(Persona.getPersonaVisa())
                               .arg(Persona.getPersonaEstCivil());
    //                                      <---- Aca pone lo que te di como ejemplo en ds Thiago.
    //Los marcadores %1, %2, %3, etc., son marcadores de posición utilizados en una cadena QString en Qt.
    //Estos marcadores se reemplazan por valores específicos cuando llamas al método arg().


    ui->label->setText(datosPersona); // Asegurarse de tener un QLabel llamado 'label' en el diseño.
    ui->pasa->show();
    ui->nopasa->show();
    ui->tabienono->show();
    ui->pasa->setEnabled(true);
    ui->nopasa->setEnabled(true);
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
    ui->pasa->setDisabled(true);
    ui->nopasa->setDisabled(true);
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
    ui->pasa->setDisabled(true);
    ui->nopasa->setDisabled(true);
}
