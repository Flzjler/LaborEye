#include "historyview.h"
#include "ui_historyview.h"

HistoryView::HistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryView)
{
    ui->setupUi(this);
}

HistoryView::~HistoryView()
{
    delete ui;
}
