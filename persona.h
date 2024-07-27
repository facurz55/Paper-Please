#ifndef PERSONA_H
#define PERSONA_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QRandomGenerator>
#include <time.h>

// #include "gameplay.h"

class Persona {
public:
    Persona();
    void Mostrar_Datos();

    void generarNombres();
    void generarFecha();
    void generarNacionalidad();
    void generarVisa();
    void generar_Estado_civil();
    void generar_Estancia();
    void pensamientos();

    //Pop indica que el documento tiene almenos un error
    void retPop(); //hace que "Pop" vuelva a valer 0 luego de ser utilizado
    int obtenerPop();

    QString obtenerGenero() const;
    QString obtenerNombre() const;
    QString obtenerApellido() const;
    QString obtenerFecha() const;
    QString obtenerNacionalidad() const;
    QString obtenerEstancia() const;
    QString getPersonaVisa() const;
    QString getPersonaEstCivil() const;
    QString obtenerPensamientos();
    QString obtenerNpc();

    //Faltan Estancia, residencia, proposito del viaje, integrantes, antecedentes
protected:
    QString tipoNpc;
    QString genero;
    QString nombre;
    QString apellido;
    QString fecha;
    QString nacionalidad;
    QString Visa;
    QString Estadocivil;
    QString Estancia;
    int pop = 0;
    int multa = 0;
    QString pensamiento;
};

#endif // PERSONA_H

