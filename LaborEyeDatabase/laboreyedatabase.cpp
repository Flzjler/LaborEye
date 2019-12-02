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
    qDebug() << "sqlSentence: " << sqlSentence;
    query.exec();
    closeDatabase();

    RecordInfo recordInfo;
    while(query.next()) {
        recordInfo.setId(query.value("id").toInt());
        recordInfo.setApplicant(query.value("applicant").toString());
        recordInfo.setAvatarId(query.value("avatar_id").toString());
        recordInfo.setStranger(query.value("stranger").toBool());
        recordInfo.setSimilar(query.value("similar").toInt());
        recordInfo.setCaptureId(query.value("capture_id").toInt());
//        recordInfo.setDel(query.value("isdel").toInt());
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
            query.prepare(sqlSentence);
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

QList<ApplicantInfo> LaborEyeDatabase::selectApplicantInfo(QString name, QString idCard,
                                                           int nowPage, int pageSize)
{
    QList<ApplicantInfo> applicantInfoList;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return applicantInfoList;
    }

    QSqlQuery query;
    QString sqlSentence;
    if(name == "" && idCard == "") {
        sqlSentence = sqlSetting->value("Select/selectApplicantInfo").toString();
        query.prepare(sqlSentence);
    } else if(name != "" && idCard == "") {
        sqlSentence = sqlSetting->value("Select/selectApplicantInfo_by_name").toString();
        query.prepare(sqlSentence);
        query.bindValue(":applicant", name);
    } else if(name == "" && idCard != "") {
        sqlSentence = sqlSetting->value("Select/selectApplicantInfo_by_idCard").toString();
        query.prepare(sqlSentence);
        query.bindValue(":sfzNo", idCard);
    } else if(name != "" && idCard != "") {
        sqlSentence = sqlSetting->value("Select/selectApplicantInfo_by_name_idCard").toString();
        query.prepare(sqlSentence);
        query.bindValue(":applicant", name);
        query.bindValue(":sfzNo", idCard);
    }

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

int LaborEyeDatabase::cntApplicant(QString name, QString idCard)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence;

    if(name == "" && idCard == "") {
        sqlSentence = sqlSetting->value("Select/cntApplicantInfo").toString();
        query.prepare(sqlSentence);
    } else if(name != "" && idCard == "") {
        sqlSentence = sqlSetting->value("Select/cntApplicantInfo_by_name").toString();
        query.prepare(sqlSentence);
        query.bindValue(":applicant", name);
    } else if(name == "" && idCard != "") {
        sqlSentence = sqlSetting->value("Select/cntApplicantInfo_by_idCard").toString();
        query.prepare(sqlSentence);
        query.bindValue(":sfzNo", idCard);
    } else if(name != "" && idCard != "") {
        sqlSentence = sqlSetting->value("Select/cntApplicantInfo_by_name_idCard").toString();
        query.prepare(sqlSentence);
        query.bindValue(":applicant", name);
        query.bindValue(":sfzNo", idCard);
    }

    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}

bool LaborEyeDatabase::deleteApplicantInfo(ApplicantInfo applicantInfo)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return false;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Update/deleteApplicantInfo").toString();
    query.prepare(sqlSentence);
    query.bindValue(":sfzNo", applicantInfo.getSfzNo());

    query.exec();
    closeDatabase();
    return true;
}

QList<QList<QVariant>> LaborEyeDatabase::selectExcelRecord(QDateTime startDateTime, QDateTime endDateTime)
{
    QList<QList<QVariant>> exportRecordList;

    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return exportRecordList;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectExportRecord").toString();

    query.prepare(sqlSentence);
    query.bindValue(":startDateTime", startDateTime);
    query.bindValue(":endDateTime", endDateTime);
    query.exec();
    closeDatabase();

    while(query.next()) {
        QList<QVariant> exportRecord;
        QString address = query.value("community").toString() + query.value("building").toString() + "幢" +
                        query.value("unit").toString() + "单元" + query.value("house").toString() + "室";
        exportRecord.append(QVariant(address));
        exportRecord.append(QVariant(query.value("applicant").toString()));
        exportRecord.append(QVariant(query.value("sfzno").toString()));
        exportRecord.append(QVariant(query.value("familyrole").toString()));
        exportRecord.append(QVariant(query.value("time_value").toDateTime()));
        exportRecord.append(QVariant(query.value("similar").toInt()));
        exportRecordList.append(exportRecord);
    }

    return exportRecordList;
}

bool LaborEyeDatabase::insertRecord(AlarmInfo alarmInfo)
{
    qDebug() << "similar: " << alarmInfo.getSimilar();
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return false;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectApplicantName_by_idCard").toString();
    query.prepare(sqlSentence);
    query.bindValue(":sfzNo", alarmInfo.getSfzNo());
    query.exec();
    QString applicant;
    if(query.next())
        applicant = query.value(0).toString();
    if(applicant == "")
        applicant = QString::fromLocal8Bit("陌生人");
    qDebug() << applicant << " " << alarmInfo.getDateTime() << " " << alarmInfo.getSfzNo();
    query.clear();
    sqlSentence = sqlSetting->value("Insert/insertRecord").toString();
    qDebug() << sqlSentence;
    query.prepare(sqlSentence);
    query.bindValue(":dateTime", alarmInfo.getDateTime());
    query.bindValue(":applicant", applicant);
    query.bindValue(":idCard", alarmInfo.getSfzNo());
    query.bindValue(":stranger", alarmInfo.getStranger());
    query.bindValue(":similar", alarmInfo.getSimilar());
    query.exec();
    closeDatabase();
    return true;
}

PersonInfo LaborEyeDatabase::selectPersonInfo(QString sfzNo)
{
    PersonInfo personInfo;

    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return personInfo;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectPersonInfo_by_sfzno").toString();
    query.prepare(sqlSentence);
    query.bindValue(":sfzNo", sfzNo);
    query.exec();
    closeDatabase();

    if(query.next()) {
        personInfo.applicant = query.value("applicant").toString();
        personInfo.address = query.value("community").toString() +
                            query.value("building").toString() +
                            query.value("unit").toString() +
                            query.value("house").toString();
    }
    return personInfo;
}

int LaborEyeDatabase::selectLastInsertId()
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectLastInsertId").toString();
    query.prepare(sqlSentence);
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}

int LaborEyeDatabase::selectHouseTableId(AddressInfo addressInfo)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return -1;
    }
    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectHouseTableId").toString();
    query.prepare(sqlSentence);
    query.bindValue(":community", addressInfo.getCommunity());
    query.bindValue(":building", addressInfo.getBuilding());
    query.bindValue(":unit", addressInfo.getUnit());
    query.bindValue(":house", addressInfo.getHouse());
    query.exec();
    closeDatabase();

    if(query.next())
        return query.value(0).toInt();
    return -1;
}

bool LaborEyeDatabase::insertApplicant(ApplicantInfo applicantInfo, AddressInfo addressInfo)
{
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return false;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Insert/insertApplicant").toString();
    query.prepare(sqlSentence);
    query.bindValue(":applicant", applicantInfo.getApplicant());
    query.bindValue(":idCard", applicantInfo.getSfzNo());
    query.bindValue(":contact", applicantInfo.getContact());
    query.bindValue(":familyRole", applicantInfo.getRole());
    query.exec();

    int lastId = selectLastInsertId();
    int houseTableId = selectHouseTableId(addressInfo);

    if(lastId == -1 || houseTableId == -1)
        return false;

    sqlSentence = sqlSetting->value("Insert/insertApplicantHouse").toString();
    query.prepare(sqlSentence);
    query.bindValue(":applicantId", lastId);
    query.bindValue(":houseId", houseTableId);
    query.exec();
    closeDatabase();

    return true;
}

QList<AddressInfo> LaborEyeDatabase::selectAddressInfo()
{
    QList<AddressInfo> addressInfoList;
    if(!openDatabase()) {
        QMessageBox::critical(nullptr, QString::fromLocal8Bit("数据库连接失败!"), db.lastError().text());
        return addressInfoList;
    }

    QSqlQuery query;
    QString sqlSentence = sqlSetting->value("Select/selectAddressInfo").toString();
    query.prepare(sqlSentence);
    query.exec();
    closeDatabase();

    AddressInfo addressInfo;
    while(query.next()) {
        addressInfo.setCommunity(query.value("community").toString());
        addressInfo.setBuilding(query.value("building").toString());
        addressInfo.setUnit(query.value("unit").toString());
        addressInfo.setHouse(query.value("house").toString());
        addressInfoList.append(addressInfo);
    }

    return addressInfoList;
}
