#ifndef SQLITE_H
#define SQLITE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "sqlite3.h"
#include  <vector>
#include <QString>
using namespace std;

class SQLite
{
public:
    SQLite();
    ~SQLite();
    void initSQLite();
    bool CreateTable(const QString sqlStr);
    vector<QString> qurey(QString select_all_sql);
    QString query(QString sqlStr);
    bool insertdb(QString sqlStr);
    bool updatadb(QString sqlStr);
    bool deletedb(QString sqlStr);
 private:
    QSqlDatabase db;

};

#endif // SQLITE_H
