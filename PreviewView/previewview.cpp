#include "previewview.h"
#include "ui_previewview.h"

PreviewView::PreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewView)
{
    ui->setupUi(this);
    QList<HWND> hwndList;
    hwndList.append(HWND(ui->lblChannel1->winId()));
    hwndList.append(HWND(ui->lblChannel2->winId()));
    Hikvision::showPreviewVideo(hwndList);
//    PICTYPE pic = static_cast<PICTYPE>(4);
//    Hikvision::downLoadPicture(CAPTUREPICTURE);
}

PreviewView::~PreviewView()
{
    delete ui;
}

void PreviewView::setAlarmInfo(NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm)
{
    qDebug() << QString::fromLocal8Bit(reinterpret_cast<char*>(faceMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byName));
    AlarmInfo alarmInfo;

    QDateTime dateTime(QDate(GET_YEAR(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_MONTH(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_DAY(faceMatchAlarm.struSnapInfo.dwAbsTime)),
                       QTime(GET_HOUR(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_MINUTE(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_SECOND(faceMatchAlarm.struSnapInfo.dwAbsTime)));
    QString sfzNo = QString::fromLocal8Bit(reinterpret_cast<char*>
                                               (faceMatchAlarm.struBlackListInfo.
                                                struBlackListInfo.struAttribute.byName));
    int similar = static_cast<int>(faceMatchAlarm.fSimilarity*100);
    if(similar >= Config::getCfg()->getSimilar()) {
        if(sfzNo[sfzNo.length()-1] != 'm') {
            qDebug().noquote() << QString::fromLocal8Bit("不是陌生人");


        } else {

        }
        alarmInfo.setStranger(false);
    } else {
        sfzNo = dateTime.toString("yyymmddhhmmss");
        alarmInfo.setStranger(true);
        //陌生人人脸图需上传至超脑
    }

    alarmInfo.setSfzNo(sfzNo);
    alarmInfo.setSimilar(similar);
    alarmInfo.setDateTime(dateTime);

    LaborEyeDatabase::getLaboreyeDatabase()->insertRecord(alarmInfo);

}

void PreviewView::on_btnClear_clicked()
{

}
