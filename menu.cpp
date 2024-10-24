#include "menu.h"
#include "ui_menu.h"
#include <QVBoxLayout>
#include "guardarpartida/guardarpartida.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu), slot(0)

{
    Puntos = 0;
    ui->setupUi(this);

    guardarpartida Guardar;

    //WIDGETS
    ui->BotonContinuar->setVisible(false);

    ui->botonContinua->hide();

    // Conexiones pantalla principal
    // Locura rareza dijo facu
    connect(ui->BotonJugar, &QPushButton::clicked, this, &Menu::SeleccionarDif);
    connect(ui->BotonAtras, &QPushButton::clicked, this, &Menu::MenuPrincipal);
    connect(ui->BotonContinuar, &QPushButton::clicked, this, &Menu::clickeoJugar);
    connect(ui->BotonBaja, &QPushButton::clicked,this, &Menu::DificultadBaja);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonSalir, &QPushButton::clicked,this,&Menu::Exit);
    connect(ui->BotonCargarPartida,&QPushButton::clicked,this,&Menu::clikeoCargarPartida);
    connect(ui->atrasMenu, &QPushButton::clicked, this, &Menu::MenuPrincipal);
    connect(ui->Slot1, &QPushButton::clicked, this, &Menu::clikeoBotonSlot);
    connect(ui->Slot2, &QPushButton::clicked, this, &Menu::clikeoBotonSlot);
    connect(ui->Slot3, &QPushButton::clicked, this, &Menu::clikeoBotonSlot);
    connect(ui->botonContinua, &QPushButton::clicked, this, &Menu::clickeoJugar);


    ui->MenuStacked->setCurrentIndex(0);
}

void Menu::guardarPartida(DatosJugador datos)
{
    guardar.guardar(datos, slot);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::textoUser(char newChar){
    ui->Slot1->setText(QString::fromUtf8(&newChar, 1));
}

void Menu::clickeoJugar()
{
    emit clickedJugar(Puntos);
    ui->BotonContinuar->setVisible(false);
}

void Menu::clikeoCargarPartida()
{
    ui->MenuStacked->setCurrentIndex(2);
}

void Menu::clikeoBotonSlot()
{
    ui->botonContinua->show();
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
    ui->botonContinua->hide();
}
