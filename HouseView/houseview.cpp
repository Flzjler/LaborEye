#include "houseview.h"
#include "ui_houseview.h"

HouseView::HouseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HouseView)
{
    ui->setupUi(this);
}

HouseView::~HouseView()
{
    delete ui;
}
