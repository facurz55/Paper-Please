#include "guardarpartida.h"

guardarpartida::guardarpartida() {
    test();
}

void guardarpartida::guardar(DatosJugador datos, int slot)
{
    if (slot < 0)
        return;

    QFile archivo(partidas[slot]);
    if (!archivo.open(QIODevice::WriteOnly))
        return;

    archivo.write(reinterpret_cast<char*>(&datos), sizeof(DatosJugador));
    archivo.close();
}

DatosJugador guardarpartida::cargar(int slot)
{
    if (slot < 0)
        return sinDatos;

    QFile archivo(partidas[slot]);
    if (!archivo.open(QIODevice::ReadOnly))
        return sinDatos;

    auto tamanio = sizeof(DatosJugador);
    if (archivo.size() != tamanio)
        return sinDatos;

    DatosJugador datos;
    archivo.read(reinterpret_cast<char*> (&datos), tamanio);
    archivo.close();
    return datos;
}

void guardarpartida::test()
{
    DatosJugador datos = {"Juanceto", 5, 1, 3};
    this->guardar(datos,1);
    qDebug() << "Guardado";
    auto test = cargar(1);
    qDebug() << "Cargado, nombre: " << test.nombre;
}
