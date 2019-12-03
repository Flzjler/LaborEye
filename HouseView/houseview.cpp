#include "houseview.h"
#include "ui_houseview.h"

int HouseView::houseRowNum = 15;
int HouseView::houseColNum = 5;

QList<QString> HouseView::buildingsId;
QList<QString> HouseView::unitsId;
QList<QString> HouseView::housesId;
QList<ApplicantRecordInfo> HouseView::applicantRecordList;

HouseView::HouseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HouseView)
{
    ui->setupUi(this);
    initUI();
}

HouseView::~HouseView()
{
    delete ui;
}

void HouseView::initUI()
{
    ui->dtStartTime->setDateTime(QDateTime::currentDateTime());
    ui->dtEndTime->setDateTime(QDateTime::currentDateTime());

    buildingsId = LaborEyeDatabase::getLaboreyeDatabase()->selectBuidingId();
    for(int i = 0; i < buildingsId.size(); ++i)
        ui->cmbBuilding->addItem(buildingsId[i]);

    ui->cmbUnit->clear();
    unitsId = LaborEyeDatabase::getLaboreyeDatabase()->selectUnitId(buildingsId[0]);
    for(int i = 0; i < unitsId.size(); ++i)
        ui->cmbUnit->addItem(unitsId[i]);

    ui->tblHouse->setColumnCount(houseColNum);
    ui->tblHouse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblHouse->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblHouse->verticalHeader()->setHidden(true);                        //取消默认行号
    ui->tblHouse->horizontalHeader()->setHidden(true);                      //取消默认列号
    ui->tblHouse->setSelectionMode(QAbstractItemView::SingleSelection);     //取消多选

    ui->tblRecord->verticalHeader()->setHidden(true);                       //取消默认行号
    ui->tblRecord->setSelectionBehavior(QAbstractItemView::SelectRows);                         //设置选择时选择一行
    ui->tblRecord->horizontalHeader()->setStretchLastSection(true);                             //设置不留空
    ui->tblRecord->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);   //设置列宽
    ui->tblRecord->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);                //设置表头伸缩格式
    ui->tblRecord->setSelectionMode(QAbstractItemView::SingleSelection);                        //取消多选
}

void HouseView::on_cmbBuilding_currentIndexChanged(const QString &arg1)
{
    ui->cmbUnit->clear();
    QList<QString> unitsId = LaborEyeDatabase::getLaboreyeDatabase()->selectUnitId(arg1);
    for(int i = 0; i < unitsId.size(); ++i)
        ui->cmbUnit->addItem(unitsId[i]);
}

void HouseView::on_lblReflash_clicked()
{
    ui->tblHouse->clear();
    ui->tblRecord->clear();

    ui->ledtName->clear();
    ui->ledtRole->clear();
    ui->ledtIdCard->clear();
    ui->ledtSimilar->clear();

    ui->lblCapture->setText("抓拍图");
    ui->lblAvatar->setText("证件照");
    ui->lblFace->setText("人脸子图");

    QString buildingId = ui->cmbBuilding->currentText();
    QString unitId = ui->cmbUnit->currentText();
    QDateTime startDateTime = ui->dtStartTime->dateTime();
    QDateTime endDateTime = ui->dtEndTime->dateTime();

    int houseNum = LaborEyeDatabase::getLaboreyeDatabase()->cntHouseNum(buildingId, unitId);
    int rowNum = houseNum / houseColNum + (houseNum % houseColNum ? 1 : 0);
    housesId = LaborEyeDatabase::getLaboreyeDatabase()->selectHouseId(buildingId, unitId);

    houseRowNum = houseRowNum < rowNum ? rowNum : houseRowNum;
    ui->tblHouse->setRowCount(houseRowNum);

    QList<HouseInfo> houseInfoList = LaborEyeDatabase::getLaboreyeDatabase()
            ->selectHouseInfo(buildingId, unitId,
                              startDateTime, endDateTime);

    for(int i = houseRowNum-1, houseId = 0; i >= 0; --i) {
        for(int j = 0; j < houseColNum; ++j) {
            QString itemText = houseId < housesId.size() ? housesId[houseId++] : "";
            QTableWidgetItem *item = new QTableWidgetItem(itemText);
            //设置内容
            item->setTextAlignment(Qt::AlignCenter);
            //设置只读
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tblHouse->setItem(i, j, item);

            item->setForeground(QBrush(QColor(128, 128, 128)));

            if(itemText != "") {
                for(int k = 0 ; k < houseInfoList.size(); ++k) {
                    if(houseInfoList[k].getHouse() == itemText)
                        item->setForeground(QBrush(QColor(0, 128, 0)));
                }
            }
        }
    }
}

void HouseView::on_tblHouse_itemDoubleClicked(QTableWidgetItem *item)
{

    ui->ledtName->clear();
    ui->ledtRole->clear();
    ui->ledtIdCard->clear();
    ui->ledtSimilar->clear();

    ui->lblCapture->setText("抓拍图");
    ui->lblAvatar->setText("证件照");
    ui->lblFace->setText("人脸子图");

    QDateTime startDateTime = ui->dtStartTime->dateTime();
    QDateTime endDateTime = ui->dtEndTime->dateTime();
    QString buildingId = ui->cmbBuilding->currentText();
    QString unitId = ui->cmbUnit->currentText();
    QString houseId = item->text();

    applicantRecordList = LaborEyeDatabase::getLaboreyeDatabase()
            ->selectApplicantRecords(buildingId, unitId, houseId,
                                     startDateTime, endDateTime);

    ui->tblRecord->clear();
    ui->tblRecord->setRowCount(applicantRecordList.size());
    QTableWidgetItem *itemVal[3];
    for(int i = 0; i < applicantRecordList.size(); i++) {
        for(int j = 0; j < 3; ++j) {
            switch(j) {
            case 0: itemVal[j] =new QTableWidgetItem(applicantRecordList[i].getDateTime()
                                                     .toString("yyyy-MM-dd ddd hh:mm"));
                break;
            case 1: itemVal[j] = new QTableWidgetItem(applicantRecordList[i].getApplicant());
                break;
            case 2: itemVal[j] = new QTableWidgetItem(applicantRecordList[i].getAvatarId());
                break;
            }

            //设置只读
            itemVal[j]->setFlags(itemVal[j]->flags() ^ Qt::ItemIsEditable);
            //设置对齐方式
            itemVal[j]->setTextAlignment(Qt::AlignCenter);
            //设置单元格内容
            ui->tblRecord->setItem(i, j, itemVal[j]);
        }
    }
}



void HouseView::on_tblRecord_cellDoubleClicked(int row)
{
    QString name = applicantRecordList[row].getApplicant();
    QString familyRole = applicantRecordList[row].getFamilyRole();
    QString sfzNo = applicantRecordList[row].getAvatarId();
    int similar = applicantRecordList[row].getSimilar();

    ui->ledtName->setText(name);
    ui->ledtRole->setText(familyRole);
    ui->ledtIdCard->setText(sfzNo);
    ui->ledtSimilar->setText(QString::number(similar));

    ui->lblCapture->clear();
    ui->lblAvatar->clear();
    ui->lblFace->clear();
    QImage captureImage(Config::getCfg()->getCapturePath()+QString::number(applicantRecordList[row].getCaptureId()));
    QImage avatarImage(Config::getCfg()->getAvatarPath()+applicantRecordList[row].getAvatarId());
    QImage faceImage(Config::getCfg()->getFacePath()+QString::number(applicantRecordList[row].getCaptureId()));
    ui->lblCapture->setPixmap(QPixmap::fromImage(captureImage).scaled(ui->lblCapture->size(),
                                                                      Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lblAvatar->setPixmap(QPixmap::fromImage(avatarImage).scaled(ui->lblAvatar->size(),
                                                                    Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lblFace->setPixmap(QPixmap::fromImage(faceImage).scaled(ui->lblFace->size(),
                                                                Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void HouseView::on_lblOutput_clicked()
{
    QDateTime startDateTime = ui->dtStartTime->dateTime();
    QDateTime endDateTime = ui->dtEndTime->dateTime();
    QString detPath = QFileDialog::getSaveFileName(this, tr("Exceld导出路径"),  "", tr("*.xlsx;;"));

    LaborEyeExcel *laborEyeExcel = LaborEyeExcel::getLaborEyeExcel();
    laborEyeExcel->setDetPath(detPath);
    laborEyeExcel->setExportData(LaborEyeDatabase::getLaboreyeDatabase()
                                                     ->selectExcelRecord(startDateTime,
                                                                         endDateTime));

    QThread *thread = new QThread();
    laborEyeExcel->moveToThread(thread);
    qDebug() << "222222222";
    connect(thread, SIGNAL(started()), laborEyeExcel, SLOT(startTrans()), Qt::QueuedConnection);
    thread->start();
}
