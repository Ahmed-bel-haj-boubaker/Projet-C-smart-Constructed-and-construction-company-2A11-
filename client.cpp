#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QTextDocument>

#include <QtPrintSupport/QPrinter>

#include<QFileDialog>
#include <QPdfWriter>

#include <QTextDocument>
#include <QTextStream>



Client::Client()
{
id_client=0; nom_client=" "; prenom_client=" "; adresse_client=" ";num_tel_client=0; email_client=" ";
}
Client::Client(int id_client,QString nom_client,QString prenom_client,QString adresse_client,int num_tel_client,QString email_client)
{this->id_client=id_client; this->nom_client=nom_client; this->prenom_client=prenom_client; this->adresse_client=adresse_client;this->num_tel_client=num_tel_client; this->email_client=email_client;}
int Client::getid_client(){return id_client;}
QString Client::getnom_client(){return nom_client;}
QString Client::getprenom_client(){return prenom_client;}
QString Client::getadresse_client(){return adresse_client;}
int Client::getnum_tel_client(){return num_tel_client;}
QString Client::getemail_client(){return email_client;}
void Client::setid_client(int id_client){this->id_client=id_client;}
void Client::setnom_client(QString nom_client){this->nom_client=nom_client;}
void Client::setprenom_client(QString prenom_client){this->prenom_client=prenom_client;}
void Client::setadresse_client(QString adresse_client){this->adresse_client=adresse_client;}
void Client::setnum_tel_client(int  num_tel_client){this->num_tel_client=num_tel_client;}
void Client::setemail_client(QString email_client){this->email_client=email_client;}
bool Client::ajouter()
{
    QSqlQuery query;
    QString id_client_string=QString::number(id_client);
    QString num_tel_client_string=QString::number(num_tel_client);

          query.prepare("INSERT INTO CLIENT (ID_CLIENT,NOM_CLIENT,PRENOM_CLIENT,ADRESSE_CLIENT,NUM_TEL_CLIENT,EMAIL_CLIENT) "
                        "VALUES (:ID_CLIENT, :NOM_CLIENT, :PRENOM_CLIENT, :ADRESSE_CLIENT, :NUM_TEL_CLIENT, :EMAIL_CLIENT)");
          query.bindValue(":ID_CLIENT",id_client_string);
          query.bindValue(":NOM_CLIENT", nom_client);
          query.bindValue(":PRENOM_CLIENT", prenom_client);
          query.bindValue(":ADRESSE_CLIENT", adresse_client);
          query.bindValue(":NUM_TEL_CLIENT", num_tel_client_string);
          query.bindValue(":EMAIL_CLIENT", email_client);


    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

          model->setQuery("SELECT * FROM CLIENT");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_CLIENT"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM_CLIENT"));
           model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM_CLIENT"));
            model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE_CLIENT"));
            model->setHeaderData(4, Qt::Horizontal,QObject::tr("NUM_TEL_CLIENT"));
            model->setHeaderData(5, Qt::Horizontal,QObject::tr("EMAIL_CLIENT"));
    return model ;
}

bool Client::supprimer(int id_client)
{
    QSqlQuery query;

          QString res=QString::number(id_client);

        query.prepare("Delete from CLIENT where ID_CLIENT=:ID_CLIENT");

        query.bindValue(":ID_CLIENT", res);

         return query.exec();
}

bool Client::modifierClient(int id_client,QString nom_client,QString prenom_client,QString adresse_client,int num_tel_client,QString email_client){
    QSqlQuery query;
    QString id_client_string=QString::number(id_client);
    QString num_tel_client_string=QString::number(num_tel_client);

       query.prepare(" UPDATE CLIENT set id_client=:id_client ,nom_client=:nom_client, prenom_client=:prenom_client ,adresse_client=:adresse_client, num_tel_client=:num_tel_client, email_client=:email_client where id_client=:id_client");
       query.bindValue(":id_client", id_client_string);
       query.bindValue(":nom_client", nom_client);
       query.bindValue(":prenom_client",prenom_client);
       query.bindValue(":adresse_client",adresse_client);
       query.bindValue(":num_tel_client", num_tel_client_string);
       query.bindValue(":email_client",email_client);
       return query.exec();
}

QSqlQueryModel * Client::trierid()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from CLIENT ORDER BY ID_CLIENT");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_CLIENT"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM_CLIENT"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL_CLIENT"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL_CLIENT"));


     return model;
 }


void Client::recherche(QTableView * table ,int id_client )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString id_client_string=QString::number(id_client);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from CLIENT where ID_CLIENT like '%"+id_client_string+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}

