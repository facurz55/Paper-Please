#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "puntos.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

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
    Ui::Menu *ui;
    int Puntos;//validar con cuanto empieza los puntos
};

#endif // MENU_H
