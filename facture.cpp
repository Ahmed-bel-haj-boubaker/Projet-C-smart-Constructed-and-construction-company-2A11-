#include "facture.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QtMath>
Facture::Facture()
{
  id_facture=0;nom_facture=" "; prenom_facture=" "; date_facture=" "; prix_produit=0; prix_projet=0; montant_total=0;
}

Facture::Facture(int id_facture ,QString nom_facture , QString prenom_facture,QString date_facture,float prix_produit,float prix_projet,float montant_total)
{ this->id_facture = id_facture ;
    this ->nom_facture=nom_facture;
    this ->prenom_facture=prenom_facture;
    this ->date_facture=date_facture;
    this ->prix_produit=prix_produit ;
    this ->prix_projet=prix_projet ;
    this->montant_total=montant_total; }
int Facture::getid_facture() { return id_facture;}
QString Facture::getnom_facture() {return nom_facture;}
QString Facture::getprenom_facture() { return prenom_facture;}
QString Facture::getdate_facture() { return date_facture;}
float Facture::getprix_produit() { return prix_produit;}
float Facture::getprix_projet() { return prix_projet;}
float Facture::getmontant_total() { return montant_total;}

void Facture::setid_facture(int id_facture) {this->id_facture = id_facture; }
void Facture::setnom_facture(QString nom_facture ) {this ->nom_facture=nom_facture; }
void Facture::setprenom_facture(QString prenom_facture) {this ->prenom_facture=prenom_facture; }
void Facture::setdate_facture(QString date_facture ) { this ->date_facture=date_facture ;}
void Facture::setprix_produit(float prix_produit ) { this ->prix_produit=prix_produit ; }
void Facture::setprix_projet(float prix_projet ) { this ->prix_projet=prix_projet ; }
void Facture::setmontant_total(float montant_total) {this ->montant_total=montant_total ; }


bool Facture::ajouter(int id_facture ,QString nom_facture , QString prenom_facture,QString date_facture,float prix_produit,float prix_projet,float montant_total)
{

 QSqlQuery query;

 QString id_string= QString::number(id_facture);
 QString prixprod_string= QString::number(prix_produit);
 QString prixproj_string= QString::number(prix_projet);
 QString monttot_string= QString::number(montant_total);

     query.prepare("INSERT INTO FACTURE (ID_FACTURE, NOM_FACTURE,PRENOM_FACTURE, DATE_FACTURE,PRIX_PRODUIT,PRIX_PROJET,MONTANT_TOTAL) "
                     "VALUES (:ID_FACTURE, :NOM_FACTURE,:PRENOM_FACTURE, :DATE_FACTURE,:PRIX_PRODUIT,:PRIX_PROJET,:MONTANT_TOTAL)");
       query.bindValue(":ID_FACTURE", id_string);
       query.bindValue(":NOM_FACTURE", nom_facture);
       query.bindValue(":PRENOM_FACTURE", prenom_facture);
        query.bindValue(":DATE_FACTURE", date_facture);
        query.bindValue(":PRIX_PRODUIT", prixprod_string);
        query.bindValue(":PRIX_PROJET", prixproj_string);
         query.bindValue(":MONTANT_TOTAL", monttot_string);




 return query.exec();

}
QSqlQueryModel* Facture::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM FACTURE");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FACTURE"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_FACTURE"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_FACTURE"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("DATE_FACTURE"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRIX_PROJET"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));


return model;
}

bool Facture::supprimer(int id_facture){
      QSqlQuery query;
      QString res=QString::number(id_facture);
    query.prepare("Delete from FACTURE where ID_FACTURE=:ID_FACTURE");
    query.bindValue(":ID_FACTURE", res);

    return  query.exec();

}


bool Facture::modifier(int id_facture, QString nom_facture, QString prenom_facture, QString date_facture, float prix_produit, float prix_projet, float montant_total) {
    QSqlQuery query;
    QString id_string= QString::number(id_facture);
    QString prixprod_string= QString::number(prix_produit);
    QString prixproj_string= QString::number(prix_projet);
    QString monttot_string= QString::number(montant_total);
       query.prepare(" UPDATE FACTURE set ID_FACTURE=:ID_FACTURE ,NOM_FACTURE=:NOM_FACTURE,PRENOM_FACTURE=:PRENOM_FACTURE ,DATE_FACTURE=:DATE_FACTURE, PRIX_PRODUIT=:PRIX_PRODUIT, PRIX_PROJET=:PRIX_PROJET, MONTANT_TOTAL=:MONTANT_TOTAL where ID_FACTURE=:ID_FACTURE");
       query.bindValue(":ID_FACTURE", id_string);
       query.bindValue(":NOM_FACTURE", nom_facture);
       query.bindValue(":PRENOM_FACTURE", prenom_facture);
        query.bindValue(":DATE_FACTURE", date_facture);

        query.bindValue(":PRIX_PRODUIT", prixprod_string);
        query.bindValue(":PRIX_PROJET", prixproj_string);
         query.bindValue(":MONTANT_TOTAL", monttot_string);
       return query.exec();
}
QSqlQueryModel * Facture::rechercher(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from FACTURE where ID_FACTURE like '%"+search+"%' or NOM_FACTURE like '%"+search+"%' or MONTANT_TOTAL like '%"+search+"%'";

    model->setQuery(qry);
    return model;
}
QSqlQueryModel *Facture::tri_idP()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  FACTURE ORDER BY ID_FACTURE");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FACTURE"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_FACTURE"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_FACTURE"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("DATE_FACTURE"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
     model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRIX_PROJET"));
     model->setHeaderData(6, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));
return model;
 }

 QSqlQueryModel *Facture::tri_Mon()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  FACTURE ORDER BY MONTANT_TOTAL ");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FACTURE"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_FACTURE"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_FACTURE"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("DATE_FACTURE"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
     model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRIX_PROJET"));
     model->setHeaderData(6, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));
return model;
 }

 QSqlQueryModel *Facture::tri_nomP()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from  FACTURE ORDER BY NOM_FACTURE ");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_FACTURE"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_FACTURE"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_FACTURE"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("DATE_FACTURE"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("PRIX_PRODUIT"));
     model->setHeaderData(5, Qt::Horizontal,QObject::tr("PRIX_PROJET"));
     model->setHeaderData(6, Qt::Horizontal,QObject::tr("MONTANT_TOTAL"));

return model;
 }
 bool Facture::calculer(int id_facture, float montant_total)
 { QSqlQuery query;
     QString res= QString::number(id_facture);
     QString monttot_string= QString::number(montant_total);

     query.prepare("UPDATE FACTURE SET MONTANT_TOTAL=:MONTANT_TOTAL WHERE id_facture=:id_facture");
     query.bindValue(":id_facture",res);
     query.bindValue(":MONTANT_TOTAL",monttot_string);

       return    query.exec();
 }
 QChart* Facture::chart_pie()
  {
      QSqlQuery q1,q2,q3;
      qreal tot=0,c1=0,c2=0;

      q1.prepare("SELECT * FROM FACTURE");
      q1.exec();

      float mont_stat=100;
       QString id_string= QString::number(mont_stat);


      q2.prepare("SELECT * FROM FACTURE WHERE MONTANT_TOTAL >'"+id_string+"'");
      q2.exec();

      q3.prepare("SELECT * FROM FACTURE WHERE MONTANT_TOTAL <'"+id_string+"'");
      q3.exec();



      while (q1.next()){tot++;}
      while (q2.next()){c1++;}
      while (q3.next()){c2++;}


      c1=c1/tot;
      c2=c2/tot;

  //     Define slices and percentage of whole they take up
      QPieSeries *series = new QPieSeries();
      series->append("montant sup 100", c1);
      series->append("Montant inf 100", c2);
  //     Create the chart widget
      QChart *chart = new QChart();

  //     Add data to chart with title and show legend
      chart->addSeries(series);
      chart->legend()->show();

      return chart;
  }
