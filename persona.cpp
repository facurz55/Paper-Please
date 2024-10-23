#include "persona.h"

Persona::Persona() {
    // Inicializar los datos del pasaporte de forma aleatoria
    datosArchivo();
    generarNombres();  // para generar el nombre
    generarFecha();
    generarNacionalidad();
    generarVisa();
    generar_Estado_civil();
    generar_Estancia();
    pensamientos();

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


void Persona::datosArchivo() {

    std::ifstream archivoMale("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/nombres masculinos.txt");
    std::ifstream archivoFem("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/nombres femeninos.txt");
    std::ifstream archivoApellidos("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/apellidos.txt");
    if (!archivoMale.is_open()) {
        return;
    }
    if (!archivoFem.is_open()) {
        return;
    }
    if (!archivoApellidos.is_open()) {
        return;
    }

    std::string nombreM;
    std::string nombreF;
    std::string apellido;
    while (std::getline(archivoMale, nombreM)) {
        if (!nombreM.empty()) {
            VnombresMale.push_back(nombreM);
        }
    }
    while (std::getline(archivoMale, nombreF)) {
        if (!nombreF.empty()) {
            VnombresFem.push_back(nombreF);
        }
    }
    while (std::getline(archivoMale, apellido)) {
        if (!apellido.empty()) {
            Vapellidos.push_back(apellido);
        }
    }
    archivoMale.close();
    archivoFem.close();
    archivoApellidos.close();



    /*QFile archivoNomMale("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/nombres masculinos.txt");
    QFile archivoNomFem("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/nombres femeninos.txt");
    QFile archivoAp("C:/Users/maria/OneDrive/Documentos/GitHub/Paper-Please/Archivos de texto/apellidos.txt");
    if (!archivoNomMale.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    if (!archivoNomFem.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    if (!archivoAp.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in1(&archivoNomMale);
    while (!in1.atEnd()) {
        QString nombreMale = in1.readLine().trimmed();
        if (!nombreMale.isEmpty()) {
            vectorNombresMale.append(nombreMale);
        }
    }

    QTextStream in2(&archivoNomFem);
    while (!in2.atEnd()) {
        QString nombreFem = in2.readLine().trimmed();
        if (!nombreFem.isEmpty()) {
            vectorNombresFem.append(nombreFem);
        }
    }

    QTextStream in3(&archivoAp);
    while (!in3.atEnd()) {
        QString apellidos = in3.readLine().trimmed();
        if (!apellidos.isEmpty()) {
            vectorApellidos.append(apellidos);
        }
    }

    archivoNomMale.close();
    archivoNomFem.close();
    archivoAp.close();*/
}


void Persona::generarNombres() {
    QStringList generos = {"masculino", "femenino"};
    int gen = QRandomGenerator::global()->bounded(generos.size());
    genero = generos[gen];

    /*QStringList nombresM = {"Gabriel", "Andrés", "Diego", "Ricardo", "Mario", "Fernando", "Javier", "Daniel", "Emilio", "Sebastián"};
    QStringList nombresF = {"María", "Ana", "Laura", "Sofía", "Carmen", "Isabel", "Patricia", "Julia", "Elena", "Marta"};*/
    int ran = QRandomGenerator::global()->bounded(0, 100);
    if (gen == 0) {
        int nbm = QRandomGenerator::global()->bounded(VnombresMale.size());
        QString Male = QString::fromStdString(VnombresMale[nbm]);
        nombre = Male;
        if (ran < 10)
        {
            int nbf = QRandomGenerator::global()->bounded(VnombresFem.size());
            QString Fem = QString::fromStdString(VnombresFem[nbf]);
            nombre = Fem;
            pop = 1;
        }
    } else {
        int nbf = QRandomGenerator::global()->bounded(VnombresFem.size());
        QString Fem = QString::fromStdString(VnombresFem[nbf]);
        nombre = Fem;
        if (ran < 10)
        {
            int nbm = QRandomGenerator::global()->bounded(VnombresMale.size());
            QString Male = QString::fromStdString(VnombresMale[nbm]);
            nombre = Male;
            pop = 1;
        }
    }


    //QStringList apellidos = {"García", "Rodríguez", "López", "Martínez", "González", "Gomez", "Sánchez", "Ramírez", "Torres", "Flores", "Navarro", "Molina"};
    int na = QRandomGenerator::global()->bounded(Vapellidos.size());
    QString APE = QString::fromStdString(Vapellidos[na]);
    apellido = APE;
}

void Persona::generarFecha() {
    int a = QRandomGenerator::global()->bounded(1970, 2003);
    fecha = QString::number(a);
}

void Persona::generarNacionalidad() {
    QStringList nacionalidades = {"boliviano/a", "paraguayo/a", "brasileño/a", "argentino/a"};
    int ns = QRandomGenerator::global()->bounded(nacionalidades.size());
    nacionalidad = nacionalidades[ns];
}

void Persona::generarVisa() {
    QStringList Visas = {"Turista", "diplomatico", "Trabajo", "Residente", "refugiado politico"};
    int vi = QRandomGenerator::global()->bounded(100);
    if (vi <= 10)
    {
        Visa = Visas[1];
        tipoNpc = "diplomático";
    }
    if ((vi > 10)&&(vi <= 40))
    {
        Visa = Visas[0];
        int tipo = QRandomGenerator::global()->bounded(100);
        tipoNpc = "aldeano";
        if (tipo > 90)
        {
            tipoNpc = "revolucionario";
            pop = 1;
            multa = 1;
        }
    }
    if ((vi > 40)&&(vi <= 70))
    {
        Visa = Visas[2];
        int tipo1 = QRandomGenerator::global()->bounded(100);
        tipoNpc = "aldeano";
        if (tipo1 > 90)
        {
            tipoNpc = "revolucionario";
            pop = 1;
            multa = 1;
        }
    }
    if ((vi > 70)&&(vi <= 90))
    {
        Visa = Visas[3];
        int tipo2 = QRandomGenerator::global()->bounded(100);
        tipoNpc = "aldeano";
        if (tipo2 > 90)
        {
            tipoNpc = "revolucionario";
            pop = 1;
            multa = 1;
        }
    }
    if (vi > 90)
    {
        Visa = Visas[4];
        tipoNpc = "refugiado político";
    }
}

void Persona::generar_Estado_civil() {
    QString estadocivil[4] = {"Soltero", "Casado", "Divorciado", "Viudo"};
    int min = 0;
    int max = 3;
    int num;
    num = min + rand() % (max + 1 - min);
    Estadocivil = estadocivil[num];
}

void Persona::pensamientos()
{
    QStringList ideas = {"Que lindo dia", "Tengo hambre", "vamos Messi"};
    int pens = QRandomGenerator::global()->bounded(ideas.size());
    pensamiento = ideas[pens];
    if (tipoNpc == "revolucionario")
    {
        QStringList ideasmalas = {"En Cuba el pueblo es feliz", "Venezuela no es verdadero comunismo", "Evo Morales <3"};
        int pens = QRandomGenerator::global()->bounded(ideasmalas.size());
        pensamiento = ideasmalas[pens];
    }
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

QString Persona::obtenerFecha() const {
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

QString Persona::obtenerPensamientos()
{
    return pensamiento;
}

QString Persona::obtenerNpc()
{
    return tipoNpc;
}



