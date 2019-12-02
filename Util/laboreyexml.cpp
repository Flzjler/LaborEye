#include "laboreyexml.h"


QString LaborEyeXML::filePath = "./uploadXML.xml";

LaborEyeXML::LaborEyeXML()
{

}

QString LaborEyeXML::getXMLPath()
{
    return filePath;
}

void LaborEyeXML::setUploadXML(QString strName)
{
    qDebug() << "enter setUploadStrangerXML: " << strName;
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly|QFile::Truncate)) {
        qDebug() << "cannot create strangerXML File";
        return;
    }
    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root=doc.createElement("FaceAppendData");
    root.setAttribute("xmlns", "http://www.hikvision.com/ver20/XMLSchema");
    root.setAttribute("version", "2.0");
    doc.appendChild(root);
    //添加时间节点
    QDomElement bornTime = doc.createElement("bornTime");
    root.appendChild(bornTime);

    //添加姓名节点
    QDomElement name = doc.createElement("name");
    QDomText text = doc.createTextNode(strName);
    name.appendChild(text);
    root.appendChild(name);

    //添加性别节点
    QDomElement sex = doc.createElement("sex");
    root.appendChild(sex);

    //添加省份、城市节点
    QDomElement province = doc.createElement("province");
    root.appendChild(province);

    QDomElement city = doc.createElement("city");
    root.appendChild(city);

    //添加证件类型、证件号节点
    QDomElement certificateType = doc.createElement("certificateType");
    root.appendChild(certificateType);
    QDomElement certificateNumber = doc.createElement("certificateNumber");
    root.appendChild(certificateNumber);

    //添加个人信息扩展列表节点
    QDomElement PersonInfoExtendList = doc.createElement("PersonInfoExtendList");
    root.appendChild(PersonInfoExtendList);

    /****************该模块可重复多次************/
    for(int i = 0; i < 2; i++) {
        QDomElement PersonInfoExtend = doc.createElement("PersonInfoExtend");//添加个人信息扩展子节点
        PersonInfoExtendList.appendChild(PersonInfoExtend);
        QDomElement id = doc.createElement("id");//添加id子节点
        text = doc.createTextNode(QString::number(i+1));
        id.appendChild(text);
        PersonInfoExtend.appendChild(id);
        QDomElement enable = doc.createElement("enable");//添加enable子节点
        text = doc.createTextNode("false");//enable赋值为false
        enable.appendChild(text);
        PersonInfoExtend.appendChild(enable);
        name = doc.createElement("name");//添加name子节点
        PersonInfoExtend.appendChild(name);
        QDomElement value = doc.createElement("value");//添加value子节点
        PersonInfoExtend.appendChild(value);
    }
    /***************************************/

    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
