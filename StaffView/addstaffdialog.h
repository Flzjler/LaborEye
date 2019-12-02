#ifndef ADDSTAFFDIALOG_H
#define ADDSTAFFDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class AddStaffDialog;
}

class AddStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffDialog(QWidget *parent = nullptr);
    ~AddStaffDialog();

public slots:
    void showAddStaffDialog();

private slots:
    void on_btnConcel_clicked();

    void on_btnConfrim_clicked();

    void on_btnAvatar_clicked();

private:
    Ui::AddStaffDialog *ui;
    QString avatarPicPath;

    void initUI();

};

#endif // ADDSTAFFDIALOG_H
