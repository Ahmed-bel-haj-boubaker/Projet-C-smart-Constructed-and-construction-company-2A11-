#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QSqlQueryModel>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMainWindow>
#include<QSqlQuery>
class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,QString,QString,QString,int,QString);
int getid_fournisseur();
QString getnom_fournisseur();
QString getprenom_fournisseur();
QString getadresse_fournisseur();
int getnum_tel_fournisseur();
QString getemail_fournisseur();
void setid_fournisseur(int);
void setnom_fournisseur(QString);
void setprenom_fournisseur(QString);
void setadresse_fournisseur(QString);
void setnum_tel_fournisseur(int);
void setemail_fournisseur(QString);

bool ajouter();
QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierFournisseur(int id_fournisseur,QString nom_fournisseur,QString prenom_fournisseur,QString adresse_fournisseur, int num_tel_fournisseur,QString email_fournisseur);
private:
    int id_fournisseur,num_tel_fournisseur;
    QString nom_fournisseur, prenom_fournisseur, adresse_fournisseur, email_fournisseur;
};

#endif // FOURNISSEUR_H
