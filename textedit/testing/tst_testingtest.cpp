#include <QtCore/QString>
#include <QtTest/QtTest>

#include <QtGui>
#include "../textedit.h"

class TestingTest : public QObject
{
    Q_OBJECT

public:

    TextEdit *txt;
   QWidget *parent;
    QApplication *a;
    TestingTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
};

TestingTest::TestingTest()
{
}

void TestingTest::initTestCase()
{
}

void TestingTest::cleanupTestCase()
{
}

void TestingTest::testCase1()
{
//QApplication a();
//    TextEdit txt;
//      bool success;
//      try
//      {
//       txt.textSize("-12");
//       success=false;}

//      catch(char* a)
//      {
//          success=true;
//      }
//      QCOMPARE(success,true);

}
void TestingTest::testCase2()
{
    QLineEdit lineEdit;

         QTest::keyClicks(&lineEdit, "hello world");

         QCOMPARE(lineEdit.text(), QString("hello world"));

}
QTEST_APPLESS_MAIN(TestingTest);

#include "tst_testingtest.moc"
