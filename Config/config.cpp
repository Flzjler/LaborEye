#include "config.h"

Config* Config::cfg = nullptr;

Config::Config()
{
    cfgSetting = new QSettings("./config/devConfig.ini",
                               QSettings::IniFormat);//存放于Debug目录中与debug/release同级目录
}

int Config::getDatabasePort()
{
    return cfgSetting->value("Database/port").toInt();
}

QString Config::getDatabaseIP()
{
    return cfgSetting->value("Database/ip").toString();
}

QString Config::getDataBaseName()
{
    return cfgSetting->value("Database/database").toString();
}

QString Config::getDatabaseUsername()
{
    return cfgSetting->value("Database/username").toString();
}

QString Config::getDatabasePasword()
{
    return cfgSetting->value("Database/password").toString();
}

void Config::setDatabasePort(int _port)
{
    cfgSetting->setValue("Database/port", _port);
}

void Config::setDatabaseIP(QString _ip)
{
    cfgSetting->setValue("Database/ip", _ip);
}

void Config::setDatabaseName(QString _databaseName)
{
    cfgSetting->setValue("Database/database", _databaseName);
}

void Config::setDatabaseUsername(QString _userName)
{
    cfgSetting->setValue("Database/username", _userName);
}

void Config::setDatabasePassword(QString _passWord)
{
    cfgSetting->setValue("Database/password", _passWord);
}

int Config::getSuBrainPort()
{
    return cfgSetting->value("SuperBrain/port").toInt();
}
int Config::getSuBrainChannel1()
{
    return cfgSetting->value("SuperBrain/channel1").toInt();
}

int Config::getSuBrainChannel2()
{
    return cfgSetting->value("SuperBrain/channel2").toInt();
}

int Config::getSuBrainChannel3()
{
    return cfgSetting->value("SuperBrain/channel3").toInt();
}

int Config::getSuBrainChannel4()
{
    return cfgSetting->value("SuperBrain/channel4").toInt();
}

QString Config::getSuBrainIP()
{
    return cfgSetting->value("SuperBrain/ip").toString();
}

QString Config::getSuBrainUsername()
{
    return cfgSetting->value("SuperBrain/username").toString();
}

QString Config::getSuBrainPasword()
{
    return cfgSetting->value("SuperBrain/password").toString();
}

void Config::setSuBrainPort(int _port)
{
    cfgSetting->setValue("SuperBrain/port", _port);
}

void Config::setSuBrainChannel1(int _channel1)
{
    cfgSetting->setValue("SuperBrain/channel1", _channel1);
}

void Config::setSuBrainChannel2(int _channel2)
{
    cfgSetting->setValue("SuperBrain/channel2", _channel2);
}

void Config::setSuBrainChannel3(int _channel3)
{
    cfgSetting->setValue("SuperBrain/channel3", _channel3);
}

void Config::setSuBrainChannel4(int _channel4)
{
    cfgSetting->setValue("SuperBrain/channel4", _channel4);
}

void Config::setSuBrainIP(QString _ip)
{
    // qDebug() << _ip;
    cfgSetting->setValue("SuperBrain/ip", _ip);
}

void Config::setSuBrainUsername(QString _userName)
{
    cfgSetting->setValue("SuperBrain/username", _userName);
}

void Config::setSuBrainPasword(QString _passWord)
{
    cfgSetting->setValue("SuperBrain/password", _passWord);
}

QString Config::getCapturePath()
{
    return cfgSetting->value("Path/capturePath").toString();
}

QString Config::getAvatarPath()
{
    return cfgSetting->value("Path/avatarPath").toString();
}

QString Config::getFacePath()
{
    return cfgSetting->value("Path/facePath").toString();
}

void Config::setCapturePath(QString _capturePath)
{
    cfgSetting->setValue("Path/capturePath", _capturePath);
}

void Config::setAvatarPath(QString _avatarPath)
{
    cfgSetting->setValue("Path/avatarPath", _avatarPath);
}

void Config::setFacePath(QString _facePath)
{
    cfgSetting->setValue("Path/facePath", _facePath);
}

int Config::getSimilar()
{
    return cfgSetting->value("Similar/similar").toInt();
}

void Config::setSimilar(int _similar)
{
    cfgSetting->setValue("Similar/similar", _similar);
}

