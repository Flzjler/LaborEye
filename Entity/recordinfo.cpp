#include "recordinfo.h"

RecordInfo::RecordInfo()
{

}

void RecordInfo::setId(int _id)
{
    id = _id;
}

int RecordInfo::getId()
{
    return id;
}

void RecordInfo::setTimeValue(QDateTime _timeValue)
{
    timeValue = _timeValue;
}

QDateTime RecordInfo::getTimeValue()
{
    return timeValue;
}

void RecordInfo::setApplicant(QString _applicant)
{
    applicant = _applicant;
}

QString RecordInfo::getApplicant()
{
    return applicant;
}

void RecordInfo::setAvatarId(QString _avatarId)
{
    avatarId = _avatarId;
}

QString RecordInfo::getAvatarId()
{
    return avatarId;
}

void RecordInfo::setStranger(bool _stranger)
{
    stranger = _stranger;
}

bool RecordInfo::getStranger()
{
    return stranger;
}

void RecordInfo::setSimilar(int _similar)
{
    similar = _similar;
}

int RecordInfo::getSimilar()
{
    return similar;
}

void RecordInfo::setCaptureId(int _captureId)
{
    captureId = _captureId;

}

int RecordInfo::getCaptureId()
{
    return captureId;
}

//void RecordInfo::setDel(bool _del)
//{
//    del = _del;
//}

//bool RecordInfo::getDel()
//{
//    return del;
//}
