#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay)
{
    ui->setupUi(this);
    ui->Boton_ReiniciarNivel->setVisible(false);
    ui->Boton_SiguienteDia->setVisible(false);
    ui->labelMultas->setVisible(false);
    ui->labelPerdiste->setVisible(false);
    ui->labelPuntos->setVisible(false);

    // Crea una animación de propiedad para el QLabel, animando su geometría
    animacionEntrada = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacion();

    animacionSalida = new QPropertyAnimation(ui->Label_NPC, "pos");
    PrepararAnimacionSalida();

    connect(animacionSalida, &QAbstractAnimation::finished, this, &gameplay::emitSalioNPC);
}

gameplay::~gameplay()
{
    delete ui;
}

QPushButton* gameplay::getReiniciarDia(){
    return ui->Boton_ReiniciarNivel;
}

QPushButton* gameplay::getBotonSiguienteDia(){
    return ui->Boton_SiguienteDia;
}

QPushButton* gameplay::getBotonSiguiente_NPC(){
    return ui->Siguiente_NPC;
}

QLabel *gameplay::getLabelNPC()
{
    return ui->Label_NPC;
}
//esto hay que verlo en lo del nivel 1 del boton terminar jornada
/*void gameplay::Boton_condiciones() {//esto para verificar si perdiste, en caso que no se muestran los puntos y multas
    if ((multas > 4) || (puntos < 0)) {
        ui->labelPerdiste->setVisible(true);//muestra un label con mensaje de perdiste
        ui->Boton_ReiniciarNivel->setVisible(true);//boton de reiniciar el juego
        ui->labelPuntos->setVisible(false);//se esconde los puntos, multas y el boton de siguiente dia
        ui->labelMultas->setVisible(false);
        ui->Boton_SiguienteDia->setVisible(false);
    } else {//en caso de que se siga el juego se muestra lo siguiente
        ui->labelPerdiste->setVisible(false);//no perdiste asi que no muestra esto
        ui->Boton_ReiniciarNivel->setVisible(false);
        ui->labelPuntos->setText(QString("Puntos: %1").arg(puntos));//se muestran los puntos (arg es paraa mostrar los puntos
        ui->labelPuntos->setVisible(true);//se abre el label de puntos
        ui->labelMultas->setText(QString("Multas: %1").arg(multas));//lo mismo para multas
        ui->labelMultas->setVisible(true);
        ui->Boton_SiguienteDia->setVisible(true);//se muestra el boton del siguiente dia
    }
}
void gameplay::on_Boton_ReiniciarNivel_clicked() {//ver como configurarlo
    resetear_nivel();
}
void gameplay::on_Boton_SiguienteDia_clicked() {//ver como configurarlo

}
*/

void gameplay::EntrarNPC()
{
    // Calcula la coordenada X central para el labelNPC
    int centerX = (width() - ui->Label_NPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 35;

    animacionEntrada->setStartValue(QPoint(-(ui->Label_NPC->width()),centerY));
    animacionEntrada->setEndValue(QPoint(centerX, centerY));

    animacionEntrada->start();
}

void gameplay::SalirNPC()
{
    // Calcula la coordenada X central para el labelNPC
    int centerX = (width() - ui->Label_NPC->width()) / 2;

    // Calcula la coordenada Y central para el labelNPC y ajusta 35 píxeles hacia arriba
    int centerY = (height() - ui->Label_NPC->height()) / 2 - 35;

    animacionSalida->setStartValue(QPoint(centerX, centerY));
    animacionSalida->setEndValue(QPoint(width() + ui->Label_NPC->height(), centerY));

    animacionSalida->start();
}

void gameplay::PrepararAnimacion()
{
    // Establece la duración de la animación en milisegundos
    animacionEntrada->setDuration(1500);

    // Establece la curva de animación para que sea suave y desacelerada al final
    animacionEntrada->setEasingCurve(QEasingCurve::OutExpo);
}

void gameplay::PrepararAnimacionSalida()
{
    // Establece la duración de la animación en milisegundos
    animacionSalida->setDuration(1500);

    // Establece la curva de animación para que sea suave y desacelerada al final
    animacionSalida->setEasingCurve(QEasingCurve::InExpo);
}

void gameplay::emitSalioNPC()
{
    emit SalioElNPC();
}


