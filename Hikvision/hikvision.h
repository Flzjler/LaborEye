#ifndef HIKVISION_H
#define HIKVISION_H

#include <time.h>

#include <QUrl>
#include <QList>
#include <QEventLoop>
#include <QNetworkAccessManager>


#include "Windows.h"
#include "HCNetSDK.h"
#include "Config/config.h"

typedef enum {
    CAPTUREPICTURE,
    AVATARPICTURE,
    FACEPICTURE
} PICTYPE;

class Hikvision : public QObject
{
    Q_OBJECT
public:
    static Hikvision* getHikvision()
    {
        if(hikvision == nullptr)
            hikvision = new Hikvision();
        return hikvision;
    }
    //显示预览录像
    static void showPreviewVideo(QList<HWND> hwndList);

    //使用url的方式下载图片
    static void downLoadPicture(PICTYPE picType);

signals:
    void returnAlarmInfo(NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm);

private:

    explicit Hikvision();
    ~Hikvision();

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

};

#endif // HIKVISION_H
