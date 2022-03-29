#ifndef MATERIEL_H
#define MATERIEL_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

class Materiel
{
public:
    Materiel();
    Materiel(int,int,QString ,float,int);
    int getID_PRODUIT();
    int getQUANTITER();
    QString getNOM_PRODUIT();
    float getPRIX_PRODUIT();
    int getREMISE();
    void setID_PRODUIT(int);
    void setQUANTITER(int);
      void setNOM_PRODUIT(QString);
    void setPRIX_PRODUIT(float);
    void setREMISE(int);
    bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
     bool modifier(int,int,QString ,float,int);
     QSqlQueryModel * Recherche(QString);
     QSqlQueryModel * trierMaterielParid();
      QSqlQueryModel * trierMaterielParNom();
      QSqlQueryModel * trierMaterielParprix();




private:
    int ID_PRODUIT;
    int QUANTITER;
    QString NOM_PRODUIT;
    float PRIX_PRODUIT ;
    int REMISE ;



};

#endif // MATERIEL_H
