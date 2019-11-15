#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QString>
#include "PreviewView/previewview.h"
#include "HistoryView/historyview.h"
#include "HouseView/houseview.h"
#include "StaffView/staffview.h"
#include "SettingView/settingview.h"

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();

private:
    Ui::MainView *ui;

    static PreviewView* previewView;
    static HistoryView* historyView;
    static HouseView* houseView;
    static StaffView* staffView;
    static SettingView* settingView;
};

#endif // MAINVIEW_H
