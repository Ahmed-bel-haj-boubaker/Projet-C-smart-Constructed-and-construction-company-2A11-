#ifndef CONG_JUST_H
#define CONG_JUST_H


class cong_just
{
public:
    cong_just();
    cong_just(QString,QString,QString,QString,qstring,float);
    int getid_();
    QString getnom_facture();
    QString getprenom_facture();
    QString getdate_facture();
     float getprix_produit();
     float getprix_projet();
     float getmontant_total();


     void setid_facture(int);
     void setnom_facture(QString);
     void setprenom_facture(QString);
     void setdate_facture(QString);
     void setprix_produit(float);
     void setprix_projet(float);
     void setmontant_total(float);

     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
     bool modifier(int,QString,QString,QString,float,float,float);



private:
  int id_facture;
  QString nom_facture,prenom_facture,date_facture;
  float  prix_produit,prix_projet,montant_total;

};

#endif // CONG_JUST_H
