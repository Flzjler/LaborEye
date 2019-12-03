#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QString>
#include <QDateTime>

class RecordInfo
{
public:
    RecordInfo();

    void setId(int _id);
    int getId();

    void setTimeValue(QDateTime _timeValue);
    QDateTime getTimeValue();

    void setApplicant(QString _applicant);
    QString getApplicant();

    void setAvatarId(QString _avatarId);
    QString getAvatarId();

    void setStranger(bool _stranger);
    bool getStranger();

    void setSimilar(int _similar);
    int getSimilar();

    void setCaptureId(int _captureId);
    int getCaptureId();

//    void setDel(bool _del);
//    bool getDel();

private:
    int id;
    QDateTime timeValue;
    QString applicant;
    QString avatarId;
    bool stranger;
    int similar;
    int captureId;
//    bool del;

};

#endif // RECORDINFO_H
