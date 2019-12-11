#include "hikvision.h"
#include <QDebug>

QString Hikvision::capturePicURL;
QString Hikvision::avatarPicURL;
QString Hikvision::facePicURL;

LONG Hikvision::lUserID;
Hikvision* Hikvision::hikvision = nullptr;
NET_VCA_FACESNAP_MATCH_ALARM Hikvision::faceMatchAlarm;
//QEventLoop* Hikvision::eventLoop = nullptr;
//QNetworkAccessManager* Hikvision::manager = nullptr;

Hikvision::Hikvision()
{

}

Hikvision::~Hikvision()
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
    qDebug() << "PreviewView: Detected face";
    switch(lCommand) {
    case COMM_SNAP_MATCH_ALARM: //人脸比对结果信息
    {
        memcpy(&faceMatchAlarm, pAlarmInfo, sizeof(NET_VCA_FACESNAP_MATCH_ALARM));

        capturePicURL = QString(reinterpret_cast<char*>(faceMatchAlarm.pSnapPicBuffer));
        capturePicURL = capturePicURL.mid(0, capturePicURL.indexOf("SEl"));

        facePicURL = QString(reinterpret_cast<char*>(faceMatchAlarm.struSnapInfo.pBuffer1));
        facePicURL = facePicURL.mid(0,facePicURL.indexOf("http://", 1));

        avatarPicURL = QString(reinterpret_cast<char*>(faceMatchAlarm.struBlackListInfo.pBuffer1));
        avatarPicURL = avatarPicURL.mid(0,avatarPicURL.indexOf("http://", 1));

        if(hikvision == nullptr)
            hikvision = new Hikvision();

        emit hikvision->returnAlarmInfo(faceMatchAlarm);
        Sleep(300);
    }
        break;
    }
    return true;
}

void Hikvision::showPreviewVideo(QList<HWND> hwndList)
{
    if(hikvision == nullptr) {
        hikvision = new Hikvision();
    }

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

    //----------------1----------------------
    //启动预览并设置回调数据流
    LONG lRealPlayHandle;
    HWND hWnd = hwndList.at(0);          //获取窗口句柄
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd = hWnd;        //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel     = Config::getCfg()->getSuBrainChannel1();      //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked     = 1;       //0- 非阻塞取流，1- 阻塞取流
    //开始播放
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, nullptr, nullptr);
    //----------------1----------------------

    //---------------2---------------------
    //启动预览并设置回调数据流
        HWND hWnd2 = hwndList.at(1);
        NET_DVR_PREVIEWINFO struPlayInfo2 = {0};
        struPlayInfo2.hPlayWnd     = hWnd2;   //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
        struPlayInfo2.lChannel     = Config::getCfg()->getSuBrainChannel2();      //预览通道号
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

    if (lHandle)
    {
        printf("NET_DVR_SetupAlarmChan_V41 error, %d\n", static_cast<int>(NET_DVR_GetLastError()));
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return;
    }
}

void Hikvision::getNET_DVR_STDXMLConfig() {
    NET_DVR_XML_CONFIG_INPUT  lpInputParam = {0};
    NET_DVR_XML_CONFIG_OUTPUT lpOutputParam = {0};
    qDebug() << "enter getNET_DVR_STDXMLConfig";//不要删除这条输出
    lpInputParam.dwSize = sizeof(lpInputParam);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/Intelligent/FDLib\r\n");
    lpInputParam.lpRequestUrl = szUrl;
    lpInputParam.dwRequestUrlLen = strlen(szUrl);
    lpInputParam.lpInBuffer = NULL;
    lpInputParam.dwInBufferSize = 0;
    lpInputParam.dwRecvTimeOut = 0;
    lpInputParam.byForceEncrpt = 0;
    lpInputParam.byNumOfMultiPart = 0;
    memset(lpInputParam.byRes, 0, sizeof (lpInputParam.byRes));
    /********************lpOutBuffer********************/
    void  *lpOutBuffer;
    lpOutputParam.dwSize = sizeof(lpOutputParam);
    lpOutputParam.lpOutBuffer = lpOutBuffer;
    lpOutputParam.dwOutBufferSize = 1024;
    DWORD  dwReturnedXMLSize;
    lpOutputParam.dwReturnedXMLSize = dwReturnedXMLSize;
    void  *lpStatusBuffer;
    lpOutputParam.lpStatusBuffer = lpStatusBuffer;
    lpOutputParam.dwStatusSize = 0;
    memset(lpOutputParam.byRes, 0, sizeof (lpOutputParam.byRes));
    /********************lpOutBuffer********************/

    bool f = NET_DVR_STDXMLConfig(lUserID, &lpInputParam, &lpOutputParam);
    qDebug() << "dwReturnedXMLSize: " << dwReturnedXMLSize;
    qDebug() << "lpOutBuffer: " << (char*)lpOutBuffer;
    qDebug() << "lpStatusBuffer: " << (char*)lpStatusBuffer;
    qDebug() << "flag: " << f << " errorCode: " << NET_DVR_GetLastError();
}

bool Hikvision::upload2FaceLib(QString name, QString picFilePath)
{
    LaborEyeXML::setUploadXML(name);
    qDebug() << "enter uploadStrangerFacePic";
    char FDID[256] = "99C615F7B4414ED3BC54E50C42DE87ED";
    QByteArray qArray = picFilePath.toLocal8Bit();
    char szPicFileName[256];
    strcpy_s(szPicFileName, qArray.data());

    qArray = LaborEyeXML::getXMLPath().toLocal8Bit();
    char szXMLFileName[256];
    strcpy_s(szXMLFileName, qArray.data());

    NET_DVR_FACELIB_COND struFaceLibCond = { 0 };
    struFaceLibCond.dwSize = sizeof(NET_DVR_FACELIB_COND);
    strcpy_s(struFaceLibCond.szFDID, FDID);
    struFaceLibCond.byConcurrent = 0;
    struFaceLibCond.byCover = 0;
    struFaceLibCond.byCustomFaceLibID = 0;
    //建立连接
    LONG m_lUploadHandle = NET_DVR_UploadFile_V40(lUserID, IMPORT_DATA_TO_FACELIB, &struFaceLibCond, sizeof(NET_DVR_FACELIB_COND),
                                                  nullptr, nullptr, 0);
    NET_DVR_SEND_PARAM_IN m_struSendParam;
    memset(&m_struSendParam, 0, sizeof(m_struSendParam));
    BYTE    *pSendAppendData = nullptr;
    BYTE    *pSendPicData = nullptr;
    //读图片文件
    //D:/Hikvision/Camera/stranger/3977.jpg
    //D:/Hikvision/Camera/stranger/3962.jpg
    qDebug() << "szPicFileName: " << szPicFileName;
    QFileInfo fileinfo(szPicFileName);
    DWORD picFileSize = static_cast<DWORD>(fileinfo.size());
    pSendPicData = new BYTE[picFileSize];
    QFile picFile(szPicFileName);
    if(!picFile.open(QIODevice::ReadOnly)) {
        qDebug()<<"Can't open the pic file!"<<endl;
        return false;
    }
    QByteArray qbt = picFile.readAll();
    picFile.close();
    pSendPicData = reinterpret_cast<byte*>(qbt.data());

    //qDebug() << "picFileSize: " << picFileSize;
    m_struSendParam.pSendData = pSendPicData;
    m_struSendParam.dwSendDataLen = picFileSize;
    m_struSendParam.byPicType = 1;

    //读XML文件
    QFileInfo xmlinfo(szXMLFileName);
    DWORD xmlFileSize = static_cast<DWORD>(xmlinfo.size());
    pSendAppendData = new BYTE[xmlFileSize];
    QFile xmlFile(szXMLFileName);
    if(!xmlFile.open(QIODevice::ReadOnly)) {
        qDebug()<<"Can't open the xml file!"<<endl;
        return false;
    }
    QByteArray xmlArray = xmlFile.readAll();
    pSendAppendData = (byte*)(xmlArray.data());
    m_struSendParam.pSendAppendData = pSendAppendData;
    m_struSendParam.dwSendAppendDataLen = xmlFileSize;
    //上传文件
    LONG flag = NET_DVR_UploadSend(m_lUploadHandle, &m_struSendParam, nullptr);
    /*qDebug() << "flag: " << flag;
        qDebug() << "errorCode: " << NET_DVR_GetLastError();*/
    LONG iStatus = -1;
    while(1) {
        DWORD dwProgress = 0;
        iStatus = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
        if (1 == iStatus) {
            /*NET_DVR_UPLOAD_FILE_RET m_struPicRet;
                memset(&m_struPicRet, 0, sizeof(m_struPicRet));
                NET_DVR_GetUploadResult(m_lUploadHandle, &m_struPicRet, sizeof(m_struPicRet));
                qDebug() << "sUrl: " << (char*)(m_struPicRet.sUrl);*/
            break;
        } else if(iStatus != 2) {
            break;
        }
        /* else if ((iStatus >= 3 && iStatus <= 10) || iStatus == 31 || iStatus == -1) {
                break;
            }*/
    }
    NET_DVR_UploadClose(m_lUploadHandle);
    return iStatus == 1;
}



void Hikvision::downLoadCapturePic(QString url)
{
//    QString url = QString(reinterpret_cast<char*>(faceMatchAlarm.pSnapPicBuffer));
//    qDebug() << "url: " << url;
    //下载抓拍图
//    url = url.mid(0, url.indexOf("SEl"));

    QEventLoop eventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), PreviewView::getPreviewView(),
                    SLOT(saveCapturePic(QNetworkReply*)));
    QUrl qUrl(url);
    qUrl.setUserName(Config::getCfg()->getSuBrainUsername());
    qUrl.setPassword(Config::getCfg()->getSuBrainPasword());

    QNetworkReply* reply = manager->get(QNetworkRequest(qUrl));
    eventLoop.exec();
}

void Hikvision::downLoadAvatarPic(QString url)
{
    //下载证件照
    QEventLoop eventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), PreviewView::getPreviewView(), SLOT(saveAvatarPic(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl qUrl(url);
    qUrl.setUserName(Config::getCfg()->getSuBrainUsername());
    qUrl.setPassword(Config::getCfg()->getSuBrainPasword());

    QNetworkReply* reply = manager->get(QNetworkRequest(qUrl));
    qDebug() << "Download Avatar Pic! The url is: " << url;
    eventLoop.exec();
}

void Hikvision::downLoadFacePic(QString url)
{
    //下载人脸子图
    QEventLoop eventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), PreviewView::getPreviewView(), SLOT(saveFacePic(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl qUrl(url);
    qUrl.setUserName(Config::getCfg()->getSuBrainUsername());
    qUrl.setPassword(Config::getCfg()->getSuBrainPasword());

    QNetworkReply* reply = manager->get(QNetworkRequest(qUrl));
//    qDebug() << "Download Face Pic! The url is: " << url;
    eventLoop.exec();
}


