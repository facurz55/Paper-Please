#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QStringList>

class Persona {
public:
    Persona();
    void generarNombres();
    void generarFecha();
    void generarNacionalidad();
    void generarVisa();
    void generar_Estado_civil();
    void generar_Estancia();
    void pensamientos();

    void retPop();
    int obtenerPop();

    int obtenerFecha() const;
    QString obtenerGenero() const;
    QString obtenerNombre() const;
    QString obtenerApellido() const;
    QString obtenerNacionalidad() const;
    QString obtenerEstancia() const;
    QString getPersonaVisa() const;
    QString getPersonaEstCivil() const;
    QString obtenerPensamientos();
    QString obtenerNpc();
protected:
    QString tipoNpc;
    QString genero;
    QString nombre;
    QString apellido;
    int fecha;
    QString nacionalidad;
    QString Visa;
    QString Estadocivil;
    QString Estancia;
    int pop = 0;
    int multa = 0;
    QString pensamiento;
};

#endif // PERSONA_H

