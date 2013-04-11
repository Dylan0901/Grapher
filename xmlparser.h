#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QList>
#include "types3d.h"

class QXmlStreamReader;

class XMLParser
{
public:
    Sector readWorld(const char*);
private:
    Triangle parseTriangle(QXmlStreamReader& xml);
};

#endif // XMLPARSER_H
