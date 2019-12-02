#include "addstaffdialog.h"
#include "ui_addstaffdialog.h"

AddStaffDialog::AddStaffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffDialog)
{
    ui->setupUi(this);
}

AddStaffDialog::~AddStaffDialog()
{
    delete ui;
}

void AddStaffDialog::initUI()
{
    avatarPicPath = "";
    ui->ledtName->clear();
    ui->ledtAvatar->clear();
    ui->ledtIdCard->clear();
    ui->ledtRole->clear();
    ui->ledtAddress->clear();
    ui->ledtContact->clear();
}

void AddStaffDialog::showAddStaffDialog()
{
    initUI();
    this->show();
}

void AddStaffDialog::on_btnConcel_clicked()
{
    initUI();
    this->close();
}

void AddStaffDialog::on_btnConfrim_clicked()
{

}

void AddStaffDialog::on_btnAvatar_clicked()
{
    avatarPicPath = QFileDialog::getOpenFileName(this,
                                                 "请选择证件照",
                                                 "",
                                                 "Image Files(*.jpg)");
}
