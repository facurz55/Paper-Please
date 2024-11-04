#include "logs.h"
#include <QString>
#include <QDateTime>

Logs::Logs() {
    this->archivo.open("/logs.txt", ios::app);
    QString fechaActual = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss");
    auto fecha = fechaActual.toStdString();
    archivo << "INICIO DEL JUEGO: " << fecha << endl;

}

Logs::~Logs()
{
    this->archivo.close();
}

void Logs::setText(string texto)
{
    QString fechaActual = "[" + QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss") + "] ";
    auto fechaLogRecibido = fechaActual.toStdString();
    archivo << fechaLogRecibido << texto << endl;
}
