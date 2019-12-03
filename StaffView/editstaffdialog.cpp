#include "editstaffdialog.h"
#include "ui_editstaffdialog.h"

EditStaffDialog::EditStaffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStaffDialog)
{
    ui->setupUi(this);
}

EditStaffDialog::~EditStaffDialog()
{
    delete ui;
}

void EditStaffDialog::showEditStaffDialog()
{
    this->show();
}
