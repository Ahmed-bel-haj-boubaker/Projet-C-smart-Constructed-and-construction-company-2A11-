#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"facture.h"
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id_facture=ui->valeur_id->text().toInt();
    QString nom_facture=ui->le_nom ->text();
    QString prenom_facture=ui->le_prenom ->text();
    QString date_facture=ui->le_date ->text();
    double prix_produit=ui->le_produit->text().toDouble();
    double prix_projet=ui->le_projet->text().toDouble();
    double montant_total=ui->le_montant->text().toDouble();
    Facture E(id_facture,nom_facture,prenom_facture,date_facture,prix_produit,prix_projet,montant_total);
    bool test=E.ajouter();
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
              ui->table_view->setModel (E.afficher());


}

void MainWindow::on_Supp_btn_clicked()
{
    int id =ui->id_val->text().toInt();
        bool test=E.supprimer(id);

        if(test)
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("échec suprresion.\n"
                                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->table_view->setModel(E.afficher());
}



void MainWindow::on_modif_btn_clicked()
{
    int id_facture=ui->valeur_id->text().toInt();
    QString nom_facture=ui->le_nom ->text();
    QString prenom_facture=ui->le_prenom ->text();
    QString date_facture=ui->le_date ->text();
    double prix_produit=ui->le_produit->text().toDouble();
    double prix_projet=ui->le_projet->text().toDouble();
    double montant_total=ui->le_montant->text().toDouble();

    Facture E(id_facture,nom_facture,prenom_facture,date_facture,prix_produit,prix_projet,montant_total);

     bool test=E.modifier(id_facture,nom_facture,prenom_facture,date_facture,prix_produit,prix_projet,montant_total);
     if(test)
   {ui->table_view->setModel(E.afficher());
   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                     QObject::tr("invite modifiée.\n"
                                 "Click ok to exit."), QMessageBox::Ok);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                     QObject::tr("echec d'ajout !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
