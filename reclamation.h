#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QSqlQueryModel>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMainWindow>
#include<QSqlQuery>
class Reclamation
{
public:
    Reclamation();
    Reclamation(int,QString,QString,QString,QString,QString);
int getid_reclamation();
QString getnom_reclamation();
QString getdate_reclamation();
QString getproduit();
QString getprobleme();
QString getid_client();

void setid_reclamation(int);
void setnom_reclamation(QString);
void setdate_reclamation(QString);
void setproduit(QString);
void setprobleme(QString);
void setid_client(QString);

bool ajouter();
QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierReclamation(int id_reclamation,QString nom_reclamation,QString date_reclamation,QString produit, QString probleme,QString id_client);
private:
    int id_reclamation;
    QString nom_reclamation , date_reclamation , produit , probleme , id_client;
};

#endif // RECLAMATION_H
