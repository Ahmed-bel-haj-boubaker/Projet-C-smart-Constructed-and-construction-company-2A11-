
#include "materiel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlTableModel>
#include <QString>
Materiel::Materiel()
{
ID_PRODUIT=0;QUANTITER=0;NOM_PRODUIT="";PRIX_PRODUIT=0;REMISE=0;
}

Materiel::Materiel(int ID_PRODUIT,int QUANTITER,QString NOM_PRODUIT,float PRIX_PRODUIT,int REMISE)
{ this->ID_PRODUIT=ID_PRODUIT;
    this->QUANTITER=QUANTITER;
    this->NOM_PRODUIT=NOM_PRODUIT;
    this->PRIX_PRODUIT=PRIX_PRODUIT;
    this->REMISE=REMISE;}

int Materiel::getID_PRODUIT(){return ID_PRODUIT;}

int Materiel::getQUANTITER(){return QUANTITER;}

QString Materiel::getNOM_PRODUIT() {return NOM_PRODUIT;}
float Materiel::getPRIX_PRODUIT(){return PRIX_PRODUIT;}
int Materiel::getREMISE(){return REMISE;}
void Materiel::setID_PRODUIT(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
void Materiel::setQUANTITER(int QUANTITER){this->QUANTITER=QUANTITER;}
void Materiel::setNOM_PRODUIT(QString NOM_PRODUIT){this->NOM_PRODUIT=NOM_PRODUIT;}
void Materiel::setPRIX_PRODUIT(float PRIX_PRODUIT){this->PRIX_PRODUIT=PRIX_PRODUIT;}
void Materiel::setREMISE(int REMISE){this->REMISE=REMISE;}


bool Materiel::ajouter()
{
   QSqlQuery query;
    QString ID_PRODUIT_string= QString::number(ID_PRODUIT);
    QString QUANTITER_string= QString::number(QUANTITER);
    QString PRIX_PRODUIT_string=QString::number(PRIX_PRODUIT);
    QString REMISE_string= QString::number(REMISE);
    query.prepare("INSERT INTO MATERIELLES (ID_PRODUIT, QUANTITER, NOM_PRODUIT,PRIX_PRODUIT,REMISE) "
                  "VALUES (:ID_PRODUIT,:QUANTITER,:NOM_PRODUIT,:PRIX_PRODUIT,:REMISE )");
    query.bindValue(":ID_PRODUIT",ID_PRODUIT_string);
    query.bindValue(":QUANTITER",QUANTITER_string);
    query.bindValue(":NOM_PRODUIT", NOM_PRODUIT);
    query.bindValue(":PRIX_PRODUIT",PRIX_PRODUIT_string);
    query.bindValue(":REMISE", REMISE_string);
   return   query.exec();
}
bool Materiel::supprimer(int ID_PRODUIT )
{
    QSqlQuery query;
    query.prepare("Delete from MATERIELLES where ID_PRODUIT=:ID_PRODUIT");
    query.bindValue(0, ID_PRODUIT);
     return   query.exec();

}
QSqlQueryModel* Materiel::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT * FROM MATERIELLES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PRODUIT"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITER"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_PRODUIT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("REMISE"));


    return model;
}



bool Materiel::modifier(int ID_PRODUIT,int QUANTITER,QString NOM_PRODUIT,float PRIX_PRODUIT,int REMISE){
     QSqlQuery query;
     QString ID_PRODUIT_string= QString::number(ID_PRODUIT);
     QString QUANTITER_string= QString::number(QUANTITER);
     QString PRIX_PRODUIT_string=QString::number(PRIX_PRODUIT);
     QString REMISE_string= QString::number(REMISE);
        query.prepare(" UPDATE MATERIELLES set ID_PRODUIT=:ID_PRODUIT ,QUANTITER=:QUANTITER, NOM_PRODUIT=:NOM_PRODUIT ,PRIX_PRODUIT=:PRIX_PRODUIT, REMISE=:REMISE where ID_PRODUIT=:ID_PRODUIT");
        query.bindValue(":ID_PRODUIT",ID_PRODUIT_string);
        query.bindValue(":QUANTITER",QUANTITER_string);
        query.bindValue(":NOM_PRODUIT", NOM_PRODUIT);
        query.bindValue(":PRIX_PRODUIT",PRIX_PRODUIT_string);
        query.bindValue(":REMISE", REMISE_string);
        return query.exec();
 }
QSqlQueryModel * Materiel::Recherche(QString a)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATERIELLES WHERE (ID_PRODUIT LIKE '%"+a+"%' OR QUANTITER LIKE '%"+a+"%' OR NOM_PRODUIT LIKE '%"+a+"%' OR PRIX_PRODUIT LIKE '%"+a+"%' OR REMISE LIKE '%"+a+"%'  ) ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("QUANTITER"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("REMISE"));
    return model;
}
//Trie Par id
/*QSqlQueryModel * Materiel::trierMaterielParid()
{

    QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from  MATERIELLES ORDER BY ID_PRODUIT ASC");

        model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_PRODUIT"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("QUANTITER"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("REMISE"));

   return model;
}
QSqlQueryModel *  Materiel::trierMaterielParNom()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  MATERIELLES ORDER BY NOM_PRODUIT ASC ");

    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("QUANTITER"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("REMISE"));
return model;
}
//Trie Par prix
QSqlQueryModel * Materiel::trierMaterielParprix()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  MATERIELLES ORDER BY PRIX_PRODUIT ASC ");

    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("QUANTITER"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("REMISE"));
return model;
}*/
//Trie Par id
QSqlQueryModel * Materiel::trierMaterielParid()
{

   /* QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM MATERIELLES order by ID_PRODUIT ASC");
           q->exec();
           model->setQuery(*q);
           return model;
           */
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM MATERIELLES  order by ID_PRODUIT ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITER"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_PRODUIT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("REMISE"));


        return model;
}

//Trie Par Nom
QSqlQueryModel * Materiel::trierMaterielParNom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM MATERIELLES order by NOM_PRODUIT ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

//Trie Par prix
QSqlQueryModel * Materiel::trierMaterielParprix()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM MATERIELLES order by PRIX_PRODUIT ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}





