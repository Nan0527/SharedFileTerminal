#include "sqlite.h"

SQLite::SQLite()
{
    qDebug() << QSqlDatabase::drivers();
}

SQLite::~SQLite()
{

}

void SQLite::initSQLite()
{
    //创建数据库实例(即创建数据库连接)
    //addDatabase() 第一个参数为要装载的驱动，这里使用qt自带的qsqlite
    //第二个参数"connectDB_1" 为自定义的数据库连接名，不是数据库名 )
    db = QSqlDatabase::addDatabase("QSQLITE", "connectDB_1");
    //选择要使用的数据库名字   即工程目录下的stock.db
    //因为连接的是本地sqlite数据库，所以  主机，用户名，密码不需要配置
    db.setDatabaseName("stock.db");
    //尝试连接数据库
    if (!db.open()) {
        qDebug()<<QString("无法打开数据库，错误为:" + db.lastError().text());
    }
    else {
        qDebug()<<QString(QStringLiteral("数据库已成功打开")).toStdString().data();
        qDebug()<<"数据库含表:"<< db.tables();  //输出数据库里面的表
        //QSL语句，参数里要填入一个数据库实例,而且一定要在 db.open()以后定义，
        //之前报了一个out of memory Unable to execute statement 就是因为在db.open()前就定义了
        /*QSqlQuery query( db );
        //如果表table_1不存在  则创建
        if( ! db.tables().contains("table_1") ) {
           bool correct =  query.exec(" create table table_1 ("
                            " sid  INTEGER PRIMARY KEY AUTOINCREMENT ,"
                            " scode varchar not null ,"
                            " sname varchar not null "
                            ")  ");
           if(!correct)
               qDebug()<<QString("建表语句执行错误：" + query.lastError().text());
           else
               qDebug()<<QString("建表table_1 成功");
        }
        else qDebug()<<QString("表table_1已存在");*/
    }
}

bool SQLite::CreateTable(const QString sqlStr)
{
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(sqlStr); //创建表
        if(!sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_query.lastError();
            return false;
        }
        db.close();
        return true;
    }
    return false;

}
vector<QString> SQLite::qurey(QString select_all_sql)//查询所有记录
{
    vector<QString> res;
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                for(int i=0;i<sql_query.ValuesAsColumns;i++)
                {
                    res.push_back(sql_query.value(i).toString());
                }
            }
        }
    }
    db.close();
    return res;
}

QString SQLite::query(QString sqlStr)//查询一个值
{
    QString res;
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(sqlStr);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                res=sql_query.value(0).toString();
            }
        }
    }
    db.close();
    return res;
}
bool SQLite::insertdb(QString sqlStr)//插入数据库
{
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(sqlStr);
        if(!sql_query.exec())
        {
            qDebug()<<QObject::tr("insert failed");
            qDebug()<<sql_query.lastError();
            return false;
        }
        db.close();
        return true;
    }
    return false;
}
bool SQLite::updatadb(QString sqlStr)//更新数据库
{
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(sqlStr);
        if(!sql_query.exec())
        {
            qDebug()<<QObject::tr("updata failed");
            qDebug()<<sql_query.lastError();
            return false;
        }
        db.close();
        return true;
    }
    return false;
}
bool SQLite::deletedb(QString sqlStr)//删除数据库
{
    if(db.open())
    {
        QSqlQuery sql_query;
        sql_query.prepare(sqlStr);
        if(!sql_query.exec())
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_query.lastError();
            return false;
        }
        db.close();
        return true;
    }
    return false;
}
