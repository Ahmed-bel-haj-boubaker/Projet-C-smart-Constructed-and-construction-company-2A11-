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
#include<QDate>
#include<QStackedWidget>
#include<QWidget>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_supp->setValidator(new QIntValidator(0,9999999,this));

    ui->id->setValidator(new QIntValidator(0,9999999,this));
    ui->l1->setValidator(new QIntValidator(0,9999999,this));

    ui->l2->setValidator(new QIntValidator(0,9999999,this));

    ui->p1->setValidator(new QIntValidator(0,9999999,this));

    ui->p2->setValidator(new QIntValidator(0,9999999,this));

    ui->h1->setValidator(new QIntValidator(0,9999999,this));
    ui->t->setValidator(new QIntValidator(0,9999999,this));

    ui->tab_projet->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    QMessageBox msgBox;
   int id_projet=ui->id->text().toInt();
   QString nom_projet=ui->nom->text();
   QString localisation=ui->local->text();
   QDate date_deb=ui->date_deb->date();
   QDate date_fin=ui->date_fin->date();
   int l1=ui->l1->text().toInt();
   int l2=ui->l2->text().toInt();
   int p1=ui->p1->text().toInt();
   int p2=ui->p2->text().toInt();
   int h1=ui->h1->text().toInt();
   int t=ui->t->text().toInt();
   projet P(id_projet, nom_projet, localisation, date_deb,date_fin,l1,l2,p1,p2,h1,t);




   if(P.ajouter()){
       msgBox.setText("Ajout avec Succes");
    ui->tab_projet->setModel(P.afficher());}
       else
           msgBox.setText("Echec de l'ajout");
  msgBox.exec();
}


void MainWindow::on_modifier_clicked()
{
    int id_projet=ui->id->text().toInt();
    QString nom_projet=ui->nom->text();
    QString localisation=ui->local->text();
    QDate date_deb=ui->date_deb->date();
    QDate date_fin=ui->date_fin->date();
    int l1=ui->l1->text().toInt();
    int l2=ui->l2->text().toInt();
    int p1=ui->p1->text().toInt();
    int p2=ui->p2->text().toInt();
    int h1=ui->h1->text().toInt();
    int t=ui->t->text().toInt();
projet P;
bool test;
test=P.modifier(id_projet, nom_projet, localisation, date_deb,date_fin,l1,l2,p1,p2,h1,t);

  QMessageBox msgBox;
       if(test){
           ui->tab_projet->setModel(P.afficher());
           msgBox.setText("modification avec Succes");
        }
           else
               msgBox.setText("Echec de la modification");
      msgBox.exec();
}

void MainWindow::on_supprimer_clicked()
{
    bool test;
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

void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    projet P;
                    ui->tab_projet->setModel(P.rechercher(ui->rechercher->text()));

}

void MainWindow::on_suiv1_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}



void MainWindow::on_suiv3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_suivi2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_tri_currentIndexChanged(int index)
{
    if(index==1)
                      ui->tab_projet->setModel(P.tri_idP());
            else if(index==2)
                      ui->tab_projet->setModel(P.tri_place());
            else if(index==3)
                      ui->tab_projet->setModel(P.tri_nomP());
}

void MainWindow::on_pushButton_clicked()
{
ui->stackedWidget->setCurrentIndex(0);
}





