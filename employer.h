#ifndef EMPLOYER_H
#define EMPLOYER_H
#include <QtDebug>
#include <QString>
#include <QSqlQuery>
#include<QObject>
#include<QSqlQueryModel>
#include<QTableView>
#include <QFloat16>
#include<QtWidgets>
#include<QtDesigner/QDesignerActionEditorInterface>
#include<mainwindow.h>

class employer
{
public:
    employer();
    employer(int,QString,QString,QString,QString,QString);
int getID();
QString getNom();
QString getPrenom();
QString getAdresse();
QString getEmail();
QString getMDP();

void setID(int);
void setNom(QString);
void setPrenom(QString);
void setAdresse(QString);
void setEmail(QString);
void setMDP(QString);
int chercher_employer_id(QString D);
bool ajouter(int ,QString ,QString ,QString ,QString,QString);

private:
    int id_employer;
    QString nom;
    QString prenom;
   QString adresse;
   QString email;
  QString  mdp;
};

#endif // EMPLOYER_H
