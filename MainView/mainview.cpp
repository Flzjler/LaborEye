#include "mainview.h"
#include "ui_mainview.h"

PreviewView* MainView::previewView = nullptr;
HistoryView* MainView::historyView = nullptr;
HouseView* MainView::houseView = nullptr;
StaffView* MainView::staffView = nullptr;
SettingView* MainView::settingView = nullptr;

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    ui->tbwMainView->removeTab(0);
    ui->tbwMainView->removeTab(0);

    if(previewView == nullptr) {
        previewView = new PreviewView();
        ui->tbwMainView->addTab(previewView, QString::fromLocal8Bit("预览"));
    }

    if(historyView == nullptr) {
        historyView = new HistoryView();
        ui->tbwMainView->addTab(historyView, QString::fromLocal8Bit("记录查看"));
    }

    if(houseView == nullptr) {
        houseView = new HouseView();
        ui->tbwMainView->addTab(houseView, QString::fromLocal8Bit("住房状况"));
    }

    if(staffView == nullptr) {
        staffView = new StaffView();
        ui->tbwMainView->addTab(staffView, QString::fromLocal8Bit("住户信息"));
    }

    if(settingView == nullptr) {
        settingView = new SettingView();
        ui->tbwMainView->addTab(settingView, QString::fromLocal8Bit("设置"));
    }
}

MainView::~MainView()
{
    delete ui;
}
