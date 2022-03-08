#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QIntValidator>
#include<QSqlQueryModel>
Fournisseur F;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
        ui->tab_fournisseur->setModel(F.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
 int id_fournisseur=ui->le_id->text().toInt();
 QString nom_fournisseur=ui->le_nom->text();
 QString prenom_fournisseur=ui->le_prenom->text();
 QString adresse_fournisseur=ui->le_adresse->text();
  int num_tel_fournisseur=ui->le_num_tel->text().toInt();
  QString email_fournisseur=ui->le_email->text();
  Fournisseur F(id_fournisseur,nom_fournisseur,prenom_fournisseur,adresse_fournisseur,num_tel_fournisseur,email_fournisseur);
  bool test=F.ajouter();
              QMessageBox msgBox;
                 if(test)
                 {
                     msgBox.setText("ajout avec succes");
                 msgBox.exec();
                 }
                 else
                 {
                     msgBox.setText("echec");
                 msgBox.exec();
                 }
                 ui->tab_fournisseur->setModel(F.afficher());

}
void MainWindow::on_pb_supprimer_clicked()
{
    Fournisseur F1; F1.setid_fournisseur(ui->le_supprimer->text().toInt());
    bool test=F1.supprimer(F1.getid_fournisseur());
    QMessageBox msgBox;
       if(test)
       {
           msgBox.setText("Suppression avec succes");
           ui->tab_fournisseur->setModel(F.afficher());
       msgBox.exec();
       }
       else
       {
           msgBox.setText("echec de suppression");
       msgBox.exec();
       }

}

void MainWindow::on_pb_modifier_clicked()
{

    int id_fournisseur=ui->le_id->text().toInt();
    QString nom_fournisseur=ui->le_nom->text();
            QString prenom_fournisseur=ui->le_prenom->text();
            QString adresse_fournisseur=ui->le_adresse->text();
            int num_tel_fournisseur=ui->le_num_tel->text().toInt();
            QString email_fournisseur=ui->le_email->text();





         ui->le_nom->setMaxLength(20);
         ui->le_prenom->setMaxLength(20);
            ui->le_adresse->setMaxLength(5); // max longueur
             ui->le_email->setMaxLength(20);
                    ui->le_id->setMaxLength(7);
                    ui->le_num_tel->setMaxLength(8);

            Fournisseur F2(id_fournisseur,nom_fournisseur,prenom_fournisseur,adresse_fournisseur,num_tel_fournisseur,email_fournisseur);

           bool test=F2.modifierFournisseur(F2.getid_fournisseur(),F2.getnom_fournisseur(),F2.getprenom_fournisseur(),F2.getadresse_fournisseur(),F2.getnum_tel_fournisseur(),F2.getemail_fournisseur());

            QMessageBox msgBox;
            if(test)
            {
                msgBox.setText("Modification avec succes");
                ui->tab_fournisseur->setModel(F.afficher());
            msgBox.exec();
            }
            else
            {
                msgBox.setText("echec de modification");
            msgBox.exec();
            }

}





void MainWindow::on_pb_afficher_clicked()
{

}


void MainWindow::on_le_modifier_clicked()
{

}
