#include "settingview.h"
#include "ui_settingview.h"

SettingView::SettingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingView)
{
    ui->setupUi(this);
}

SettingView::~SettingView()
{
    delete ui;
}
