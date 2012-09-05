/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created: Wed 5. Sep 13:22:39 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qml/textedit.h"
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
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      28,    9,   20,    9, 0x0a,
      39,    9,   20,    9, 0x0a,
      54,   50,    9,    9, 0x0a,
      77,    9,   72,    9, 0x0a,
      88,   50,   72,    9, 0x0a,
     108,   50,    9,    9, 0x0a,
     127,    9,    9,    9, 0x0a,
     146,    9,    9,    9, 0x0a,
     161,    9,    9,    9, 0x0a,
     172,    9,    9,    9, 0x0a,
     188,    9,    9,    9, 0x0a,
     203,  201,    9,    9, 0x0a,
     225,  223,    9,    9, 0x0a,
     254,  243,    9,    9, 0x0a,
     269,    9,    9,    9, 0x0a,
     283,  281,    9,    9, 0x0a,
     310,  303,    9,    9, 0x0a,
     352,    9,    9,    9, 0x0a,
     376,    9,    9,    9, 0x0a,
     399,    9,    9,    9, 0x0a,
     407,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextEdit[] = {
    "TextEdit\0\0fileNew()\0QString\0fileOpen()\0"
    "openWord()\0str\0saveWord(QString)\0bool\0"
    "fileSave()\0fileSaveAs(QString)\0"
    "filePrint(QString)\0filePrintPreview()\0"
    "filePrintPdf()\0textBold()\0textUnderline()\0"
    "textItalic()\0f\0textFamily(QString)\0p\0"
    "textSize(QString)\0styleIndex\0"
    "textStyle(int)\0textColor()\0a\0"
    "textAlign(QAction*)\0format\0"
    "currentCharFormatChanged(QTextCharFormat)\0"
    "cursorPositionChanged()\0clipboardDataChanged()\0"
    "about()\0printPreview(QPrinter*)\0"
};

void TextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TextEdit *_t = static_cast<TextEdit *>(_o);
        switch (_id) {
        case 0: _t->fileNew(); break;
        case 1: { QString _r = _t->fileOpen();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->openWord();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->saveWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->fileSaveAs((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->filePrint((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->filePrintPreview(); break;
        case 8: _t->filePrintPdf(); break;
        case 9: _t->textBold(); break;
        case 10: _t->textUnderline(); break;
        case 11: _t->textItalic(); break;
        case 12: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->textColor(); break;
        case 16: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 17: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 18: _t->cursorPositionChanged(); break;
        case 19: _t->clipboardDataChanged(); break;
        case 20: _t->about(); break;
        case 21: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
