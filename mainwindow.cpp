#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget;
    setCentralWidget(stackedWidget);

    menuPage= new Menu();

    stackedWidget->addWidget(menuPage);
    stackedWidget->setCurrentWidget(menuPage);

    MostrarVentanas();  // Llama a la función para configurar el QStackedWidget
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: MostrarVentanas(){

}

