#ifndef ADDRESSINFO_H
#define ADDRESSINFO_H

#include <QString>

class AddressInfo
{
public:
    AddressInfo();

    void setCommunity(QString _community);
    QString getCommunity();

    void setBuilding(QString _building);
    QString getBuilding();

    void setUnit(QString _unit);
    QString getUnit();

    void setHouse(QString _house);
    QString getHouse();

private:
    QString community;
    QString building;
    QString unit;
    QString house;

};

#endif // ADDRESSINFO_H
