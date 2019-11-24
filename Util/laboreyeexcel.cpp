#include "laboreyeexcel.h"

LaborEyeExcel* LaborEyeExcel::laborEyeExcel = nullptr;

LaborEyeExcel::LaborEyeExcel()
{

}

void LaborEyeExcel::setExportData(QList<QList<QVariant>> _exportData)
{
    //设置导出数据
    exportData = _exportData;
}

void LaborEyeExcel::setDetPath(QString _detPath)
{
    detPath = _detPath;
}

#include <QDebug>
void LaborEyeExcel::startTrans()
{
    //写入Excel
//    writeSheet();
    qDebug() << "1111";
}

//void LaborEyeExcel::writeSheet()
//{
//    //多线程必须初始化
//    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

//    QAxObject excel("Excel.Application");
//    QAxObject *work_books = excel.querySubObject("WorkBooks");

//    work_books->dynamicCall("Add");
//    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
//    QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);  //Sheets(int)也可换用Worksheets(int)

//    if(exportData.size() <= 0)
//        return;
//    if(nullptr == work_sheet || work_sheet->isNull())
//        return;
//    int row = exportData.size();
//    int col = exportData.at(0).size();

//    for (int i = 1; i <= row; ++i)
//    {
//        for (int j = 1; j <= col; ++j)
//        {
//            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
//            cell->setProperty("Value", exportData[i-1][j-1]);
//        }
//    }

//    work_book->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(detPath));  //另存为另一个文件
//    excel.dynamicCall("Quit(void)", false);  //退出
//}
