#include "employer.h"
#include <QtDebug>
#include <QString>
#include <QSqlQuery>
#include<QObject>
#include<QSqlQueryModel>
#include<QTableView>
#include <QFloat16>
#include<QtWidgets>
#include<QtDesigner/QDesignerActionEditorInterface>
#include<mainwindow.h>
employer::employer()
{
    id_employer=0;
    nom="";
    prenom="";
    adresse="";
    email="";
    mdp="";
}
employer::employer(int id_employer,QString nom,QString prenom,QString adresse,QString email ,QString mdp)
{
    this->id_employer=id_employer;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->email=email;
    this->mdp=mdp;

}

int employer::getID(){return id_employer;}
QString employer::getNom(){return nom;}
QString employer::getPrenom(){return prenom;}
QString employer::getAdresse(){return adresse;}
QString employer::getEmail(){return email;}
QString employer::getMDP(){return mdp;}

void employer::setID(int id_employer){this->id_employer=id_employer;}
void employer::setNom(QString nom){this->nom=nom;}
void employer::setPrenom(QString prenom){this->prenom=prenom;}
void employer::setAdresse(QString adresse){this->adresse=adresse;}
void employer::setEmail(QString email){this->email=email;}
void employer::setMDP(QString mdp){this->mdp=mdp;}


bool employer::ajouter(int id_employer,QString nom,QString prenom,QString adresse,QString email ,QString mdp)
{

    QSqlQuery query;
       QString res = QString::number(id_employer);

    query.prepare("INSERT INTO EMPLOYER(id_employer,nom,prenom,adresse,email,mdp) "
                  "VALUES (:id_employer,:nom,:prenom,:adresse,:email,:mdp)");
    query.bindValue(":id_employer",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":email",email);
    query.bindValue(":mdp",mdp);
    return query.exec();

}


int  employer::chercher_employer_id(QString D)
 {

       employer E;

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT * FROM employer  WHERE  id_employer=:D");
        checkQuery.bindValue(":D",D);

        if (checkQuery.exec())
        {qDebug() << "employer trouver:" ;

            if (checkQuery.next())
            {
              return  checkQuery.value(3).toInt();




            }
        }


 qDebug() << "employer n'est pas trouver:";
return 100;
      }
