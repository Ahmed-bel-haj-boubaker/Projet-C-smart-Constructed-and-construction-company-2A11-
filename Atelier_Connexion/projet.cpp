#include "projet.h"
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
projet::projet()
{
id_projet=0; nom_projet="";localisation="",l1=0,l2=0,p1=0,p2=0,h1=0,t=0;

}
projet::projet(int id_projet,QString nom_projet,QString localisation, QDate date_deb ,QDate date_fin,int l1,int l2,int p1,int p2,int h1,int t)
{
    this->id_projet=id_projet;
   this->nom_projet=nom_projet;
    this->localisation=localisation;
    this->date_deb=date_deb;
    this->date_fin=date_fin;
    this->l1=l1;
    this->l2=l2;
    this->p1=p1;
    this->p2=p2;
    this->h1=h1;
    this->t=t;
}

int projet::getid(){return id_projet;}

QString projet:: getnom_projet(){return nom_projet;}
QString projet::getlocalisation(){return localisation;}
QDate projet:: getDate_deb(){return date_deb;}
QDate projet:: getDate_fin(){return date_fin;}
int projet::getL1(){return l1;}
int projet::getL2(){return l2;}
int projet::getP1(){return p1;}
int projet::getP2(){return p2;}
int projet::getH1(){return h1;}
int projet::getT(){return t;}
void projet::setid(int id_projet){this->id_projet=id_projet;}
void projet::setnom_projet(QString nom_projet){ this->nom_projet=nom_projet;}
void projet::setlocalisation(QString localisation){ this->localisation=localisation;}
void projet::setDate_deb(QDate date_deb){this->date_deb=date_deb;}
void projet::setDate_fin(QDate date_fin){this->date_fin=date_fin;}
void projet::setL1(int l1){this->l1=l1;}
void projet::setL2(int l2){this->l2=l2;}
void projet::setP1(int p1){this->p1=p1;}
void projet::setP2(int p2){this->p2=p2;}
void projet::setH1(int h1){this->h1=h1;}
void projet::setT(int t){this->t=t;}




bool projet::ajouter()
{

    QSqlQuery query;
       QString res = QString::number(id_projet);

    query.prepare("INSERT INTO PROJET(id_projet,nom_projet,localisation, date_deb,date_fin,l1,l2,p1,p2,h1,t) "
                  "VALUES (:id_projet,:nom_projet,:localisation, :date_deb,:date_fin,:l1,:l2,:p1,:p2,:h1,:t)");
    query.bindValue(":id_projet",res);
    query.bindValue(":nom_projet",nom_projet);
    query.bindValue(":localisation",localisation);
    query.bindValue(":date_deb",date_deb);
    query.bindValue(":date_fin",date_fin);
    query.bindValue(":l1",l1);
    query.bindValue(":l2",l2);
    query.bindValue(":p1",p1);
    query.bindValue(":p2",p2);
    query.bindValue(":h1",h1);
    query.bindValue(":t",t);
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

bool projet::modifier(int id_projet,QString nom_projet,QString localisation, QDate date_deb ,QDate date_fin,int l1,int l2,int p1,int p2,int h1,int t)
{
 QSqlQuery query;
    QString res= QString::number(id_projet);

    query.prepare("UPDATE PROJET SET nom_projet=:nom_projet,localisation=:localisation,date_deb=:date_deb,date_fin=:date_fin,l1=:l1,l2=:l2,p1=:p1,p2=:p2,h1=:h1,t=:t WHERE id_projet=:id_projet");
    query.bindValue(":id_projet",res);
    query.bindValue(":nom_projet",nom_projet);
    query.bindValue(":localisation",localisation);
    query.bindValue(":date_deb",date_deb);
    query.bindValue(":date_fin",date_fin);
    query.bindValue(":l1",l1);
    query.bindValue(":l2",l2);
    query.bindValue(":p1",p1);
    query.bindValue(":p2",p2);
    query.bindValue(":h1",h1);
    query.bindValue(":t",t);
    return    query.exec();

}
QSqlQueryModel * projet::rechercher(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from projet where id_projet like '%"+search+"%' or nom_projet like '%"+search+"%' or localisation like '%"+search+"%'";

    model->setQuery(qry);
    return model;
}
QSqlQueryModel *projet::tri_idP()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  projet ORDER BY id_projet");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom projet"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("Localisation"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date debut"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("Date fin"));
return model;
 }

 QSqlQueryModel *projet::tri_place()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  projet ORDER BY localisation ");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom projet"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("Localisation"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date debut"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("Date fin"));
return model;
 }

 QSqlQueryModel *projet::tri_nomP()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  projet ORDER BY nom_projet");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom projet"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("Localisation"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date debut"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("Date fin"));
return model;
 }

/* QSqlQueryModel * projet::filtre_nomP(QString filtre)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     QString qry="select * from projet where nom_projet like '%"+filtre+"%'";

     model->setQuery(qry);
     return model;
}*/
