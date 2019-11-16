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

QList<RecordInfo> LaborEyeDatabase::selectRecordInfo(QDateTime startDateTime, QDateTime endDateTime,
                                                     QString stranger, QString idCard,
                                                     int nowPage, int pageSize)
{
    QList<RecordInfo> recordInfoList;

    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return recordInfoList;
    }
    QSqlQuery query;
    QString sqlSentence;
    if(stranger == QString::fromLocal8Bit("是")) {
        if(idCard == "") { //查询所有的陌生人
            sqlSentence = sqlSetting->value("Select/selectRecords_stranger").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") { //根据陌生人编号查询陌生人
            sqlSentence = sqlSetting->value("Select/selectRecords_by_idCard_Stranger").toString();
            query.bindValue(":idCard", idCard);
        }
    } else if(stranger == QString::fromLocal8Bit("否")) {
        if(idCard == "") { //查询所有非陌生人
            sqlSentence = sqlSetting->value("Select/selectRecords_noStranger").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") {   //根据身份证编号查询非陌生人
            sqlSentence = sqlSetting->value("Select/selectRecords_by_idCard_noStranger").toString();
            query.prepare(sqlSentence);
            query.bindValue(":idCard", idCard);
        }
    } else if(stranger == QString::fromLocal8Bit("不限")) {
        if(idCard == "") {  //查询所有记录
            sqlSentence = sqlSetting->value("Select/seletRecords_all").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") {   //根据身份证号/陌生人编号查询记录
            sqlSentence = sqlSetting->value("Select/selectRecords_by_idCard").toString();
            query.prepare(sqlSentence);
            query.bindValue(":idCard", idCard);
        }
    }

    query.bindValue(":startDateTime", startDateTime);
    query.bindValue(":endDateTime", endDateTime);
    query.bindValue(":startId", (nowPage-1)*pageSize);
    query.bindValue(":pageSize", pageSize);
    query.exec();
    closeDatabase();

    RecordInfo recordInfo;
    while(query.next()) {
        recordInfo.setId(query.value("id").toInt());
        recordInfo.setApplicant(query.value("applicant").toString());
        recordInfo.setAvatarId(query.value("avatar_id").toString());
        recordInfo.setStranger(query.value("stranger").toBool());
        recordInfo.setSimilar(query.value("similar").toInt());
        recordInfo.setDel(query.value("del").toInt());
        recordInfo.setTimeValue(query.value("time_value").toDateTime());
        recordInfoList.append(recordInfo);
    }

    return recordInfoList;
}

int LaborEyeDatabase::cntRecords()
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/cntRecords").toString();
    query.prepare(sqlSentence);
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}
