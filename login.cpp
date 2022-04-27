#include"login.h"
#include <QProgressBar>
#include <QStatusBar>
#include <QSqlQuery>
#include <QDebug>
#include<iostream>
#include <QTimer>
#include "mainwindow.h"
#include "connection.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QMainWindow>
#include"employer.h"
#include"projet.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    animation= new QPropertyAnimation(ui->label_3,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(200,200,100,50));
    animation->setEndValue(QRect(0,0,320,200));
    animation->start();



    animation= new QPropertyAnimation(ui->label,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(200,200,100,50));
    animation->setEndValue(QRect(0,0,320,700));
    animation->start();
}

login::~login()
{
    delete ui;
}

void login::on_valider_clicked()
{

     QString email= ui->email->text();
     QString mdp= ui->mdp->text();


    QSqlQuery query;
    QString select = "SELECT * FROM employer WHERE email=:email AND mdp=:mdp";

    query.prepare(select);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);


    query.exec();
    if (query.exec())
    {
        if (query.next())
     {
            QMessageBox::information(nullptr, QObject::tr("Bienvenue"),
                                  QObject::tr("Vous etes connectés à notre application..\n"
                                              "Bienvenue"), QMessageBox::Ok);
            this->close();
            MainWindow *main;
            main = new MainWindow();
            main->show();
            delay = new QTimer(this);
           connect(delay,SIGNAL(timeout()),this,SLOT(closeWin()));
           delay->start(500);

            }
            else
            {  QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                     QObject::tr("Invalid username or password..\n"
                                                 "Click Cancel to exit."), QMessageBox::Ok);

            }
        }



    }


void login::on_pushButton_clicked()
{
    ui->stackedWidget3->setCurrentIndex(1);
}

void login::on_valider_2_clicked()
{
    employer em;
        QMessageBox msgBox;
       int id_employer=ui->id_nv->text().toInt();
       QString nom=ui->nom_nv->text();
       QString prenom=ui->prenom_nv->text();
      QString adresse=ui->adresse_nv->text();
       QString email=ui->email_nv->text();
        QString mdp=ui->mdp_nv->text();

      bool test=em.ajouter(id_employer,nom,prenom,adresse,email,mdp);




       if(test){
        //  N.notification_ajoutProjet();
         msgBox.setText("Ajout avec Succes");
      //  ui->tab_projet->setModel(P.afficher());
       // ui->tab_projet_2->setModel(P.afficher());
ui->stackedWidget3->setCurrentIndex(0);
       }
           else
               msgBox.setText("Echec de l'ajout");
      msgBox.exec();
}

