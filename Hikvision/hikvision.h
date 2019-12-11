#ifndef HIKVISION_H
#define HIKVISION_H

#include <time.h>

#include <QUrl>
#include <QFile>
#include <QList>
#include <QFileInfo>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkAccessManager>


#include "Windows.h"
#include "HCNetSDK.h"
#include "Config/config.h"
#include "Util/laboreyexml.h"
#include "PreviewView/previewview.h"

class Hikvision : public QObject
{
    Q_OBJECT
public:
    static Hikvision* getHikvision()
    {
        if(hikvision == nullptr)
            hikvision = new Hikvision();
//        if(eventLoop == nullptr)
//            eventLoop = new QEventLoop();
//        if(manager == nullptr)
//            manager = new QNetworkAccessManager();
        return hikvision;
    }
    //显示预览录像
    static void showPreviewVideo(QList<HWND> hwndList);

    //使用url的方式下载抓拍图
    static void downLoadCapturePic(QString url);
    static void downLoadAvatarPic();
    static void downLoadFacePic();

//    static QEventLoop* getEventLoop() {
//        if(eventLoop == nullptr)
//            eventLoop = new QEventLoop();
//        return eventLoop;
//    }
//    static QNetworkAccessManager* getManager() {
//        if(manager == nullptr)
//            manager = new QNetworkAccessManager();
//        return manager;
//    }

    //向人脸库中添加一条信息
    static bool upload2FaceLib(QString name, QString picFilePath);

    static QString getPicURL();
    static QString picURL;

signals:
    void returnAlarmInfo(NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm);

private:

    explicit Hikvision();
    ~Hikvision();

//    static QEventLoop* eventLoop;

//    static QNetworkAccessManager* manager;

    static Hikvision* hikvision;

    static LONG lUserID;

    //人脸比对结果报警上传结构体
    static NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm;

    //异常回调函数
    static void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID,
                                             LONG lHandle, void *pUser);
    //报警回调函数
    static BOOL CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer,
                                         char *pAlarmInfo, DWORD dwBufLen, void* pUser);

    //获取超脑能力集信息
    static void getNET_DVR_STDXMLConfig();


};

#endif // HIKVISION_H
