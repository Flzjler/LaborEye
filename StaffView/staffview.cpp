#include "staffview.h"
#include "ui_staffview.h"

StaffView::StaffView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffView)
{
    ui->setupUi(this);
}

StaffView::~StaffView()
{
    delete ui;
}
