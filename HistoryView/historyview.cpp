#include "historyview.h"
#include "ui_historyview.h"

int HistoryView::pageSize = 0;
int HistoryView::tolPages = 0;
int HistoryView::nowPage = 0;

HistoryView::HistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryView)
{
    ui->setupUi(this);

    initUI();
}

HistoryView::~HistoryView()
{
    delete ui;
}

void HistoryView::initUI()
{
    nowPage = 1;
    pageSize = 14;
    int _tolPages = LaborEyeDatabase::getLaboreyeDatabase()->cntRecords();
    tolPages = _tolPages / pageSize + (_tolPages % pageSize ? 1 : 0);

    ui->ledtNowpage->setText(QString::number(nowPage));
    ui->lblTolpage->setText("/ " + QString::number(tolPages));
    //设置页码输入的范围
    ui->ledtNowpage->setValidator(new QIntValidator(1, tolPages, this));

    ui->dtEdtStartDate->setDateTime(QDateTime::currentDateTime());
    ui->dtEdtEndDate->setDateTime(QDateTime::currentDateTime());

    ui->cboxStranger->setCurrentIndex(2);

    //设置选择时选择一行
    ui->tblRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不留空
    ui->tblRecord->horizontalHeader()->setStretchLastSection(true);
    //设置列宽
    ui->tblRecord->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //设置表格行数
    ui->tblRecord->setRowCount(pageSize);
    //设置表头伸缩格式
    ui->tblRecord->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //取消多选
    ui->tblRecord->setSelectionMode(QAbstractItemView::SingleSelection);

}

QList<RecordInfo> HistoryView::getRecordInfo()
{
    QDateTime startDateTime = ui->dtEdtStartDate->dateTime();
    QDateTime endDateTime = ui->dtEdtEndDate->dateTime();
    QString stranger = ui->cboxStranger->currentText();
    QString idCard = ui->ledtIdCard->text();

    QList<RecordInfo> recordInfoList =LaborEyeDatabase::getLaboreyeDatabase()->selectRecordInfo(startDateTime, endDateTime,
                               stranger, idCard,
                               nowPage, pageSize);

    int recordsNum = LaborEyeDatabase::getLaboreyeDatabase()->cntRecordsNum(startDateTime, endDateTime,
                            stranger, idCard);
    tolPages = recordsNum / pageSize + (recordsNum%pageSize ? 1 : 0);

    return recordInfoList;
}

void HistoryView::setTblItem()
{
    QList<RecordInfo> recordInfoList = getRecordInfo();

    ui->tblRecord->clear();
    QTableWidgetItem *item[3];

    for(int i = 0; i < recordInfoList.size(); ++i) {
        for(int j = 0; j < colNum; ++j) {
            switch(j) {
            case 0: item[j] =new QTableWidgetItem(recordInfoList[i].getTimeValue()
                                                  .toString("yyyy-MM-dd ddd hh:mm"));
                break;
            case 1: item[j] = !recordInfoList[i].getStranger()
                        ? new QTableWidgetItem(recordInfoList[i].getApplicant())
                        : new QTableWidgetItem(QString::fromLocal8Bit("陌生人"));
                break;
            case 2: item[j] = recordInfoList[i].getAvatarId().length()
                        ? new QTableWidgetItem(recordInfoList[i].getAvatarId())
                        : new QTableWidgetItem(QString::fromLocal8Bit("未知"));
                break;
            }

            //设置只读
            item[j]->setFlags(item[j]->flags() ^ Qt::ItemIsEditable);
            //设置对齐方式
            item[j]->setTextAlignment(Qt::AlignCenter);
            //设置单元格内容
            ui->tblRecord->setItem(i, j, item[j]);
        }
    }
    for(int i = recordInfoList.size(); i < pageSize; ++i) {
        for(int j = 0; j < colNum; ++j) {
            item[j] = new QTableWidgetItem(QString(""));
            //设置只读
            item[j]->setFlags(item[j]->flags() ^ Qt::ItemIsEditable);
            //设置对齐方式
            item[j]->setTextAlignment(Qt::AlignCenter);
            //设置单元格内容
            ui->tblRecord->setItem(i, j, item[j]);
        }

    }
    ui->lblTolpage->setText("/ " + QString::number(tolPages));
}

void HistoryView::on_btnConfirm_clicked()
{
    nowPage = 1;
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void HistoryView::on_btnPrepage_clicked()
{
    if(nowPage == 1)
        return;

    --nowPage;
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void HistoryView::on_btnNxtpage_clicked()
{
    if(nowPage == tolPages)
        return;

    ++nowPage;
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void HistoryView::on_btnJmppage_clicked()
{
    nowPage = ui->ledtNowpage->text().toInt();
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}
