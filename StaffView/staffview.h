#ifndef STAFFVIEW_H
#define STAFFVIEW_H

#include <QWidget>
#include <QObject>

#include "addstaffdialog.h"
#include "editstaffdialog.h"
#include "LaborEyeDatabase/laboreyedatabase.h"

namespace Ui {
class StaffView;
}

class StaffView : public QWidget
{
    Q_OBJECT

public:
    explicit StaffView(QWidget *parent = nullptr);
    ~StaffView();

signals:
    void _showEditStaffDialog();
    void _showAddStaffDialog();

private slots:
    void on_btnPrepage_clicked();

    void on_btnNxtpage_clicked();

    void on_btnJmppage_clicked();

    void on_btnConfirm_clicked();

    void on_btnDel_clicked();

    void on_btnEdit_clicked();

    void on_btnAdd_clicked();

private:
    Ui::StaffView *ui;

    static int pageSize;                //每页显示的记录数
    static int tolPages;                //总页数
    static int nowPage;                 //当前页码
    static QString name;
    static QString idCard;

    const int colNum = 4;               //表格列数

    static QList<ApplicantInfo> applicantInfoList;

    static EditStaffDialog *editStaffDialog;
    static AddStaffDialog *addStaffDialog;

    void initUI();

    void getStaffInfo();

    void setTblItem();
};

#endif // STAFFVIEW_H
