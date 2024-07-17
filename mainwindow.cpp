#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStackedWidget>

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
    game_2 = game->findChild<QWidget*>("game_2");

    stackedWidget->addWidget(menuPage); //añade la ventana del menu
    stackedWidget->addWidget(page_2);  // Añade page_2 al stackedWidget
    stackedWidget->addWidget(game); //añade la ventana donde jugamos
    stackedWidget->addWidget(game_2);

    connect(menuPage->getBotonJugar(), &QPushButton::clicked, this, &MainWindow::CambiarPagina);
    connect(menuPage->getBotonAtras(), &QPushButton::clicked, this, &MainWindow::Volver);
    connect(menuPage->getBotonContinuar(), &QPushButton::clicked, this, &MainWindow::ComenzarJuego);
    connect(game->getBotonSiguiente_NPC(), &QPushButton::clicked, this, &MainWindow::SalirNPC);
    connect(game->getBotonSiguienteDia(), &QPushButton::clicked, this, &MainWindow::ComenzarSiguieneDia);
    connect(game->getReiniciarDia(), &QPushButton::clicked, this, &MainWindow::ReinciarElNivel);
    connect(game->getFinalizarTurno(), &QPushButton::clicked, this, &MainWindow::PantallaPuntos);


    stackedWidget->setCurrentWidget(menuPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ComenzarSiguieneDia(){//<----------------------ACA SE COMIENZA EL SIGUEINTE DIA.
    stackedWidget->setCurrentWidget(game);
    EntradaNPC();
}

void MainWindow::ReinciarElNivel(){//<----------------------ACA SE REINCIA EL NIVEL
    stackedWidget->setCurrentWidget(game);
    EntradaNPC();
}

void MainWindow::PantallaPuntos(){//<----------------------ACA SE INCIA LA PANTALLA PUNTOS CUANDO SE PRESIONA EL BOTON FINALIZAR TURNO
    stackedWidget->setCurrentWidget(game_2);
}

void MainWindow::CambiarPagina()
{
    stackedWidget->setCurrentWidget(page_2);
}

void MainWindow::Volver(){
    stackedWidget->setCurrentWidget(menuPage);
}

void MainWindow::ComenzarJuego() {

    // Cambia el widget actual del stackedWidget al widget del juego (game)
    stackedWidget->setCurrentWidget(game);

    EntradaNPC();
}

void MainWindow::EntradaNPC(){
    game->EntrarNPC();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // Llama al método resizeEvent de la clase base (QMainWindow)
    QMainWindow::resizeEvent(event);

    // Verifica si el widget actual del stackedWidget es la ventana del juego
    if (stackedWidget->currentWidget() == game) {
        // Obtiene el puntero al QLabel que contiene la imagen del NPC
        QLabel *labelNPC = game->getLabelNPC();

        // Calcula la coordenada X central para el labelNPC
        int centerX = (game->width() - labelNPC->width()) / 2;

        // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
        int centerY = (game->height() - labelNPC->height()) / 2 - 35;

        // Obtiene el rectángulo de geometría actual del labelNPC
        QRect currentRect = labelNPC->geometry();

        // Crea un nuevo rectángulo con la posición central calculada y el tamaño actual del labelNPC
        QRect newRect(centerX, centerY, currentRect.width(), currentRect.height());

        // Establece la nueva geometría del labelNPC con el rectángulo calculado
        labelNPC->setGeometry(newRect);
    }
}

void MainWindow::SalirNPC() {
    game->SalirNPC();

    // Conecta la señal finished() de la animación para reiniciar ComenzarJuego
    connect(game, &gameplay::SalioElNPC, this, &MainWindow::EntradaNPC);
}
