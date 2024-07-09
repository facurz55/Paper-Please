#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "persona.h"
#include <QMainWindow>

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
    void Button();

    void pushButton_2();

    void siPasa();

    void noPasa();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
