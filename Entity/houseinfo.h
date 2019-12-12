#ifndef HOUSEINFO_H
#define HOUSEINFO_H

#include <QString>
#include <QDebug>

class HouseInfo
{
public:
    explicit HouseInfo();

    void setId(int _id);
    int getId();

    void setCommunity(QString _community);
    QString getCommunity();

    void setBuilding(QString _building);
    QString getBuilding();

    void setUnit(QString _unit);
    QString getUnit();

    void setHouse(QString _house);
    QString getHouse();

    void setArea(double _area);
    double getArea();

private:
    int id;

    QString community;

    QString building;

    QString unit;

    QString house;

    double area;


};

#endif // HOUSEINFO_H
