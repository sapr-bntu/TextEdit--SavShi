#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QtGui>
#include "../textedit.h"
//#include ""

class TesttextEdit : public QObject
{
    Q_OBJECT

public:
    TesttextEdit();
    TextEdit *txt;
    QApplication *a;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
  //  void testCase2();
    //void testCase3();
    //void testCase4();
    //void testCase5();
    //void testCase6();
    //void testCase7();
    //void testCase8();
   // void testCase9();
    //void testCase10();
};

TesttextEdit::TesttextEdit()
{
}

void TesttextEdit::initTestCase()
{
}

void TesttextEdit::cleanupTestCase()
{
}

void TesttextEdit::testCase1()
{

    TextEdit txt;
//   bool p;
//   p=txt->FileNew();
    QCOMPARE(true,txt.fileNew());

}
//void TesttextEdit::testCase2()
//{
//    txt->actionEditForTest->activate(QAction::Trigger);
//    QTextEdit mytxt;
//    QCOMPARE(mytxt.toPlainText(), QString("Pavlova Viktoria is student of BNTU"));
//   // QVERIFY(mytxt.i));
//}
//void TesttextEdit::testCase3()
//{

//}
//void TesttextEdit::testCase4()
//{
//    bool p;
//    p=txt->textBold();
//    QCOMPARE(true,txt->textBold());
//}
//void TesttextEdit::testCase5()
//{
//   TextEdit txt;
//   bool success;
//   try
//   {
//    txt.textSize("-12");
//    success=false;}

//   catch(char* a)
//   {
//       success=true;
//   }
//   QCOMPARE(success,true);
//}
//void TesttextEdit::testCase6()
//{
//    TextEdit txt;
//    QString str="";
//    bool result;
//    try
//    {
//        txt.ForSaveWord(str);
//        result=false;
//    }
//    catch(char* a)
//    {
//        result=true;
//    }
//    QCOMPARE(result,true);
//}
//void TesttextEdit::testCase7()
//{
//    int index=0;
//    bool success;
//    try
//    {
//        txt->textStyle(index);;
//        success=false;
//    }
//    catch(char* a)
//    {
//        success=true;
//    }
//    QCOMPARE(success,true);
//}
//void TesttextEdit::testCase8()
//{
//    qDebug()<<"You have to open G:/Lab1_tests/textedit/1.jpg";
//    bool result;
//    try
//    {
//        txt->fileOpen("G:/Lab1_tests/textedit/1.jpg");
//        result=false;
//    }
//    catch(char* a)
//    {
//        result=true;
//    }
//    QCOMPARE(result,true);
//}
//void TesttextEdit::testCase9()
//{
//    qDebug()<<"You have to open unexisting document";
//    bool result;
//    try
//    {
//        txt->fileOpen("G:/Lab1_tests/textedit/ha.doc");
//        result=false;
//    }
//    catch(char* a)
//    {
//        result=true;
//    }
//    QCOMPARE(result,true);
//}
//void TesttextEdit::testCase10()
//{
//   QVERIFY(true);
//}
QTEST_APPLESS_MAIN(TesttextEdit);

#include "testtextedit.moc"
