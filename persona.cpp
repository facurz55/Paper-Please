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

    generarResidencia();
    generarProposito();
}

// Métodos de generación de datos
void Persona::generar_Estancia()
{
    int fallo = generador.bounded(100);
    if (Visa == "Turista")
    {
        int ran1 = generador.bounded(1, 3);
        QString est = QString("%1 semanas")
            .arg(QString::number(ran1));
        Estancia = est;
        if (fallo < 10)
        {
            int rand1 = generador.bounded(4, 10);
            QString est = QString("%1 semanas")
                .arg(QString::number(rand1));
            Estancia = est;
            pop = 1;
        }
    }
    if (Visa == "diplomatico")
    {
        int ran2 = generador.bounded(2, 4);
        QString est = QString("%1 años")
            .arg(QString::number(ran2));
        Estancia = est;
        if (fallo < 5)
        {
            int rand2 = generador.bounded(6, 18);
            QString est = QString("%1 meses")
                .arg(QString::number(rand2));
            Estancia = est;
            pop = 1;
        }
        if (fallo > 95)
        {
            int rand2 = generador.bounded(5, 10);
            QString est = QString("%1 años")
                .arg(QString::number(rand2));
            Estancia = est;
            pop = 1;
        }
    }
    if (Visa == "Trabajo")
    {
        int ran3 = generador.bounded(6, 18);
        QString est = QString("%1 meses")
            .arg(QString::number(ran3));
        Estancia = est;
        if (fallo < 10)
        {
            int rand3 = generador.bounded(19, 26);
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
            int rand1 = generador.bounded(2, 100);
            QString est = QString("%1 años")
            .arg(QString::number(rand1));
            Estancia = est;
            pop = 1;
        }
    }
}


void Persona::datosArchivo() {

    QFile archivoNomMale(":/Archivos de texto/nombres masculinos.txt");
    QFile archivoNomFem(":/Archivos de texto/nombres femeninos.txt");
    QFile archivoAp(":/Archivos de texto/apellidos.txt");
    if (!archivoNomMale.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    if (!archivoNomFem.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }
    if (!archivoAp.open(QFile::ReadOnly | QFile::Text)) {
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
    archivoAp.close();
    return;
}

void Persona::generarNombres() {
    QStringList generos = {"masculino", "femenino"};
    int gen = generador.bounded(generos.size());
    genero = generos[gen];
    int ran = generador.bounded(0, 100);
    if (gen == 0) {
        if (!vectorNombresMale.isEmpty()) {
        int nbm = generador.bounded(vectorNombresMale.size());
        nombre = vectorNombresMale[nbm];

        if (ran < 10)
        {
            int nbf = generador.bounded(vectorNombresFem.size());
            nombre = vectorNombresFem[nbf];
            pop = 1;
        }
        }
    } else {
        if (!vectorNombresFem.isEmpty()) {
        int nbf = generador.bounded(vectorNombresFem.size());
        nombre = vectorNombresFem[nbf];
        if (ran < 10)
        {
            int nbm = generador.bounded(vectorNombresMale.size());
            nombre = vectorNombresMale[nbm];
            pop = 1;
        }
        }
    }
    if (!vectorApellidos.isEmpty()) {
    int na = generador.bounded(vectorApellidos.size());
    apellido = vectorApellidos[na];
    }
}

void Persona::generarFecha() {
    int a = generador.bounded(1970, 2003);
    fecha = QString::number(a);
}

void Persona::generarNacionalidad() {
    QStringList nacionalidades = {"boliviano/a", "paraguayo/a", "brasileño/a", "argentino/a"};
    int ns = generador.bounded(nacionalidades.size());
    nacionalidad = nacionalidades[ns];
}

void Persona::generarVisa() {
    QStringList Visas = {"Turista", "diplomatico", "Trabajo", "Residente", "refugiado politico"};
    int vi = generador.bounded(100);
    if (vi <= 10)
    {
        Visa = Visas[1];
        tipoNpc = "diplomático";
    }
    if ((vi > 10)&&(vi <= 40))
    {
        Visa = Visas[0];
        int tipo = generador.bounded(100);
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
        int tipo1 = generador.bounded(100);
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
        int tipo2 = generador.bounded(100);
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
    int pens = generador.bounded(ideas.size());
    pensamiento = ideas[pens];
    if (tipoNpc == "revolucionario")
    {
        QStringList ideasmalas = {"En Cuba el pueblo es feliz", "Venezuela no es verdadero comunismo", "Evo Morales <3"};
        int pens = generador.bounded(ideasmalas.size());
        pensamiento = ideasmalas[pens];
    }
}

void Persona::generarResidencia(){
    int out = generador.bounded(100);
    if(nacionalidad == "boliviano/a"){
        residencia = "Bolivia";
        if(out < 10){
            QStringList pais = {"Paraguay", "Brasil", "Argentina"};
            int pai = generador.bounded(pais.size());
            residencia = pais[pai];
        }
    }
    if(nacionalidad == "paraguayo/a"){
        residencia = "Paraguay";
        if(out < 10){
            QStringList pais = {"Bolivia", "Brasil", "Argentina"};
            int pai = generador.bounded(pais.size());
            residencia = pais[pai];
        }
    }
    if(nacionalidad == "brasileño/a"){
        residencia = "Brasil";
        if(out < 10){
            QStringList pais = {"Bolivia", "Paraguay", "Argentina"};
            int pai = generador.bounded(pais.size());
            residencia = pais[pai];
        }
    }
    if(nacionalidad == "argentino/a"){
        residencia = "Argentina";
        if(out < 10){
            QStringList pais = {"Bolivia", "Paraguay", "Brasil"};
            int pai = generador.bounded(pais.size());
            residencia = pais[pai];
        }
    }
}

void Persona::generarProposito(){
    int mal = generador.bounded(100);
    if(Visa == "Turista"){
        QStringList propositos = {"Turismo", "visitar a un familiar"};
        int prop = generador.bounded(propositos.size());
        proposito = propositos[prop];
        if(mal < 10){
            QStringList malProposito = {"trabajo", "residencia", "estereotipo no convencional de peruano"};
            int prop = generador.bounded(malProposito.size());
            residencia = malProposito[prop];
        }
    }
    if(Visa == "diplomatico"){
        QStringList propositos = {"negociaciones internacionales", "relaciones internacionales"};
        int prop = generador.bounded(propositos.size());
        proposito = propositos[prop];
            if(mal < 10){
            QStringList malProposito = {"trabajo", "residencia", "estereotipo no convencional de peruano", "se ma quedo la motora"};
            int prop = generador.bounded(malProposito.size());
            residencia = malProposito[prop];
        }
    }
    if(Visa == "Trabajo"){
        QStringList propositos = {"trabajo"};
        int prop = generador.bounded(propositos.size());
        proposito = propositos[prop];
            if(mal < 10){
            QStringList malProposito = {"residencia", "estereotipo no convencional de boliguayo", "string.h"};
            int prop = generador.bounded(malProposito.size());
            residencia = malProposito[prop];
        }
    }
    if(Visa == "Residente"){
        QStringList propositos = {"residencia"};
        int prop = generador.bounded(propositos.size());
        proposito = propositos[prop];
            if(mal < 10){
            QStringList malProposito = {"trabajo", "estereotipo no convencional de somali", "estoy buscando a Rusher King"};
            int prop = generador.bounded(malProposito.size());
            residencia = malProposito[prop];
        }
    }
    if(Visa == "refugiado politico"){
        QStringList propositos = {"asilo politico"};
        int prop = generador.bounded(propositos.size());
        proposito = propositos[prop];
            if(mal < 10){
            QStringList malProposito = {"trabajo", "recidencia", "estereotipo no convencional de peruano", "si mi nacionalidad es boliviano pido disculpas"};
            int prop = generador.bounded(malProposito.size());
            residencia = malProposito[prop];
        }
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



