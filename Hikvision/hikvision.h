#ifndef HIKVISION_H
#define HIKVISION_H

#include <stdio.h>
#include <iostream>
#include "Windows.h"
#include "HCNetSDK.h"
#include <time.h>
#include <QList>

#include "Config/config.h"

using namespace std;

class Hikvision
{
public:
    Hikvision();
    static void showPreviewVideo(QList<HWND> hwndList); //显示预览录像

private:
    static void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID,
                                             LONG lHandle, void *pUser);

};

#endif // HIKVISION_H
