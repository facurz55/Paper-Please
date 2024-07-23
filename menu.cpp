#include "menu.h"
#include "ui_menu.h"
#include "puntos.h"

#include <QVBoxLayout>
Menu::Menu(QWidget *parent)
    : QWidget(parent) ,Puntos(0)
    , ui(new Ui::Menu)

{
    puntos2 = new puntos();
    ui->setupUi(this);
    // Ocultar el botón Siguiente al inicio
    ui->BotonContinuar->setVisible(false);

    connect(ui->BotonBaja, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadBaja);
    connect(ui->BotonSalir, &QPushButton::clicked,this,&Menu::Exit);
}

Menu::~Menu()
{
    delete ui;
}


QPushButton* Menu::getBotonJugar() {//esto es para llamar en el qstaked
    return ui->BotonJugar;
}

QPushButton* Menu::getBotonAtras() {//esto es para llamr en el qstaked
    return ui->BotonAtras;
}

void Menu::DificultadBaja(){//Aca tiene que ir el codigo de cada dificultad
//puntos=100
    puntos2->puntuacion_asignada1();//asigna los puntos
ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadMedia(){//Aca tiene que ir el codigo de cada dificultad
//puntos=50
    puntos2->puntuacion2_asignada2();//asigna los puntos
ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadAlta(){//Aca tiene que ir el codigo de cada dificultad
//puntos=0;
    puntos2->puntuacion3_asignada3();//asigna los puntos
ui->BotonContinuar->setVisible(true);
}

void Menu::Exit(){//Cierra la aplicacion
    QApplication::quit();
}

void Menu::Continuar(){//Boton para comenzar el juego(debe irse a la pantalla del juego)


}

QPushButton* Menu::getBotonContinuar(){
    return ui->BotonContinuar;
}
