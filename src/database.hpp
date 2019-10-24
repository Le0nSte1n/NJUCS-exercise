#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QDebug>
#include <QFile>

namespace Warehouse {
    class Database{
    public:
        Database(QString name, QString dbPath="warehouse.db"){
            //初始化数据库
            db = QSqlDatabase::addDatabase("QSQLITE",name);
            db.setDatabaseName(dbPath);
            if(db.open()){
                qDebug()<<dbPath+" : has been opened successfully";
            }
            else {
                qDebug()<<"Cannot open db: "<<dbPath<<" : "<<db.lastError();
            }

            query = new QSqlQuery(db);
        }

        ~Database(){
            db.close();
            delete query;
        }

        bool createTables()
        {
            //创建property
            sql = "CREATE TABLE \"property\" ("
                        "\"id\"	INTEGER NOT NULL UNIQUE,"
                        "\"type\"	TEXT NOT NULL,"
                        "\"subject\"	TEXT,"
                        "\"keywords\"	TEXT NOT NULL,"
                        "\"source\"	TEXT,"
                        "\"status\"	INTEGER,"
                        "PRIMARY KEY(\"id\")"
                    ");";
            query->prepare(sql);
            if(query->exec()){
                qDebug()<<"Create table property successfully";
            }
            else {
                qDebug()<<"Cannot create table property: "<<query->lastError();
                return false;
            }

            //创建question表
            sql = "CREATE TABLE \"data\" ("
                                         "\"id\"	INTEGER NOT NULL UNIQUE,"
                                         "\"title\"	TEXT NOT NULL,"
                                         "\"question\"	TEXT NOT NULL,"
                                         "\"answer\"	TEXT,"
                                         "\"tip\"	TEXT,"
                                         "PRIMARY KEY(\"id\")"
                                     ");";
            query->prepare(sql);
            if(query->exec()){
                qDebug()<<"Create table data successfully";
            }
            else {
                qDebug()<<"Cannot create table question : "<<query->lastError();
                return false;
            }

            sql = "CREATE TABLE \"subject\" ("
                        "\"id\"	INTEGER NOT NULL UNIQUE,"
                        "\"value\"	TEXT NOT NULL,"
                        "PRIMARY KEY(\"id\")"
                    ");";
            query->prepare(sql);
            if(query->exec()){
                qDebug()<<"Create table subject successfully";
            }
            else {
                qDebug()<<"Cannot create table subject: "<<query->lastError();
                return false;
            }

            sql = "CREATE TABLE \"type\" ("
                        "\"id\"	INTEGER NOT NULL UNIQUE,"
                        "\"value\"	TEXT NOT NULL,"
                        "PRIMARY KEY(\"id\")"
                    ");";
            query->prepare(sql);
            if(query->exec()){
                qDebug()<<"Create table type successfully";
            }
            else {
                qDebug()<<"Cannot create table type : "<<query->lastError();
                return false;
            }

            return true;
        }

        int getMaxId(QString tableName)
        {
            int maxId = -1;
            sql = QString("select max(id) from %1").arg(tableName);
            query->prepare(sql);
            if(query->exec()){
                while(query->next()){
                    maxId = query->value(0).toInt();
                }
            }
            else {
                qDebug()<<"Cannot query max id from table : "<<tableName;
            }
            return maxId;
        }

    public:
        QString sql;
        QSqlQuery *query;

    private:
        QSqlDatabase db;
    };
}

#endif // DATABASE_HPP
