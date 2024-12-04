#include "databaseop.h"

databaseop::databaseop()
{
    //判断是否连接成功
    if (QSqlDatabase::contains("qt_sql_default_connection")==true)
    {
        //,qt_sql_default_connection
      database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        //创建QSQLITE数据库
        database = QSqlDatabase::addDatabase("QSQLITE");
        //设置文件名字
        database.setDatabaseName("MyDataBase.db");
    }


    if (false == database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }




}



databaseop::~databaseop()
{
    database.close();
}


void databaseop::excutSql(QSqlQuery * sqlQuery,QString sql)
{


    //QSqlQuery sqlQuery;
    if(!sqlQuery->exec(sql))//判断是否执行成功
    {
        qDebug()<<"--------"<<sqlQuery->lastError();
    }
    else
    {
        qDebug()<<"执行sql ok";
    }
}
