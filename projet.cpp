#include "projet.h"
#include <QtDebug>
#include <QString>
#include <QSqlQuery>
#include<QObject>
#include<QSqlQueryModel>
#include<QTableView>

projet::projet()
{
id_projet=0; nom_projet="";localisation="";

}
projet::projet(int id_projet,QString nom_projet,QString localisation, QDate date_deb ,QDate date_fin)
{
    this->id_projet=id_projet;
   this->nom_projet=nom_projet;
    this->localisation=localisation;
    this->date_deb=date_deb;
    this->date_fin=date_fin;
}

int projet::getid(){return id_projet;}

QString projet:: getnom_projet(){return nom_projet;}
QString projet::getlocalisation(){return localisation;}
QDate projet:: getDate_deb(){return date_deb;}
QDate projet:: getDate_fin(){return date_fin;}

void projet::setid(int id_projet){this->id_projet=id_projet;}
void projet::setnom_projet(QString nom_projet){ this->nom_projet=nom_projet;}
void projet::setlocalisation(QString localisation){ this->localisation=localisation;}
void projet::setDate_deb(QDate date_deb){this->date_deb=date_deb;}
void projet::setDate_fin(QDate date_fin){this->date_fin=date_fin;}


bool projet::ajouter()
{

    QSqlQuery query;
       QString res = QString::number(id_projet);

    query.prepare("INSERT INTO PROJET(id_projet,nom_projet,localisation, date_deb,date_fin) "
                  "VALUES (:id_projet,:nom_projet,:localisation, :date_deb,:date_fin)");
    query.bindValue(":id_projet",res);
    query.bindValue(":nom_projet",nom_projet);
    query.bindValue(":localisation",localisation);
    query.bindValue(":date_deb",date_deb);
  query.bindValue(":date_fin",date_fin);
    return query.exec();

}
QSqlQueryModel* projet::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM projet");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom projet"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Localisation"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date debut"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("Date fin"));


return model;
}
bool projet::supprimer(int id_projet)
{
    query.prepare("DELETE FROM PROJET WHERE id_projet=:id_projet");
    query.bindValue(":id_projet",id_projet);

    return query.exec();
}

bool projet::modifier(int id_projet)
{
 QSqlQuery query;
    QString res= QString::number(id_projet);

    query.prepare("UPDATE PROJET SET nom_projet=:nom_projet,localisation=:localisation,date_deb=:date_deb,date_fin=:date_fin WHERE id_projet=:id_projet");
    query.bindValue(":id_projet",res);
    query.bindValue(":nom_projet",nom_projet);
    query.bindValue(":localisation",localisation);
    query.bindValue(":date_deb",date_deb);
    query.bindValue(":date_fin",date_fin);
    return    query.exec();

}
QSqlQueryModel * projet::rechercher(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from projet where id_projet like '%"+search+"%' or nom_projet like '%"+search+"%' or localisation like '%"+search+"%'";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}
