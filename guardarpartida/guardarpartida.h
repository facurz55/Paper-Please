#ifndef GUARDARPARTIDA_H
#define GUARDARPARTIDA_H

#include <QObject>
#include "datosjugador.h"
#include <QString>
#include <QCoreApplication>
#include <QDir>

class guardarpartida: public QObject
{
    Q_OBJECT
public:
    guardarpartida();
    void guardar(DatosJugador datos, int slot);
    DatosJugador cargar(int slot);
    void test();
private:
    QString partidas[3] = {"partida1.dat", "partida2.dat", "partida3.dat"};
    DatosJugador sinDatos = {0,0,0,0};
};

#endif // GUARDARPARTIDA_H
