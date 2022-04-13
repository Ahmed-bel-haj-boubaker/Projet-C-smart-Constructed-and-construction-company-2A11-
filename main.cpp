#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include <QtSql>
#include <iostream>
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include "login.h"
#include "ui_login.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
login l;
    Connection c;
    bool test=c.createconnect();

    if(test)

    {l.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
      {  QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}



    return a.exec();
}
