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

    void setDatabasePort(int _port);
    void setDatabaseIP(QString _ip);
    void setDatabaseName(QString _databaseName);
    void setDatabaseUsername(QString _userName);
    void setDatabasePassword(QString _passWord);

    int getSuBrainPort();
    int getSuBrainChannel1();
    int getSuBrainChannel2();
    int getSuBrainChannel3();
    int getSuBrainChannel4();
    QString getSuBrainIP();
    QString getSuBrainUsername();
    QString getSuBrainPasword();

    void setSuBrainPort(int _port);
    void setSuBrainChannel1(int _channel1);
    void setSuBrainChannel2(int _channel2);
    void setSuBrainChannel3(int _channel3);
    void setSuBrainChannel4(int _channel4);
    void setSuBrainIP(QString _ip);
    void setSuBrainUsername(QString _userName);
    void setSuBrainPasword(QString _passWord);

    QString getCapturePath();
    QString getAvatarPath();
    QString getFacePath();

    void setCapturePath(QString _capturePath);
    void setAvatarPath(QString _avatarPath);
    void setFacePath(QString _facePath);

    int getSimilar();

    void setSimilar(int _similar);

private:
    Config();
    ~Config();
    QSettings* cfgSetting;
    static Config* cfg;
};


#endif // CONFIG_H
