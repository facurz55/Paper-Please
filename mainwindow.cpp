#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget;
    setCentralWidget(stackedWidget);

    menuPage = new Menu();
    game = new gameplay();
    page_2 = menuPage->findChild<QWidget*>("page_2");

    stackedWidget->addWidget(menuPage); //añade la ventana del menu
    stackedWidget->addWidget(page_2);  // Añade page_2 al stackedWidget
    stackedWidget->addWidget(game); //añade la ventana donde jugamos

    connect(menuPage->getBotonJugar(), &QPushButton::clicked, this, &MainWindow::CambiarPagina);
    connect(menuPage->getBotonAtras(), &QPushButton::clicked, this, &MainWindow::Volver);
    connect(menuPage->getBotonContinuar(), &QPushButton::clicked, this, &MainWindow::ComenzarJuego);

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

void MainWindow::ComenzarJuego(){
    stackedWidget->setCurrentWidget(game);
}
