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
    void on_btnPrepage_clicked();       //点击上一页

    void on_btnNxtpage_clicked();       //点击下一页

    void on_btnConfirm_clicked();       //点击确定

    void on_btnJmppage_clicked();       //点击跳转

private:
    Ui::HistoryView *ui;

    static int pageSize;                //每页显示的记录数
    static int tolPages;                //总页数
    static int nowPage;                 //当前页码
    static QDateTime startDateTime;
    static QDateTime endDateTime;
    static QString isStranger;
    static QString idCard;

    const int colNum = 3;               //表格列数

    void initUI();                      //初始化UI

    void setTblItem();                  //设置表格内容

    QList<RecordInfo> getRecordInfo();  //获取历史记录

};

#endif // HISTORYVIEW_H
