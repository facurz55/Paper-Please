#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioDevice>
#include "puntos.h"
#include "guardarpartida/guardarpartida.h"
#include "guardarpartida/datosjugador.h"
#include "gameplay.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void startMusic();
    void stopMusic(); // Método para detener la música*/

public slots:
    void guardarPartida(DatosJugador datos, int);
    void cambiarNombreBoton(const QString &nombre);
    void cargarPartida(int slot);
    void cargarSlot(int slot);

signals:
    void clickedJugar(int dificultad);
    void enviarJugador(DatosJugador);

private slots:
    void SeleccionarDif();
    void MenuPrincipal();
    void clickeoJugar();
    void clikeoCargarPartida();
    void clikeoBotonSlot();
    void DificultadBaja();
    void DificultadMedia();
    void DificultadAlta();
    void Exit();
    void ComenzarPartidaSlot();

private:
    guardarpartida guardar;
    Ui::Menu *ui;
    int Puntos;//validar con cuanto empieza los puntos
    int indiceSlot;
    int slot;
    DatosJugador jugador;
    QMediaPlayer *backgroundMusic;
    QAudioOutput *audioOutput;      // Puntero a QAudioOutput
};

#endif // MENU_H
