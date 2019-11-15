#include "config.h"

Config* Config::cfg = nullptr;

Config::Config()
{
    cfgSetting = new QSettings(":/Src/devConfig.ini", QSettings::IniFormat);
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
