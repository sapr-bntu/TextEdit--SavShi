/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created: Fri 31. Aug 17:52:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../textedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      29,    9,   24,    9, 0x0a,
      45,   39,   24,    9, 0x0a,
      63,    9,    9,    9, 0x0a,
      79,   74,    9,    9, 0x0a,
      97,    9,   24,    9, 0x0a,
     108,    9,   24,    9, 0x0a,
     121,    9,    9,    9, 0x0a,
     133,    9,    9,    9, 0x0a,
     152,    9,    9,    9, 0x0a,
     167,    9,   24,    9, 0x0a,
     178,    9,    9,    9, 0x0a,
     194,    9,   24,    9, 0x0a,
     209,  207,    9,    9, 0x0a,
     239,  237,  229,    9, 0x0a,
     272,  261,  257,    9, 0x0a,
     287,    9,    9,    9, 0x0a,
     301,  299,    9,    9, 0x0a,
     328,  321,    9,    9, 0x0a,
     370,    9,    9,    9, 0x0a,
     394,    9,    9,    9, 0x0a,
     417,    9,    9,    9, 0x0a,
     425,    9,    9,    9, 0x0a,
     453,  449,   24,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextEdit[] = {
    "TextEdit\0\0EditForTest()\0bool\0fileNew()\0"
    "title\0fileOpen(QString)\0OpenWord()\0"
    "text\0SaveWord(QString)\0fileSave()\0"
    "fileSaveAs()\0filePrint()\0filePrintPreview()\0"
    "filePrintPdf()\0textBold()\0textUnderline()\0"
    "textItalic()\0f\0textFamily(QString)\0"
    "QString\0p\0textSize(QString)\0int\0"
    "styleIndex\0textStyle(int)\0textColor()\0"
    "a\0textAlign(QAction*)\0format\0"
    "currentCharFormatChanged(QTextCharFormat)\0"
    "cursorPositionChanged()\0clipboardDataChanged()\0"
    "about()\0printPreview(QPrinter*)\0str\0"
    "ForSaveWord(QString&)\0"
};

void TextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TextEdit *_t = static_cast<TextEdit *>(_o);
        switch (_id) {
        case 0: _t->EditForTest(); break;
        case 1: { bool _r = _t->fileNew();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->fileOpen((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->OpenWord(); break;
        case 4: _t->SaveWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->filePrint(); break;
        case 8: _t->filePrintPreview(); break;
        case 9: _t->filePrintPdf(); break;
        case 10: { bool _r = _t->textBold();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: _t->textUnderline(); break;
        case 12: { bool _r = _t->textItalic();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: { QString _r = _t->textSize((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->textStyle((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: _t->textColor(); break;
        case 17: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 18: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 19: _t->cursorPositionChanged(); break;
        case 20: _t->clipboardDataChanged(); break;
        case 21: _t->about(); break;
        case 22: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 23: { bool _r = _t->ForSaveWord((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TextEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TextEdit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextEdit,
      qt_meta_data_TextEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextEdit))
        return static_cast<void*>(const_cast< TextEdit*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
