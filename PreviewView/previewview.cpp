#include "previewview.h"
#include "ui_previewview.h"

PreviewView* PreviewView::previewView;
QList<AlarmInfo> PreviewView::alarmInfoList;

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
    //    qDebug() << QString::fromLocal8Bit(reinterpret_cast<char*>(faceMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byName));

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
            alarmInfo.setApplicant(LaborEyeDatabase::getLaboreyeDatabase()->
                                   selectPersonInfo(sfzNo).applicant);
            alarmInfo.setAddress(LaborEyeDatabase::getLaboreyeDatabase()->
                                 selectPersonInfo(sfzNo).address);

        } else {

        }
        alarmInfo.setStranger(false);
    } else {
        sfzNo = dateTime.toString("yyyy-MM-dd hh:mm:ss");
        alarmInfo.setStranger(true);
        //陌生人人脸图需上传至超脑
    }
    if(alarmInfo.getApplicant() == "")
        alarmInfo.setApplicant(QString::fromLocal8Bit("陌生人"));
    alarmInfo.setSfzNo(sfzNo);
    alarmInfo.setSimilar(similar);
    alarmInfo.setDateTime(dateTime);
    //    qDebug() << alarmInfo.getSfzNo() << " " << alarmInfo.getSimilar();
    alarmInfoList.append(alarmInfo);

    setPersonInfo(alarmInfo);

    addPersonInfoList(alarmInfo);

    LaborEyeDatabase::getLaboreyeDatabase()->insertRecord(alarmInfo);

    //    Hikvision::getHikvision()->downLoadCapturePic();

}

void PreviewView::saveCapturePic(QNetworkReply* reply)
{
    qDebug() << "PreviewView:: saveCapturePic exec";

    QByteArray bytes = reply->readAll();

    //抓拍图片路径设置
    QString dirCapture = Config::getCfg()->getCapturePath() +
            alarmInfo.getDateTime().toString("yyyy-MM-dd hh:mm:ss") +
            "_" + alarmInfo.getSfzNo() + ".jpg";

    //保存抓拍图片文件
    QFile file(dirCapture);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(bytes);
        file.close();
    }
}

void PreviewView::setPersonInfo(AlarmInfo alarmInfo)
{
    ui->ledtName->setText(alarmInfo.getApplicant());
    ui->ledtIdCard->setText(alarmInfo.getSfzNo());
    ui->ledtSimilar->setText(QString::number(alarmInfo.getSimilar()));
    ui->ledtAddress->setText(alarmInfo.getAddress());

    QPixmap pixmap ;
    if(alarmInfo.getStranger() || alarmInfo.getApplicant() == "陌生人") {
        pixmap.load(":/Src/icon/cuowu.png");
    } else {
        pixmap.load(":/Src/icon/gou.png");
    }
    pixmap.scaled(ui->lblIcon->size(), Qt::KeepAspectRatio);
    ui->lblIcon->setScaledContents(true);
    ui->lblIcon->setPixmap(pixmap);
}

void PreviewView::addPersonInfoList(AlarmInfo alarmInfo)
{
    QIcon icon;
    if(alarmInfo.getStranger() || alarmInfo.getApplicant() == "陌生人") {
        icon.addFile(":/Src/icon/jinggao.png");
    } else {
        icon.addFile(":/Src/icon/tishi.png");
    }
    QString alarmText = alarmInfo.getDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\t" +
            alarmInfo.getApplicant() + "\t" + alarmInfo.getSfzNo();
    QListWidgetItem* item = new QListWidgetItem();
    item->setText(alarmText);
    item->setIcon(icon);
    ui->lstRecord->insertItem(0, item);
}

void PreviewView::on_btnClear_clicked()
{
    alarmInfoList.clear();
    ui->lstRecord->clear();
    ui->lblCapture->setText("抓拍图");
    ui->lblAvatar->setText("证件照");
    ui->lblFace->setText("人脸子图");
    ui->lblIcon->clear();
    ui->ledtName->clear();
    ui->ledtIdCard->clear();
    ui->ledtAddress->clear();
    ui->ledtSimilar->clear();
}

void PreviewView::on_btnSearch_clicked()
{
    on_btnClear_clicked();
    if(ui->ledtSearch->text() == "") {
        for(int i = 0; i < alarmInfoList.size(); ++i)
            addPersonInfoList(alarmInfoList[i]);
    } else {
        for(int i = 0; i < alarmInfoList.size(); ++i) {
            if(alarmInfoList[i].getApplicant() == ui->ledtSearch->text())
                addPersonInfoList(alarmInfoList[i]);
        }
    }
}
