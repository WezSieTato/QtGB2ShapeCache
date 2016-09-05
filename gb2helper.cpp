#include "gb2helper.h"

#include <QStringList>
#include <QList>

QPointF GB2Helper::pointFromString(const QString &pointString)
{
    QString theString(pointString);
    theString.remove('{');
    theString.remove('}');
    QStringList list = theString.split(",");
    QPointF point(list.at(0).toFloat(), list.at(1). toFloat());
    return point;
}
