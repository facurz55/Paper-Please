#ifndef CONDICIONES_H
#define CONDICIONES_H
#include <QString>
#include <QRandomGenerator>

#include "persona.h"

class condiciones
{
public:
    condiciones();
    ~condiciones(); //Para limpiar la memoria

    void generarCondicionesNivel1();
    int generarNumero();
    int generarNumero2();

    QString obtenerNacionalidad();
    QString obtenerFecha();
    QString obtenerTipoVisita();
    QString obtenerEstancia();
    QString obtenerEstCivil();

protected:
    QString nacionalidad;
    QString fecha;
    QString tipoVisita;
    QString estancia;
    QString estCivil;
    QString paisResidencia;
    QString proposito;
    QString compania;
    QString objetos;
    QString tipoCarreraUni;

private:
    Persona* NPC;

};

#endif // CONDICIONES_H
