#include "mainwindow.h"
#include "connection.h"
#include "employer.h"
#include "conges.h"
#include "arduino.h"
#include <QApplication>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnection();
    MainWindow w;
    if(test)
    {
    w.show();
    QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("connection successful. \n"
                 "Click Cancel to exit. "), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                     QObject::tr("connection faiked. \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


    w.show();
    return a.exec();
}
