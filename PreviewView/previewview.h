#ifndef PREVIEWVIEW_H
#define PREVIEWVIEW_H

#include <QWidget>
#include <QNetworkReply>

#include "Hikvision/hikvision.h"
#include "Entity/alarminfo.h"
#include "LaborEyeDatabase/laboreyedatabase.h"

//时间解析宏定义
#define GET_YEAR(_time_)      (((_time_)>>26) + 2000)
#define GET_MONTH(_time_)     (((_time_)>>22) & 15)
#define GET_DAY(_time_)       (((_time_)>>17) & 31)
#define GET_HOUR(_time_)      (((_time_)>>12) & 31)
#define GET_MINUTE(_time_)    (((_time_)>>6)  & 63)
#define GET_SECOND(_time_)    (((_time_)>>0)  & 63)

namespace Ui {
class PreviewView;
}

class PreviewView : public QWidget
{
    Q_OBJECT

public:
    static PreviewView* getPreviewView()
    {
        if(previewView == nullptr)
            previewView = new PreviewView();
        return previewView;
    }


public slots:
    void setAlarmInfo(NET_VCA_FACESNAP_MATCH_ALARM faceMatchAlarm);

    void saveCapturePic(QNetworkReply*);

    void saveAvatarPic(QNetworkReply*);

    void saveFacePic(QNetworkReply*);

private slots:
    void on_btnClear_clicked();

    void on_btnSearch_clicked();

private:
    Ui::PreviewView *ui;
    AlarmInfo alarmInfo;
    explicit PreviewView(QWidget *parent = nullptr);
    ~PreviewView();
    static PreviewView* previewView;
    static QList<AlarmInfo> alarmInfoList;

    void setPersonInfo(AlarmInfo alarmInfo);
    void addPersonInfoList(AlarmInfo alarmInfo);
};

#endif // PREVIEWVIEW_H
