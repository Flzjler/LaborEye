#ifndef LABOREYEDATABASE_H
#define LABOREYEDATABASE_H

#include <QList>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>

#include "Config/config.h"
#include "Entity/recordinfo.h"
#include "Entity/houseinfo.h"

class LaborEyeDatabase
{
public:

    static LaborEyeDatabase* getLaboreyeDatabase()
    {
        if(laborEyeDatabase == nullptr)
            laborEyeDatabase = new LaborEyeDatabase();
        return laborEyeDatabase;
    }

    //根据条件筛查识别记录
    QList<RecordInfo> selectRecordInfo(QDateTime startDateTime, QDateTime endDateTime,
                                              QString stranger, QString idCard,
                                              int nowPage, int pageSize);

    //根据幢号、单元号查询房屋数量
    int cntHouseNum(QString buildingId, QString unitId);

    //查询所有进出识别记录条数
    int cntRecords();

    //根据条件查询进出识别记录条数
    int cntRecordsNum(QDateTime startDateTime, QDateTime endDateTime,
                             QString stranger, QString idCard);

    //查询小区所有幢号
    QList<QString> selectBuidingId();

    //根据幢号查询所有单元号
    QList<QString> selectUnitId(QString buildingId);

    //根据幢号和单元号查询房号
    QList<QString> selectHouseId(QString buildingId, QString unitId);

    //根据幢号、单元号、日期查询有住户进出的房屋
    QList<HouseInfo> selectHouseInfo(QString buildingId, QString unitId,
                                    QDateTime startDateTime, QDateTime endDateTime);


private:
    LaborEyeDatabase();
    ~LaborEyeDatabase();
    bool openDatabase();
    void closeDatabase();

    QSqlDatabase db;
    QSettings *sqlSetting;
    static LaborEyeDatabase* laborEyeDatabase;
};

#endif // LABOREYEDATABASE_H
