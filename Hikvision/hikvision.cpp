#include "hikvision.h"
#include <QDebug>

NET_VCA_FACESNAP_MATCH_ALARM Hikvision::faceMatchAlarm;

Hikvision::Hikvision()
{

}

void CALLBACK Hikvision::g_ExceptionCallBack(DWORD dwType, LONG lUserID,
                                             LONG lHandle, void *pUser)
{
    qDebug() << "lUserID: " << lUserID << " lHandle" << lHandle << " pUser" << pUser;
    switch (dwType) {
    case EXCEPTION_RECONNECT:    //预览时重连
        qDebug() << "----------reconnect--------" << time(nullptr);
        break;
    default:
        break;
    }
}

BOOL CALLBACK Hikvision::MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
    switch(lCommand) {
    case COMM_SNAP_MATCH_ALARM: //人脸比对结果信息
    {
        qDebug() << "PreviewView: Detected face";
        memcpy(&faceMatchAlarm, pAlarmInfo, sizeof(NET_VCA_FACESNAP_MATCH_ALARM));
        //设置报警信息，用于记录所需用到的的报警数据
        //setAlarmInfo(struFaceMatchAlarm);
        //设置报警文本，用于在下方列表区显示
        //setAlarmText();
        //数据库操作
        //saveToDatabase();
        break;
    }
        return TRUE;
    }
    return true;
}


void Hikvision::showPreviewVideo(QList<HWND> hwndList)
{
    //---------------------------------------
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    //---------------------------------------
    //设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, nullptr, g_ExceptionCallBack, nullptr);

    //---------------------------------------
    // 注册设备
    LONG lUserID;

    //登录参数，包括设备地址、登录用户、密码等
    //NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_USER_LOGIN_INFO struLoginInfo;
    struLoginInfo.bUseAsynLogin = 0; //同步登录方式

    strcpy_s(struLoginInfo.sDeviceAddress,
             Config::getCfg()->getSuBrainIP().toLocal8Bit().data()); //设备IP地址
    struLoginInfo.wPort = static_cast<WORD>(Config::getCfg()->getSuBrainPort()); //设备服务端口
    strcpy_s(struLoginInfo.sUserName,
             Config::getCfg()->getSuBrainUsername().toLocal8Bit().data()); //设备登录用户名
    strcpy_s(struLoginInfo.sPassword,
             Config::getCfg()->getSuBrainPasword().toLocal8Bit().data()); //设备登录密码

    //设备信息, 输出参数
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID < 0)
    {
        printf("Login failed, error code: %d\n", static_cast<int>(NET_DVR_GetLastError()));
        NET_DVR_Cleanup();
        return;
    }

    //----------------1-----------------------
    //启动预览并设置回调数据流
    LONG lRealPlayHandle;
    HWND hWnd = hwndList.at(0);          //获取窗口句柄
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd = hWnd;        //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel     = 33;      //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked     = 1;       //0- 非阻塞取流，1- 阻塞取流
    //开始播放
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, nullptr, nullptr);
    //----------------1-----------------------

    //    if (lRealPlayHandle < 0)
    //    {
    //        printf("NET_DVR_RealPlay_V40 error\n");
    //        NET_DVR_Logout(lUserID);
    //        NET_DVR_Cleanup();
    //        return;
    //    }

    //---------------2-----------------------
    //启动预览并设置回调数据流
    HWND hWnd2 = hwndList.at(1);
    NET_DVR_PREVIEWINFO struPlayInfo2 = {0};
    struPlayInfo2.hPlayWnd     = hWnd2;   //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo2.lChannel     = 34;      //预览通道号
    struPlayInfo2.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo2.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo2.bBlocked     = 1;       //0- 非阻塞取流，1- 阻塞取流
    //开始播放
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo2, nullptr, nullptr);
    //---------------2-----------------------


    //设置报警回调函数
    NET_DVR_SetDVRMessageCallBack_V31(MessageCallback, nullptr);
    //启用布防
    LONG lHandle;
    NET_DVR_SETUPALARM_PARAM  struAlarmParam = {0};
    struAlarmParam.dwSize=sizeof(struAlarmParam);
    //其他报警布防参数不需要设置

    lHandle = NET_DVR_SetupAlarmChan_V41(lUserID, & struAlarmParam);
    if (lHandle < 0)
    {
        printf("NET_DVR_SetupAlarmChan_V41 error, %d\n", static_cast<int>(NET_DVR_GetLastError()));
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return;
    }

    //Sleep(10000);
    //---------------------------------------
    //关闭预览
    //NET_DVR_StopRealPlay(lRealPlayHandle);
    //注销用户
    //NET_DVR_Logout(lUserID);
    //释放SDK资源
    //NET_DVR_Cleanup();
}

void Hikvision::downLoadPicture(PICTYPE picType)
{
    QString url = QString(reinterpret_cast<char*>(faceMatchAlarm.pSnapPicBuffer));

    switch (picType) {
    case CAPTUREPICTURE:
        url = url.mid(0, url.indexOf("SEl"));
        qDebug() << "Download Capture Pic! The url is: " << url;
        break;
    case AVATARPICTURE:
        url = url.mid(0, url.indexOf("http://",1));
        qDebug() << "Download Avatar Pic! The url is: " << url;
        break;
    case FACEPICTURE:
        url = url.mid(0, url.indexOf("http://")+6);
        qDebug() << "Download Face Pic! The url is: " << url;
        break;
    }

    QEventLoop eventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QUrl qUrl(url);
    qUrl.setUserName(Config::getCfg()->getSuBrainUsername());
    qUrl.setPassword(Config::getCfg()->getSuBrainPasword());
    //QNetworkReply* reply = manager->get(QNetworkRequest(url));
    //connect(manager, SIGNAL(finished(QNetworkReply*)), previewView, SLOT(showAvatarPic(QNetworkReply*)));
    //connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
}


