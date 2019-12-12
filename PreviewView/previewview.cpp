#include "previewview.h"
#include "ui_previewview.h"

PreviewView* PreviewView::previewView;
QList<AlarmInfo> PreviewView::alarmInfoList;
AlarmInfo PreviewView::alarmInfo;

PreviewView::PreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewView)
{
    ui->setupUi(this);
    QList<HWND> hwndList;
    hwndList.append(HWND(ui->lblChannel1->winId()));
    hwndList.append(HWND(ui->lblChannel2->winId()));
    Hikvision::showPreviewVideo(hwndList);
}

PreviewView::~PreviewView()
{
    delete ui;
}

void PreviewView::setAlarmInfo(NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm)
{
    //    qDebug() << QString::fromLocal8Bit(reinterpret_cast<char*>(faceMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byName));

    bool is2Upload = false;
    QDateTime dateTime(QDate(GET_YEAR(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_MONTH(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_DAY(faceMatchAlarm.struSnapInfo.dwAbsTime)),
                       QTime(GET_HOUR(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_MINUTE(faceMatchAlarm.struSnapInfo.dwAbsTime),
                             GET_SECOND(faceMatchAlarm.struSnapInfo.dwAbsTime)));
    QString sfzNo = "";
    int similar = static_cast<int>(faceMatchAlarm.fSimilarity*100);
    if(similar >= Config::getCfg()->getSimilar()) {
        sfzNo = QString::fromLocal8Bit(reinterpret_cast<char*>
                                       (faceMatchAlarm.struBlackListInfo.
                                        struBlackListInfo.struAttribute.byName));
        if(sfzNo[sfzNo.length()-1] != 'm') { //非陌生人
            alarmInfo.setApplicant(LaborEyeDatabase::getLaboreyeDatabase()->
                                   selectPersonInfo(sfzNo).applicant);
            alarmInfo.setAddress(LaborEyeDatabase::getLaboreyeDatabase()->
                                 selectPersonInfo(sfzNo).address);
            alarmInfo.setStranger(false);

        } else { //曾经出现过的陌生人
            alarmInfo.setApplicant(QString::fromLocal8Bit("陌生人"));
            alarmInfo.setAddress("");
            alarmInfo.setStranger(true);
        }

    } else { //新陌生人
        alarmInfo.setApplicant(QString::fromLocal8Bit("陌生人"));
        sfzNo = dateTime.toString("yyyyMMddhhmmss");
//        qDebug() << "stranger's sfzNo: " << sfzNo;
        alarmInfo.setStranger(true);
        is2Upload = true;
    }

    if(alarmInfo.getApplicant() == "")
        alarmInfo.setApplicant(QString::fromLocal8Bit("陌生人"));
    alarmInfo.setSfzNo(sfzNo);
    alarmInfo.setSimilar(similar);
    alarmInfo.setDateTime(dateTime);

    alarmInfoList.append(alarmInfo);

    Sleep(300);

    //下载图片至本地
    QString url = Hikvision::capturePicURL;
    Hikvision::getHikvision()->downLoadCapturePic(url);

    url = Hikvision::avatarPicURL;
    Hikvision::getHikvision()->downLoadAvatarPic(url);

    url = Hikvision::facePicURL;
    Hikvision::getHikvision()->downLoadFacePic(url);

    setPersonInfo();
    addPersonInfoList(alarmInfo);

    LaborEyeDatabase::getLaboreyeDatabase()->insertRecord(alarmInfo);

    if(is2Upload) {
        //陌生人人脸图需上传至超脑
        Hikvision::getHikvision()->upload2FaceLib(sfzNo+"m", Config::getCfg()->getFacePath() +
                                                                 alarmInfo.getDateTime().toString("yyyyMMddhhmmss") +
                                                                 "_" + alarmInfo.getSfzNo() + ".jpg");
        is2Upload = false;
    }
}

void PreviewView::setPersonInfo()
{
    ui->ledtName->setText(alarmInfo.getApplicant());
    ui->ledtIdCard->setText(alarmInfo.getSfzNo());
    ui->ledtSimilar->setText(QString::number(alarmInfo.getSimilar()));
    ui->ledtAddress->setText(alarmInfo.getAddress());

    QPixmap pixmap ;
    if(alarmInfo.getStranger() || alarmInfo.getApplicant() == QString::fromLocal8Bit("陌生人")) {
        pixmap.load(":/Src/icon/cuowu.png");
    } else {
        pixmap.load(":/Src/icon/gou.png");
    }
    pixmap.scaled(ui->lblIcon->size(), Qt::KeepAspectRatio);
    ui->lblIcon->setScaledContents(true);
    ui->lblIcon->setPixmap(pixmap);
//    qDebug() << "pic alarmInfo: " << alarmInfo.getDateTime().toString("yyyy-MM-dd hh:mm:ss") << " " << alarmInfo.getSfzNo();

    QString picName = alarmInfo.getDateTime().toString("yyyyMMddhhmmss").append("_" + alarmInfo.getSfzNo() + ".jpg");
    QImage captureImage(Config::getCfg()->getCapturePath() + picName);

//    qDebug() << "show Capture Pic Path: " << Config::getCfg()->getCapturePath() + picName;

    QImage avatarImage(Config::getCfg()->getAvatarPath() + alarmInfo.getSfzNo() + ".jpg");

    QImage faceImage(Config::getCfg()->getFacePath() + picName);

    ui->lblCapture->setPixmap(QPixmap::fromImage(captureImage).scaled(ui->lblCapture->size(),
                                                                      Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->lblAvatar->setPixmap(QPixmap::fromImage(avatarImage).scaled(ui->lblAvatar->size(),
                                                                     Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->lblFace->setPixmap(QPixmap::fromImage(faceImage).scaled(ui->lblFace->size(),
                                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void PreviewView::addPersonInfoList(AlarmInfo alarmInfo)
{
    QIcon icon;
    if(alarmInfo.getStranger() || alarmInfo.getApplicant() == QString::fromLocal8Bit("陌生人")) {
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
    ui->lblCapture->setText(QString::fromLocal8Bit("抓拍图"));
    ui->lblAvatar->setText(QString::fromLocal8Bit("证件照"));
    ui->lblFace->setText(QString::fromLocal8Bit("人脸子图"));
    ui->lblIcon->clear();
    ui->ledtName->clear();
    ui->ledtIdCard->clear();
    ui->ledtAddress->clear();
    ui->ledtSimilar->clear();

//    Hikvision::getNET_DVR_STDXMLConfig();
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

void PreviewView::saveCapturePic(QNetworkReply* reply)
{
//    qDebug() << "PreviewView:: saveCapturePic exec";

    QByteArray bytes = reply->readAll();

    //抓拍图片路径设置
    QString picName = alarmInfo.getDateTime().toString("yyyyMMddhhmmss").
                            append("_" + alarmInfo.getSfzNo() + ".jpg");
    QString dirCapture = Config::getCfg()->getCapturePath() + picName;
//    qDebug() << "dirCapturePic: " << dirCapture;

    //保存抓拍图片文件
    QFile file(dirCapture);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(bytes);
        file.close();
    }
}

void PreviewView::saveAvatarPic(QNetworkReply* reply)
{
    qDebug() << "PreviewView:: saveAvatarPic exec";

    QByteArray bytes = reply->readAll();

    //证件图片路径设置
    QString dirAvatar = Config::getCfg()->getAvatarPath() +
                        alarmInfo.getSfzNo() + ".jpg";
    qDebug() << "dirAvatar: " << dirAvatar;

    //保存证件图片文件
    QFile file(dirAvatar);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(bytes);
        file.close();
    }
}

void PreviewView::saveFacePic(QNetworkReply* reply)
{
//    qDebug() << "PreviewView:: saveFacePic exec";

    QByteArray bytes = reply->readAll();

    //人脸图片路径设置
    QString picName = alarmInfo.getDateTime().toString("yyyyMMddhhmmss").
                        append("_" + alarmInfo.getSfzNo() + ".jpg");
    QString dirFace = Config::getCfg()->getFacePath() + picName;
//    qDebug() << "dirFace: " << dirFace;
    //保存人脸子图文件
    QFile file(dirFace);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(bytes);
        file.close();
    }
}

void PreviewView::on_lstRecord_itemDoubleClicked(QListWidgetItem *item)
{
    int currentRow = ui->lstRecord->currentRow();
    int index = alarmInfoList.size() - 1 - currentRow;
    alarmInfo = alarmInfoList[index];
    setPersonInfo();
}
