/****************************************************************************
** Meta object code from reading C++ file 'hcloseframe.h'
**
** Created: Thu Apr 19 22:55:17 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "hcloseframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hcloseframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_HCloseFrame[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       1,   15, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

 // properties: name, type, flags
      39,   31, 0x0a095003,

       0        // eod
};

static const char qt_meta_stringdata_HCloseFrame[] = {
    "HCloseFrame\0\0showHideWidgets()\0QString\0"
    "caption\0"
};

const QMetaObject HCloseFrame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HCloseFrame,
      qt_meta_data_HCloseFrame, 0 }
};

const QMetaObject *HCloseFrame::metaObject() const
{
    return &staticMetaObject;
}

void *HCloseFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HCloseFrame))
	return static_cast<void*>(const_cast<HCloseFrame*>(this));
    return QWidget::qt_metacast(_clname);
}

int HCloseFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showHideWidgets(); break;
        }
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = caption(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: changeCaption(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
