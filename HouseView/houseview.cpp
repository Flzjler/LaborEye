#include "houseview.h"
#include "ui_houseview.h"

int HouseView::houseRowNum = 15;
int HouseView::houseColNum = 5;

QList<QString> HouseView::buildingsId;
QList<QString> HouseView::unitsId;
QList<QString> HouseView::housesId;

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
