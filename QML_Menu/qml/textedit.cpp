 #include "textedit.h"
 //#include <QAxObject>
 #include <QAction>
 #include <QApplication>
 #include <QClipboard>
 #include <QColorDialog>
 #include <QComboBox>
 #include <QFontComboBox>
 #include <QFile>
 #include <QFileDialog>
 #include <QFileInfo>
 #include <QFontDatabase>
 #include <QMenu>
 #include <QMenuBar>
 #include <QPrintDialog>
 #include <QPrinter>
 #include <QTextCodec>
 #include <QTextEdit>
 #include <QToolBar>
 #include <QTextCursor>
 #include <QTextDocumentWriter>
 #include <QTextList>
 #include <QtDebug>
 #include <QCloseEvent>
 #include <QMessageBox>
 #include <QPrintPreviewDialog>
 //#include <ActiveQt/qaxobject.h>
 //#include <ActiveQt/qaxbase.h>
 #include <QProcess>

 #ifdef Q_WS_MAC
 const QString rsrcPath = ":/images/mac";
 #else
 const QString rsrcPath = ":/images/win";
 #endif

 TextEdit::TextEdit(QWidget *parent)
     : QMainWindow(parent)
 {
     setToolButtonStyle(Qt::ToolButtonFollowStyle);
     setupFileActions();
     setupEditActions();
     setupTextActions();

     {
         QMenu *helpMenu = new QMenu(tr("Help"), this);
         menuBar()->addMenu(helpMenu);
         helpMenu->addAction(tr("About"), this, SLOT(about()));
         helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
     }

     textEdit = new QTextEdit(this);
     connect(textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
             this, SLOT(currentCharFormatChanged(QTextCharFormat)));
     connect(textEdit, SIGNAL(cursorPositionChanged()),
             this, SLOT(cursorPositionChanged()));

     setCentralWidget(textEdit);
     textEdit->setFocus();
     setCurrentFileName(QString());

     fontChanged(textEdit->font());
     colorChanged(textEdit->textColor());
     alignmentChanged(textEdit->alignment());

     connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
             actionSave, SLOT(setEnabled(bool)));
     connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
             this, SLOT(setWindowModified(bool)));
     connect(textEdit->document(), SIGNAL(undoAvailable(bool)),
             actionUndo, SLOT(setEnabled(bool)));
     connect(textEdit->document(), SIGNAL(redoAvailable(bool)),
             actionRedo, SLOT(setEnabled(bool)));

     setWindowModified(textEdit->document()->isModified());
     actionSave->setEnabled(textEdit->document()->isModified());
     actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
     actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

     connect(actionUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
     connect(actionRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));

     actionCut->setEnabled(false);
     actionCopy->setEnabled(false);

     connect(actionCut, SIGNAL(triggered()), textEdit, SLOT(cut()));
     connect(actionCopy, SIGNAL(triggered()), textEdit, SLOT(copy()));
     connect(actionPaste, SIGNAL(triggered()), textEdit, SLOT(paste()));

     connect(textEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
     connect(textEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

 #ifndef QT_NO_CLIPBOARD
     connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
 #endif

     QString initialFile = ":/example.html";
     const QStringList args = QCoreApplication::arguments();
     if (args.count() == 2)
         initialFile = args.at(1);

     //if (!load(initialFile))
      //   fileNew();
 }

 void TextEdit::closeEvent(QCloseEvent *e)
 {
     if (maybeSave())
         e->accept();
     else
         e->ignore();
 }

 void TextEdit::setupFileActions()
 {
     QToolBar *tb = new QToolBar(this);
     tb->setWindowTitle(tr("File Actions"));
     addToolBar(tb);

     QMenu *menu = new QMenu(tr("&File"), this);
     menuBar()->addMenu(menu);

     QAction *a;

     QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
     a = new QAction( newIcon, tr("&New"), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::New);
     connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
     tb->addAction(a);
     menu->addAction(a);

     a = new QAction(QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png")),
                     tr("&Open..."), this);
     a->setShortcut(QKeySequence::Open);
     connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
     tb->addAction(a);
     menu->addAction(a);

     menu->addSeparator();

     actionSave = a = new QAction(QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png")),
                                  tr("&Save"), this);
     a->setShortcut(QKeySequence::Save);
     connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
     a->setEnabled(false);
     tb->addAction(a);
     menu->addAction(a);

     a = new QAction(tr("Save &As..."), this);
     a->setPriority(QAction::LowPriority);
     connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
     menu->addAction(a);
     menu->addSeparator();

 #ifndef QT_NO_PRINTER
     a = new QAction(QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png")),
                     tr("&Print..."), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::Print);
     connect(a, SIGNAL(triggered()), this, SLOT(filePrint()));
     tb->addAction(a);
     menu->addAction(a);

     a = new QAction(QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png")),
                     tr("Print Preview..."), this);
     connect(a, SIGNAL(triggered()), this, SLOT(filePrintPreview()));
     menu->addAction(a);

     a = new QAction(QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png")),
     tr("&Export PDF..."), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(Qt::CTRL + Qt::Key_D);
     connect(a, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
     tb->addAction(a);
     menu->addAction(a);
     menu->addSeparator();

     actionopenWord = a = new QAction(QIcon::fromTheme("OpenWord", QIcon(rsrcPath + "/word.ico")), tr("OpenWord"), this);
     connect(a, SIGNAL(triggered()), this, SLOT(OpenWord()));
     tb->addAction(a);
     /*actionSaveWord = a = new QAction(QIcon::fromTheme("SaveWord", QIcon(rsrcPath + "/word.ico")), tr("SaveWord"), this);
     connect(a, SIGNAL(triggered()), this, SLOT(SaveWord()));
     tb->addAction(a);*/

 #endif

     a = new QAction(tr("&Quit"), this);
     a->setShortcut(Qt::CTRL + Qt::Key_Q);
     connect(a, SIGNAL(triggered()), this, SLOT(close()));
     menu->addAction(a);
 }

 void TextEdit::setupEditActions()
 {
     QToolBar *tb = new QToolBar(this);
     tb->setWindowTitle(tr("Edit Actions"));
     addToolBar(tb);
     QMenu *menu = new QMenu(tr("&Edit"), this);
     menuBar()->addMenu(menu);

     QAction *a;
     a = actionUndo = new QAction(QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png")),
                                               tr("&Undo"), this);
     a->setShortcut(QKeySequence::Undo);
     tb->addAction(a);
     menu->addAction(a);
     a = actionRedo = new QAction(QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png")),
                                               tr("&Redo"), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::Redo);
     tb->addAction(a);
     menu->addAction(a);
     menu->addSeparator();
     a = actionCut = new QAction(QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png")),
                                              tr("Cu&t"), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::Cut);
     tb->addAction(a);
     menu->addAction(a);
     a = actionCopy = new QAction(QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png")),
                                  tr("&Copy"), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::Copy);
     tb->addAction(a);
     menu->addAction(a);
     a = actionPaste = new QAction(QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png")),
                                   tr("&Paste"), this);
     a->setPriority(QAction::LowPriority);
     a->setShortcut(QKeySequence::Paste);
     tb->addAction(a);
     menu->addAction(a);
 #ifndef QT_NO_CLIPBOARD
     if (const QMimeData *md = QApplication::clipboard()->mimeData())
         actionPaste->setEnabled(md->hasText());
 #endif
 }

 void TextEdit::setupTextActions()
 {
     QToolBar *tb = new QToolBar(this);
     tb->setWindowTitle(tr("Format Actions"));
     addToolBar(tb);

     QMenu *menu = new QMenu(tr("F&ormat"), this);
     menuBar()->addMenu(menu);

     actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                  tr("&Bold"), this);
     actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
     actionTextBold->setPriority(QAction::LowPriority);
         QFont bold;
     bold.setBold(true);
     actionTextBold->setFont(bold);
     connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
     tb->addAction(actionTextBold);
     menu->addAction(actionTextBold);
     actionTextBold->setCheckable(true);

     actionTextItalic = new QAction(QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png")),
                                    tr("&Italic"), this);
     actionTextItalic->setPriority(QAction::LowPriority);
     actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
     QFont italic;
     italic.setItalic(true);
     actionTextItalic->setFont(italic);
     connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
     tb->addAction(actionTextItalic);
     menu->addAction(actionTextItalic);
     actionTextItalic->setCheckable(true);

     actionTextUnderline = new QAction(QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png")),
                                       tr("&Underline"), this);
     actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
     actionTextUnderline->setPriority(QAction::LowPriority);
     QFont underline;
     underline.setUnderline(true);
     actionTextUnderline->setFont(underline);
     connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
     tb->addAction(actionTextUnderline);
     menu->addAction(actionTextUnderline);
     actionTextUnderline->setCheckable(true);

     menu->addSeparator();

     QActionGroup *grp = new QActionGroup(this);
     connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));


     if (QApplication::isLeftToRight()) {
         actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")),
                                       tr("&Left"), grp);
         actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
         actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
     } else {
         actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
         actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
         actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")), tr("&Left"), grp);
     }
     actionAlignJustify = new QAction(QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png")), tr("&Justify"), grp);

     actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
     actionAlignLeft->setCheckable(true);
     actionAlignLeft->setPriority(QAction::LowPriority);
     actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
     actionAlignCenter->setCheckable(true);
     actionAlignCenter->setPriority(QAction::LowPriority);
     actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
     actionAlignRight->setCheckable(true);
     actionAlignRight->setPriority(QAction::LowPriority);
     actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
     actionAlignJustify->setCheckable(true);
     actionAlignJustify->setPriority(QAction::LowPriority);

     tb->addActions(grp->actions());
     menu->addActions(grp->actions());

     menu->addSeparator();

     QPixmap pix(16, 16);
     pix.fill(Qt::black);
     actionTextColor = new QAction(pix, tr("&Color..."), this);
     connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
     tb->addAction(actionTextColor);
     menu->addAction(actionTextColor);

     tb = new QToolBar(this);
     tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
     tb->setWindowTitle(tr("Format Actions"));
     addToolBarBreak(Qt::TopToolBarArea);
     addToolBar(tb);

     comboStyle = new QComboBox(tb);
     tb->addWidget(comboStyle);
     comboStyle->addItem("Standard");
     comboStyle->addItem("Bullet List (Disc)");
     comboStyle->addItem("Bullet List (Circle)");
     comboStyle->addItem("Bullet List (Square)");
     comboStyle->addItem("Ordered List (Decimal)");
     comboStyle->addItem("Ordered List (Alpha lower)");
     comboStyle->addItem("Ordered List (Alpha upper)");
     comboStyle->addItem("Ordered List (Roman lower)");
     comboStyle->addItem("Ordered List (Roman upper)");
     connect(comboStyle, SIGNAL(activated(int)),
             this, SLOT(textStyle(int)));

     comboFont = new QFontComboBox(tb);
     tb->addWidget(comboFont);
     connect(comboFont, SIGNAL(activated(QString)),
             this, SLOT(textFamily(QString)));

     comboSize = new QComboBox(tb);
     comboSize->setObjectName("comboSize");
     tb->addWidget(comboSize);
     comboSize->setEditable(true);

     QFontDatabase db;
     foreach(int size, db.standardSizes())
         comboSize->addItem(QString::number(size));

     connect(comboSize, SIGNAL(activated(QString)),
             this, SLOT(textSize(QString)));
     comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                    .pointSize())));
 }

 QString TextEdit::load(const QString &f)
 {
     if (!QFile::exists(f))
         return false;
     QFile file(f);
     if (!file.open(QFile::ReadOnly))
         return false;

     QByteArray data = file.readAll();

     QTextCodec *codec = Qt::codecForHtml(data);
     QString str = codec->toUnicode(data);
     return str;
 }

 bool TextEdit::maybeSave()
 {
     if (!textEdit->document()->isModified())
         return true;
     if (fileName.startsWith(QLatin1String(":/")))
         return true;
     QMessageBox::StandardButton ret;
     ret = QMessageBox::warning(this, tr("Application"),
                                tr("The document has been modified.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel);
     if (ret == QMessageBox::Save)
         return fileSave();
     else if (ret == QMessageBox::Cancel)
         return false;
     return true;
 }

 void TextEdit::setCurrentFileName(const QString &fileName)
 {
     this->fileName = fileName;
     textEdit->document()->setModified(false);

     QString shownName;
     if (fileName.isEmpty())
         shownName = "untitled.txt";
     else
         shownName = QFileInfo(fileName).fileName();
 }

 void TextEdit::fileNew()
 {
     if (maybeSave()) {
         textEdit->clear();
         setCurrentFileName(QString());
     }
 }


 void TextEdit::openWord()
 {
     QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                               QString(), tr("*docx"));

     QString program = "7z.exe -y x "+fn;
     qDebug()<<program;
     QProcess *zipProcess  = new QProcess();
     zipProcess->start(program);
     zipProcess->waitForFinished();

     QString fn1 = "./word/document.xml";
     QFile file(fn1);
     file.open(QFile::ReadOnly);
     QTextStream in(&file);
     QChar ch;
     QString str;
     bool temp = false;
     bool word = false;
     bool wordread = false;
     bool prob = false;
     bool prob1 = false;
     int kol = 0;
     int Count = 0;
     while (!in.atEnd())
     {
         in >> ch;
         if(word == true)
         {
             if (ch == '<')
             {
                 wordread = false;
                 word = false;
                 temp = false;
             }
            if(wordread == true)
                 str+=ch;
            if (ch == '>')
                wordread = true;
         }

         if(word == false)
         {
             if ((ch == 't')&&(temp == true)&&(Count!=0))
                 word = true;
             Count = 0;
             if (ch == ':')
             {
                 Count++;
                 temp=true;
             }
             if(prob1 == true)
                if(ch == 'r')
                    if(kol==0)
                        kol++;
                     else
                     {
                         str+="\n";
                         kol=0;
                     }
             else
                 prob1 = false;
             if(prob == true)
                if(ch == 'P')
                 prob1 = true;
             else
                 prob = false;
             if (ch == 'p')
                 prob = true;
         }

     }
     textEdit->setPlainText(str);
 }


 void TextEdit::SaveWord()
 {
     QString fn = QFileDialog::getSaveFileName(this, tr("Save File..."),
                                               QString(), tr("All Files (*)"));


     QFile fille;
     fille.setFileName("./2/word/document.xml");
     fille.open(QIODevice::ReadOnly);
     QByteArray bytteet;
     bytteet = fille.readAll();
     fille.close();
     fille.remove();
     QString str;
     str=textEdit->toPlainText();
     fille.open(QIODevice::WriteOnly);
     QByteArray dddd= str.toLocal8Bit();
     bytteet = bytteet.replace("ZZZZZZ",dddd);
     fille.write(bytteet);
     fille.close();
//     qDebug()<<bytteet;

     QString program = "7z.exe a -tzip -y 1.docx ./2/*";
     qDebug()<<program;
     QProcess *zipProcess  = new QProcess();
     zipProcess->start(program);
     zipProcess->waitForFinished();


 }

 QString TextEdit::fileOpen()
 {
     QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                               QString(), tr("Files (*.txt );;All Files (*)"));
     QString text = "";
     if (!fn.isEmpty())
       text = load(fn);
     return text;
 }

 bool TextEdit::fileSave()
 {
     //if (fileName.isEmpty())
        // return fileSaveAs();

     QTextDocumentWriter writer(fileName);
     bool success = writer.write(textEdit->document());
     if (success)
         textEdit->document()->setModified(false);
     return success;
 }

 bool TextEdit::fileSaveAs(const QString &str)
 {
     textEdit->setText(str);
     QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                               QString(), tr("Text files (*.txt)"));
     if (fn.isEmpty())
         return false;
     if (! (fn.endsWith(".txt", Qt::CaseInsensitive)))
         fn += ".txt";
     setCurrentFileName(fn);
     return fileSave();
 }

 void TextEdit::filePrint(const QString &str)
 {
     textEdit->setText(str);
 #ifndef QT_NO_PRINTER
     QPrinter printer(QPrinter::HighResolution);
     QPrintDialog *dlg = new QPrintDialog(&printer, this);
     if (textEdit->textCursor().hasSelection())
         dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
     dlg->setWindowTitle(tr("Print Document"));
     if (dlg->exec() == QDialog::Accepted) {
         textEdit->print(&printer);
     }
     delete dlg;
 #endif
 }

 void TextEdit::filePrintPreview()
 {
 #ifndef QT_NO_PRINTER
     QPrinter printer(QPrinter::HighResolution);
     QPrintPreviewDialog preview(&printer, this);
     connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
     preview.exec();
 #endif
 }

 void TextEdit::printPreview(QPrinter *printer)
 {
 #ifdef QT_NO_PRINTER
     Q_UNUSED(printer);
 #else
     textEdit->print(printer);
 #endif
 }

 void TextEdit::filePrintPdf()
 {
 #ifndef QT_NO_PRINTER
     QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                     QString(), "*.pdf");
     if (!fileName.isEmpty()) {
         if (QFileInfo(fileName).suffix().isEmpty())
             fileName.append(".pdf");
         QPrinter printer(QPrinter::HighResolution);
         printer.setOutputFormat(QPrinter::PdfFormat);
         printer.setOutputFileName(fileName);
         textEdit->document()->print(&printer);
     }
 #endif
 }

 void TextEdit::textBold()
 {
     QTextCharFormat fmt;
     fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
     mergeFormatOnWordOrSelection(fmt);
 }

 void TextEdit::textUnderline()
 {
     QTextCharFormat fmt;
     fmt.setFontUnderline(actionTextUnderline->isChecked());
     mergeFormatOnWordOrSelection(fmt);
 }

 void TextEdit::textItalic()
 {
     QTextCharFormat fmt;
     fmt.setFontItalic(actionTextItalic->isChecked());
     mergeFormatOnWordOrSelection(fmt);
 }

 void TextEdit::textFamily(const QString &f)
 {
     QTextCharFormat fmt;
     fmt.setFontFamily(f);
     mergeFormatOnWordOrSelection(fmt);
 }

 void TextEdit::textSize(const QString &p)
 {
     qreal pointSize = p.toFloat();
     if (p.toFloat() > 0) {
         QTextCharFormat fmt;
         fmt.setFontPointSize(pointSize);
         mergeFormatOnWordOrSelection(fmt);
     }
 }

 void TextEdit::textStyle(int styleIndex)
 {
     QTextCursor cursor = textEdit->textCursor();

     if (styleIndex != 0) {
         QTextListFormat::Style style = QTextListFormat::ListDisc;

         switch (styleIndex) {
             default:
             case 1:
                 style = QTextListFormat::ListDisc;
                 break;
             case 2:
                 style = QTextListFormat::ListCircle;
                 break;
             case 3:
                 style = QTextListFormat::ListSquare;
                 break;
             case 4:
                 style = QTextListFormat::ListDecimal;
                 break;
             case 5:
                 style = QTextListFormat::ListLowerAlpha;
                 break;
             case 6:
                 style = QTextListFormat::ListUpperAlpha;
                 break;
             case 7:
                 style = QTextListFormat::ListLowerRoman;
                 break;
             case 8:
                 style = QTextListFormat::ListUpperRoman;
                 break;
         }

         cursor.beginEditBlock();

         QTextBlockFormat blockFmt = cursor.blockFormat();

         QTextListFormat listFmt;

         if (cursor.currentList()) {
             listFmt = cursor.currentList()->format();
         } else {
             listFmt.setIndent(blockFmt.indent() + 1);
             blockFmt.setIndent(0);
             cursor.setBlockFormat(blockFmt);
         }

         listFmt.setStyle(style);

         cursor.createList(listFmt);

         cursor.endEditBlock();
     } else {
         // ####
         QTextBlockFormat bfmt;
         bfmt.setObjectIndex(-1);
         cursor.mergeBlockFormat(bfmt);
     }
 }

 void TextEdit::textColor()
 {
     QColor col = QColorDialog::getColor(textEdit->textColor(), this);
     if (!col.isValid())
         return;
     QTextCharFormat fmt;
     fmt.setForeground(col);
     mergeFormatOnWordOrSelection(fmt);
     colorChanged(col);
 }

 void TextEdit::textAlign(QAction *a)
 {
     if (a == actionAlignLeft)
         textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
     else if (a == actionAlignCenter)
         textEdit->setAlignment(Qt::AlignHCenter);
     else if (a == actionAlignRight)
         textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
     else if (a == actionAlignJustify)
         textEdit->setAlignment(Qt::AlignJustify);
 }

 void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
 {
     fontChanged(format.font());
     colorChanged(format.foreground().color());
 }

 void TextEdit::cursorPositionChanged()
 {
     alignmentChanged(textEdit->alignment());
 }

 void TextEdit::clipboardDataChanged()
 {
 #ifndef QT_NO_CLIPBOARD
     if (const QMimeData *md = QApplication::clipboard()->mimeData())
         actionPaste->setEnabled(md->hasText());
 #endif
 }

 void TextEdit::about()
 {
     QMessageBox::about(this, tr("About"), tr("This"));
 }

 void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
 {
     QTextCursor cursor = textEdit->textCursor();
     if (!cursor.hasSelection())
         cursor.select(QTextCursor::WordUnderCursor);
     cursor.mergeCharFormat(format);
     textEdit->mergeCurrentCharFormat(format);
 }

 void TextEdit::fontChanged(const QFont &f)
 {
     comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
     comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
     actionTextBold->setChecked(f.bold());
     actionTextItalic->setChecked(f.italic());
     actionTextUnderline->setChecked(f.underline());
 }

 void TextEdit::colorChanged(const QColor &c)
 {
     QPixmap pix(16, 16);
     pix.fill(c);
     actionTextColor->setIcon(pix);
 }

 void TextEdit::alignmentChanged(Qt::Alignment a)
 {
     if (a & Qt::AlignLeft) {
         actionAlignLeft->setChecked(true);
     } else if (a & Qt::AlignHCenter) {
         actionAlignCenter->setChecked(true);
     } else if (a & Qt::AlignRight) {
         actionAlignRight->setChecked(true);
     } else if (a & Qt::AlignJustify) {
         actionAlignJustify->setChecked(true);
     }
 }
