#include "laboreyedatabase.h"

LaborEyeDatabase* LaborEyeDatabase::laborEyeDatabase = nullptr;

LaborEyeDatabase::LaborEyeDatabase()
{
    //数据库配置信息
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setPort(Config::getCfg()->getDatabasePort());
    db.setHostName(Config::getCfg()->getDatabaseIP());
    db.setDatabaseName(Config::getCfg()->getDataBaseName());
    db.setUserName(Config::getCfg()->getDatabaseUsername());
    db.setPassword(Config::getCfg()->getDatabasePasword());

    //加载sql语句配置文件
    sqlSetting = new QSettings(":/Src/sql.ini", QSettings::IniFormat);
}

bool LaborEyeDatabase::openDatabase()
{
    //数据库打开失败
    if(!db.open())
        return false;
    return true;
}

void LaborEyeDatabase::closeDatabase()
{
    if(db.isOpen())
        db.close();
}

void LaborEyeDatabase::sqlTest()
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QObject::tr("数据库连接失败!"), db.lastError().text());
        return;
    }
    QSqlQuery query;
    qDebug() << "Test SQL Sentence: " << sqlSetting->value("Test/testSQL").toString();
    query.prepare(sqlSetting->value("Test/testSQL").toString());
    query.exec();
    closeDatabase();
    if(query.next())
        qDebug() << "Test Result: " << query.value(0).toInt();
}
