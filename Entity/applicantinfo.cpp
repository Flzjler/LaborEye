#include "applicantinfo.h"

ApplicantInfo::ApplicantInfo()
{

}

void ApplicantInfo::setApplicant(QString _applicant)
{
    applicant = _applicant;
}

QString ApplicantInfo::getApplicant()
{
    return applicant;
}

void ApplicantInfo::setSfzNo(QString _sfzNo)
{
    sfzNo = _sfzNo;
}

QString ApplicantInfo::getSfzNo()
{
    return sfzNo;
}

void ApplicantInfo::setContact(QString _contact)
{
    contact = _contact;
}

QString ApplicantInfo::getContact()
{
    return contact;
}

void ApplicantInfo::setBuilding(QString _building)
{
    building = _building;
}

QString ApplicantInfo::getBuilding()
{
    return building;
}

void ApplicantInfo::setUnit(QString _unit)
{
    unit = _unit;
}

QString ApplicantInfo::getUnit()
{
    return unit;
}

void ApplicantInfo::setHouse(QString _house)
{
    house = _house;
}

QString ApplicantInfo::getHouse()
{
    return house;
}

void ApplicantInfo::setRole(QString _role)
{
    role = _role;
}

QString ApplicantInfo::getRole()
{
    return role;
}
