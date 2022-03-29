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
#include <QMessageBox>
#include <QTextEdit>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include<QFileDialog>
#include <QPdfWriter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include <QPrintDialog>
#include <QFile>
#include <QDateTime>






Materiel M;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  ui->E_produit_ID->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Prix->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Quantiter->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Remise->setValidator(new QIntValidator(0, 9999999, this));
  QRegExp rx("[a-zA-Z]+");
      QValidator *validator = new QRegExpValidator(rx, this);
      ui->E_produit_Nom->setValidator(validator);

ui->tabl_produit->setModel(M.afficher());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_B_produit_ajouter_clicked()
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Ajouter \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();

    int ID_PRODUIT=ui->E_produit_ID->text().toInt();
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
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Supprimer \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
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
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Afficher \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
    ui->tabl_produit->setModel(M.afficher());

}

void MainWindow::on_B_produit_Modifier_clicked()
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Modifier \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
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

void MainWindow::on_E_produit_Reherche_textChanged(const QString &arg1)
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Recherche \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
    ui->tabl_produit->setModel(M.Recherche(arg1));
    }


void MainWindow::on_B_produit_tri_textActivated(const QString &arg1)
{

    if(arg1==1)
                          ui->tabl_produit->setModel(M.trierMaterielParid());
                else if(arg1==2)
                          ui->tabl_produit->setModel(M.trierMaterielParNom());
                else if(arg1==3)
                          ui->tabl_produit->setModel(M.trierMaterielParprix());



  }



void MainWindow::on_B_produit_Imprimer_clicked()
{



    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");


        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Imprimer \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
    QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = ui->tabl_produit->model()->rowCount();
                         const int columnCount = ui->tabl_produit->model()->columnCount();
                         QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                         out <<"<html>\n"
                               "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             << "<title>ERP - COMmANDE LIST<title>\n "
                             << "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
                             "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                               "</br> </br>";
                         // headers
                         out << "<thead><tr bgcolor=#d6e5ff>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tabl_produit->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tabl_produit->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tabl_produit->isColumnHidden(column)) {
                                     QString data =ui->tabl_produit->model()->data(ui->tabl_produit->model()->index(row, column)).toString().simplified();
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


void MainWindow::on_B_produit_tri_activated()
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Tri \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();

        if (ui->B_produit_tri->currentText()=="Tri Par ID_PRODUIT")
        {
            ui->tabl_produit->setModel(M.trierMaterielParid());
        }
        else if(ui->B_produit_tri->currentText()=="Tri Par NOM_PRODUIT")
        {
            ui->tabl_produit->setModel(M.trierMaterielParNom());
        }
        else
        {
            ui->tabl_produit->setModel(M.trierMaterielParprix());
        }


}



void MainWindow::on_B_produit_Historique_clicked()
{

}

void MainWindow::on_B_produit_satistique_clicked()
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  Stastique \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from MATERIELLES where  QUANTITER >= 500");
            float dispo1=model->rowCount();

            model->setQuery("select * from MATERIELLES where QUANTITER <500");
            float dispo=model->rowCount();

            float total=dispo1+dispo;
                QString a=QString("stockes . " +QString::number((dispo1*100)/total,'f',2)+"%" );
                QString b=QString("ventes .  "+QString::number((dispo*100)/total,'f',2)+"%" );
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
            chart->setTitle(" des  QUANTITER :Nb QUANTITER: "+ QString::number(total));
            chart->legend()->hide();


            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}


void MainWindow::on_B_produit_Historique_2_clicked()
{
    QFile f("C:/Users/User/Desktop/Gestion_materiele/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  historique \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        if(!f.open(QFile::ReadOnly | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream in(&f);
        QString textt = in.readAll();
        ui->plainTextEdit->setPlainText(textt);
        f.close();

}
