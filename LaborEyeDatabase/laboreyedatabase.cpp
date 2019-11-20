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

QList<QString> LaborEyeDatabase::selectBuidingId()
{
    QList<QString> buildingId;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return buildingId;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectBuidingId").toString();
    query.prepare(sqlSentence);
    query.exec();
    closeDatabase();

    while(query.next())
        buildingId.append(query.value("building").toString());
    return buildingId;
}

QList<QString> LaborEyeDatabase::selectUnitId(QString buildingId)
{
    QList<QString> unitId;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return unitId;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectUnitId").toString();
    query.prepare(sqlSentence);
    query.bindValue(":buildingId", buildingId);

    query.exec();
    closeDatabase();

    while(query.next())
        unitId.append(query.value("unit").toString());
    return unitId;
}

int LaborEyeDatabase::cntRecordsNum(QDateTime startDateTime, QDateTime endDateTime,
                                    QString stranger, QString idCard)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence;
    if(stranger == QString::fromLocal8Bit("是")) {
        if(idCard == "") { //查询所有的陌生人
            sqlSentence = sqlSetting->value("Select/cntRecords_stranger").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") { //根据陌生人编号查询陌生人
            sqlSentence = sqlSetting->value("Select/cntRecords_by_idCard_Stranger").toString();
            query.bindValue(":idCard", idCard);
        }
    } else if(stranger == QString::fromLocal8Bit("否")) {
        if(idCard == "") { //查询所有非陌生人
            sqlSentence = sqlSetting->value("Select/cntRecords_noStranger").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") {   //根据身份证编号查询非陌生人
            sqlSentence = sqlSetting->value("Select/cntRecords_by_idCard_noStranger").toString();
            query.prepare(sqlSentence);
            query.bindValue(":idCard", idCard);
        }
    } else if(stranger == QString::fromLocal8Bit("不限")) {
        if(idCard == "") {  //查询所有记录
            sqlSentence = sqlSetting->value("Select/cntRecords_all").toString();
            query.prepare(sqlSentence);
        } else if(idCard != "") {   //根据身份证号/陌生人编号查询记录
            sqlSentence = sqlSetting->value("Select/cntRecords_by_idCard").toString();
            query.prepare(sqlSentence);
            query.bindValue(":idCard", idCard);
        }
    }

    query.bindValue(":startDateTime", startDateTime);
    query.bindValue(":endDateTime", endDateTime);
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
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

QList<QString> LaborEyeDatabase::selectHouseId(QString buildingId, QString unitId)
{
    QList<QString> housesId;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return housesId;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectHouseId").toString();
    query.prepare(sqlSentence);
    query.bindValue(":buildingId", buildingId);
    query.bindValue(":unitId", unitId);
    query.exec();
    closeDatabase();

    while(query.next())
        housesId.append(query.value("house").toString());
    return housesId;
}

int LaborEyeDatabase::cntHouseNum(QString buildingId, QString unitId)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/cntHouseNum").toString();
    query.prepare(sqlSentence);
    query.bindValue(":buildingId", buildingId);
    query.bindValue(":unitId", unitId);
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}

QList<HouseInfo> LaborEyeDatabase::selectHouseInfo(QString buildingId, QString unitId,
                                                    QDateTime startDateTime, QDateTime endDateTime)
{
    QList<HouseInfo> houseInfoList;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return houseInfoList;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectHouseRecords_by_Time").toString();
    query.prepare(sqlSentence);
    query.bindValue(":buildingId", buildingId);
    query.bindValue(":unitId", unitId);
    query.bindValue(":startDateTime", startDateTime);
    query.bindValue(":endDateTime", endDateTime);
    query.exec();
    closeDatabase();

    HouseInfo houseInfo;
    while(query.next()) {
        houseInfo.setId(query.value("id").toInt());
        houseInfo.setCommunity(query.value("community").toString());
        houseInfo.setBuilding(query.value("building").toString());
        houseInfo.setUnit(query.value("unit").toString());
        houseInfo.setHouse(query.value("house").toString());
        houseInfo.setArea(query.value("area").toDouble());
        houseInfoList.append(houseInfo);
    }
    return houseInfoList;
}

QList<ApplicantRecordInfo> LaborEyeDatabase::selectApplicantRecords(QString buildingId, QString unitId, QString houseId,
                                                  QDateTime startDateTime, QDateTime endDateTime)
{
    QList<ApplicantRecordInfo> applicantRecordsList;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return applicantRecordsList;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectApplicantRecord").toString();

    query.prepare(sqlSentence);
    query.bindValue(":buildingId", buildingId);
    query.bindValue(":unitId", unitId);
    query.bindValue(":houseId", houseId);
    query.bindValue(":startDateTime", startDateTime);
    query.bindValue(":endDateTime", endDateTime);
    query.exec();
    closeDatabase();

    ApplicantRecordInfo applicantRecordInfo;
    while(query.next()) {
        applicantRecordInfo.setDateTime(query.value("time_value").toDateTime());
        applicantRecordInfo.setApplicant(query.value("applicant").toString());
        applicantRecordInfo.setAvatarId(query.value("avatar_id").toString());
        applicantRecordInfo.setSimilar(query.value("similar").toInt());
        applicantRecordInfo.setCaptureId(query.value("capture_id").toInt());
        applicantRecordInfo.setFamilyRole(query.value("familyrole").toString());
        applicantRecordsList.append(applicantRecordInfo);
    }

    return applicantRecordsList;
}

QList<ApplicantInfo> LaborEyeDatabase::selectApplicantInfo(int nowPage, int pageSize)
{
    QList<ApplicantInfo> applicantInfoList;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return applicantInfoList;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectApplicantInfo").toString();

    query.prepare(sqlSentence);
    query.bindValue(":startId", (nowPage-1)*pageSize);
    query.bindValue(":pageSize", pageSize);
    query.exec();
    closeDatabase();

    ApplicantInfo applicantInfo;
    while(query.next()) {
        applicantInfo.setApplicant(query.value("applicant").toString());
        applicantInfo.setSfzNo(query.value("sfzno").toString());
        applicantInfo.setContact(query.value("contact").toString());
        applicantInfo.setBuilding(query.value("building").toString());
        applicantInfo.setUnit(query.value("unit").toString());
        applicantInfo.setHouse(query.value("house").toString());
        applicantInfoList.append(applicantInfo);
    }

    return applicantInfoList;
}

int LaborEyeDatabase::cntApplicant()
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/cntApplicantInfo").toString();
    query.prepare(sqlSentence);
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}
