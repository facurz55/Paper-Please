#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QStringList>

class Persona {
public:
    Persona();
    void Mostrar_Datos();

    QString obtenerGenero() const;
    QString obtenerNombre() const;
    QString obtenerApellido() const;
    int obtenerFecha() const;
    QString obtenerNacionalidad() const;
    QString getPersonaVisa() const;
    QString getPersonaEstCivil() const;
    //Faltan Estancia, residencia, proposito del viaje, integrantes, antecedentes

private:
    void generarNombres();
    void generarFecha();
    void generarNacionalidad();
    void generarVisa();
    void generar_Estado_civil();
    void generar_Estancia();

    QString genero;
    QString nombre;
    QString apellido;
    int fecha;
    QString nacionalidad;
    QString Visa;
    QString Estadocivil;
    QString Estancia;
};

#endif // PERSONA_H

