#include "addressdialog.h"
#include "ui_addressdialog.h"

QList<AddressInfo> AddressDialog::addressInfoList;

AddressDialog::AddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressDialog)
{
    ui->setupUi(this);
}

AddressDialog::~AddressDialog()
{
    delete ui;
}

QTreeWidgetItem* AddressDialog::addTreeRoot(QString name, int colNum) {
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeAddress);
    treeItem->setText(colNum, name);
    return treeItem;
}

QTreeWidgetItem* AddressDialog::addTreeChild(QTreeWidgetItem *parent, QString name, int colNum) {
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(colNum, name);
    parent->addChild(treeItem);
    return treeItem;
}


void AddressDialog::setTreeAddressUI(QTreeWidgetItem *parent, AddressInfo addressInfo, int cur, int nowIdx)
{
    for(int i = nowIdx; i < addressInfoList.size(); ++i) {
        if(cur == 0) { //小区名字
            if(i && addressInfoList[i].getCommunity() == addressInfoList[i-1].getCommunity()) continue;
            QTreeWidgetItem *p = addTreeRoot(addressInfoList[i].getCommunity(), 0);
            setTreeAddressUI(p, addressInfoList[i], cur+1, i);
        } else if(cur == 1)  { //幢
            if(addressInfoList[i].getCommunity() != addressInfo.getCommunity()) return;
            if(i && addressInfoList[i].getBuilding() == addressInfoList[i-1].getBuilding()) continue;
            QTreeWidgetItem *p = addTreeChild(parent, addressInfoList[i].getBuilding(), 1);
            setTreeAddressUI(p, addressInfoList[i], cur+1, i);
        } else if(cur == 2) { //单元
            if(addressInfoList[i].getBuilding() != addressInfo.getBuilding() ||
                    addressInfoList[i].getCommunity() != addressInfo.getCommunity())
                return;
            if(i && addressInfoList[i].getUnit() == addressInfoList[i-1].getUnit()) continue;
            QTreeWidgetItem *p = addTreeChild(parent, addressInfoList[i].getUnit(), 2);
            setTreeAddressUI(p, addressInfoList[i], cur+1, i);
        } else if(cur == 3) { //室
            if(addressInfoList[i].getUnit() != addressInfo.getUnit() ||
                    addressInfoList[i].getBuilding() != addressInfo.getBuilding() ||
                    addressInfoList[i].getCommunity() != addressInfo.getCommunity())
                return;
            if(i && addressInfoList[i].getHouse() == addressInfoList[i-1].getHouse()) continue;
            addTreeChild(parent, addressInfoList[i].getHouse(), 3);
        }
    }
}

void AddressDialog::showAddressDialog()
{
    this->show();
    ui->treeAddress->header()->setSectionResizeMode(QHeaderView::Stretch);
    addressInfoList = LaborEyeDatabase::getLaboreyeDatabase()->selectAddressInfo();
    std::sort(addressInfoList.begin(), addressInfoList.end());
    setTreeAddressUI(nullptr, addressInfoList[0], 0, 0);
    for(int i = 0; i < addressInfoList.size(); ++i)
        qDebug() << addressInfoList[i].getCommunity() << " "
                 << addressInfoList[i].getBuilding() << " "
                 << addressInfoList[i].getUnit() << " "
                 << addressInfoList[i].getHouse();

}

void AddressDialog::on_btnConfirm_clicked()
{

}

void AddressDialog::on_btnConcel_clicked()
{
    this->close();
}
