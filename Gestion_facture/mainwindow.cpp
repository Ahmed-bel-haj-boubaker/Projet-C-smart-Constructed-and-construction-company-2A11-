#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"facture.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>
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
#include<QSqlQuery>
#include<QtMath>
#include<QSystemTrayIcon>
#include "qrcode.h"

using namespace qrcodegen ;


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool subTrigger = false;
bool addTrigger = false;

QString memory = "0";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_fac->setModel(E.afficher());
     ui->tab_Fac->setModel(E.afficher());
    //Set up empty display panel

    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add1, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract1, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply1, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide1, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals1, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearScreen()));
    connect(ui->MemClear1, SIGNAL(released()), this, SLOT(MemoryClear()));
    connect(ui->MemStore1, SIGNAL(released()), this, SLOT(MemoryStore()));
    connect(ui->MemRecall1, SIGNAL(released()), this, SLOT(MemoryRecall()));


    QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                             notifier->setIcon(QIcon(""));
                              notifier->show();
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
    float prix_produit=ui->le_produit->text().toDouble();
    float prix_projet=ui->le_projet->text().toDouble();
    float montant_total=ui->le_montant->text().toDouble();
    Facture E(id_facture,nom_facture,prenom_facture,date_facture,prix_produit,prix_projet,montant_total);
    bool test=E.ajouter(id_facture,nom_facture,prenom_facture,date_facture,prix_produit,prix_projet,montant_total);
           QMessageBox msgBox;

              if(test)
              {
                  msgBox.setText("ajout avec succes");
                  QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                                           notifier->setIcon(QIcon(""));
                                            notifier->show();
                  notifier->showMessage("facture ajouté","OK",QSystemTrayIcon::Critical,10000);

                  ui->table_fac->setModel(E.afficher());
                   ui->tab_Fac->setModel(E.afficher());
              msgBox.exec();

              }
              else
              {
                  msgBox.setText("echec");
              msgBox.exec();
              }


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
        ui->table_fac->setModel(E.afficher());
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
   {ui->table_fac->setModel(E.afficher());
   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                     QObject::tr("invite modifiée.\n"
                                 "Click ok to exit."), QMessageBox::Ok);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                     QObject::tr("echec d'ajout !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    Facture E;
   ui->table_fac->setModel(E.rechercher(ui->rechercher->text()));
}

void MainWindow::on_tri_currentIndexChanged(int index)
{
    if(index==1)
    {ui->table_fac->setModel(E.tri_idP());
    }else if (index==2){
        ui->table_fac->setModel(E.tri_Mon());}
    else if (index==3)
    {ui->table_fac->setModel(E.tri_nomP());
    }

}

void MainWindow::on_suiv1_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}



void MainWindow::on_imprimer_clicked()
{
    QDate date = QDate::currentDate();
    QString dte=date.toString("dd.MM.yyyy");
    QString html1="<!DOCTYPE html>"
                 "<html>"
                 "<head>"
                 "<style>"
                 "#customers {"
                  " font-family: 'Trebuchet MS', Arial, Helvetica, sans-serif;"
                   "border-collapse: collapse;"
                    "width: 100%;"
                 "}"

                 "#customers td, #customers th {"
                   "border: 1px solid #ddd;"
                   "padding: 8px;"
                 "}"

                 "#customers tr:nth-child(even){background-color: #f2f2f2;}"

                 "#customers tr:hover {background-color: #ddd;}"

                 "#customers th {"
                   "padding-top: 12px;"
                   "padding-bottom: 12px;"
                   "text-align: left;"
                   "background-color: #4CAF50;"
                   "color: white;"
                 "}"
                 "</style>"
                 "</head>"
                 "<body>"
                  "<div align=right>"
                     "Ariana,"+dte+""
                  "</div>"
                 "<div><h1 align='center'>La liste des des Factures</h1></div>"
                 "<br/>"
                 "<table id='customers';margin-left:auto;margin-right:auto;>"
                   "<tr>"
                     "<th>Identifiant</th>"
                     "<th>Nom</th>"
                     "<th>Prenom</th>"
                     "<th>Date Facture</th>"
                     "<th>Montant Total</th>"

                   "</tr>";

    QString html2="";
        QSqlQuery query;
        query.prepare("select * from facture ");
       if (query.exec())
        {
            while (query.next())
            {
               html2=html2+"<tr>"
              "<td>"+query.value(0).toString()+"</td>"
              "<td>"+query.value(1).toString()+"</td>"
              "<td>"+query.value(2).toString()+"</td>"
              "<td>"+query.value(3).toString()+"</td>"
              "<td>"+query.value(4).toString()+"</td>"

            "</tr>";
            }
        }

QString html3="</table>"
                 "</body>"
                 "</html> ";
QString html=html1+html2+html3;

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);

    //printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QPrintDialog *dialog = new QPrintDialog(&printer);
    if (dialog->exec() == QDialog::Accepted)
    {
        document.print(&printer);
        QPainter painter (&printer);
        painter.begin(&printer);



    printer.setPageMargins(QMarginsF(15, 15, 15, 15));


    painter.end();

    }
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(buttonVal);
    }
    else
    {
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}


void MainWindow::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    subTrigger = false;
    addTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    //Parsing math buttons
         if (QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    else if (QString::compare(buttonVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }

    ui->Display->setText("");
}

void MainWindow::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger)
    {
             if (addTrigger)
        {
            solution = calcVal + dblDisplayVal;
        }
        else if (subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        }
        else if (multTrigger)
        {
            solution = calcVal * dblDisplayVal;
        }
        else if (divTrigger)
        {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void MainWindow::ClearScreen()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    if (QString::compare(buttonVal, "AC", Qt::CaseInsensitive) == 0)
    {
       ui->Display->setText("0");
    }
}

void MainWindow::MemoryClear()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    if (QString::compare(buttonVal, "MC", Qt::CaseInsensitive) == 0)
    {
       memory = "0";
    }
}

void MainWindow::MemoryStore()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    if (QString::compare(buttonVal, "MS", Qt::CaseInsensitive) == 0)
    {
       memory = ui->Display->text();
    }
}

void MainWindow::MemoryRecall()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    if (QString::compare(buttonVal, "MR", Qt::CaseInsensitive) == 0)
    {
        if (QString::compare(memory, "0"))
        ui->Display->setText(memory);
    }
}





void MainWindow::on_calcul_clicked()
{
    int id_facture=ui->id_fac->text().toInt();

    float montant_total=ui->sommeF->text().toInt();
  Facture E;
  bool test;
  test=E.calculer(id_facture,montant_total);

    QMessageBox msgBox;
         if(test){
             ui->tab_Fac->setModel(E.afficher());
              ui->table_fac->setModel(E.afficher());
             msgBox.setText("Calcul avec Succes");
                 }
             else
                 msgBox.setText("Echec de la calculation");
        msgBox.exec();
}
void MainWindow::statF(QString table,QString critere,int valeur1,int valeur2,QString unite)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString valeur1QString=QString::number(valeur1);
    QString valeur2QString=QString::number(valeur2);
                model->setQuery("select * from "+table+" where "+critere+"<"+valeur1QString);
                float countFirst=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+" between " +valeur1QString+ " and "+valeur2QString);
                float countSecond=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+">"+valeur2QString);
                float countThird=model->rowCount();
                float total=countFirst+countSecond+countThird;
                QString a=QString("moins de "+valeur1QString+" "+unite+" "+QString::number((countFirst*100)/total,'f',2)+"%" );
                QString b=QString("entre "+valeur1QString+ " et " +valeur2QString+" "+unite+" "+QString::number((countSecond*100)/total,'f',2)+"%" );
                QString c=QString("Plus que "+valeur2QString +" "+unite+" "+QString::number((countThird*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,countFirst);
                series->append(b,countSecond);
                series->append(c,countThird);
        if (countFirst!=0)
        {QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());}
        if ( countSecond!=0)
        {
                 QPieSlice *slice1 = series->slices().at(1);
                 slice1->setLabelVisible();
        }
       if(countThird!=0)
        {
                 QPieSlice *slice2 = series->slices().at(2);
                 slice2->setLabelVisible();
        }
                QChart *chart = new QChart();
                chart->addSeries(series);
                if(critere=="montant_total")
                    critere="montant_total";
                chart->setTitle("Pourcentage Par " +critere+":Nombre Des " +table+" :" +QString::number(total));
                chart->legend()->hide();
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();

}
void MainWindow::on_statF_clicked()
{
    statF("FACTURE","montant_total",1000,5000,"DT");
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int tabeq=ui->table_fac->currentIndex().row();
    QVariant idd=ui->table_fac->model()->data(ui->table_fac->model()->index(tabeq,0));
    QString numero= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from FACTURE where ID_FACTURE=:id");
    qry.bindValue(":id",numero);
    qry.exec();
    QString  NOM_FACTURE,PRENOM_FACTURE,DATE_FACTURE,PRIX_PRODUIT;

    while(qry.next())
    {
        numero=qry.value(0).toString();
        NOM_FACTURE=qry.value(1).toString();
        PRENOM_FACTURE=qry.value(2).toString();
        DATE_FACTURE=qry.value(3).toString();
          PRIX_PRODUIT=qry.value(4).toString();
    }
    numero=QString(numero);
    numero="ID:"+numero+"NOM_FACTURE:"+NOM_FACTURE+"PRENOM_FACTURE:"+PRENOM_FACTURE+"DATE_FACTURE:"+DATE_FACTURE+"PRIX_PRODUIT:"+PRIX_PRODUIT;
    QrCode qr = QrCode::encodeText(numero.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++)
    {
    for (int x = 0; x < qr.getSize(); x++)
    {
    int color = qr.getModule(x, y);  // 0 for white, 1 for black

    // You need to modify this part
    if(color==0)
       im.setPixel(x, y,qRgb(254, 254, 254));
    else
       im.setPixel(x, y,qRgb(0, 0, 0));
    }
    }
    im=im.scaled(200,200);
    ui->label_57->setPixmap(QPixmap::fromImage(im));

}

void MainWindow::on_Supp_btn_2_clicked()
{
    int tabeq=ui->table_fac->currentIndex().row();
    QVariant idd=ui->table_fac->model()->data(ui->table_fac->model()->index(tabeq,0));
    QString numero= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from FACTURE where ID_FACTURE=:id");
    qry.bindValue(":id",numero);
    qry.exec();
    int  NOM_FACTURE,PRENOM_FACTURE,DATE_FACTURE,PRIX_PRODUIT,projet;

    while(qry.next())
    {
        numero=qry.value(0).toString();

          PRIX_PRODUIT=qry.value(4).toInt();
          projet=qry.value(5).toInt();
    }
    int som=PRIX_PRODUIT+projet;
    QString somm=QString::number(som);
    ui->id_val_2->setText(somm);
}
