#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include<QPushButton>
#include <QTimer>
#include <QTime>
#include "persona.h"
#include "puntos.h"

namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = nullptr);
    ~gameplay();
    QLabel* getLabelNPC();
    QPushButton* getBotonSiguiente_NPC();

private slots:
    void siPasa();
    void noPasa();
    void actualizarLabelConPersona();
    void mostrarD();
    void cerrarDatos();

    void vivaPeron();

    void iniciarCronometro();
    void detenerCronometro();
    void actualizarCronometro();
    void pasarDia();
    void preguntar();

private:
    Ui::gameplay *ui;
    Persona Persona;
    puntos puntos;
    QTimer *cronometro;
    QTime tiempoInicio;
    QTime tiempoActual;
    QTime horaFin;

};

#endif // GAMEPLAY_H
