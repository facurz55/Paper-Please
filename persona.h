#ifndef PERSONA_H
#define PERSONA_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QRandomGenerator>

#include <QFile>
#include <QTextStream>
#include <QVector>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <time.h>

// #include "gameplay.h"

class Persona {
public:
    Persona();
    void Mostrar_Datos();
    //PERRA CACHONDA
    void generarNombres();
    void generarFecha();
    void generarNacionalidad();
    void generarVisa();
    void generar_Estado_civil();
    void generar_Estancia();
    void pensamientos();
    void datosArchivo();

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
    QVector<QString> vectorNombresMale;
    QVector<QString> vectorNombresFem;
    QVector<QString> vectorApellidos;
    std::vector<std::string> VnombresMale;
    std::vector<std::string> VnombresFem;
    std::vector<std::string> Vapellidos;

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

