#include "staffview.h"
#include "ui_staffview.h"

int StaffView::pageSize;                //每页显示的记录数
int StaffView::tolPages;                //总页数
int StaffView::nowPage;                 //当前页码
QString StaffView::name;
QString StaffView::idCard;
QList<ApplicantInfo> StaffView::applicantInfoList;
EditStaffDialog* StaffView::editStaffDialog = nullptr;
AddStaffDialog* StaffView::addStaffDialog = nullptr;

StaffView::StaffView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffView)
{
    ui->setupUi(this);
    initUI();
    setTblItem();
}

StaffView::~StaffView()
{
    delete ui;
}

void StaffView::initUI()
{
    nowPage = 1;
    pageSize = 14;
    name = ui->ledtName->text();
    idCard = ui->ledtIdCard->text();

    ui->ledtNowpage->setText(QString::number(nowPage));
    ui->lblTolpage->setText("/ " + QString::number(tolPages));
    int applicantNum = LaborEyeDatabase::getLaboreyeDatabase()->cntApplicant(name ,idCard);
    tolPages = applicantNum / pageSize + (applicantNum%pageSize ? 1 : 0);

    //设置页码输入的范围
    ui->ledtNowpage->setValidator(new QIntValidator(1, tolPages, this));

    //设置选择时选择一行
    ui->tblStaffInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不留空
    ui->tblStaffInfo->horizontalHeader()->setStretchLastSection(true);
    //设置列宽
    ui->tblStaffInfo->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //设置表格行数
    ui->tblStaffInfo->setRowCount(pageSize);
    //设置表头伸缩格式
    ui->tblStaffInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //取消多选
    ui->tblStaffInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    //取消默认行号
    ui->tblStaffInfo->verticalHeader()->setHidden(true);
}

void StaffView::getStaffInfo()
{
    applicantInfoList = LaborEyeDatabase::getLaboreyeDatabase()->selectApplicantInfo(name, idCard,
                                                                                                            nowPage, pageSize);

    int applicantNum = LaborEyeDatabase::getLaboreyeDatabase()->cntApplicant(name, idCard);
    tolPages = applicantNum / pageSize + (applicantNum%pageSize ? 1 : 0);
}

void StaffView::setTblItem()
{
    ui->tblStaffInfo->clear();

    getStaffInfo();

    QTableWidgetItem *item[4];
    for(int i = 0; i < applicantInfoList.size(); ++i) {
        for(int j = 0; j < colNum; ++j) {
            switch(j) {
            case 0: item[j] = new QTableWidgetItem(applicantInfoList[i].getApplicant());
                break;
            case 1: item[j] = new QTableWidgetItem(applicantInfoList[i].getSfzNo());
                break;
            case 2: item[j] = new QTableWidgetItem(applicantInfoList[i].getContact());
                break;
            case 3:
                QString address = QString::fromLocal8Bit("新兴茗苑") + applicantInfoList[i].getBuilding() + QString::fromLocal8Bit("幢") +
                                    applicantInfoList[i].getUnit() + QString::fromLocal8Bit("单元") +
                                    applicantInfoList[i].getHouse() + QString::fromLocal8Bit("室");
                item[j] = new QTableWidgetItem(address);
                break;
            }

            //设置只读
            item[j]->setFlags(item[j]->flags() ^ Qt::ItemIsEditable);
            //设置对齐方式
            item[j]->setTextAlignment(Qt::AlignCenter);
            //设置单元格内容
            ui->tblStaffInfo->setItem(i, j, item[j]);
        }
    }
    for(int i = applicantInfoList.size(); i < pageSize; ++i) {
        for(int j = 0; j < colNum; ++j) {
            item[j] = new QTableWidgetItem(QString(""));
            //设置只读
            item[j]->setFlags(item[j]->flags() ^ Qt::ItemIsEditable);
            //设置对齐方式
            item[j]->setTextAlignment(Qt::AlignCenter);
            //设置单元格内容
            ui->tblStaffInfo->setItem(i, j, item[j]);
        }
    }
    ui->lblTolpage->setText("/ " + QString::number(tolPages));
}

void StaffView::on_btnPrepage_clicked()
{
    if(nowPage == 1)
        return;
    nowPage--;
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void StaffView::on_btnNxtpage_clicked()
{
    if(nowPage == tolPages)
        return;
    nowPage++;
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void StaffView::on_btnJmppage_clicked()
{
    nowPage = ui->ledtNowpage->text().toInt();
    ui->ledtNowpage->setText(QString::number(nowPage));
    setTblItem();
}

void StaffView::on_btnConfirm_clicked()
{
    nowPage = 1;
    name = ui->ledtName->text();
    idCard = ui->ledtIdCard->text();

    ui->ledtNowpage->setText(QString::number(nowPage));

    setTblItem();
}

void StaffView::on_btnDel_clicked()
{
    if(ui->tblStaffInfo->currentRow() == -1) {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先选择需要删除的住户信息!"));
        return;
    }
    int choose= QMessageBox::question(this,  QString::fromLocal8Bit("警告"),
                                   QString::fromLocal8Bit("是否删除该住户信息?"),
                                  QMessageBox::Yes | QMessageBox::No);

    ApplicantInfo delApplicantInfo = applicantInfoList[ui->tblStaffInfo->currentRow()];
    if (choose== QMessageBox::Yes) {
        if(LaborEyeDatabase::getLaboreyeDatabase()->deleteApplicantInfo(delApplicantInfo)) {
            QMessageBox::information(this,  QString::fromLocal8Bit("提示"),  QString::fromLocal8Bit("删除成功"));
            setTblItem();
        } else {
            QMessageBox::information(this,  QString::fromLocal8Bit("提示"),  QString::fromLocal8Bit("删除失败"));
        }
    }
}

void StaffView::on_btnEdit_clicked()
{
    if(ui->tblStaffInfo->currentRow() == -1) {
        QMessageBox::information(this,  QString::fromLocal8Bit("提示"),
                                 QString::fromLocal8Bit("请先选择需要编辑的住户信息!"));
        return;
    }
    if(editStaffDialog == nullptr)
        editStaffDialog = new EditStaffDialog();
    QObject::connect(this, SIGNAL(_showEditStaffDialog()), editStaffDialog, SLOT(showEditStaffDialog()));
    emit _showEditStaffDialog();
}

void StaffView::on_btnAdd_clicked()
{
    if(addStaffDialog == nullptr)
        addStaffDialog = new AddStaffDialog();
    QObject::connect(this, SIGNAL(_showAddStaffDialog()), addStaffDialog, SLOT(showAddStaffDialog()));
    emit _showAddStaffDialog();
}
