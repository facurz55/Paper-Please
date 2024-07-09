#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "menu.h"
#include <QMainWindow>
#include <QStackedWidget>

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

private slots:
    void CambiarPagina();//Pasar a page_2
    void Volver();//volver a page

private:
    Ui::MainWindow *ui;
    Menu *menuPage;//Puntero de la clase
    QStackedWidget *stackedWidget; //Puntero para el StackedWidget
    QWidget *page_2; // Placeholder para la página del juego
};
#endif // MAINWINDOW_H
