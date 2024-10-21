#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include<QPropertyAnimation>
#include <QMainWindow>
#include <QSoundEffect>

#include "persona.h"
#include "menu.h"
#include "gameplay.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void actualizarLabelConPersona(const Persona &persona);
private slots:
    //void Button();


protected:
    //Esta función se llamará automáticamente cada vez que el widget sea redimensionado,
    //permitiendo que se manejen eventos de redimensionamiento personalizados dentro de la clase.
    //Override se utiliza para indicar que esta función está sobrescribiendo una función virtual de una clase base.
    void resizeEvent(QResizeEvent *event) override;



private slots:
    void Volver();//volver a page
    void ComenzarJuego(int Dificultad);//Muesta la pantalla gameplay


    //void pushButton_2();

    //void siPasa();

    //void noPasa();
private:
    Ui::MainWindow *ui;

    QSoundEffect sonido;
    Menu *menuPage;//Puntero de la clase
    gameplay *game;//Puntero para la pantalla donde jugamos
    QStackedWidget * stackedWidget; //Puntero para el StackedWidget
};
#endif // MAINWINDOW_H
