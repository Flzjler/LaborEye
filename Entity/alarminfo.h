#ifndef ALARMINFO_H
#define ALARMINFO_H

#include <QString>
#include <QDateTime>

class AlarmInfo
{
public:
    AlarmInfo();

    void setDateTime(QDateTime _dateTime);
    QDateTime getDateTime();

    void setApplicant(QString _applicant);
    QString getApplicant();

    void setSfzNo(QString _sfzNo);
    QString getSfzNo();

    void setSimilar(int _similar);
    int getSimilar();

    void setAddress(QString _address);
    QString getAddress();
    
    void setStranger(bool _stranger);
    bool getStranger();

private:
    QDateTime dateTime;
    QString applicant;
    QString sfzNo;
    QString address;
    int similar;
    bool stranger;
};

#endif // ALARMINFO_H
