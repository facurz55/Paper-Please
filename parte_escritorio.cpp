#include "parte_escritorio.h"
#include "ui_parte_escritorio.h"

parte_escritorio::parte_escritorio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::parte_escritorio)
{
    ui->setupUi(this);
}

parte_escritorio::~parte_escritorio()
{
    delete ui;
}
