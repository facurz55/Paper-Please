#include "menu.h"
#include "ui_menu.h"

#include <QVBoxLayout>
Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)

{
    Puntos = 0;
    ui->setupUi(this);

    //WIDGETS
    ui->BotonContinuar->setVisible(false);

    // Conexiones pantalla principal
    // Locura rareza dijo facu
    connect(ui->BotonJugar, &QPushButton::clicked, this, &Menu::SeleccionarDif);
    connect(ui->BotonAtras, &QPushButton::clicked, this, &Menu::MenuPrincipal);

    // Conectamos el boton de jugar:
    connect(ui->BotonContinuar, &QPushButton::clicked, this, &Menu::clickeoJugar);

    //CONEXIONES
    connect(ui->BotonBaja, &QPushButton::clicked,this, &Menu::DificultadBaja);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonSalir, &QPushButton::clicked,this,&Menu::Exit);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::clickeoJugar()
{
    emit clickedJugar(Puntos);
}

void Menu::DificultadBaja(){//Aca tiene que ir el codigo de cada dificultad
//puntos=100
    Puntos = 0;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadMedia(){//Aca tiene que ir el codigo de cada dificultad
//puntos=50
    Puntos = 1;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadAlta(){//Aca tiene que ir el codigo de cada dificultad
//puntos=0;
    Puntos = 2;
    ui->BotonContinuar->setVisible(true);
}

void Menu::Exit(){//Cierra la aplicacion
    QApplication::quit();
}

void Menu::SeleccionarDif()
{
    ui->MenuStacked->setCurrentIndex(1);
}

void Menu::MenuPrincipal()
{
    ui->MenuStacked->setCurrentIndex(0);
}
