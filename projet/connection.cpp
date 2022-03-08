#include "connection.h"

//Test Tutoriel Git
connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("dali");
    db.setPassword("dali");
    if (db.open())
    test=true;


    return test;
}
