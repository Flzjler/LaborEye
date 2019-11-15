#include "previewview.h"
#include "ui_previewview.h"

PreviewView::PreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewView)
{
    ui->setupUi(this);
}

PreviewView::~PreviewView()
{
    delete ui;
}
