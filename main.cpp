#include "mainwindow.h"
#include "persona.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Persona Persona1;
    Persona1.Mostrar_Datos();

    return a.exec();
}
