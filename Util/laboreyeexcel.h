#ifndef LABOREYEEXCEL_H
#define LABOREYEEXCEL_H

#include <QList>
#include <QString>
#include <QApplication>
#include <QAxObject>
#include <QDir>
#include <QThread>
#include <QFile>
#include <Windows.h>
#include <QObject>

class LaborEyeExcel : public QObject
{
    Q_OBJECT
public:
    static LaborEyeExcel* getLaborEyeExcel()
    {
        if(laborEyeExcel == nullptr)
            laborEyeExcel = new LaborEyeExcel();
        return laborEyeExcel;
    }
    void setExportData(QList<QList<QVariant>> _exportData);
    void setDetPath(QString _detPath);

public slots:
    void startTrans();

private:
    explicit LaborEyeExcel();
     ~LaborEyeExcel();
    void writeSheet();

    QString detPath;
    QList<QList<QVariant>> exportData;
    static LaborEyeExcel* laborEyeExcel;
};

#endif // LABOREYEEXCEL_H
