#ifndef CONGES_H
#define CONGES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>

class conges
{

public:
    conges(){}
    conges(QString,QString ,QString ,QDate ,QDate ,int ,QString,QString );//constructeur par defaut



    QString getnom(){return nom;}
    QString getresponsable(){return responsable;}
    QString gettype(){return type;}


    QDate getdate_d(){return date_d;}
    QDate getdate_f(){return date_f;}

    int getnbr(){return nbr;}

    QString getcommentaire(){return commentaire;}
    QString getacceptation() {return acceptation;}


    void setnom(QString d){nom=d;}
    void setresponsable(QString a){responsable=a;}
    void settype(QString cr){this->type=cr;}
    void setdate_d(QDate dd){date_d=dd;}
    void setdate_f(QDate df){date_f=df;}
    void setnbr(int nb){this->nbr=nb;}
    void setcommentaire(QString ce) {commentaire = ce;}
    void setacceptation(QString fafa) {acceptation = fafa;}

    bool ajouter_a();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherRech(QString,QString);
    // QSqlQueryModel* afficherTri(QString);
    //bool supprimer(int id_l);
    //bool modifier(int,QString,QString,int,QString,QString);
    //bool recherche_mod(int);

private:
    int nbr;
    QString nom, responsable, type,commentaire,acceptation;
    QDate date_d,date_f;

};

#endif // CONGES_H
