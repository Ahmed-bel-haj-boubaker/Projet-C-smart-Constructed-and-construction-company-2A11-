#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>

#include<QFileDialog>
#include <QPdfWriter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>



class Client
{
public:
    Client();
    Client(int,QString,QString,QString,int,QString);
int getid_client();
QString getnom_client();
QString getprenom_client();
QString getadresse_client();
int getnum_tel_client();
QString getemail_client();
void setid_client(int);
void setnom_client(QString);
void setprenom_client(QString);
void setadresse_client(QString);
void setnum_tel_client(int);
void setemail_client(QString);
bool ajouter();


QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierClient(int id_client,QString nom_client ,QString prenom_client,QString adresse_client,int num_tel_client, QString email_client);
QSqlQueryModel * trierid();
void recherche(QTableView * tabl, int);
QSqlQueryModel * getAlertes();

private:
    int id_client,num_tel_client;
    QString nom_client, prenom_client, adresse_client, email_client;


};
#endif // CLIENT_H
