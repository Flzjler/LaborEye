#ifndef HOUSEVIEW_H
#define HOUSEVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <QTableWidgetItem>
#include "Util/laboreyeexcel.h"
#include "LaborEyeDatabase/laboreyedatabase.h"

namespace Ui {
class HouseView;
}

class HouseView : public QWidget
{
    Q_OBJECT

public:
    explicit HouseView(QWidget *parent = nullptr);
    ~HouseView();

private slots:
    void on_cmbBuilding_currentIndexChanged(const QString &arg1);

    void on_lblReflash_clicked();

    void on_tblHouse_itemDoubleClicked(QTableWidgetItem *item);



    void on_tblRecord_cellDoubleClicked(int row);

    void on_lblOutput_clicked();

private:
    Ui::HouseView *ui;
    static int houseRowNum;
    static int houseColNum;

    static QList<QString> buildingsId;
    static QList<QString> unitsId;
    static QList<QString> housesId;
    static QList<ApplicantRecordInfo> applicantRecordList;

    void initUI();
};

#endif // HOUSEVIEW_H
