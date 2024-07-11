#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStackedWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget;
    setCentralWidget(stackedWidget);

    menuPage = new Menu();
    page_2 = menuPage->findChild<QWidget*>("page_2");

    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(page_2);  // Añade page_2 al stackedWidget

    connect(menuPage->getBotonJugar(), &QPushButton::clicked, this, &MainWindow::CambiarPagina);
    connect(menuPage->getBotonAtras(), &QPushButton::clicked, this, &MainWindow::Volver);

    stackedWidget->setCurrentWidget(menuPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CambiarPagina()
{
    stackedWidget->setCurrentWidget(page_2);
}

void MainWindow::Volver(){
    stackedWidget->setCurrentWidget(menuPage);
}

