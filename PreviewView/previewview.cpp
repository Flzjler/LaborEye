#include "previewview.h"
#include "ui_previewview.h"

PreviewView::PreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewView)
{
    ui->setupUi(this);
    QList<HWND> hwndList;
    hwndList.append((HWND)ui->lblChannel1->winId());
    hwndList.append((HWND)ui->lblChannel2->winId());
    Hikvision::showPreviewVideo(hwndList);
}

PreviewView::~PreviewView()
{
    delete ui;

}
