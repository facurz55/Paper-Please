#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "menu.h"
#include "gameplay.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include<QPropertyAnimation>

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

protected:
    //Esta función se llamará automáticamente cada vez que el widget sea redimensionado,
    //permitiendo que se manejen eventos de redimensionamiento personalizados dentro de la clase.
    //Override se utiliza para indicar que esta función está sobrescribiendo una función virtual de una clase base.
    void resizeEvent(QResizeEvent *event) override;



private slots:
    void CambiarPagina();//Pasar a page_2
    void Volver();//volver a page
    void ComenzarJuego();//Muesta la pantalla gameplay
    void EntradaNPC();//Funcion para la entrada del NPC
    void SalirNPC(); //Funcion para la salida del NPC

private:
    Ui::MainWindow *ui;
    Menu *menuPage;//Puntero de la clase
    gameplay *game;//Puntero para la pantalla donde jugamos
    QStackedWidget *stackedWidget; //Puntero para el StackedWidget
    QWidget *page_2; // Placeholder para la página del juego
};
#endif // MAINWINDOW_H
