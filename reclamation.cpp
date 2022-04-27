#include "reclamation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>

Reclamation::Reclamation()
{
id_reclamation=0; nom_reclamation=" "; date_reclamation=" "; produit=" "; probleme=" "; id_client=" ";
}
Reclamation::Reclamation(int id_reclamation,QString nom_reclamation,QString date_reclamation,QString produit,QString probleme,QString id_client)
{this->id_reclamation=id_reclamation; this->nom_reclamation=nom_reclamation; this->date_reclamation=date_reclamation; this->produit=produit;this->probleme=probleme;this->id_client=id_client;}
int Reclamation::getid_reclamation(){return id_reclamation;}
QString Reclamation::getnom_reclamation(){return nom_reclamation;}
QString Reclamation::getdate_reclamation(){return date_reclamation;}
QString Reclamation::getproduit(){return produit;}
QString Reclamation::getprobleme(){return probleme;}
QString Reclamation::getid_client(){return id_client;}
void Reclamation::setid_reclamation(int id_reclamation){this->id_reclamation=id_reclamation;}
void Reclamation::setnom_reclamation(QString nom_reclamation){this->nom_reclamation=nom_reclamation;}
void Reclamation::setdate_reclamation(QString date_reclamation){this->date_reclamation=date_reclamation;}
void Reclamation::setproduit(QString produit){this->produit=produit;}
void Reclamation::setprobleme(QString probleme){this->probleme=probleme;}
void Reclamation::setid_client(QString id_client){this->id_client=id_client;}

bool Reclamation::ajouter()
{
    QSqlQuery query;
    QString id_reclamation_string=QString::number(id_reclamation);


         query.prepare("INSERT INTO reclamation (id_reclamation,nom_reclamation,date_reclamation,produit,probleme,id_client) "
                       "VALUES (:id, :forename,:surname, :produit, :probleme ,:id_client)");
          query.bindValue(":id", id_reclamation_string);
         query.bindValue(":nom_reclamation", nom_reclamation);
         query.bindValue(":date_reclamation", date_reclamation);
         query.bindValue(":produit", produit);
         query.bindValue(":probleme", probleme);
         query.bindValue(":id_client", id_client);
return query.exec();
}
bool Reclamation::supprimer(int id_reclamation)
{
    QSqlQuery query;

         query.prepare("Delete from reclamation where id_reclamation=:id_reclamation");
         query.bindValue(":id_reclamation", id_reclamation);

         return query.exec();
}
QSqlQueryModel* Reclamation::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

          model->setQuery("SELECT * FROM reclamation");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_reclamation"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("nom_reclamation"));
           model->setHeaderData(1, Qt::Horizontal,QObject::tr("date_reclamation"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("produit"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("probleme"));
             model->setHeaderData(1, Qt::Horizontal,QObject::tr("id_client"));

    return model ;

}
bool Reclamation::modifierReclamation(int id_reclamation,QString nom_reclamation,QString date_reclamation,QString produit,QString probleme ,QString id_client)

{


    QSqlQuery query;

    query.prepare("update RECLAMATION set id_reclamation=:id_reclamation,nom_reclamation=:nom_reclamation,date_reclamation=:date_reclamation,produit=:produit,probleme=:probleme ,id_client=:id_client where id_reclamation=:id_reclamation");

    query.bindValue(":id_reclamation",id_reclamation);
    query.bindValue(":nom_reclamation",nom_reclamation);

    query.bindValue(":date_reclamation",date_reclamation);

    query.bindValue(":produit",produit);

    query.bindValue(":probleme",probleme);
      query.bindValue(":id_client",id_client);



    return query.exec();


}





