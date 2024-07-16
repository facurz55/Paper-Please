#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStackedWidget>
=======
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
    connect(game->getBotonSiguiente_NPC(), &QPushButton::clicked, this, &MainWindow::SalirNPC);


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

void MainWindow::ComenzarJuego() {

    // Cambia el widget actual del stackedWidget al widget del juego (game)
    stackedWidget->setCurrentWidget(game);

    EntradaNPC();
}

void MainWindow::EntradaNPC(){

    // Obtiene el puntero al QLabel que contiene la imagen del NPC en el juego
    QLabel *labelNPC = game->getLabelNPC();

    // Crea una animación de propiedad para el QLabel, animando su geometría
    QPropertyAnimation *animation = new QPropertyAnimation(labelNPC, "geometry");

    // Calcula la coordenada X central para el labelNPC
    int centerX = (game->width() - labelNPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (game->height() - labelNPC->height()) / 2 - 35;

    // Define el rectángulo inicial fuera de la vista a la izquierda
    QRect startRect(-labelNPC->width(), centerY, labelNPC->width(), labelNPC->height());

    // Define el rectángulo final centrado en la ventana del juego
    QRect endRect(centerX, centerY, labelNPC->width(), labelNPC->height());

    // Establece la duración de la animación en milisegundos
    animation->setDuration(1000);

    // Establece el valor inicial de la animación (posición inicial del labelNPC)
    animation->setStartValue(startRect);

    // Establece el valor final de la animación (posición final del labelNPC)
    animation->setEndValue(endRect);

    // Establece la curva de animación para que sea suave y desacelerada al final
    animation->setEasingCurve(QEasingCurve::OutExpo);

    // Inicia la animación y la configura para eliminarse automáticamente cuando se detenga
    animation->start(QPropertyAnimation::DeleteWhenStopped);
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
    // Obtiene el puntero al QLabel que contiene la imagen del NPC en el juego
    QLabel *labelNPC = game->getLabelNPC();

    // Crea una animación de propiedad para el QLabel, animando su geometría
    QPropertyAnimation *animation = new QPropertyAnimation(labelNPC, "geometry");

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (game->height() - labelNPC->height()) / 2 - 35;

    // Calcula la coordenada X para que el labelNPC salga completamente de la vista a la derecha
    int endX = game->width();

    // Obtiene el rectángulo de geometría actual del labelNPC (posición actual del NPC)
    QRect startRect = labelNPC->geometry();

    // Define el rectángulo final fuera de la vista a la derecha, manteniendo la altura y ancho del labelNPC
    QRect endRect(endX, centerY, labelNPC->width(), labelNPC->height());

    // Establece la duración de la animación en milisegundos
    animation->setDuration(1000);

    // Establece el valor inicial de la animación (posición actual del labelNPC)
    animation->setStartValue(startRect);

    // Establece el valor final de la animación (rectángulo fuera de la vista a la derecha)
    animation->setEndValue(endRect);

    // Establece la curva de animación para que sea suave al inicio y desacelerada al final
    animation->setEasingCurve(QEasingCurve::InExpo);

    // Inicia la animación y la configura para eliminarse automáticamente cuando se detenga
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    // Conecta la señal finished() de la animación para reiniciar ComenzarJuego
    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::EntradaNPC);
}

