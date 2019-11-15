#ifndef HOUSEVIEW_H
#define HOUSEVIEW_H

#include <QWidget>

namespace Ui {
class HouseView;
}

class HouseView : public QWidget
{
    Q_OBJECT

public:
    explicit HouseView(QWidget *parent = nullptr);
    ~HouseView();

private:
    Ui::HouseView *ui;
};

#endif // HOUSEVIEW_H
