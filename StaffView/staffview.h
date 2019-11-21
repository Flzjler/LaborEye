#ifndef STAFFVIEW_H
#define STAFFVIEW_H

#include <QWidget>

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

private slots:
    void on_btnPrepage_clicked();

    void on_btnNxtpage_clicked();

    void on_btnJmppage_clicked();

    void on_btnConfirm_clicked();

    void on_btnDel_clicked();

private:
    Ui::StaffView *ui;

    static int pageSize;                //每页显示的记录数
    static int tolPages;                //总页数
    static int nowPage;                 //当前页码
    static QString name;
    static QString idCard;

    const int colNum = 4;               //表格列数

    static QList<ApplicantInfo> applicantInfoList;

    void initUI();

    void getStaffInfo();

    void setTblItem();
};

#endif // STAFFVIEW_H
