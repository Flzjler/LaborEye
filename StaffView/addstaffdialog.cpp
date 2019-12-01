#include "addstaffdialog.h"
#include "ui_addstaffdialog.h"

AddStaffDialog::AddStaffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffDialog)
{
    ui->setupUi(this);
}

AddStaffDialog::~AddStaffDialog()
{
    delete ui;
}

void AddStaffDialog::showAddStaffDialog()
{
    this->show();
}
