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
    QPushButton* getBotonJugar();
    QPushButton* getBotonAtras();
    QPushButton* getBotonContinuar();

private slots:
    void DificultadBaja();
    void DificultadMedia();
    void DificultadAlta();
    void Exit();
    void Continuar();

private:
    Ui::Menu *ui;
    int Puntos;//validar con cuanto empieza los puntos
    puntos puntos2;
};

#endif // MENU_H
