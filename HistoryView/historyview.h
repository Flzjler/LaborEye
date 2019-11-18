#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>

#include "LaborEyeDatabase/laboreyedatabase.h"

namespace Ui {
class HistoryView;
}

class HistoryView : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryView(QWidget *parent = nullptr);
    ~HistoryView();

private slots:
    void on_btnPrepage_clicked();

    void on_btnNxtpage_clicked();

    void on_btnConfirm_clicked();

    void on_btnJmppage_clicked();

private:
    Ui::HistoryView *ui;

    static int pageSize;    //每页显示的记录数
    static int tolPages;    //总页数
    static int nowPage;     //当前页码
    const int colNum = 3;   //表格列数

    void initUI();
    void setTblItem();
    QList<RecordInfo> getRecordInfo();

};

#endif // HISTORYVIEW_H
