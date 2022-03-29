#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

class Connection
{
   QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnect();
};

#endif // CONNECTION_H
