#include "menu.h"
#include "ui_menu.h"
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
    Puntos=100;
// ui->scoreLabel->setText("Puntuación: " + QString::number(Puntos));
}
void Menu::DificultadMedia(){
    Puntos=50;
// ui->scoreLabel->setText("Puntuación: " + QString::number(Puntos));
}
void Menu::DificultadAlta(){
    Puntos=0;
// ui->scoreLabel->setText("Puntuación: " + QString::number(Puntos));
}
