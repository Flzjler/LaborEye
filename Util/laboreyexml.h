#ifndef LABOREYEXML_H
#define LABOREYEXML_H

#include <QString>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QFile>
#include <QDebug>

class LaborEyeXML
{
public:
    LaborEyeXML();

    //设置上传超脑人脸库的XML信息
    static void setUploadXML(QString strName);

    static QString getXMLPath();

private:
    static QString filePath;

};

#endif // LABOREYEXML_H
