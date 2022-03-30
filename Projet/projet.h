#ifndef PROJET_H
#define PROJET_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>
#include <QTableView>
#include <QFloat16>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

class projet
{
public:
    projet();
    projet(int,QString,QString,QDate,QDate,int,int,int,int,int,int,int,int);
int getid();
QString getnom_projet();
QString getlocalisation();
QSqlQuery query;
QDate getDate_deb();
QDate getDate_fin();
int getL1();
int getL2();
int getP1();
int getP2();
int getH1();
int getT();
int getS();
int getC();
 void setid(int);
 void setnom_projet(QString);
 void setlocalisation(QString);
 void setDate_deb(QDate);
void setDate_fin(QDate);
void setL1(int);
void setL2(int);
void setP1(int);
void setP2(int);
void setH1(int);
void setT(int);
void setS(int);
void setC(int);
 bool ajouter();
 QSqlQueryModel* afficher();
 bool supprimer(int);
 bool modifier(int,QString,QString,QDate,QDate,int,int,int,int,int,int);
 bool calculer(int,int,int);
bool modifier_emploi(QString , QDate, QDate);

     QSqlQueryModel* rechercher(QString search);

     QSqlQueryModel * tri_idP();
     QSqlQueryModel * tri_place();
     QSqlQueryModel * tri_nomP();
     void stats(QString ,QString ,int,int,QString);

     QChartView * piechart();
     QChartView * piechart2();

private:
 int id_projet;
 QString nom_projet;
 QString localisation;
 QDate date_deb;
 QDate date_fin;
 int l1;
 int l2;
 int p1;
 int p2;
 int h1;
 int t;
int S;
int cout;
};

#endif // PROJET_H
