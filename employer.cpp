#include "employer.h"

employer::employer(int id_l,QString nom,QString prenom,int num,QString adresse,QString mail)
{

     this->id_l=id_l;
     this->nom=nom;
     this->prenom=prenom;
     this->num=num;
    this->adresse=adresse;
    this->mail=mail;

}
bool  employer::ajouter()
{
QSqlQuery query;
QString res = QString::number(id_l);

query.prepare("insert into employer (id_l, nom, prenom, num, adresse, mail)" "values (:id_l, :nom, :prenom, :num, :adresse, :mail)");

query.bindValue(":id_l" ,res);
query.bindValue(":nom" ,nom);
query.bindValue(":prenom" ,prenom);
query.bindValue(":num" ,num);
query.bindValue(":adresse" ,adresse);
query.bindValue(":mail" ,mail);


return query.exec();


}
QSqlQueryModel * employer::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from employer");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("mail"));
return model;
}
QSqlQueryModel * employer::afficherTri(QString critere)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from employer order by "+critere);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("mail"));
return model;
}
QSqlQueryModel * employer::afficherRech(QString rech,QString critere)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from employer where "+critere+" like '"+rech+"%'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("mail"));
return model;
}
bool employer::supprimer(int id_l)

{
  QSqlQuery query;
   QString res = QString::number(id_l);

   query.prepare("Delete from employer where id_l= :id_l");

   query.bindValue(":id_l",res);

return query.exec();
}

bool employer::modifier(int id_l,QString nom,QString prenom,int num,QString adresse,QString mail)
{

       QSqlQuery query;
       QString id_l_string=QString::number(id_l);

    query.prepare("UPDATE employer SET  nom= :nom , prenom= :prenom , num= :num , adresse= :adresse , mail= :mail  WHERE id_l= :id_l ");
    query.bindValue(":id_l",id_l);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":adresse",adresse);
    query.bindValue(":mail",mail);

    return query.exec();
     }
//bool employer::recherche_mod(int)
//{ }
