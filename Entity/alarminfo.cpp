#include "alarminfo.h"

AlarmInfo::AlarmInfo()
{

}

void AlarmInfo::setDateTime(QDateTime _dateTime)
{
    dateTime = _dateTime;
}

QDateTime AlarmInfo::getDateTime()
{
    return dateTime;
}

void AlarmInfo::setApplicant(QString _applicant)
{
    applicant = _applicant;
}

QString AlarmInfo::getApplicant()
{
    return applicant;
}

void AlarmInfo::setSfzNo(QString _sfzNo)
{
    sfzNo = _sfzNo;
}

QString AlarmInfo::getSfzNo()
{
    return sfzNo;
}

void AlarmInfo::setSimilar(int _similar)
{
    similar = _similar;
}

int AlarmInfo::getSimilar()
{
    return similar;
}

void AlarmInfo::setStranger(bool _stranger)
{
    stranger = _stranger;
}

bool AlarmInfo::getStranger()
{
    return stranger;
}

void AlarmInfo::setAddress(QString _address)
{
    address = _address;
}

QString AlarmInfo::getAddress()
{
    return address;
}
