#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include "reclamation.h"
#include "utilisateur.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QIntValidator>
#include<QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include<QFileDialog>
#include <QPdfWriter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>

Fournisseur F;
Reclamation R;
Utilisateur U;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_idt->setValidator(new QIntValidator(0, 9999999, this));

         QValidator *validator = new QIntValidator(1, 99999999, this); // pour les int
         ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
         ui->le_idu->setValidator(new QIntValidator(0, 9999999, this));
ui->le_id_client->setValidator(validator);
ui->le_id_employe->setValidator(validator);


        ui->tab_fournisseur->setModel(F.afficher());
        ui->tab_reclamation->setModel(R.afficher());
        ui->tab_utilisateur->setModel(U.afficher());
        ui->tab_fournisseur->setModel(F.trierid());

}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::controlsaisie(){

    if ( ui->le_id->text().isEmpty() ||
         ui->le_id->text().toInt() == 0 ||

            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_adresse->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->le_num_tel->text().isEmpty() ||
            ui->le_num_tel->text().toInt() == 0
         )
        return 0;
    else
        return 1;
}

bool MainWindow::controlsaisie2(){

    if (
            ui->le_idt->text().isEmpty() ||// si vide
            ui->le_idt->text().toInt() == 0 || //si contient 7arff

            !(ui->le_nomt->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_produit->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_probleme->text().contains(QRegExp("^[A-Za-z]+$")))

          )
        return 0;
    else
        return 1;
}
//cntr de saisirr reclamation//
bool MainWindow::controlsaisie3(){

    if ( ui->le_idt->text().isEmpty() ||
         ui->le_idt->text().toInt() == 0 ||

            !(ui->le_nomt->text().contains(QRegExp("^[A-Za-z]+$"))) ||
             ui->le_date->text().isEmpty() ||
             ui->le_date->text().toInt() == 0  ||
            !(ui->le_produit->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_probleme->text().contains(QRegExp("^[A-Za-z]+$"))) ||



         ui->le_id_client->text().isEmpty() ||
         ui->le_id_client->text().toInt() == 0
         )
        return 0;
    else
        return 1;
}
//fin//
//ctrl de saisie utilisateur//
bool MainWindow::controlsaisie4(){

    if ( ui->le_idu->text().isEmpty() ||
         ui->le_idu->text().toInt() == 0 ||

            !(ui->le_username->text().contains(QRegExp("^[A-Za-z]+$"))) ||

         ui->le_id_employe->text().isEmpty() ||
         ui->le_id_employe->text().toInt() == 0


         )
        return 0;
    else
        return 1;
}


//fin//


void MainWindow::on_pb_ajouter_clicked()
{
    if (controlsaisie()){
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
    else {
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("veuiller remplir tous les champs correctement.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
        }
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

            Fournisseur F2(id_fournisseur,nom_fournisseur,prenom_fournisseur,adresse_fournisseur, num_tel_fournisseur, email_fournisseur);

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

void MainWindow::on_pb_ajouter_2_clicked()
{
    if (controlsaisie3()){
 int id_reclamation=ui->le_idt->text().toInt();
 QString nom_reclamation=ui->le_nomt->text();
 QString date_reclamation=ui->le_date->text();
 QString produit=ui->le_produit->text();
  QString probleme=ui->le_probleme->text();
  QString id_client=ui->le_id_client->text();
  Reclamation R(id_reclamation,nom_reclamation,date_reclamation,produit,probleme,id_client);
  bool test=R.ajouter();
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
                 ui->tab_reclamation->setModel(R.afficher());

}
    else {
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("veuiller remplir tous les champs correctement.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
        }
        }

void MainWindow::on_le_supprimer_2_clicked()
{
    Reclamation R1; R1.setid_reclamation(ui->suppr->text().toInt());
        bool test=R1.supprimer(R1.getid_reclamation());
        QMessageBox msgBox;
           if(test)
           {
               msgBox.setText("Suppression avec succes");
               ui->tab_reclamation->setModel(R.afficher());
           msgBox.exec();
           }
           else
           {
               msgBox.setText("echec de suppression");
           msgBox.exec();
           }
}


void MainWindow::on_pb_modifier_2_clicked()
{
    int id_reclamation=ui->le_idt->text().toInt();
        QString nom_reclamation=ui->le_nomt->text();
                QString date_reclamation=ui->le_date->text();
                QString produit=ui->le_produit->text();

                QString probleme=ui->le_probleme->text();
                QString id_client=ui->le_id_client->text();





             ui->le_nomt->setMaxLength(20);
             ui->le_date->setMaxLength(20);
                ui->le_produit->setMaxLength(5); // max longueur
                 ui->le_probleme->setMaxLength(20);
                        ui->le_idt->setMaxLength(7);
                         ui->le_id_client->setMaxLength(20);


                Reclamation R2(id_reclamation,nom_reclamation,date_reclamation,produit,probleme,id_client);

               bool test=R2.modifierReclamation(R2.getid_reclamation(),R2.getnom_reclamation(),R2.getdate_reclamation(),R2.getproduit(),R2.getprobleme(),R2.getid_client());

                QMessageBox msgBox;
                if(test)
                {
                    msgBox.setText("Modification avec succes");
                    ui->tab_reclamation->setModel(R.afficher());
                msgBox.exec();
                }
                else
                {
                    msgBox.setText("echec de modification");
                msgBox.exec();
                }

}



void MainWindow::on_ajouter_clicked()
{
    if (controlsaisie4()){
 int id=ui->le_idu->text().toInt();
 QString username=ui->le_username->text();
 QString email=ui->le_emailu->text();
 QString password=ui->le_password->text();
  QString id_employe=ui->le_id_employe->text();
  Utilisateur U(id,username,email,password,id_employe);
  bool test=U.ajouter();
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
                 ui->tab_utilisateur->setModel(U.afficher());

}
    else {
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("veuiller remplir tous les champs correctement.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
        }
        }



void MainWindow::on_supprimer_clicked()
{
    Utilisateur U1; U1.setid(ui->supp->text().toInt());
    bool test=U1.supprimer(U1.getid());
    QMessageBox msgBox;
       if(test)
       {
           msgBox.setText("Suppression avec succes");
           ui->tab_utilisateur->setModel(U.afficher());
       msgBox.exec();
       }
       else
       {
           msgBox.setText("echec de suppression");
       msgBox.exec();
       }

}

void MainWindow::on_modifier_clicked()
{

    int id=ui->le_idu->text().toInt();
    QString username=ui->le_username->text();
            QString email=ui->le_emailu->text();
            QString password=ui->le_password->text();
            QString id_employe=ui->le_id_employe->text();





         ui->le_username->setMaxLength(20);
         ui->le_emailu->setMaxLength(20);
            ui->le_adresse->setMaxLength(5); // max longueur
             ui->le_password->setMaxLength(20);
                    ui->le_id_employe->setMaxLength(7);


            Utilisateur U2(id,username,email,password,id_employe);

           bool test=U2.modifierUtilisateur(U2.getid(),U2.getusername(),U2.getemail(),U2.getpassword(),U2.getid_employe());

            QMessageBox msgBox;
            if(test)
            {
                msgBox.setText("Modification avec succes");
                ui->tab_utilisateur->setModel(U.afficher());
            msgBox.exec();
            }
            else
            {
                msgBox.setText("echec de modification");
            msgBox.exec();
            }

}







void MainWindow::on_pushButton_clicked()
{
    QStackedWidget stackedWidget;
            connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));
            QString username=ui->le_username->text();
                    QString password = ui->le_password->text();
                    if(username == "rima" && password == "rima")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                   //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));
                    ui->stackedWidget->setCurrentIndex(1);
                    }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "emna" && password == "emna")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(2);
                    }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "malek" && password == "malek")
                            { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(3);
                    }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "ibtihel" && password == "ibtihel")
                                { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(4);
                    }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                    else if(username == "ahmed" && password == "ahmed")
                                    { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(5);
                    }
                    else if(username == "daly" && password == "daly")
                        { QMessageBox::information(this, "Login", "Username and password is correct");
                          ui->stackedWidget->setCurrentIndex(6);
                          }
                                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                                else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }

}

void MainWindow::on_pb_trier_clicked()
{
    ui->tab_fournisseur->setModel(F.trierid());
}

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    Fournisseur F;



      int id_fournisseur= ui->recherche->text().toInt();

      F.recherche(ui->tab_fournisseur,id_fournisseur);

      if (ui->recherche->text().isEmpty())
      {

          ui->tab_fournisseur->setModel(F.afficher());

      }
   }

void MainWindow::on_pdf_clicked()
{QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tab_fournisseur->model()->rowCount();
    const int columnCount = ui->tab_fournisseur->model()->columnCount();
    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - COMmANDE LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> ****LISTE DES  licence commerciale ****"+TT+" </strong></h1>"
        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_fournisseur->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_fournisseur->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_fournisseur->isColumnHidden(column)) {
                QString data =ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void MainWindow::on_stat_clicked()
{

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from FOURNISSEUR where ADRESSE_FOURNISSEUR = 'sud' ");
        float dispo1=model->rowCount();

        model->setQuery("select * from FOURNISSEUR where ADRESSE_FOURNISSEUR = 'nord' ");
        float dispo=model->rowCount();

        float total=dispo1+dispo;
            QString a=QString("sud . " +QString::number((dispo1*100)/total,'f',2)+"%" );
            QString b=QString("nord .  "+QString::number((dispo*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,dispo1);
            series->append(b,dispo);
        if (dispo1!=0)
        {QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());}
        if ( dispo!=0)
        {
            QPieSlice *slice1 = series->slices().at(1);
            slice1->setLabelVisible();
        }

        QChart *chart = new QChart();


        chart->addSeries(series);
        chart->setTitle(" ADRESSE_FOURNISSEUR :Nb ADRESSE_FOURNISSEUR: "+ QString::number(total));
        chart->legend()->hide();


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();
}





void MainWindow::on_pb_afficher_2_clicked()
{

}












void MainWindow::on_afficher_clicked()
{

}

