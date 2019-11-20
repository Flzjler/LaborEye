#ifndef APPLICANTINFO_H
#define APPLICANTINFO_H

#include <QString>


class ApplicantInfo
{
public:
    ApplicantInfo();

    void setApplicant(QString _applicant);
    QString getApplicant();

    void setSfzNo(QString _sfzNo);
    QString getSfzNo();

    void setContact(QString _contact);
    QString getContact();

    void setBuilding(QString _building);
    QString getBuilding();

    void setUnit(QString _unit);
    QString getUnit();

    void setHouse(QString _house);
    QString getHouse();

private:
    QString applicant;
    QString sfzNo;
    QString contact;
    QString building;
    QString unit;
    QString house;

};

#endif // APPLICANTINFO_H
