#include "staffview.h"
#include "ui_staffview.h"

StaffView::StaffView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffView)
{
    ui->setupUi(this);
    initUI();
}

StaffView::~StaffView()
{
    delete ui;
}

void StaffView::initUI()
{
    //设置选择时选择一行
    ui->tblStaffInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不留空
    ui->tblStaffInfo->horizontalHeader()->setStretchLastSection(true);
    //设置列宽
    ui->tblStaffInfo->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //设置表格行数
    ui->tblStaffInfo->setRowCount(14);
    //设置表头伸缩格式
    ui->tblStaffInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
