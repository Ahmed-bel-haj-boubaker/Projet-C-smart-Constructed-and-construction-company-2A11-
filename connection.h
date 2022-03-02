#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
//test
class Connection
{
public:
    Connection();
    bool createconnect();
    QSqlDatabase db;
};

#endif // CONNECTION_H
