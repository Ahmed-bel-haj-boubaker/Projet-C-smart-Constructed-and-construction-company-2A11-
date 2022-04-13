#ifndef RDV_H
#define RDV_H
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QSqlQuery>

#include <QtSql/QSqlQueryModel>
#include <QMainWindow>
#include<QTableView>

class Rdv
{
public:
    Rdv();
    Rdv(int,QDate,int,int);
int getid_rdv();
QDate getdate_rdv();
int getheure_rdv();
int getIDCLIENT();
void setid_rdv(int);
void setdate_rdv(QDate);
void setheure_rdv(int);
void setIDCLIENT(int);

bool ajouter1();
QSqlQueryModel* afficher1();
    bool supprimer1(int);
    bool modifierRdv(int id_rdv,QDate date_rdv ,int heure_rdv);

private:
    int id_rdv,heure_rdv,IDCLIENT;
    QDate date_rdv;

};

#endif // RDV_H
