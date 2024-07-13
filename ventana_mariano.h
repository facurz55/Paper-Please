#ifndef VENTANA_MARIANO_H
#define VENTANA_MARIANO_H
#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>
#include <QTime>
#include "persona.h"

namespace Ui {
class ventana_Mariano;
}
class ventana_Mariano : public QMainWindow
{
    Q_OBJECT

public:
    explicit ventana_Mariano(QWidget *parent = nullptr);
    ~ventana_Mariano();

signals:
    void seCerro();

protected:
    void eventoCerrar(QCloseEvent *event);

private slots:
    void siPasa();
    void noPasa();
    void actualizarLabelConPersona();
    void iniciarCronometro();
    void detenerCronometro();
    void actualizarCronometro();
    void pasarDia();
    void preguntar();

private:
    Ui::ventana_Mariano *ui;
    Persona Persona;
    QTimer *cronometro;
    QTime tiempoInicio;
    QTime tiempoActual;
    QTime horaFin;
};

#endif // VENTANA_MARIANO_H
