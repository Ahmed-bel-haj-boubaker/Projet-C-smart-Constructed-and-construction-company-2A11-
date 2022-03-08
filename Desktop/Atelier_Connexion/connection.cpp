#include "connection.h"
//Test Tutoriel Git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("rima");//inserer nom de l'utilisateur
db.setPassword("rima");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
