#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
Fournisseur::Fournisseur()
{
id_fournisseur=0; nom_fournisseur=" "; prenom_fournisseur=" "; adresse_fournisseur=" ";num_tel_fournisseur=0;email_fournisseur=" ";
}
Fournisseur::Fournisseur(int id_fournisseur,QString nom_fournisseur,QString prenom_fournisseur,QString adresse_fournisseur,int num_tel_fournisseur,QString email_fournisseur)
{this->id_fournisseur=id_fournisseur; this->nom_fournisseur=nom_fournisseur; this->prenom_fournisseur=prenom_fournisseur; this->adresse_fournisseur=adresse_fournisseur;this->num_tel_fournisseur=num_tel_fournisseur;this->email_fournisseur=email_fournisseur;}
int Fournisseur::getid_fournisseur(){return id_fournisseur;}
QString Fournisseur::getnom_fournisseur(){return nom_fournisseur;}
QString Fournisseur::getprenom_fournisseur(){return prenom_fournisseur;}
QString Fournisseur::getadresse_fournisseur(){return adresse_fournisseur;}
int Fournisseur::getnum_tel_fournisseur(){return num_tel_fournisseur;}
QString Fournisseur::getemail_fournisseur(){return email_fournisseur;}
void Fournisseur::setid_fournisseur(int id_fournisseur){this->id_fournisseur=id_fournisseur;}
void Fournisseur::setnom_fournisseur(QString nom_fournisseur){this->nom_fournisseur=nom_fournisseur;}
void Fournisseur::setprenom_fournisseur(QString prenom_fournisseur){this->prenom_fournisseur=prenom_fournisseur;}
void Fournisseur::setadresse_fournisseur(QString adresse_fournisseur){this->adresse_fournisseur=adresse_fournisseur;}
void Fournisseur::setnum_tel_fournisseur(int  num_tel_fournisseur){this->num_tel_fournisseur=num_tel_fournisseur;}
void Fournisseur::setemail_fournisseur(QString email_fournisseur){this->email_fournisseur=email_fournisseur;}

bool Fournisseur::ajouter()
{
    QSqlQuery query;
    QString id_fournisseur_string=QString::number(id_fournisseur);
QString num_tel_fournisseur_string=QString::number(num_tel_fournisseur);
         query.prepare("INSERT INTO fournisseur (id_fournisseur,nom_fournisseur,prenom_fournisseur,adresse_fournisseur,num_tel_fournisseur,email_fournisseur) "
                       "VALUES (:id, :forename,:surname, :adresse, :num_tel, :email)");
         query.bindValue(":id", id_fournisseur_string);
         query.bindValue(":forename", nom_fournisseur);
         query.bindValue(":surname", prenom_fournisseur);
         query.bindValue(":adresse", adresse_fournisseur);

         query.bindValue(":num_tel", num_tel_fournisseur_string);
         query.bindValue(":email", email_fournisseur);
return query.exec();
}
bool Fournisseur::supprimer(int id_fournisseur)
{
    QSqlQuery query;

         query.prepare("Delete from fournisseur where id_fournisseur=:id_fournisseur");
         query.bindValue(":id_fournisseur", id_fournisseur);

         return query.exec();
}
QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

          model->setQuery("SELECT * FROM fournisseur");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_fournisseur"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("nom_fournisseur"));
           model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom_fournisseur"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("adresse_fournisseur"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("num_tel_fournisseur"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("email_fournisseur"));

    return model ;

}
bool Fournisseur::modifierFournisseur(int id_fournisseur,QString nom_fournisseur,QString prenom_fournisseur,QString adresse_fournisseur,int num_tel_fournisseur,QString email_fournisseur)

{


    QSqlQuery query;

    query.prepare("update FOURNISSEUR set id_fournisseur=:id_fournisseur,nom_fournisseur=:nom_fournisseur,prenom_fournisseur=:prenom_fournisseur,adresse_fournisseur=:adresse_fournisseur,num_tel_fournisseur=:num_tel_fournisseur,email_fournisseur=:email_fournisseur where id_fournisseur=:id_fournisseur");

    query.bindValue(":id_fournisseur",id_fournisseur);
    query.bindValue(":nom_fournisseur",nom_fournisseur);

    query.bindValue(":prenom_fournisseur",prenom_fournisseur);

    query.bindValue(":adresse_fournisseur",adresse_fournisseur);
    query.bindValue(":num_tel_fournisseur",num_tel_fournisseur);
    query.bindValue(":email_fournisseur",email_fournisseur);



    return query.exec();


}





