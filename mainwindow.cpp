#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QSqlTableModel>
#include<QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
Materiel M;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  ui->E_produit_ID->setValidator(new QIntValidator(0, 9999999, this));
ui->tabl_produit->setModel(M.afficher());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_B_produit_ajouter_clicked()
{int ID_PRODUIT=ui->E_produit_ID->text().toInt();
    int QUANTITER=ui->E_produit_Quantiter->text().toInt();
   QString NOM_PRODUIT=ui->E_produit_Nom->text();
   double PRIX_PRODUIT=ui->E_produit_Prix->text().toDouble();
   int REMISE=ui->E_produit_Remise->text().toInt();

       Materiel M(ID_PRODUIT,QUANTITER,NOM_PRODUIT,PRIX_PRODUIT,REMISE);

       bool test=M.ajouter();
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
                           ui->tabl_produit->setModel(M.afficher());
      }




void MainWindow::on_B_produit_supprimer_clicked()
{
    Materiel M1; M1.setID_PRODUIT(ui->E_produit_ID_supprimer->text().toInt());
    bool test=M1.supprimer(M1.getID_PRODUIT());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("Suppression avec succes.");
        ui->tabl_produit->setModel(M.afficher());
    }

    else
       QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("suppression non effectuee.\n" "click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_B_produit_Afficher_clicked()
{
    ui->tabl_produit->setModel(M.afficher());

}

void MainWindow::on_B_produit_Modifier_clicked()
{
    int ID_PRODUIT=ui->E_produit_ID->text().toInt();
        int QUANTITER=ui->E_produit_Quantiter->text().toInt();
       QString NOM_PRODUIT=ui->E_produit_Nom->text();
       double PRIX_PRODUIT=ui->E_produit_Prix->text().toDouble();
       int REMISE=ui->E_produit_Remise->text().toInt();

       Materiel M(ID_PRODUIT,QUANTITER,NOM_PRODUIT,PRIX_PRODUIT,REMISE);


             bool test=M.modifier(ID_PRODUIT,QUANTITER,NOM_PRODUIT,PRIX_PRODUIT,REMISE);
             if(test)
           {ui->tabl_produit->setModel(M.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);

           }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}
