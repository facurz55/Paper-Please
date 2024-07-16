#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include<QPushButton>
//#include "puntos.h"
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
    //este boton tenemos que moverlo a la parte del nivel 1 el boton condicionales
    void Boton_condiciones();//las condiciones para ver si perdiste o seguis al siguiente nivel

    void on_Boton_ReiniciarNivel_clicked();//reinicia el nivel para volver a jugar

    void on_Boton_SiguienteDia_clicked();//permite ingresar al siguiente nivel
private:
    Ui::gameplay *ui;
    //hay que llamar a la clase de puntos y multas para ver cuanto hicieron
    //  puntos punto;
    // multas multa;
};

#endif // GAMEPLAY_H
