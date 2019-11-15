#include <QApplication>

#include <QString>
#include "MainView/mainview.h"
#include "LaborEyeDatabase/laboreyedatabase.h"
#include "Config/config.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainView mainView;
    mainView.show();
    Config *cfg = Config::getCfg();
    //qDebug() << cfg->getDataBaseName();
    LaborEyeDatabase* lb = LaborEyeDatabase::getLaboreyeDatabase();
    lb->sqlTest();
    return a.exec();
}
