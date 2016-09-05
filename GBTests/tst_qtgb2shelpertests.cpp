#include <QString>
#include <QtTest>

#include <qtgb2helper.h>

class QtGb2SHelperTests : public QObject
{
    Q_OBJECT

public:
    QtGb2SHelperTests();

private Q_SLOTS:
    void testpointFromString_data();
    void testpointFromString();

};

QtGb2SHelperTests::QtGb2SHelperTests()
{

}

void QtGb2SHelperTests::testpointFromString_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QPointF>("result");

    QTest::newRow("Zero point") << "{0,0}" << QPointF(0, 0);
    QTest::newRow("Point of integer") << "{2,3}" << QPointF(2, 3);
    QTest::newRow("Point of floats") << "{2.3,3.2}" << QPointF(2.3f, 3.2f);
}

void QtGb2SHelperTests::testpointFromString()
{
    QFETCH(QString, string);
    QFETCH(QPointF, result);

    QPointF point = QtGB2Helper::pointFromString(string);

    QCOMPARE(point, result);
}

QTEST_APPLESS_MAIN(QtGb2SHelperTests)

#include "tst_qtgb2shelpertests.moc"
