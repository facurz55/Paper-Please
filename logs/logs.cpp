#include "logs.h"


Logs::Logs() {
    QString fechaActual = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss");
    QFile archivo("logs.txt");

    if(!archivo.open(QIODevice::Text | QIODevice::Append)){
        qDebug() << "No se pudo abrir el archivo de logs";
    }

    QTextStream stream(&archivo);
    stream << "INICIO DEL JUEGO: " << fechaActual  << "\n";
    archivo.close();

}

Logs::~Logs()
{

}

void Logs::setText(QString texto)
{
    QString fechaActual = "[" + QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss") + "] ";
    qDebug() << "anduvo";

    QFile archivo("logs.txt");

    if(!archivo.open(QIODevice::Text | QIODevice::Append)){
        qDebug() << "No se pudo abrir el archivo de logs";
    }

    QTextStream stream(&archivo);
    stream << fechaActual << texto << "\n";
    archivo.close();
}
