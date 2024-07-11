#include "persona.h"
#include <QDebug>
#include <QRandomGenerator>
#include <stdlib.h>
#include <time.h>

Persona::Persona() {
    // Inicializar los datos del pasaporte de forma aleatoria
    generarNombres();  // para generar el nombre
    generarFecha();
    generarNacionalidad();
    generarVisa();
    generar_Estado_civil();
    generar_Estancia();
}

// Métodos de generación de datos
void Persona::generar_Estancia()
{
    int fallo = QRandomGenerator::global()->bounded(100);
    if (Visa == "Turista")
    {
        int ran1 = QRandomGenerator::global()->bounded(1, 3);
        QString est = QString("%1 semanas")
            .arg(QString::number(ran1));
        Estancia = est;
        if (fallo < 10)
        {
            int rand1 = QRandomGenerator::global()->bounded(4, 10);
            QString est = QString("%1 semanas")
                .arg(QString::number(rand1));
            Estancia = est;
            pop = 1;
        }
    }
    if (Visa == "diplomatico")
    {
        int ran2 = QRandomGenerator::global()->bounded(2, 4);
        QString est = QString("%1 años")
            .arg(QString::number(ran2));
        Estancia = est;
        if (fallo < 5)
        {
            int rand2 = QRandomGenerator::global()->bounded(6, 18);
            QString est = QString("%1 meses")
                .arg(QString::number(rand2));
            Estancia = est;
            pop = 1;
        }
        if (fallo > 95)
        {
            int rand2 = QRandomGenerator::global()->bounded(5, 10);
            QString est = QString("%1 años")
                .arg(QString::number(rand2));
            Estancia = est;
            pop = 1;
        }
    }
    if (Visa == "Trabajo")
    {
        int ran3 = QRandomGenerator::global()->bounded(6, 18);
        QString est = QString("%1 meses")
            .arg(QString::number(ran3));
        Estancia = est;
        if (fallo < 10)
        {
            int rand3 = QRandomGenerator::global()->bounded(19, 26);
            QString est = QString("%1 meses")
                .arg(QString::number(rand3));
            Estancia = est;
            pop = 1;
        }
    }
    if (Visa == "Residente")
    {
        Estancia = "indefinido";
        if (fallo < 10)
        {
            int rand1 = QRandomGenerator::global()->bounded(2, 100);
            QString est = QString("%1 años")
            .arg(QString::number(rand1));
            Estancia = est;
            pop = 1;
        }
    }
}

void Persona::generarNombres() {
    QStringList generos = {"masculino", "femenino"};
    int gen = QRandomGenerator::global()->bounded(generos.size());
    genero = generos[gen];
    QStringList nombresM = {"Gabriel", "Andrés", "Diego", "Ricardo", "Mario", "Fernando", "Javier", "Daniel", "Emilio", "Sebastián"};
    QStringList nombresF = {"María", "Ana", "Laura", "Sofía", "Carmen", "Isabel", "Patricia", "Julia", "Elena", "Marta"};
    int ran = QRandomGenerator::global()->bounded(0, 100);
    if (gen == 0) {
        int nbm = QRandomGenerator::global()->bounded(nombresM.size());
        nombre = nombresM[nbm];
        if (ran < 10)
        {
            int nbf = QRandomGenerator::global()->bounded(nombresF.size());
            nombre = nombresF[nbf];
            pop = 1;
        }
    } else {
        int nbf = QRandomGenerator::global()->bounded(nombresF.size());
        nombre = nombresF[nbf];
        if (ran < 10)
        {
            int nbm = QRandomGenerator::global()->bounded(nombresM.size());
            nombre = nombresM[nbm];
            pop = 1;
        }
    }
    QStringList apellidos = {"García", "Rodríguez", "López", "Martínez", "González", "Gomez", "Sánchez", "Ramírez", "Torres", "Flores", "Navarro", "Molina"};
    int na = QRandomGenerator::global()->bounded(apellidos.size());
    apellido = apellidos[na];
}

void Persona::generarFecha() {
    int a = QRandomGenerator::global()->bounded(1970, 2003);
    fecha = a;
}

void Persona::generarNacionalidad() {
    QStringList nacionalidades = {"Bolita", "Paragua", "Brazuk", "Ario(argentino)"};
    int ns = QRandomGenerator::global()->bounded(nacionalidades.size());
    nacionalidad = nacionalidades[ns];
}

void Persona::generarVisa() {
    QStringList Visas = {"Turista", "diplomatico", "Trabajo", "Residente"};
    int vi = QRandomGenerator::global()->bounded(Visas.size());
    Visa = Visas[vi];
}

void Persona::generar_Estado_civil() {
    QString estadocivil[4] = {"Soltero", "Casado", "Divorciado", "Viudo"};
    int min = 0;
    int max = 3;
    int num;
    num = min + rand() % (max + 1 - min);
    Estadocivil = estadocivil[num];
}

// Métodos para obtener los datos
QString Persona::obtenerGenero() const {
    return genero;
}

QString Persona::obtenerNombre() const {
    return nombre;
}

QString Persona::obtenerApellido() const {
    return apellido;
}

int Persona::obtenerFecha() const {
    return fecha;
}

QString Persona::obtenerNacionalidad() const {
    return nacionalidad;
}

QString Persona::getPersonaVisa() const {
    return Visa;
}

QString Persona::getPersonaEstCivil() const {
    return Estadocivil;
}

QString Persona::obtenerEstancia() const
{
    return Estancia;
}

void Persona::retPop()
{
    pop = 0;
}

int Persona::obtenerPop()
{
    return pop;
}

void Persona::Mostrar_Datos() {
    qDebug() << "Genero: " << this->obtenerGenero();
    qDebug() << "Nombre: " << this->obtenerNombre();
    qDebug() << "Apellido: " << this->obtenerApellido();
    qDebug() << "Fecha de Nacimiento: " << this->obtenerFecha();
    qDebug() << "Nacionalidad: " << this->obtenerNacionalidad();
    qDebug() << "Tipo de Visa: " << this->getPersonaVisa();
    qDebug() << "Estado Civil: " << this->getPersonaEstCivil();
}



