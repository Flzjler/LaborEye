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

    bool operator < (const AddressInfo & addressInfo) const {
        if(community != addressInfo.community) return community < addressInfo.community;
        if(building != addressInfo.building) return building < addressInfo.building;
        if(unit != addressInfo.unit) return unit < addressInfo.unit;
        return house.compare(addressInfo.house) == 0;
    }

private:
    QString community;
    QString building;
    QString unit;
    QString house;

};

#endif // ADDRESSINFO_H
