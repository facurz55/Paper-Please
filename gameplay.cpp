#include "gameplay.h"
#include "ui_gameplay.h"

gameplay::gameplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameplay)
{
    ui->setupUi(this);
    ui->Boton_ReiniciarNivel->setVisible(false);
    ui->labelPerdiste->setVisible(false);
    ui->labelPuntos->setVisible(false);
    ui->labelMultas->setVisible(false);
    ui->Boton_SiguienteDia->setVisible(false);
}

gameplay::~gameplay()
{
    delete ui;
}

QLabel* gameplay::getLabelNPC(){
    return ui->Label_NPC;
}

QPushButton* gameplay::getBotonSiguiente_NPC(){
    return ui->Siguiente_NPC;
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

void gameplay::on_Boton_ReiniciarNivel_clicked()
{

}


void gameplay::on_Boton_SiguienteDia_clicked()
{

}

