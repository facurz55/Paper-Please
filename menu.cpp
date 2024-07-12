#include "menu.h"
#include "ui_menu.h"
#include "puntos.cpp"

#include <QVBoxLayout>
Menu::Menu(QWidget *parent)
    : QWidget(parent) ,Puntos(0)
    , ui(new Ui::Menu)

{
    ui->setupUi(this);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadBaja);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::DificultadBaja(){
    //puntos=100
    puntos2.puntuacion_asignada1();//asigna los puntos
}
void Menu::DificultadMedia(){
    //puntos=50
    puntos2.puntuacion2_asignada2();//asigna los puntos
}
void Menu::DificultadAlta(){
    //puntos=0;
    puntos2.puntuacion3_asignada3();//asigna los puntos
}
