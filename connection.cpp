#include"connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

//Test Tutoriel GIT
Connection::Connection(){}

bool Connection::createconnect()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;

db.setDatabaseName("test_bd");
db.setUserName("ibtihel");//inserer nom de l'utilisateur
db.setPassword("ibtihel");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection::closeConnect(){db.close();}
