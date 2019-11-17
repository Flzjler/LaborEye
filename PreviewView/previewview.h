#ifndef PREVIEWVIEW_H
#define PREVIEWVIEW_H

#include <QWidget>

#include "Hikvision/hikvision.h"

namespace Ui {
class PreviewView;
}

class PreviewView : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewView(QWidget *parent = nullptr);
    ~PreviewView();

private:
    Ui::PreviewView *ui;
};

#endif // PREVIEWVIEW_H
