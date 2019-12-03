#include "addressinfo.h"

AddressInfo::AddressInfo()
{

}

void AddressInfo::setCommunity(QString _community)
{
    community = _community;
}

QString AddressInfo::getCommunity()
{
    return community;
}

void AddressInfo::setBuilding(QString _building)
{
    building = _building;
}

QString AddressInfo::getBuilding()
{
    return building;
}

void AddressInfo::setUnit(QString _unit)
{
    unit = _unit;
}

QString AddressInfo::getUnit()
{
    return unit;
}

void AddressInfo::setHouse(QString _house)
{
    house = _house;
}

QString AddressInfo::getHouse()
{
    return house;
}
