#include "menu.h"
#include "ui_menu.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QAudioDevice>
#include "guardarpartida/guardarpartida.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu), slot(0)

{
    Puntos = 0;
    ui->setupUi(this);

    guardarpartida Guardar;

    //WIDGETS
    ui->BotonContinuar->setVisible(false);

    // Inicializa el reproductor de música
    backgroundMusic = new QMediaPlayer(this);

    // Inicializa QAudioOutput para controlar el volumen
    audioOutput = new QAudioOutput(this);
    backgroundMusic->setAudioOutput(audioOutput);  // Asigna el audio output al reproductor

    // Establece el archivo de música
    backgroundMusic->setSource(QUrl("qrc:/counter16.wav"));

    // Configura el volumen a través de QAudioOutput
    audioOutput->setVolume(0.1);  // Volumen en rango de 0.0 a 1.0
    backgroundMusic->setLoops(QMediaPlayer::Infinite); // Hacer que la música loopee
    // Reproduce la música
    backgroundMusic->play();

    // Conexiones pantalla principal
    // Locura rareza dijo facu
    connect(ui->BotonJugar, &QPushButton::clicked, this, &Menu::SeleccionarDif);
    connect(ui->BotonAtras, &QPushButton::clicked, this, &Menu::MenuPrincipal);

    // Conectamos el boton de jugar:
    connect(ui->BotonContinuar, &QPushButton::clicked, this, &Menu::clickeoJugar);

    //CONEXIONES
    connect(ui->BotonBaja, &QPushButton::clicked,this, &Menu::DificultadBaja);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonSalir, &QPushButton::clicked,this,&Menu::Exit);

    ui->MenuStacked->setCurrentIndex(0);
}

void Menu::guardarPartida(DatosJugador datos)
{
    guardar.guardar(datos, slot);
}

Menu::~Menu()
{
    delete ui;
}

// Método para detener la música
void Menu::stopMusic()
{
    backgroundMusic->stop(); // Detener la música
}

void Menu::clickeoJugar()
{
    stopMusic(); // Detener la música al jugar
    emit clickedJugar(Puntos);
}

void Menu::DificultadBaja(){//Aca tiene que ir el codigo de cada dificultad
//puntos=100
    Puntos = 0;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadMedia(){//Aca tiene que ir el codigo de cada dificultad
//puntos=50
    Puntos = 1;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadAlta(){//Aca tiene que ir el codigo de cada dificultad
//puntos=0;
    Puntos = 2;
    ui->BotonContinuar->setVisible(true);
}

void Menu::Exit(){//Cierra la aplicacion
    QApplication::quit();
}

void Menu::SeleccionarDif()
{
    ui->MenuStacked->setCurrentIndex(1);
}

void Menu::MenuPrincipal()
{
    ui->MenuStacked->setCurrentIndex(0);
}
