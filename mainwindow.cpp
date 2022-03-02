#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"projet.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include<QLineEdit>
#include<QIntValidator>
#include <iostream>
#include <QSound>

#include<QMediaPlayer>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,999999,this));

    ui->tab_projet->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSound ::play("qrc:/click.mp3");
        play.play();


     QMessageBox msgBox;
    int id_projet=ui->id->text().toInt();
    QString nom_projet=ui->nom->text();
    QString localisation=ui->local->text();
    QDate date_deb=ui->date_deb->date();
    QDate date_fin=ui->date_fin->date();
    projet P(id_projet, nom_projet, localisation, date_deb,date_fin);

    if(P.ajouter()){
        msgBox.setText("Ajout avec Succes");
     ui->tab_projet->setModel(P.afficher());}
        else
            msgBox.setText("Echec de l'ajout");
   msgBox.exec();
}


void MainWindow::on_pb_supprimer_clicked()
{bool test;
  projet P;
P.setid(ui->id_supp->text().toInt());
 test=P.supprimer(P.getid());
 QMessageBox msgBox;
 if(test){
     msgBox.setText("Supprission avec Succes");
     ui->tab_projet->setModel(P.afficher());
 }
     else
         msgBox.setText("Echec de la supprission");
msgBox.exec();
 }


void MainWindow::on_pb_modifier_clicked()
{


    int id_projet=ui->id->text().toInt();
    QString nom_projet=ui->nom->text();
    QString localisation=ui->local->text();
    QDate date_deb=ui->date_deb->date();
    QDate date_fin=ui->date_fin->date();
projet P(id_projet,nom_projet,localisation,date_deb,date_fin);

bool test=P.modifier(id_projet);

  QMessageBox msgBox;
       if(test){

           ui->tab_projet->setModel(P.afficher());
           msgBox.setText("Modifier avec Succes");
        }
           else
               msgBox.setText("Echec de la modification");
      msgBox.exec();
   }






void MainWindow::on_lawej_textChanged(const QString &arg1)
{
    projet P;
                 ui->tab_projet->setModel(P.rechercher(ui->lawej->text()));
}
