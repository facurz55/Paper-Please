#include "menu.h"
#include "ui_menu.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QAudioDevice>
#include <qdebug.h>
#include "guardarpartida/guardarpartida.h"

Menu::Menu(Logs * logs,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu), slot(-1), log(logs)

{
    Puntos = 0;
    ui->setupUi(this);
    //
    //WIDGETS
    ui->BotonContinuar->setVisible(false);
    ui->botonContinua->hide();

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
    startMusic();


    // Conexiones pantalla principal
    // Locura rareza dijo facu
    connect(ui->BotonJugar, &QPushButton::clicked, this, &Menu::SeleccionarDif);
    connect(ui->BotonAtras, &QPushButton::clicked, this, &Menu::MenuPrincipal);
    connect(ui->BotonContinuar, &QPushButton::clicked, this, &Menu::clickeoJugar);
    connect(ui->BotonBaja, &QPushButton::clicked,this, &Menu::DificultadBaja);
    connect(ui->BotonMedia, &QPushButton::clicked,this, &Menu::DificultadMedia);
    connect(ui->BotonAlta, &QPushButton::clicked,this, &Menu::DificultadAlta);
    connect(ui->BotonSalir, &QPushButton::clicked,this,&Menu::Exit);
    connect(ui->BotonCargarPartida,&QPushButton::clicked,this,&Menu::clikeoCargarPartida);
    connect(ui->atrasMenu, &QPushButton::clicked, this, &Menu::MenuPrincipal);
    connect(ui->Slot1, &QPushButton::clicked, this, [this]() { this->slot = 0; this->clikeoBotonSlot(); this->cargarPartida(slot);});
    connect(ui->Slot2, &QPushButton::clicked, this, [this]() { this->slot = 1; this->clikeoBotonSlot(); this->cargarPartida(slot); });
    connect(ui->Slot3, &QPushButton::clicked, this, [this]() { this->slot = 2; this->clikeoBotonSlot(); this->cargarPartida(slot); });
    connect(ui->botonContinua, &QPushButton::clicked, this, &Menu::ComenzarPartidaSlot);

    ui->MenuStacked->setCurrentIndex(0);
}

void Menu::guardarPartida(DatosJugador datos, int Slot)
{
    guardar.guardar(datos, Slot);
}

void Menu::cargarPartida(int slot){
    jugador = guardar.cargar(slot);
    emit enviarJugador(jugador);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::cargarSlot(int slot){
    indiceSlot = slot;
}


void Menu::cambiarNombreBoton(const QString &nombre)
{
    switch(indiceSlot){
    case 0: ui->Slot1->setText(nombre); break;
    case 1: ui->Slot2->setText(nombre); break;
    case 2: ui->Slot3->setText(nombre); break;
    default: break;
    }
}


// Método para detener la música
void Menu::stopMusic(){
    backgroundMusic->stop(); // Detener la música
}

void Menu::startMusic() {
    if (backgroundMusic->playbackState() != QMediaPlayer::PlayingState) {
        backgroundMusic->play();
    }
}

void Menu::clickeoJugar(){
    log->setText("Jugador Empezo a jugar.");
    stopMusic(); // Detener la música al jugar
    emit clickedJugar(Puntos);
    ui->BotonContinuar->setVisible(false);
    ui->MenuStacked->setCurrentIndex(0);
}

void Menu::ComenzarPartidaSlot(){
    log->setText("Jugador eligio partida.");
    stopMusic();
    qDebug()<<jugador.nombre;
    emit clickedJugar(jugador.puntuacion);
    ui->BotonContinuar->setVisible(false);
    ui->MenuStacked->setCurrentIndex(0);
}


void Menu::clikeoCargarPartida(){
    log->setText("Jugador cargo partida.");
    ui->MenuStacked->setCurrentIndex(2);
}

void Menu::clikeoBotonSlot(){
    ui->botonContinua->show();
}

void Menu::DificultadBaja(){//Aca tiene que ir el codigo de cada dificultad
//puntos=100
    log->setText("Jugador selecciono dificutald baja.");
    Puntos = 0;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadMedia(){//Aca tiene que ir el codigo de cada dificultad
//puntos=50
    log->setText("Jugador selecciono dificutald normal.");
    Puntos = 1;
    ui->BotonContinuar->setVisible(true);
}

void Menu::DificultadAlta(){//Aca tiene que ir el codigo de cada dificultad
//puntos=0;
    log->setText("Jugador selecciono dificutald Alta.");
    Puntos = 2;
    ui->BotonContinuar->setVisible(true);
}

void Menu::Exit(){//Cierra la aplicacion
    log->setText("Jugador salio del juego.");
    QApplication::quit();
}

void Menu::SeleccionarDif()
{
    ui->MenuStacked->setCurrentIndex(1);
}

void Menu::MenuPrincipal()
{
    log->setText("Jugador vuelve al menu.");
    ui->MenuStacked->setCurrentIndex(0);
    ui->botonContinua->hide();
}
