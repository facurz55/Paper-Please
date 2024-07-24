#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include<QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include "persona.h"
#include "puntos.h"
#include "condiciones.h"
#include "multas.h"

namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = nullptr);
    ~gameplay();
    void EntrarNPC();
    void SalirNPC();
    QPushButton* getBotonSiguiente_NPC();
    QLabel *getLabelNPC();
    QPushButton* getBotonSiguienteDia();//Ventana de Thiago
    QPushButton* getReiniciarDia();//ventana de thiago
    QPushButton* getFinalizarTurno();//ventana game
    QPushButton* getBotonCondiciones();//boton para condiciones
    QPushButton* getBotonVolver();
    void MostrarCondiciones();

signals:
    void SalioElNPC();

private slots:
    //este boton tenemos que moverlo a la parte del nivel 1 el boton condicionales
    //void Boton_condiciones();//las condiciones para ver si perdiste o seguis al siguiente nivel
    //CAMBIEN EL NOMBRE DE ESTAS FUNCIONES POR FAVOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOR
    //void on_Boton_ReiniciarNivel_clicked();//reinicia el nivel para volver a jugar

    //void on_Boton_SiguienteDia_clicked();//permite ingresar al siguiente nivel
    void siPasa();
    void noPasa();
    void actualizarLabelConPersona();
    void mostrarD();
    void mostrarVisa();
    void cerrarDatos();
    void DatosFinalizar();
    void vivaPeron();
    void cambiarSkinNPC();
    void iniciarCronometro();
    void detenerCronometro();
    void actualizarCronometro();
    void pasarDia();
    void preguntar();

private:
    Ui::gameplay *ui;
    QPropertyAnimation * animacionEntrada;
    void PrepararAnimacion();

    QPropertyAnimation * animacionSalida;
    void PrepararAnimacionSalida();
    void emitSalioNPC();
    //hay que llamar a la clase de puntos y multas para ver cuanto hicieron
    //  puntos punto;
    // multas multa;
    Persona Persona;
    puntos puntos;
    multas* multa;
    QTimer *cronometro;
    QTime tiempoInicio;
    QTime tiempoActual;
    QTime horaFin;
    condiciones* condicion;
    QString condicion1;
    const QString ALDEANO = "image:url(:/pngwing.com.png);";
    const QString REFUGIADOPOLITICO = "image:url(/pngwing.com (2).png)";
    const QString REVOLUCIONARIO = "image:url(:/pngwing.com (3).png)";
    const QString DIPLOMATICO = "image:url(:/pngwing.com (1).png)";
};

#endif // GAMEPLAY_H
