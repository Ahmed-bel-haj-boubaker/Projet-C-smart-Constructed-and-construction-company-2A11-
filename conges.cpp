#include "conges.h"

conges::conges(QString nom,QString responsable,QString type,QDate date_d,QDate date_f,int nbr,QString commentaire,QString acceptation)
{
    this->nom=nom;
    this->responsable=responsable;
    this->type=type;
    this->date_d=date_d;
    this->date_f=date_f;
    this->nbr=nbr;
    this->commentaire=commentaire;
    this->acceptation=acceptation;
}


bool  conges::ajouter_a()
{
    QSqlQuery query;
    QString res = QString::number(nbr);

    query.prepare("insert into conge (nom,responsable,type,date_d,date_f,nbr,commentaire,acceptation)" "values (:nom, :responsable, :type, :date_d, :date_f, :nbr, :commentaire, :acceptation)");

    query.bindValue(":nom" ,nom);
    query.bindValue(":responsable" ,responsable);
    query.bindValue(":type" ,type);
    query.bindValue(":date_d" ,date_d);
    query.bindValue(":date_f" ,date_f);
    query.bindValue(":nbr" ,res);
    query.bindValue(":commentaire" ,commentaire);
    query.bindValue(":acceptation" ,acceptation);


    return query.exec();

}
QSqlQueryModel * conges::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from conge");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("responsable"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_d"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_f"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nbr"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("commentaire"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("acceptation"));

    return model;
}



QSqlQueryModel * conges::afficherRech(QString rech,QString critere)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from conge where "+critere+" like '"+rech+"%'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("responsable"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_d"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_f"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("nbr"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("commentaire"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("acceptation"));
return model;
}
