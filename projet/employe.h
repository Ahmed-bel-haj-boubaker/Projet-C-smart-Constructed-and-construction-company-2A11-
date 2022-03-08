#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQueryModel>


class employe
{
public:
    employe();
    employe(int,QString,QString,QString,QString,int,QString);

    int getid_employe();
    QString getnom_employe();
    QString getprenom_employe();
    QString getadresse_employe();
    int getnum_employe();
    QString getemail_employe();


     void setid_employe(int);
     void setnom_employe(QString);
     void setprenom_employe(QString);
     void setadresse_employe(QString);
     void setnum_employe(int);
     void setemail_employe(QString);

     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
     bool modifier(int,QString,QString,QString,QString,int,QString);



private:
  int id_employe,num_employe;
  QString nom_employe,prenom_employe,adresse_employe,email_employe;

};

#endif // EMPLOYE_H
