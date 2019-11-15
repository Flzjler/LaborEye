#ifndef LABOREYEDATABASE_H
#define LABOREYEDATABASE_H

#include <QSqlQuery>
#include <QSettings>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>

#include "Config/config.h"

class LaborEyeDatabase
{
public:
    static LaborEyeDatabase* getLaboreyeDatabase()
    {
        if(laborEyeDatabase == nullptr)
            laborEyeDatabase = new LaborEyeDatabase();
        return laborEyeDatabase;
    }

    void sqlTest();

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
