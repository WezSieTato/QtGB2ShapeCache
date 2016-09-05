#include <QString>
#include <QtTest>

#include <gb2helper.h>

class Gb2SHelperTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testpointFromString_data();
    void testpointFromString();

};

void Gb2SHelperTests::testpointFromString_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QPointF>("result");

    QTest::newRow("Zero point") << "{0,0}" << QPointF(0, 0);
    QTest::newRow("Point of integer") << "{2,3}" << QPointF(2, 3);
    QTest::newRow("Point of floats") << "{2.3,3.2}" << QPointF(2.3f, 3.2f);
}

void Gb2SHelperTests::testpointFromString()
{
    QFETCH(QString, string);
    QFETCH(QPointF, result);

    QPointF point = GB2Helper::pointFromString(string);

    QCOMPARE(point, result);
}

QTEST_APPLESS_MAIN(Gb2SHelperTests)

#include "tst_gb2shelpertests.moc"
