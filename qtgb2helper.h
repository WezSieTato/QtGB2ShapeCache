#ifndef QTGB2HELPER_H
#define QTGB2HELPER_H

#include <QPointF>
#include <QString>

class QtGB2Helper
{
public:
    QtGB2Helper();

    static QPointF pointFromString(const QString &pointString);
};

#endif // QTGB2HELPER_H
