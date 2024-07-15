#include "mariano.h"
#include "ui_mariano.h"

Mariano::Mariano(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mariano)
{
    ui->setupUi(this);
}

Mariano::~Mariano()
{
    delete ui;
}
