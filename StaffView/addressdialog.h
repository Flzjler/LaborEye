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

public slots:
    void showAddressDialog();

private slots:
    void on_btnConcel_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::AddressDialog *ui;
    static QList<AddressInfo> addressInfoList;
    QTreeWidgetItem* addTreeRoot(QString name, int colNum);
    QTreeWidgetItem* addTreeChild(QTreeWidgetItem *parent, QString name, int colNum);
    void setTreeAddressUI(QTreeWidgetItem *parent, AddressInfo addressInfo, int cur, int nowIdx);
};

#endif // ADDRESSDIALOG_H
