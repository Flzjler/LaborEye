#ifndef EDITSTAFFDIALOG_H
#define EDITSTAFFDIALOG_H

#include <QDialog>

namespace Ui {
class EditStaffDialog;
}

class EditStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStaffDialog(QWidget *parent = nullptr);
    ~EditStaffDialog();

public slots:
    void showEditStaffDialog();

private:
    Ui::EditStaffDialog *ui;
};

#endif // EDITSTAFFDIALOG_H
