#ifndef EMPLOYER_H
#define EMPLOYER_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>



class employer
{

public:
    employer(){}
    employer(int,QString,QString,int,QString,QString);//constructeur par defaut

    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString getadresse(){return adresse;}
    QString getmail(){return mail;}



    int getid_l(){return id_l;}
    int getnum(){return num;}

    void setnom(QString d){nom=d;}
    void setprenom(QString a){nom=a;}
    void setid_l(int id_l){this->id_l=id_l;}
    void setnum(int num){this->num=num;}
    void setadresse(QString t){adresse=t;}
    void setmail(QString o){mail=o;}

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherRech(QString,QString);
    QSqlQueryModel* afficherTri(QString);
bool supprimer(int id_l);
bool modifier(int,QString,QString,int,QString,QString);
bool recherche_mod(int);

private:
int id_l,num;
QString nom, prenom, adresse,mail;

};

#endif // EMPLOYER_H
