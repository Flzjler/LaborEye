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

    QList<RecordInfo> selectRecordInfo(QDateTime startDateTime, QDateTime endDateTime,
                                              QString stranger, QString idCard,
                                              int nowPage, int pageSize);
    QList<QString> selectBuidingId();

    QList<QString> selectUnitId(QString buildingId);

    QList<QString> selectHouseId(QString buildingId, QString unitId);

    QList<HouseInfo> selectHouseInfo(QString buildingId, QString unitId,
                                    QDateTime startDateTime, QDateTime endDateTime);

    int cntHouseNum(QString buildingId, QString unitId);

    int cntRecords();

    int cntRecordsNum(QDateTime startDateTime, QDateTime endDateTime,
                             QString stranger, QString idCard);


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
