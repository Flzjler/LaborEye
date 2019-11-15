#ifndef STAFFVIEW_H
#define STAFFVIEW_H

#include <QWidget>

namespace Ui {
class StaffView;
}

class StaffView : public QWidget
{
    Q_OBJECT

public:
    explicit StaffView(QWidget *parent = nullptr);
    ~StaffView();

private:
    Ui::StaffView *ui;
};

#endif // STAFFVIEW_H
