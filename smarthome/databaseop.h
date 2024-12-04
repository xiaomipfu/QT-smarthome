#ifndef DATABASEOP_H
#define DATABASEOP_H

#include <QSqlDatabase>
#include <QsqlQuery>
#include <QSqlError>
#include <QDebug>


class databaseop
{
public:
    databaseop();
    QSqlDatabase database;
    ~databaseop();
    void excutSql(QSqlQuery * sqlQuery,QString sql);
};

#endif // DATABASEOP_H
