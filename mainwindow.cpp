#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "hotel.h"
#include <QPixmap>
#include <QComboBox>
#include "notification.h"
#include "smtp.h"
#include "qcustomplot.h"
#include "statistique.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ok.notification_Ouverture("GESTION HOTELS/DESTINATIONS");
    ui->tableView->setModel(tmpdestination.afficher());
    ui->tableView2->setModel(tmphotel.afficherH());
    ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
    ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
    QPixmap back1("C:/Users/Haboub/Pictures/Wallpapers/witcherHorizon.jpg");
    QPixmap back2("C:/Users/Haboub/Pictures/Wallpapers/trave1background.jpg");
    QPixmap back3("C:/Users/Haboub/Pictures/Wallpapers/hotel1background.jpg");
    QPixmap back4("C:/Users/Haboub/Pictures/Wallpapers/hotel2background.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_destination_clicked()
{

    //CODE INCREMENTAION STILL NOT FUNCTIONAL
    // GET TO IT FATTY.
    //int code = 0;
    int promo = ui->promo_aajouter->text().toInt();
    QString nom = ui->nom_aajout->text();
    QString description = ui->description_aajouter->text();
    destination d(description,nom,0,promo);
    bool test=d.ajouter();
    if(test)
    {
        ok.notification_ajout_destination(nom);
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());
        QMessageBox::information(nullptr,QObject::tr("Ajout Destination"),"Destination Ajoutée");
    }

}

void MainWindow::on_SupprimerDestination_clicked()
{
    int code= ui->code_asupprimer->text().toInt();
    bool test=tmpdestination.supprimer(code);
    if(test)
    {
        ui->tableView->setModel(tmpdestination.afficher());
        ui->comboBox->setModel(tmpdestination.ModelCodeDestinations());

       ui->code_asupprimer->setText("");
    }
    else{}
}

void MainWindow::on_ajouter_hotel_clicked()
{
    int idhotel = ui->id_ajout_hotel->text().toInt();
    int etoiles = ui->etoiles_ajout_hotel->text().toInt();
    QString nom = ui->nom_ajouter_hotel->text();
    QString adresse = ui->adresse_ajout_hotel->text();
    int coutparnuit = ui->cout_ajout_hotel->text().toInt();

    hotel h(idhotel, nom, adresse, etoiles, coutparnuit);
    bool test=h.ajouterH();
    if(test)
    {
        /////////////////////
        ok.notification_ajout_hotel(nom);
       ///////////////////////
         ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
        ui->tableView2->setModel(tmphotel.afficherH());
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"Well done sire!");
    }else
        QMessageBox::information(nullptr,QObject::tr("Ajout Hotel"),"ERROR MY LIEGE");
}


void MainWindow::on_supprimer_hotel_clicked()
{
    int idhotel= ui->idhotel_asupprimer->text().toInt();
    bool test=tmphotel.supprimer(idhotel);
    if(test)
    {
        ui->tableView2->setModel(tmphotel.afficherH());
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"Well done sire!");
    }
    else
        QMessageBox::information(nullptr,QObject::tr("Suppression Hotel"),"ERROR MY LIEGE");
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //QString code = QString::number(ui->comboBox->currentText().toInt());
    QString code = arg1;
    QSqlQuery query;
    query.prepare("select * from destination where code='"+code+"'");
    query.exec();
    while(query.next())
    {
        ui->nom_amodifier->setText(query.value(0).toString());
        ui->description_amodifier->setText(query.value(2).toString());
        ui->promo_amodifier->setText(query.value(3).toString());
    }
}

void MainWindow::on_Modifier_clicked()
{
    int code =ui->comboBox->currentText().toInt();
    int promo = ui->promo_amodifier->text().toInt();
    QString description = ui->description_amodifier->text();
    QString nom = ui->nom_amodifier->text();
 destination d;
 bool y=d.modifier(description,nom,code,promo);
 if(y)
 {
     ui->tableView->setModel(tmpdestination.afficher());
    QMessageBox::information(nullptr,QObject::tr("Modification Destination"),"Well done sire!");
 }
 else
 {
    QMessageBox::information(nullptr,QObject::tr("Modification Destination"),"Error my liege !");
 }
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString idhotel = QString::number(arg1.toInt());
    QSqlQuery query;
    query.prepare("select * from hotel where idhotel='"+idhotel+"'");
    query.exec();
    while(query.next())
    {
        ui->nomhotel_amodifier->setText(query.value(1).toString());
        ui->adressehotel_amodifier->setText(query.value(2).toString());
        ui->etoileshotel_amodifier->setText(query.value(3).toString());
        ui->couthotel_amodifier->setText(query.value(4).toString());
    }
}

void MainWindow::on_ModifierHotel_clicked()
{
    int idhotel =ui->comboBox_2->currentText().toInt();
    int coutparnuit = ui->couthotel_amodifier->text().toInt();
    QString adresse = ui->adressehotel_amodifier->text();
    QString nom = ui->nomhotel_amodifier->text();
    int etoiles = ui->etoileshotel_amodifier->text().toInt();
 hotel h;
 bool y = h.modifier(adresse,nom,etoiles,coutparnuit,idhotel);
 if(y)
 {
     ui->comboBox_2->setModel(tmphotel.ModelidhotelHotel());
     ui->tableView2->setModel(tmphotel.afficherH());
    QMessageBox::information(nullptr,QObject::tr("Modification Hotel"),"Well done sire!");
 }
 else
 {
    QMessageBox::information(nullptr,QObject::tr("Modification Hotel"),"Error my liege !");
 }
}

void MainWindow::on_trierChercher_2_textChanged(const QString &arg1)
{
    valeur=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    etat=arg1;
    ui->tableView->setModel(tmpdestination.recherche(valeur,etat));
}

void MainWindow::on_trierChercher_textChanged(const QString &arg1)
{

    valeur=arg1;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int b=arg1;
    etat=b;
    ui->tableView2->setModel(tmphotel.recherche(valeur,etat));

}

void MainWindow::on_mail_button_clicked()
{
        Smtp* smtp = new Smtp("nooblolsaibot1@gmail.com", "haboubax", "smtp.gmail.com", 465);
        if(smtp->sendMail("nooblolsaibot1@gmail.com","oussema.benjabli@esprit.tn" , "YAAAY","MAILING T5DM"))
        QMessageBox::information(nullptr,QObject::tr("mail"),"séntmail wéll doné siré");
}




void MainWindow::on_TabDestinations_tabBarClicked(int index)
{
    int just_stop_warning = index;
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y,0);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
void MainWindow::on_pushButton_clicked()
{
    statistique * e = new statistique();
    setWindowModality(Qt::WindowModal);
    e->show();
}
