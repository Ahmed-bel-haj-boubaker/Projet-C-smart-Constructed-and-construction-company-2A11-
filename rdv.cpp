#include "rdv.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QDate>

Rdv::Rdv()

{
id_rdv=0; date_rdv=QDate::currentDate(); heure_rdv=0;IDCLIENT=0;

}
Rdv::Rdv(int id_rdv,QDate date_rdv ,int heure_rdv,int IDCLIENT)
{this->id_rdv=id_rdv; this->date_rdv=date_rdv; this->heure_rdv=heure_rdv;this->IDCLIENT=IDCLIENT;}
int Rdv::getid_rdv(){return id_rdv;}
QDate Rdv::getdate_rdv(){return date_rdv;}
int Rdv::getheure_rdv(){return heure_rdv;}
int Rdv::getIDCLIENT(){return IDCLIENT;}


void Rdv::setid_rdv(int id_rdv){this->id_rdv=id_rdv;}
void Rdv::setdate_rdv(QDate date_rdv){this->date_rdv=date_rdv;}
void Rdv::setheure_rdv(int heure_rdv){this->heure_rdv=heure_rdv;}
void Rdv::setIDCLIENT(int IDCLIENT){this->IDCLIENT=IDCLIENT;}


bool Rdv::ajouter1()
{
    QSqlQuery query;
    QString id_rdv_string=QString::number(id_rdv);
    QString heure_rdv_string=QString::number(heure_rdv);
    QString idclientt=QString::number(IDCLIENT);

          query.prepare("INSERT INTO RENDEZ_VOUS (ID_RDV,DATE_RDV,HEURE_RDV,IDCLIENT) "
                        "VALUES (:ID_RDV, :DATE_RDV, :HEURE_RDV, :IDCLIENT)");
          query.bindValue(":ID_RDV",id_rdv_string);
          query.bindValue(":DATE_RDV", date_rdv);
          query.bindValue(":HEURE_RDV", heure_rdv_string);
          query.bindValue(":IDCLIENT", idclientt);




    return query.exec();
}

QSqlQueryModel* Rdv::afficher1()
{
    QSqlQueryModel* model1 =new QSqlQueryModel();

          model1->setQuery("select * from RENDEZ_VOUS");
          model1->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_RDV"));
          model1->setHeaderData(1,Qt::Horizontal, QObject::tr("DATE_RDV"));
           model1->setHeaderData(2,Qt::Horizontal, QObject::tr("HEURE_RDV"));
           model1->setHeaderData(3,Qt::Horizontal, QObject::tr("IDCLIENT"));


    return model1 ;
}

bool Rdv::supprimer1(int id_rdv)
{
    QSqlQuery query;

          QString res=QString::number(id_rdv);

        query.prepare("Delete from RENDEZ_VOUS where ID_RDV=:ID_RDV");

        query.bindValue(":ID_RDV", res);

         return query.exec();
}

bool Rdv::modifierRdv(int id_rdv,QDate date_rdv,int heure_rdv){
    QSqlQuery query;
    QString id_rdv_string=QString::number(id_rdv);
    QString heure_rdv_string=QString::number(heure_rdv);

       query.prepare(" UPDATE RENDEZ_VOUS set id_rdv=:ID_RDV ,date_rdv=:DATE_RDV, heure_rdv=:HEURE_RDV where id_rdv=:ID_RDV ");
       query.bindValue(":ID_RDV", id_rdv_string);
       query.bindValue(":DATE_RDV", date_rdv);
       query.bindValue(":HEURE_RDV",heure_rdv_string);

       return query.exec();
}
