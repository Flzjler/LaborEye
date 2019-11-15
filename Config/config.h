#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QString>
#include <QSettings>

class Config
{
public:
    static Config* getCfg()
    {
        if(cfg == nullptr)
            cfg = new Config();
        return cfg;
    }

    int getDatabasePort();
    QString getDatabaseIP();
    QString getDataBaseName();
    QString getDatabaseUsername();
    QString getDatabasePasword();

private:
    Config();
    ~Config();
    QSettings* cfgSetting;
    static Config* cfg;

};


#endif // CONFIG_H
