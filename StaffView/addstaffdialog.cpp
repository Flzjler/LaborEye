#include "addstaffdialog.h"
#include "ui_addstaffdialog.h"

AddressDialog* AddStaffDialog::addressDialog = nullptr;

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

void AddStaffDialog::on_btnAvatar_clicked()
{
    avatarPicPath = QFileDialog::getOpenFileName(this,
                                                 "请选择证件照",
                                                 "",
                                                 "Image Files(*.jpg)");
    ui->ledtAvatar->setText(avatarPicPath);

}

void AddStaffDialog::on_btnConfrim_clicked()
{
    if(ui->ledtName->text() == "" || ui->ledtRole->text() == ""
            || ui->ledtAvatar->text() == "" || ui->ledtIdCard->text() == ""
            || ui->ledtAddress->text() == "" || ui->ledtContact->text() == "") {
        QMessageBox::information(this, "提示", "请将内容填写完整");
        return;
    }

    ApplicantInfo applicantInfo;
    applicantInfo.setApplicant(ui->ledtName->text());
    applicantInfo.setContact(ui->ledtContact->text());
    applicantInfo.setSfzNo(ui->ledtIdCard->text());
    applicantInfo.setRole(ui->ledtRole->text());

    QString avatarPicPath = ui->ledtAvatar->text();

    Hikvision::getHikvision()->upload2FaceLib(applicantInfo.getApplicant(), avatarPicPath);
}

void AddStaffDialog::on_btnConcel_clicked()
{
    initUI();
    this->close();
}


void AddStaffDialog::on_btnAddress_clicked()
{
    if(addressDialog == nullptr)
        addressDialog = new AddressDialog();
    QObject::connect(this, SIGNAL(_showAddressDialog()), addressDialog, SLOT(showAddressDialog()));
    emit _showAddressDialog();
}
