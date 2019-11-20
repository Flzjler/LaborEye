#ifndef APPLICANTRECORDINFO_H
#define APPLICANTRECORDINFO_H

#include <QString>
#include <QDateTime>

class ApplicantRecordInfo
{
public:
    ApplicantRecordInfo();

    void setSimilar(int _similar);
    int getSimilar();

    void setCaptureId(int _captureId);
    int getCaptureId();

    void setDateTime(QDateTime _dateTime);
    QDateTime getDateTime();

    void setApplicant(QString _applicant);
    QString getApplicant();

    void setAvatarId(QString _avatarId);
    QString getAvatarId();

    void setFamilyRole(QString _familyRole);
    QString getFamilyRole();

private:
    int similar;

    int captureId;

    QDateTime  dateTime;

    QString applicant;

    QString avatarId;

    QString familyRole;

};

#endif // APPLICANTRECORDINFO_H
