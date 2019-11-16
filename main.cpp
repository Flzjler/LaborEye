#include <QApplication>

#include <QFile>
#include <QString>
#include <QMessageBox>
#include "MainView/mainview.h"

#include "LaborEyeDatabase/laboreyedatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载QSS样式
    QFile qssFile(":/Src/light.css");
    if(qssFile.open(QFile::ReadOnly)) {
        a.setStyleSheet(QString(QLatin1String(qssFile.readAll())));
        qssFile.close();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("样式加载失败!"),
                                QObject::tr("样式文件加载失败!"));
    }

    MainView mainView;
    mainView.show();

//    LaborEyeDatabase* lb = LaborEyeDatabase::getLaboreyeDatabase();
//    qDebug() << lb->cntRecords();
    return a.exec();
}
