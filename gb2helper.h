#ifndef QTGB2HELPER_H
#define QTGB2HELPER_H

#include <QPointF>
#include <QString>

class GB2Helper
{
public:
    static QPointF pointFromString(const QString &pointString);
};

#endif // QTGB2HELPER_H
