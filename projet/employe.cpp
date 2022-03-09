#include "employe.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>

employe::employe()
{
  id_employe=0;nom_employe=" "; prenom_employe=" "; adresse_employe=" "; num_employe=0; email_employe=" ";
}

employe::employe(int id_employe ,QString nom_employe , QString prenom_employe,QString adresse_employe,int num_employe,QString email_employe)
{ this->id_employe = id_employe ;
    this ->nom_employe=nom_employe;
    this ->prenom_employe=prenom_employe;
    this ->adresse_employe=adresse_employe;
    this ->num_employe=num_employe ;
    this ->email_employe=email_employe ;}
int employe::getid_employe() { return id_employe;}
QString employe::getnom_employe() {return nom_employe;}
QString employe::getprenom_employe() { return prenom_employe;}
QString employe::getadresse_employe() { return adresse_employe;}
int employe::getnum_employe() { return num_employe;}
QString employe::getemail_employe() { return email_employe;}

void employe::setid_employe(int id_employe) {this->id_employe = id_employe; }
void employe::setnom_employe(QString nom_employe ) {this ->nom_employe=nom_employe; }
void employe::setprenom_employe(QString prenom_employe) {this ->prenom_employe=prenom_employe; }
void employe::setadresse_employe(QString adresse_employe ) { this ->adresse_employe=adresse_employe;}
void employe::setnum_employe(int num_employe ) { this ->num_employe=num_employe ; }
void employe::setemail_employe(QString email_employe) { this ->email_employe=email_employe; }


bool employe::ajouter()
{
 bool test=false;

 QSqlQuery query;
 QString id_string= QString::number(id_employe);
 QString numempl_string= QString::number(num_employe);

     query.prepare("INSERT INTO employe (ID_EMPLOYE, NOM_EMPLOYE,PRENOM_EMPLOYE, ADRESSE_EMPLOYE,NUM_EMPLOYE,EMAIL_EMPLOYE) "
                     "VALUES (:ID_EMPLOYE, :NOM_EMPLOYE,:PRENOM_EMPLOYE, :ADRESSE_EMPLOYE,:NUM_EMPLOYE,:EMAIL_EMPLOYE)");
       query.bindValue(":ID_EMPLOYE", id_string);
       query.bindValue(":NOM_EMPLOYE", nom_employe);
       query.bindValue(":PRENOM_EMPLOYE", prenom_employe);
        query.bindValue(":ADRESSE_EMPLOYE", adresse_employe);

        query.bindValue(":NUM_EMPLOYE", numempl_string);
        query.bindValue(":EMAIL_EMPLOYE", email_employe);


       query.exec();

 return test;

}
QSqlQueryModel* employe::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM EMPLOYE");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_EMPLOYE"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_EMPLOYE"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_EMPLOYE"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE_EMPLOYE"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("NUM_EMPLOYE"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("EMAIL_EMPLOYE"));



return model;
}

bool employe::supprimer(int id_employe){
      QSqlQuery query;
      QString res=QString::number(id_employe);
    query.prepare("Delete from FACTURE where ID_FACTURE=:ID_FACTURE");
    query.bindValue(":ID_EMPLOYE", res);

    return  query.exec();

}


bool employe::modifier(int,QString, QString, QString, QString, int, QString) {
    QSqlQuery query;
    QString id_string= QString::number(id_employe);
    QString numempl_string= QString::number(num_employe);

        query.prepare("INSERT INTO employe (ID_EMPLOYE, NOM_EMPLOYE,PRENOM_EMPLOYE, ADRESSE_EMPLOYE,NUM_EMPLOYE,EMAIL_EMPLOYE) "
                        "VALUES (:ID_EMPLOYE, :NOM_EMPLOYE,:PRENOM_EMPLOYE, :ADRESSE_EMPLOYE,:NUM_EMPLOYE,:EMAIL_EMPLOYE)");
          query.bindValue(":ID_EMPLOYE", id_string);
          query.bindValue(":NOM_EMPLOYE", nom_employe);
          query.bindValue(":PRENOM_EMPLOYE", prenom_employe);
           query.bindValue(":ADRESSE_EMPLOYE", adresse_employe);

           query.bindValue(":NUM_EMPLOYE", numempl_string);
           query.bindValue(":EMAIL_EMPLOYE", email_employe);

       return query.exec();
}

//Test Ajout Fichier Tutoriel Git
