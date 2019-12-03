#ifndef ADDSTAFFDIALOG_H
#define ADDSTAFFDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "Util/laboreyexml.h"
#include "Entity/applicantinfo.h"
#include "Entity/addressinfo.h"
#include "addressdialog.h"
#include "Hikvision/hikvision.h"

namespace Ui {
class AddStaffDialog;
}

class AddStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffDialog(QWidget *parent = nullptr);
    ~AddStaffDialog();

signals:
    void _showAddressDialog();

public slots:
    void showAddStaffDialog();
    void getAddressInfo(AddressInfo _addressInfo);

private slots:
    void on_btnConcel_clicked();

    void on_btnConfrim_clicked();

    void on_btnAvatar_clicked();

    void on_btnAddress_clicked();

private:
    Ui::AddStaffDialog *ui;
    QString avatarPicPath;
    ApplicantInfo applicantInfo;
    AddressInfo addressInfo;
    static AddressDialog* addressDialog;

    void initUI();

};

#endif // ADDSTAFFDIALOG_H
