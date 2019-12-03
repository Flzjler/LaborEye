#include "houseinfo.h"

HouseInfo::HouseInfo()
{

}

void HouseInfo::setId(int _id)
{
    id = _id;
}

int HouseInfo::getId()
{
    return id;
}

void HouseInfo::setCommunity(QString _community)
{
    community = _community;
}

QString HouseInfo::getCommunity()
{
    return community;
}

void HouseInfo::setBuilding(QString _building)
{
    _building = building;
}

QString HouseInfo::getBuilding()
{
    return building;
}

void HouseInfo::setUnit(QString _unit)
{
    unit = _unit;
}

QString HouseInfo::getUnit()
{
    return unit;
}

void HouseInfo::setHouse(QString _house)
{
    house = _house;
}

QString HouseInfo::getHouse()
{
    return house;
}

void HouseInfo::setArea(double _area)
{
    area = _area;
}

double HouseInfo::getArea()
{
    return area;
}
