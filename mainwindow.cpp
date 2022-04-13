#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projet.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QString>
#include <QDebug>
#include<QLineEdit>
#include<QIntValidator>
#include<QDate>
#include<QStackedWidget>
#include<QWidget>
#include"notification.h"
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>
#include <QApplication>
#include <QLabel>
#include <QPixmap>

#include"employer.h"
#include <QSoundEffect>
#include<QSound>





using namespace std;
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
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

    notifier = new QSystemTrayIcon(this);
        notifier->setIcon(QIcon(":/prefix/new/res/notification.jpg"));
        notifier->show();
    //



    ui->setupUi(this);
     setWindowTitle("Gestion Des Projets");
     setWindowIcon(QIcon(":/prefix/new/res/constop.png"));




ui->info_2->hide();
     ui->tableView_emploi->setModel(P.afficher());
     ui->dateEdit_emploi->setDisplayFormat("d MMM yyyy");
     ui->dateTimeEdit_emploiS->setDisplayFormat("d MMM yyyy h:m");
     ui->dateTimeEdit_emploiE->setDisplayFormat("d MMM yyyy h:m");
     ui->dateEdit_emploi->setDate(QDate::currentDate());
     ui->dateTimeEdit_emploiS->setDateTime(QDateTime::currentDateTime());
     ui->dateTimeEdit_emploiE->setDateTime(QDateTime::currentDateTime().addDays(1));
     ui->calendarWidget_2->setDateRange(QDate::currentDate(), QDate::currentDate().addDays(30));





    ui->id_supp->setValidator(new QIntValidator(0,9999999,this));
    ui->id->setValidator(new QIntValidator(0,9999999,this));
    ui->l1->setValidator(new QIntValidator(0,9999999,this));
    ui->l2->setValidator(new QIntValidator(0,9999999,this));
    ui->p1->setValidator(new QIntValidator(0,9999999,this));
    ui->p2->setValidator(new QIntValidator(0,9999999,this));
    ui->h1->setValidator(new QIntValidator(0,9999999,this));
    ui->t->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_projet->setModel(P.afficher());
    ui->tab_projet_2->setModel(P.afficher());

    QString date_string_on_db = "05/04/2022";
    QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
    if(QDate::currentDate()==Date)M.appliquerRemise();
  ui->E_produit_ID->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Prix->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Quantiter->setValidator(new QIntValidator(0, 9999999, this));
  ui->E_produit_Remise->setValidator(new QIntValidator(0, 9999999, this));
  QRegExp rx("[a-zA-Z]+");
      QValidator *validator = new QRegExpValidator(rx, this);
      ui->E_produit_Nom->setValidator(validator);

ui->tabl_produit->setModel(M.afficher());



    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearScreen()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemoryClear()));
    connect(ui->MemStore, SIGNAL(released()), this, SLOT(MemoryStore()));
    connect(ui->MemRecall, SIGNAL(released()), this, SLOT(MemoryRecall()));

}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    QMessageBox msgBox;
    bool test;
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
 int S=ui->S->text().toInt();
int cout=ui->cout->text().toInt();



if(nom_projet==""|| localisation==""||id_projet==0||l1==0 ||l2==0||p1==0||p2==0||h1==0||t==0)


            {
                          QMessageBox::critical(nullptr, QObject::tr("vide"),
                          QObject::tr("veuillez saisir tous les champs correctement!\n"), QMessageBox::Cancel);
                          test=false;

            }
else{


   projet P(id_projet, nom_projet, localisation, date_deb,date_fin,l1,l2,p1,p2,h1,t,S,cout);

   if(P.ajouter()){


       PopUp *popUp = new PopUp;
       popUp->setPopupText("PROJET AJOUTER !!!!");
       popUp->show();

       QMediaPlayer *player = new QMediaPlayer;
       player->setMedia(QUrl(":/prefix/new/res/click.mp3"));
       player->play();


notification n;
   n.notification_ajoutProjet();
     msgBox.setText("Ajout avec Succes");
    ui->tab_projet->setModel(P.afficher());
    ui->tab_projet_2->setModel(P.afficher());

ui->id->clear();
ui->nom->clear();
ui->local->clear();
ui->date_deb->clear();
ui->date_fin->clear();
ui->l1->clear();
ui->l2->clear();
ui->p1->clear();
ui->p2->clear();
ui->h1->clear();
ui->t->clear();
QMessageBox::information(nullptr, QObject::tr("Projet Ajouter"),
                         QObject::tr("Projet Ajouter.\n"
                                     "Click Ok to exit."), QMessageBox::Ok);

   }

else{
QMessageBox::critical(nullptr, QObject::tr("Projet Ajouter"),
                      QObject::tr("Erreur !.\n"
                                  "Click Ok to exit."), QMessageBox::Ok);


  } }
}

void MainWindow::on_modifier_clicked()
{

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl(":/prefix/new/res/click.mp3"));
    player->play();

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

PopUp *popUp = new PopUp;
popUp->setPopupText("PROJET MODIFIER !!!!");
popUp->show();

notification n;
n.notification_modifierProjet();


           ui->tab_projet->setModel(P.afficher());
           ui->tab_projet_2->setModel(P.afficher());

           msgBox.setText("modification avec Succes");
           ui->id->clear();
           ui->nom->clear();
           ui->local->clear();
           ui->date_deb->clear();
           ui->date_fin->clear();
           ui->l1->clear();
           ui->l2->clear();
           ui->p1->clear();
           ui->p2->clear();
           ui->h1->clear();
           ui->t->clear();
           QMessageBox::information(nullptr, QObject::tr("Projet Modifier"),
                                    QObject::tr("Projet Modifier.\n"
                                                "Click Ok to exit."), QMessageBox::Ok);

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Projet Modifier"),
                                 QObject::tr("Erreur !.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);


  }
void MainWindow::on_supprimer_clicked()
{

    notification n;
    bool test;
      projet P;
    P.setid(ui->id_supp->text().toInt());
     test=P.supprimer(P.getid());
     QMessageBox msgBox;
     if(test){

         n.notification_supprimerProjet();

         ui->tab_projet->setModel(P.afficher());
         ui->tab_projet_2->setModel(P.afficher());
         ui->id_supp->clear();
         QMessageBox::information(nullptr, QObject::tr("Projet Supprimer"),
                                  QObject::tr("Projet Supprimer.\n"
                                              "Click Ok to exit."), QMessageBox::Ok);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Projet Supprimer"),
                               QObject::tr("Erreur !.\n"
                                           "Click Ok to exit."), QMessageBox::Ok);


}

void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    projet P;
   ui->tab_projet->setModel(P.rechercher(ui->rechercher->text()));

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
ui->stackedWidget->setCurrentIndex(1);
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
        ui->Display->setText(QString::number(dblNewVal));
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







void MainWindow::on_calculer_clicked()
{
      int id_projet=ui->id_s->text().toInt();

      int S=ui->S->text().toInt();
      int cout=ui->cout->text().toInt();
    projet P;
    bool test;
    test=P.calculer(id_projet,S,cout);

      QMessageBox msgBox;
           if(test){
               ui->tab_projet->setModel(P.afficher());
                ui->tab_projet_2->setModel(P.afficher());
               msgBox.setText("Calcul avec Succes");
               ui->S->clear();
              ui->cout->clear();
              ui->id_s->clear();
                   }
               else
                   msgBox.setText("Echec de la calculation");
          msgBox.exec();
    }
void MainWindow::stats(QString table,QString critere,int valeur1,int valeur2,QString unite)
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
                if(critere=="S")
                    critere="S";
                chart->setTitle("Pourcentage Par " +critere+":Nombre Des " +table+" :" +QString::number(total));
                chart->legend()->hide();
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();

}

void MainWindow::on_stat_clicked()
{
    stats("PROJET","S",180,550,"Metre carré");

}

void MainWindow::on_traduction_currentIndexChanged(int index)
{


    if(index==1)
                  {  ui->label_10->setText("Id Projet:");
        ui->label_11->setText("Localisation:");
         ui->label_12->setText("Nom Projet :");
          ui->label_13->setText("Date debut:");
           ui->label_14->setText("Date Fin:");
       ui->ajouter->setText("Ajouter");
       ui->modifier->setText("Modifier");
               ui->supprimer->setText("Supprimer");
            //   ui->rechercher->setText("Search...");
 ui->label_15->setText("L1 (La longeurs total de la maison):");
  ui->label_16->setText("L2 (la longueur du décroché):");
   ui->label_17->setText("P1 (la profondeur du décroché):");
    ui->label_18->setText("P2 (la profondeur du décroché):");
     ui->label_19->setText("H1 (La surface totale des murs):");
      ui->label_20->setText("T (Pente du toit en deg):");
      ui->suiv1->setText("SUIVANT");
      ui->suivi2->setText("SUIVANT");
      ui->avant->setText("AVANT");
      ui->avant_2->setText("AVANT");
      ui->calculer->setText("calculer");
      ui->stat->setText("statistique");
ui->projet->setText("Projet");
ui->materielle->setText("Materielle");
ui->facture->setText("Facture");
ui->fournisseur->setText("Fournisseur");
ui->employer->setText("employer");
ui->client->setText("Client");
ui->label_41->setText("ID Projet:");
ui->label_42->setText("Surfaces Total:");
ui->label_43->setText("Le Cout:");
ui->imprimer->setText("Imprimer");
    }
    if(index==2)
                  {  ui->label_10->setText("Project Id:");
        ui->label_11->setText("Project location :  ");
         ui->label_12->setText("Project Name :   ");
          ui->label_13->setText("       starting date:  ");
           ui->label_14->setText("       Expiry date:  ");
       ui->ajouter->setText("Add");
       ui->modifier->setText("Modify");
               ui->supprimer->setText("Delete");
            //   ui->rechercher->setText("Search...");
 ui->label_15->setText("L1 (the total length of the house):");
  ui->label_16->setText("L2 (the length of the hook):");
   ui->label_17->setText("P1 (the depth of the hook):");
    ui->label_18->setText("P2 (the depth of the hook):");
     ui->label_19->setText("H1 (The total area of ​​​​the walls):");
      ui->label_20->setText("T (Roof pitch in deg):");
      ui->suiv1->setText("Next");
      ui->suivi2->setText("Next");
      ui->avant->setText("Before");
      ui->avant_2->setText("Before");
      ui->calculer->setText("calculate");
      ui->stat->setText("statistical");
ui->projet->setText("Project");
ui->materielle->setText("material");
ui->facture->setText("bill ");
ui->fournisseur->setText("supplier");
ui->employer->setText("employee");
ui->client->setText("customer");
ui->label_41->setText("Project Id:");
ui->label_42->setText("Total Area:");
ui->label_43->setText("The Cost:");
ui->imprimer->setText("Print");

    }
    else if(index==3){
        ui->label_10->setText("       معرف المشروع:  ");
     ui->label_11->setText("       موقع المشروع :  ");
      ui->label_12->setText("       اسم المشروع :  ");
       ui->label_13->setText("       تاريخ البدء :  ");
        ui->label_14->setText("       تاريخ الانتهاء :  ");
    ui->ajouter->setText("أضف");
    ui->modifier->setText("تعديل");
            ui->supprimer->setText(" مسح ");
          //  ui->rechercher->setText(" بحث");
            ui->label_15->setText("L1 (الطول الإجمالي للمنزل):");
             ui->label_16->setText("L2 (طول الخطاف):");
              ui->label_17->setText("P1 (عمق الخطاف):");
               ui->label_18->setText("P2 (عمق الخطاف):");
                ui->label_19->setText("H1 (المساحة الإجمالية للأسوار):");
                 ui->label_20->setText("T (درجة السقف بالدرجة):");
                 ui->suiv1->setText("التالي");
                 ui->suivi2->setText("التالي");
                 ui->avant->setText("قبل");
                 ui->avant_2->setText("قبل");
                 ui->calculer->setText("احسب");
                 ui->stat->setText("إحصائية");
           ui->projet->setText("المشروع");
           ui->materielle->setText("مواد");
           ui->facture->setText("فاكتور ");
           ui->fournisseur->setText("المورد");
           ui->employer->setText("الموظف");
           ui->client->setText("عميل");
           ui->label_41->setText("معرف المشروع: ");
           ui->label_42->setText("المساحة الكلية:");
           ui->label_43->setText("التكلفة:");
           ui->imprimer->setText("اطبع:");

    }

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
            "<img src=':/prefix/new/res/constop.png' ></img>"
                  "</div>"
                 "<div><h1 align='center'>La liste des Projets</h1></div>"
                 "<br/>"
                 "<table id='customers';margin-left:auto;margin-right:auto;>"
                   "<tr>"
                     "<th>Identifiant</th>"
                     "<th>Localisation</th>"
                     "<th>Nom Projet</th>"
                     "<th>Date de debut</th>"
                     "<th>Date fin</th>"

                   "</tr>";

    QString html2="";
        QSqlQuery query;
        query.prepare("select * from projet ");
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
void MainWindow::on_suiv1_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_suivi2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}
void MainWindow::on_avant_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_avant_2_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_tri_local_currentIndexChanged(int index)
{
    if(index==1)
    {
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->nabeul->width();
       int h = ui->nabeul->height();
        ui->nabeul->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }
    else if(index==2)
    {ui->nabeul->clear();
        ui->grom->clear();
        ui->tozeur->clear();
        ui->sousse->clear();
        ui->sfax->clear();
        ui->kass->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->ariana->width();
       int h = ui->ariana->height();
        ui->ariana->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(index==3)
    {ui->nabeul->clear();
        ui->ariana->clear();
        ui->tozeur->clear();
        ui->sousse->clear();
        ui->sfax->clear();
        ui->kass->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->grom->width();
       int h = ui->grom->height();
        ui->grom->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(index==4)
    {ui->nabeul->clear();
        ui->grom->clear();
        ui->ariana->clear();
        ui->sousse->clear();
        ui->sfax->clear();
        ui->kass->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->tozeur->width();
       int h = ui->tozeur->height();
        ui->tozeur->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(index==5)
    {ui->nabeul->clear();
        ui->grom->clear();
        ui->tozeur->clear();
        ui->sousse->clear();
        ui->sfax->clear();
        ui->ariana->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->kass->width();
       int h = ui->kass->height();
        ui->kass->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(index==6)
    {ui->nabeul->clear();
        ui->grom->clear();
        ui->tozeur->clear();
        ui->ariana->clear();
        ui->sfax->clear();
        ui->kass->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->sousse->width();
       int h = ui->sousse->height();
        ui->sousse->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else if(index==7)
    {ui->nabeul->clear();
        ui->grom->clear();
        ui->tozeur->clear();
        ui->sousse->clear();
        ui->ariana->clear();
        ui->kass->clear();

        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->sfax->width();
       int h = ui->sfax->height();
        ui->sfax->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
}

/************************EMPLOYER**************************/

void MainWindow::on_employer_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}


void MainWindow::on_ajouter_Employer_clicked()
{
    employer em;
        QMessageBox msgBox;
       int id_employer=ui->id_employer->text().toInt();
       QString nom=ui->nom_2->text();
       QString prenom=ui->prenom->text();
      QString adresse=ui->adresse->text();
       QString email=ui->email->text();
        QString mdp=ui->mdp->text();

      bool test=em.ajouter(id_employer,nom,prenom,adresse,email,mdp);




       if(test){
        //  N.notification_ajoutProjet();
         msgBox.setText("Ajout avec Succes");
      //  ui->tab_projet->setModel(P.afficher());
       // ui->tab_projet_2->setModel(P.afficher());

       }
           else
               msgBox.setText("Echec de l'ajout");
      msgBox.exec();
}

void MainWindow::on_logOUT_clicked()
{this->close();
    login *l;
    l = new login();
    l->show();
}

void MainWindow::on_logOUT_2_clicked()
{
    this->close();
        login *l;
        l = new login();
        l->show();
}

void MainWindow::on_projet_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_14_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tableView_emploi_clicked(const QModelIndex &index)
{
    QString mtrcl_emp = ui->tableView_emploi->model()->index(index.row(), 0).data().toString();
    ui->label_mtrcl_emploi->setText(mtrcl_emp);
}

void MainWindow::on_dateTimeEdit_emploiS_dateTimeChanged(const QDateTime &dateTime)
{
    bool dateTimeEditS_hadfocus  = true;
    bool dateTimeEditE_hadfocus  = false;
}

void MainWindow::on_calendarWidget_2_clicked(const QDate &date)
{
    bool dateTimeEditS_hadfocus  = true;
    bool dateTimeEditE_hadfocus  = false;
    ui->dateTimeEdit_emploiS->setCalendarPopup(true);
    ui->dateTimeEdit_emploiE->setCalendarPopup(true);

    if( dateTimeEditS_hadfocus )
        ui->dateTimeEdit_emploiE->setDate(date);
    else if( dateTimeEditE_hadfocus )
        ui->dateTimeEdit_emploiS->setDate(date);

    QDateTime date_min = QDateTime::currentDateTime();
    QDateTime date_max = date_min.addDays(30);
    ui->dateTimeEdit_emploiS->setDateTimeRange(date_min, date_max);
    ui->dateTimeEdit_emploiE->setDateTimeRange(date_min, date_max);
}

void MainWindow::on_pushButton_emploi_goto_clicked()
{
    QDate date = ui->dateEdit_emploi->date();
    ui->calendarWidget_2->setSelectedDate(date);
}

void MainWindow::on_dateTimeEdit_emploiE_dateTimeChanged(const QDateTime &dateTime)
{
  bool   dateTimeEditS_hadfocus  = false;
  bool  dateTimeEditE_hadfocus  = true;
}

void MainWindow::on_pushButton_mdf_emploi_clicked()
{
 QString  id_projet = ui->label_mtrcl_emploi->text();
    QDate date_deb = ui->dateTimeEdit_emploiS->date();
    QDate date_fin = ui->dateTimeEdit_emploiE->date();
    qDebug() << P.modifier_emploi(id_projet,date_deb,date_fin);
      ui->tableView_emploi->setModel(P.afficher());
}

void MainWindow::on_suivi2_2_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_avant_3_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_tab_projet_clicked(const QModelIndex &index)
{
  QString id_projet = ui->tab_projet->model()->index(index.row(), 0).data().toString();
  QString nom_projet = ui->tab_projet->model()->index(index.row(), 1).data().toString();
  QString localisation = ui->tab_projet->model()->index(index.row(), 2).data().toString();
  QString l1 = ui->tab_projet->model()->index(index.row(), 5).data().toString();
  QString l2 = ui->tab_projet->model()->index(index.row(), 6).data().toString();
  QString p1 = ui->tab_projet->model()->index(index.row(), 7).data().toString();
  QString p2 = ui->tab_projet->model()->index(index.row(), 8).data().toString();
  QString h1 = ui->tab_projet->model()->index(index.row(),9).data().toString();
  QString t = ui->tab_projet->model()->index(index.row(), 10).data().toString();


    ui->id->setText(id_projet);
    ui->nom->setText(nom_projet);
     ui->local->setText(localisation);
      ui->l1->setText(l1);
       ui->l2->setText(l2);
        ui->p1->setText(p1);
         ui->p2->setText(p2);
          ui->h1->setText(h1);
          ui->t->setText(t);
}

void MainWindow::on_rechercher_local_textChanged(const QString &arg1)
{


    ui->tab_loc->setModel(P.rechercher_local(ui->rechercher_local->text()));


    //projet P;
  QString test=ui->rechercher_local->text();

if(test=="nabeul")
{
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->nabeul->width();
   int h = ui->nabeul->height();
    ui->nabeul->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->info->setText("Projet Nabeul\n****************\n Hammamet nord \n nabeul centre");


}
else if(test=="ariana")
{ui->nabeul->clear();
    ui->grom->clear();
    ui->tozeur->clear();
    ui->sousse->clear();
    ui->sfax->clear();
    ui->kass->clear();
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->ariana->width();
   int h = ui->ariana->height();
    ui->ariana->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->info->setText("Projet Ariana\n****************\n Ariana Soghra rue 8520 \n ESPRIT");

}
else if(test=="grombalia")
{ui->nabeul->clear();
    ui->ariana->clear();
    ui->tozeur->clear();
    ui->sousse->clear();
    ui->sfax->clear();
    ui->kass->clear();
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->grom->width();
   int h = ui->grom->height();
    ui->grom->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->info->setText("Projet Grombalia\n****************\n Turki Hay mandra 8084 \n Grombalia malasine");

}
else if(test=="sfax")
{ui->nabeul->clear();
    ui->ariana->clear();
    ui->tozeur->clear();
    ui->sousse->clear();
    ui->grom->clear();
    ui->kass->clear();
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->grom->width();
   int h = ui->grom->height();
    ui->sfax->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->info->setText("Projet Sfax\n****************\n El Amra rue ibnou Khaldoun \n sidi mansour rue 8500");

}else if(test=="tozeur"){
ui->nabeul->clear();
        ui->grom->clear();
        ui->ariana->clear();
        ui->sousse->clear();
        ui->sfax->clear();
        ui->kass->clear();
        QPixmap pix(":/prefix/new/res/pin-png-39478.png");
       int w = ui->tozeur->width();
       int h = ui->tozeur->height();
        ui->tozeur->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->info->setText("Projet Tozeur\n****************\n Hay Nefta rue Tijeni \n El Wahat rue ibnou jazar");

}
else if(test=="kasserine")
{ui->nabeul->clear();
    ui->grom->clear();
    ui->tozeur->clear();
    ui->sousse->clear();
    ui->sfax->clear();
    ui->ariana->clear();
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->kass->width();
   int h = ui->kass->height();
    ui->kass->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
     ui->info->setText("Projet Kasserine\n****************\n Hay Lwoustani 8021 rue andalos \n El Bassatine rue ibnou khaldoun");
}
else if(test=="sousse")
{ui->nabeul->clear();
    ui->grom->clear();
    ui->tozeur->clear();
    ui->ariana->clear();
    ui->sfax->clear();
    ui->kass->clear();
    QPixmap pix(":/prefix/new/res/pin-png-39478.png");
   int w = ui->sousse->width();
   int h = ui->sousse->height();
    ui->sousse->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->info->setText("projet Sousse\n****************\n Khazema 8030 rue andalos\n");
}

}



void MainWindow::on_notif_clicked()
{
    ui->info_2->show();

ui->info_2->setModel(P.afficher());
}

void MainWindow::on_materielle_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}


/**************MATERILLES***********************/
void MainWindow::on_B_produit_ajouter_clicked()
{
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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
           QString date_string_on_db = "06/04/2022";
           QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
           if(QDate::currentDate()==Date)M.appliquerRemise();
           QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                           notifier->setIcon(QIcon("C:/Users/User/Desktop/Gestion_materiele/main.png"));
                            notifier->show();
                            notifier->showMessage("Materiel ajouté","Succes",QSystemTrayIcon::Information,10000);

                           }
                           else
                           {
           QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                           notifier->setIcon(QIcon(""));
                            notifier->show();
                            notifier->showMessage("Materiel non ajouté","Echéc",QSystemTrayIcon::Critical,10000);

                           }
                           ui->tabl_produit->setModel(M.afficher());
      }




void MainWindow::on_B_produit_supprimer_clicked()
{
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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

    if(test)
    {  QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
        notifier->setIcon(QIcon(""));
         notifier->show();
         notifier->showMessage("Materiel supprimé","Succés",QSystemTrayIcon::Information,10000);

        ui->tabl_produit->setModel(M.afficher());
    }

    else{
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Materiel non supprimé","Echéc",QSystemTrayIcon::Critical,10000);

    }
       }

void MainWindow::on_B_produit_Afficher_clicked()
{
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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
           {
                 QString date_string_on_db = "06/04/2022";
                 QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
                 if(QDate::currentDate()==Date)M.appliquerRemise();


                 ui->tabl_produit->setModel(M.afficher());
                 QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                                 notifier->setIcon(QIcon(""));
                                  notifier->show();
                                  notifier->showMessage("Materiel modifié","Succes",QSystemTrayIcon::Information,10000);


           }
             else
               {  QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                                 notifier->setIcon(QIcon(""));
                                  notifier->show();
                                  notifier->showMessage("Materiel non modifié","Echec",QSystemTrayIcon::Critical,10000);

}}

void MainWindow::on_E_produit_Reherche_textChanged(const QString &arg1)
{
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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



    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");


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
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           QSqlQuery q;
           q.prepare("SELECT * FROM  MATERIELLES ");
           q.exec();
           QString pdf="<br> <h1  style='color:blue'>LISTE DES materielles  <br></h1>\n <br> <table>  <tr>  <th>ID_PRODUIT </th> <th>QUANTITER </th> <th>   </th> <th>NOM_PRODUIT  </th><th>PRIX_PRODUIT </th><th>REMISE  </th> </tr>" ;


           while ( q.next()) {


               pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toInt() +" <td>" +q.value(3).toInt() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toInt() +" "" " "</td> </td>" ;
           }
           doc.setHtml(pdf);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

}




void MainWindow::on_B_produit_tri_activated()
{
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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
    QFile f("C:/Users/ALPHA/Desktop/ProjetAhmed/historique.txt");
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

void MainWindow::on_B_produit_Imprimer_2_clicked()
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
                "<img src=':/prefix/new/res/constop.png' ></img>"
                      "</div>"
                     "<div><h1 align='center'>La liste des Projets</h1></div>"
                     "<br/>"
                     "<table id='customers';margin-left:auto;margin-right:auto;>"
                       "<tr>"
                         "<th>Identifiant</th>"
                         "<th>Localisation</th>"
                         "<th>Nom Projet</th>"
                         "<th>Date de debut</th>"
                         "<th>Date fin</th>"

                       "</tr>";

        QString html2="";
            QSqlQuery query;
            query.prepare("select * from MATERILLES ");
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


void MainWindow::on_suiv1_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_avant_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);

}
