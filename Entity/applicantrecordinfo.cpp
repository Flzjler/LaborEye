#include "applicantrecordinfo.h"

ApplicantRecordInfo::ApplicantRecordInfo()
{

}

void ApplicantRecordInfo::setSimilar(int _similar)
{
    similar = _similar;
}

int ApplicantRecordInfo::getSimilar()
{
    return similar;
}

void ApplicantRecordInfo::setCaptureId(int _captureId)
{
    captureId = _captureId;
}

int ApplicantRecordInfo::getCaptureId()
{
    return captureId;
}

void ApplicantRecordInfo::setDateTime(QDateTime _dateTime)
{
    dateTime = _dateTime;
}

QDateTime ApplicantRecordInfo::getDateTime()
{
    return dateTime;
}

void ApplicantRecordInfo::setApplicant(QString _applicant)
{
    applicant = _applicant;
}

QString ApplicantRecordInfo::getApplicant()
{
    return applicant;
}

void ApplicantRecordInfo::setAvatarId(QString _avatarId)
{
    avatarId = _avatarId;
}

QString ApplicantRecordInfo::getAvatarId()
{
    return avatarId;
}


void ApplicantRecordInfo::setFamilyRole(QString _familyRole)
{
    familyRole = _familyRole;
}
QString ApplicantRecordInfo::getFamilyRole()
{
    return familyRole;
}
