#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay)
{
    ui->setupUi(this);
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

