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
    void MostrarVentanas();
    void Mostrar5Botones();


private:
    Ui::MainWindow *ui;
    Menu *menuPage;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
