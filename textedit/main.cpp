#include "textedit.h"
 #include <QApplication>
#include <QTextCodec>

 int main( int argc, char ** argv )
 {
     Q_INIT_RESOURCE(textedit);

     QApplication a( argc, argv );
     QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
     QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
     TextEdit mw;
     mw.resize( 700, 500 );
     mw.show();
     return a.exec();
 }
