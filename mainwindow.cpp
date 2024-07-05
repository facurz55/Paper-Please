#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarLabelConPersona(const Persona &persona)
{
    QString datosPersona = QString("Genero: %1\nNombre: %2\nApellido: %3\nFecha de Nacimiento: %4\nNacionalidad: %5\nTipo de Visa: %6\nEstado Civil: %7")
        .arg(persona.obtenerGenero())
        .arg(persona.obtenerNombre())
        .arg(persona.obtenerApellido())
        .arg(persona.obtenerFecha())
        .arg(persona.obtenerNacionalidad())
        .arg(persona.getPersonaVisa())
        .arg(persona.getPersonaEstCivil());
    //                                      <---- Aca pone lo que te di como ejemplo en ds Thiago.
    //Los marcadores %1, %2, %3, etc., son marcadores de posición utilizados en una cadena QString en Qt.
    //Estos marcadores se reemplazan por valores específicos cuando llamas al método arg().


    ui->label->setText(datosPersona); // Asegurarse de tener un QLabel llamado 'label' en el diseño.
}
