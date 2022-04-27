#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QValidator>
#include "conges.h"
#include "employer.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QApplication>
#include <QtCore>
#include <QPdfWriter>
#include <QMessageBox>
#include <QLabel>
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <string>
#include <QDateEdit>
#include <QDate>
#include <QCalendarWidget>
#include <QImage>
#include <QVBoxLayout>
#include <QFile>
#include <QPixmap>
#include <QCheckBox>
#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ajoutid_l->setValidator(new QIntValidator(0, 999999,  this));
    ui->ajout_num->setValidator(new QIntValidator(0, 999999,  this));

    QPixmap pix("C:/Users/dalid/OneDrive/Documents/Nouveau dossier (2)/res/papa.png");
    pix.scaledToWidth(ui->label_image->width(), Qt::SmoothTransformation);
    ui->label_pic->setPixmap(pix);


    ui->tableView->setModel(e.afficher());
    //ui->tableView_2->setModel(v.afficher());





    ui->label_a_1->setText("-------");
        arduino = new QSerialPort(this);
        serialBuffer = "";
        parsed_data = "";
        temperature_value = 0.0;


        bool arduino_is_available = false;
        QString arduino_uno_port_name;
        //
        //  For each available serial port
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_uno_port_name = serialPortInfo.portName();
                }
            }
        }


        if(arduino_is_available){
            qDebug() << "Found the arduino port...\n";
            arduino->setPortName(arduino_uno_port_name);
            arduino->open(QSerialPort::ReadOnly);
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setFlowControl(QSerialPort::NoFlowControl);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }else{
            qDebug() << "Couldn't find the correct port for the arduino.\n";
            QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int id_l=ui->ajoutid_l->text().toInt();
    QString nom=ui->ajout_nom->text();
    QString prenom=ui->ajout_prenom->text();
    int num=ui->ajout_num->text().toInt();
    QString adresse=ui->lineEdit->text();
    QString mail=ui->lineEdit_2->text();




    employer e(id_l,nom,prenom,num,adresse,mail);

    bool test=e.ajouter();
    if(test)
    {
        ui->tableView->setModel(e.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Ajout effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Ajout non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);

}
void MainWindow::on_pb_supprimer_2_clicked()
{
    int id_l=ui->ajoutid_l1->text().toInt();
    bool test=e.supprimer(id_l);
    if(test)
    {

        ui->tableView->setModel(e.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Supression effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Suppression non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_Modifier_clicked()
{
    employer e;
     int id_l=ui->ajoutid_l->text().toInt();
     QString nom=ui->ajout_nom->text();
     QString prenom=ui->ajout_prenom->text();
     int num=ui->ajout_num->text().toInt();
     QString adresse=ui->lineEdit->text();
     QString mail=ui->lineEdit_2->text();

    bool test= e.modifier(id_l,nom,prenom,num,adresse,mail);
     QMessageBox msg;
    if(test)
    {    ui->tableView->setModel(e.afficher());
                    msg.setText("modifie avec succés");

                    }
                    else
                    {
                    msg.setText("Echec au niveau de la modification ");
                    }
                    msg.exec();

                ui->ajoutid_l->clear();
                ui->ajout_nom->clear();
                ui->ajout_prenom->clear();
                ui->ajout_num->clear();
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();

}



void MainWindow::on_recherche_mod_clicked()
{
    QSqlQuery query;
    query.prepare("select nom, prenom, num, adresse, mail from employer where id_l=?;");
    query.addBindValue(ui->ajoutid_l->text());
    if(query.exec())
       {
        while(query.next())
         {

    ui->ajout_prenom->setText(query.value(1).toString());
    ui->ajout_nom->setText(query.value(0).toString());
    ui->ajout_num->setText(query.value(2).toString());
    ui->lineEdit->setText(query.value(3).toString());
    ui->lineEdit_2->setText(query.value(4).toString());
            }
        }
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(e.afficherRech(ui->lineEditRech->text(),ui->comboBoxRech->currentText()));

}

void MainWindow::on_pushButton_4_clicked()
{
     ui->tableView->setModel(e.afficherTri(ui->comboBoxTri->currentText()));
}





void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_print_clicked()
{


    int montant = ui->ajout_6->text().toInt();
    int duree = ui->ajout_5->text().toInt();
    int taux = ui->ajout_4->text().toInt();
    int salaire = ui->ajout_3->text().toInt();

    float pource = 0;
    float men = 0;

    if(duree != 0){
    men = (montant +((montant * taux)/100))/(duree * 12);
    }else
    {
        QMessageBox::information(nullptr, QObject::tr("not ok") ,
                                 QObject::tr(" Veuillez remplir les champs vides."
                                             " Clicked Cancel to exit.") , QMessageBox::Cancel);
    }


    if(salaire != 0){
        pource = (men * 100)/salaire;
    }else
    {
        QMessageBox::information(nullptr, QObject::tr("not ok") ,
                                 QObject::tr(" Veuillez remplir les champs vides."
                                             " Clicked Cancel to exit.") , QMessageBox::Cancel);
    }

    ui->label_2->setNum(men);
    ui->label_25->setNum(pource);
}



void MainWindow::on_print_3_clicked()
{
    int montant = ui->ajout_20->text().toInt();
    int duree = ui->ajout_17->text().toInt();
    int taux = ui->ajout_19->text().toInt();

    float men = 0;

    if (true){
        men = ((montant * (duree*12))-(((montant * (duree*12))/100)*taux));
    }else
    {
        QMessageBox::information(nullptr, QObject::tr("not ok") ,
                                 QObject::tr(" Veuillez remplir les champs vides."
                                             " Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    ui->label_46->setNum(men);

}

void MainWindow::on_print_7_clicked()
{

    QDate date = QDate::currentDate();
    QString dte=date.toString("dd.MM.yyyy");

    QString nomprenom = ui->ajout_2->text();
    QString poste = ui->ajout_7->text();

    int montant = ui->ajout_6->text().toInt();
    int taux = ui->ajout_4->text().toInt();
    int x = ui->ajout_5->text().toInt();
    int duree = x*12;

    QString html1="<!DOCTYPE html>"
                    "<html>"
                    "<head>"
                    "<style>"
                    "table {"
                      "border-collapse: collapse;"
                      "width: 100%;"
                    "}"

                    "th, td {"
                      "text-align: left;"
                      "padding: 8px;"
                    "}"

                    "tr:nth-child(even){background-color: #f2f2f2}"

                    "th {"
                      "background-color: #04AA6D;"
                      "color: white;"
                    "}"
                    "</style>"
                    "</head>"



                  "<body>"
                  "<div align=right>"
                     "Ariana,"+dte+""
                  "</div>"
                    "<br><br>"
                 "<div style='font-size:150px;'>"
                        "<strong>Nom : "+nomprenom+"</strong>"
                 "</div>"
                    "<br>"
                    "<div style='font-size:150px;'>"
                        "<strong>Poste : "+poste+"</strong>"
                    "</div>"
                                         "<br><br>"


                 "<table>"
                   "<tr>"
                     "<th>Mois</th>"
                     "<th>Interêts</th>"
                     "<th>Capital amorti</th>"
                     "<th>Reste dû</th>"
                     "<th></th>"

                   "</tr>";

    QString html2="";

        float men = 0;


        men = (montant +((montant * taux)/100))/(duree);
           int taux_en_tnd = (montant *taux)/100;
        int f = montant;
           for (int i =1;i<=duree;i++){

                   f -=men;
                   QString ddd = QString::number(i);
                   html2=html2+"<tr>"
                        "<td>Mois "+ddd+"<td>";

                   QString taux_en_tnd1 = QString::number(taux_en_tnd-(taux_en_tnd*i/100));
                   html2=html2+"<td>"+taux_en_tnd1+" tnd<td>";

                   QString men1 = QString::number(men-(taux_en_tnd-(taux_en_tnd*i/100)));
                   html2=html2+"<td>"+men1+" tnd<td>";

                   QString f1 = QString::number(f);
                   if(i == duree){
                       html2=html2+"<td> 0 tnd<td>"
                             "</tr>";
                   }else {
                   html2=html2+"<td>"+f1+" tnd<td>"
                         "</tr>";
                   }

               }



            // ////////
QString html3="</table>"
              "<br><br><br><br><br><br><br><br>"
              "<div style='align:right;color:red;bottom: 20px;';>"
              "Constop"
              "</div>"

                 "</body>"
                 "</html> ";


// /////////////////////////////////////////////////////////////

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


void MainWindow::on_print_5_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images (*.png *.jpeg *.jpg"));

    if(QString::compare(filename,QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
            image = image.scaledToWidth(ui->label_image->width(), Qt::SmoothTransformation);

            ui->label_image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            // Error handling
        }
    }
}

void MainWindow::on_print_4_clicked()
{

    QString nom=ui->ajout_27->text();
    QString responsable=ui->ajout_28->text();
    QString type=ui->comboBox->currentText();

    QDate date_d=ui->date_d->date();
    QDate date_f=ui->date_f->date();

    int nbr=ui->ajout_34->text().toInt();

    QString commentaire=ui->ajout_35->text();
    QString acceptation=ui->comboBox_2->currentText();


    conges v(nom,responsable,type,date_d,date_f,nbr,commentaire,acceptation);

    bool test=v.ajouter_a();

    if(test)
    {
        //ui->tableView_2->setModel(e.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Ajout effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Ajout non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}


void MainWindow::update_label_a_1()

{

        data=A.read_from_arduino ();

        if(data=="1")

            ui->label_a_1->setText ("ON"); // si les données reçues de arduino via la liaison série sont égales à 1

        // alors afficher ON

        else if (data=="0")

            ui->label_a_1->setText("OFF"); //alors afficher ON // si les données reçues de arduino via la liaison série sont égales à e

}




void MainWindow::on_pushButton_a_clicked ()

{
    A.write_to_arduino ("1"); //envoyer 1 à arduino

}

void MainWindow::on_pushButton_a_2_clicked() // implémentation du slot bouton off k

{

    A.write_to_arduino ("0"); //envoyer 0 à arduino

}

void MainWindow::on_pushButton_a_3_clicked () {// implémentation du slot bouton +

    A.write_to_arduino ("2"); //envoyer 2 à arduino
}



void MainWindow::on_pushButton_a_4_clicked () // implémentation du slot bouton - A.write_to_arduino ("3"); //envoyer 3 à arduino
{
    A.write_to_arduino ("3");
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->tableView_2->setModel(v.afficherRech(ui->lineEditRech_2->text(),ui->comboBoxRech_2->currentText()));

}








void MainWindow::readSerial()
{
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */
    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

    //  Check to see if there less than 3 tokens in buffer_split.
    //  If there are at least 3 then this means there were 2 commas,
    //  means there is a parsed temperature value as the second token (between 2 commas)
    if(buffer_split.length() < 3){
        // no parsed value yet so continue accumulating bytes from serial in the buffer.
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
        serialBuffer = "";
        qDebug() << buffer_split << "\n";
        parsed_data = buffer_split[1];
        temperature_value = (9/5.0) * (parsed_data.toDouble()) + 32; // convert to fahrenheit
        qDebug() << "Temperature: " << temperature_value << "\n";
        parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
        MainWindow::updateTemperature(parsed_data);
    }

}

void MainWindow::updateTemperature(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->label_a_1->setText(sensor_reading);
}
