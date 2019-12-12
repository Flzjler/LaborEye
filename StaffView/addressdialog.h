#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include <algorithm>
#include <QTreeWidgetItem>

#include "LaborEyeDatabase/laboreyedatabase.h"
#include "Entity/addressinfo.h"

namespace Ui {
class AddressDialog;
}

class AddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressDialog(QWidget *parent = nullptr);
    ~AddressDialog();

signals:
    void _returnAddressInfo(AddressInfo);

public slots:
    void showAddressDialog();

private slots:
    void on_treeAddress_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::AddressDialog *ui;
    static QList<AddressInfo> addressInfoList;
    QTreeWidgetItem* addTreeRoot(QString name, int colNum);
    QTreeWidgetItem* addTreeChild(QTreeWidgetItem *parent, QString name, int colNum);
    void setTreeAddressUI(QTreeWidgetItem *parent, AddressInfo addressInfo, int cur, int nowIdx);
};

#endif // ADDRESSDIALOG_H
