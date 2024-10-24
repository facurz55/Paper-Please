#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //STACKEDWIDGET
    stackedWidget = new QStackedWidget(this);

    setCentralWidget(stackedWidget);
    menuPage = new Menu(this);
    game = new gameplay(this);

    stackedWidget->addWidget(menuPage);     //añade la ventana del menu
    stackedWidget->addWidget(game);         //añade la ventana donde jugamos

    stackedWidget->setCurrentWidget(menuPage);

    //CONEXIONES de botones.
    connect(menuPage, &Menu::clickedJugar, this, &MainWindow::ComenzarJuego);
    connect(game, &gameplay::GuardarDatos, menuPage, &Menu::guardarPartida);
    connect(game, &gameplay::volverAlMenuClicked, this, &MainWindow::volverAlMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Volver(){
    stackedWidget->setCurrentWidget(menuPage);
}

void MainWindow::ComenzarJuego(int Dificultad) {

    // Cambia el widget actual del stackedWidget al widget del juego (game)
    stackedWidget->setCurrentWidget(game);
    game->Empezar(Dificultad);
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

void MainWindow::volverAMenu(){
    stackedWidget->setCurrentWidget(menuPage);
}
void MainWindow::volverAlMenu() {
     stackedWidget->setCurrentWidget(Page);
}
