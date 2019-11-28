#ifndef HOTEL_H
#define HOTEL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>


class hotel
{
  public :
    //CONSTRUCTORS
    hotel();
    hotel(int,QString,QString,int,int);
    //GETTERS
    QString getNom(){return nom;}
    int getId_hotel(){return  idhotel;}
    QString getAdresse(){return adresse;}
    int getEtoiles(){return etoiles;}
    int getCout_par_nuit(){return coutparnuit;}
    //SETTERS
    void setNom(QString nom){this->nom=nom;}
    void setEtoiles(int etoiles){this->etoiles=etoiles;}
    void setAdresse(QString adresse){this->adresse=adresse;}
    void setiIdhotel(int idhotel){this->idhotel=idhotel;}
    void setCoutparnuit(int coutparnuit){this->coutparnuit=coutparnuit;}

    //CRUD
    bool ajouterH();
    bool supprimer(int);
    bool modifier(QString adresse, QString nom, int etoiles, int coutparnuit,int idhotel);
   QSqlQueryModel * afficherH();
   QSqlQueryModel * ModelidhotelHotel();
   //
   QSqlQueryModel * recherche(QString valeur,int etat);

private :
    QString nom,adresse;
    int etoiles,idhotel;
    int coutparnuit;
};

#endif // HOTEL_H
