#ifndef SETTINGVIEW_H
#define SETTINGVIEW_H

#include <QWidget>
#include <QFileDialog>

#include "Config/config.h"

namespace Ui {
class SettingView;
}

class SettingView : public QWidget
{
    Q_OBJECT

public:
    explicit SettingView(QWidget *parent = nullptr);
    ~SettingView();

private slots:


    void on_btnCapturePath_clicked();

    void on_btnAvatarPath_clicked();

    void on_btnFacePath_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::SettingView *ui;

    void initUI();
    void changeSetting();
};

#endif // SETTINGVIEW_H
