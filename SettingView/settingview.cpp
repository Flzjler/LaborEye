#include "settingview.h"
#include "ui_settingview.h"

SettingView::SettingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingView)
{
    ui->setupUi(this);
    initUI();
}

SettingView::~SettingView()
{
    delete ui;
}

void SettingView::initUI()
{
    ui->ledtSuBrainIP->setText(Config::getCfg()->getSuBrainIP());
    ui->ledtSuBrainPort->setText(QString::number(Config::getCfg()->getSuBrainPort()));
    ui->ledtSuBrainUsername->setText(Config::getCfg()->getSuBrainUsername());
    ui->ledtSuBrainPwd->setText(Config::getCfg()->getSuBrainPasword());
    ui->ledtSuBrainChannel1->setText(QString::number(Config::getCfg()->getSuBrainChannel1()));
    ui->ledtSuBrainChannel2->setText(QString::number(Config::getCfg()->getSuBrainChannel2()));
    ui->ledtSuBrainChannel3->setText(QString::number(Config::getCfg()->getSuBrainChannel3()));
    ui->ledtSuBrainChannel4->setText(QString::number(Config::getCfg()->getSuBrainChannel4()));

    ui->ledtDBIP->setText(Config::getCfg()->getDatabaseIP());
    ui->ledtDBPort->setText(QString::number(Config::getCfg()->getDatabasePort()));
    ui->ledtDBName->setText(Config::getCfg()->getDataBaseName());
    ui->ledtDBUsername->setText(Config::getCfg()->getDatabaseUsername());
    ui->ledtDBPwd->setText(Config::getCfg()->getDatabasePasword());

    ui->ledtCapturePath->setText(Config::getCfg()->getCapturePath());
    ui->ledtAvatarPath->setText(Config::getCfg()->getAvatarPath());
    ui->ledtFacePath->setText(Config::getCfg()->getFacePath());
}

void SettingView::changeSetting()
{
    Config::getCfg()->setSuBrainIP(ui->ledtSuBrainIP->text());
    Config::getCfg()->setSuBrainPort(ui->ledtSuBrainPort->text().toInt());
    Config::getCfg()->setSuBrainUsername(ui->ledtSuBrainUsername->text());
    Config::getCfg()->setSuBrainPasword(ui->ledtSuBrainPwd->text());
    Config::getCfg()->setSuBrainChannel1(ui->ledtSuBrainChannel1->text().toInt());
    Config::getCfg()->setSuBrainChannel2(ui->ledtSuBrainChannel2->text().toInt());
    Config::getCfg()->setSuBrainChannel3(ui->ledtSuBrainChannel3->text().toInt());
    Config::getCfg()->setSuBrainChannel4(ui->ledtSuBrainChannel4->text().toInt());

    Config::getCfg()->setDatabaseIP(ui->ledtDBIP->text());
    Config::getCfg()->setDatabasePort(ui->ledtDBPort->text().toInt());
    Config::getCfg()->setDatabaseUsername(ui->ledtDBUsername->text());
    Config::getCfg()->setDatabasePassword(ui->ledtDBPwd->text());

    Config::getCfg()->setCapturePath(ui->ledtCapturePath->text());
    Config::getCfg()->setAvatarPath(ui->ledtAvatarPath->text());
    Config::getCfg()->setFacePath(ui->ledtFacePath->text());
    //qDebug() << ui->ledtFacePath->text();
}

void SettingView::on_btnCapturePath_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("抓拍图路径"), "./");
    ui->ledtCapturePath->setText(file_path + "/");
}

void SettingView::on_btnAvatarPath_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("证件图路径"), "./");
    ui->ledtAvatarPath->setText(file_path + "/");
}

void SettingView::on_btnFacePath_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("人脸子图路径"), "./");
    ui->ledtFacePath->setText(file_path + "/");
}

void SettingView::on_btnConfirm_clicked()
{
    changeSetting();
    initUI();
}
