#include "mainwindow.h"
#include "persona.h"
#include <QApplication>
#include "ventana_mariano.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
