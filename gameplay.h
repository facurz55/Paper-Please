#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include<QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "persona.h"
#include "puntos.h"
#include "condiciones.h"
#include "multas.h"
#include "guardarpartida/datosjugador.h"
#include "menu.h"

namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = nullptr);
    void Empezar(int Dificultad);
    void Empezar(DatosJugador datos);

    void setUpPuntos(int Dificultad);
    ~gameplay();
    void EntrarNPC();
    void SalirNPC();
    char *getNombrePartida();
    QPushButton* getBotonSiguiente_NPC();
    QLabel *getLabelNPC();
    void MostrarCondiciones();

signals:
    void SalioElNPC();
    void clickedSiguienteDia();
    void clickedReiniciar();
    void clickedFinalizar();
    void clickedCondiciones();
    void clickedVolverMesa();
    void GuardarDatos(DatosJugador);
    void volverAlMenuClicked();
    void nombrePartidaActualizado(const QString &nombre);



public slots:
    void iniciarReloj();

private slots:
    //este boton tenemos que moverlo a la parte del nivel 1 el boton condicionales
    //void Boton_condiciones();//las condiciones para ver si perdiste o seguis al siguiente nivel
    //void on_Boton_ReiniciarNivel_clicked();//reinicia el nivel para volver a jugar
    //void on_Boton_SiguienteDia_clicked();//permite ingresar al siguiente nivel
    void ReiniciarNivel();
    void CondicionesNivel();
    void VolverMesa();
    void ComenzarSiguienteDia();
    void clikedCancelarGuardar();
    void clikedGuardarPartida();
    void clikedConfirmarGuardar();
    void siPasa();
    void noPasa();
    void actualizarLabelDocumento();
    void actualizarLabelVisa();
    void mostrarDocumentos();
    void cerrarDocumentos();
    void DatosFinalizar();
    void generarNpc();
    void cambiarSkinNPC();
    void detenerReloj();
    void actualizarReloj();
    void preguntar();
    void PrepararAnimacion();
    void PrepararAnimacionSalida();

private:
    int Nivel;
    Ui::gameplay *ui;
    QPropertyAnimation * animacionEntrada;
    QPropertyAnimation * animacionSalida;
    Persona Persona;
    puntos Puntos;
    multas multa;
    QTimer *Reloj;
    QTime tiempoInicio;
    QTime tiempoActual;
    QTime horaFin;
    condiciones condicion;
    char nombrePartida[50];
    QString condicion1;
    const QString ALDEANO = "image:url(:/elprimooo.png);";
    const QString REFUGIADOPOLITICO = "image:url(:/pngwing.com (2).png);";
    const QString REVOLUCIONARIO = "image:url(:/negritopix.png);";
    const QString DIPLOMATICO = "image:url(:/momardo.png);";
    QMediaPlayer *SonidoDenegar;
    QMediaPlayer *SonidoAceptar;
    QMediaPlayer *SonidoPapel;
    QMediaPlayer *MusicaGameplay;
    QAudioOutput *audioOutputPapel;
    QAudioOutput *audioOutputDenegar;
    QAudioOutput *audioOutputAceptar;
    QAudioOutput *audioOutputGameplay;

};

#endif // GAMEPLAY_H
