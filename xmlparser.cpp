#include "xmlparser.h"
#include "types3d.h"
#include <vector>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <iostream>

Sector XMLParser::readWorld(const char* file_name) {
    //QFile* file = new QFile(":/xml/world.xml");
    QFile* file = new QFile(file_name);
    Sector sector;
    std::vector<Triangle> walls;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::critical(this,
        //                      "QXSRExample::parseXML",
        //                      "Couldn't open example.xml",
        //                      QMessageBox::Ok);
        return sector;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "sectors") {
                continue;
            }
            if(xml.name() == "sector") {
                continue;
            }
            if(xml.name() == "item") {
                walls.push_back(this->parseTriangle(xml));
            }
        }
    }
    if(xml.hasError()) {
        //QMessageBox::critical(this,
        //                      "QXSRExample::parseXML",
        //                      xml.errorString(),
        //                      QMessageBox::Ok);
    }
    xml.clear();
    sector.numTriangles = 1;
    sector.triangles = walls;
    return sector;
}

Triangle XMLParser::parseTriangle(QXmlStreamReader& xml) {
    Triangle item;
    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "item") {
        return item;
    }
    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("type")) {
        item.setType(attributes.value("type").toString().toStdString().c_str());
    }
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "item")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if(xml.name() == "point") {
                QXmlStreamAttributes attr = xml.attributes();
                float x = attr.value("x").toString().toFloat();
                float y = attr.value("y").toString().toFloat();
                float z = attr.value("z").toString().toFloat();
                float u = attr.value("u").toString().toFloat();
                float v = attr.value("v").toString().toFloat();
                item.addVertex(x, y, z, u, v);
            }
        }
        xml.readNext();
    }
    return item;
}
