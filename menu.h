#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "puntos.h"
#include "guardarpartida/guardarpartida.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

public slots:
    void guardarPartida(DatosJugador datos);

signals:
    void clickedJugar(int dificultad);

private slots:
    void SeleccionarDif();
    void MenuPrincipal();
    void clickeoJugar();

    void DificultadBaja();
    void DificultadMedia();
    void DificultadAlta();
    void Exit();


private:
    guardarpartida guardar;
    Ui::Menu *ui;
    int Puntos;//validar con cuanto empieza los puntos
    int slot;
};

#endif // MENU_H
