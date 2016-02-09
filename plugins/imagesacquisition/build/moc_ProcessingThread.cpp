/****************************************************************************
** Meta object code from reading C++ file 'ProcessingThread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ProcessingThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProcessingThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessingThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   34,   40,   40, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   69,   40,   40, 0x08,
      81,  114,   40,   40, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProcessingThread[] = {
    "ProcessingThread\0newFrame(QImage)\0"
    "frame\0\0updateAcquisitionFlag(bool)\0"
    "isAcquiring\0updateAcquisitionFolder(QString)\0"
    "folder\0"
};

void ProcessingThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProcessingThread *_t = static_cast<ProcessingThread *>(_o);
        switch (_id) {
        case 0: _t->newFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->updateAcquisitionFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateAcquisitionFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProcessingThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProcessingThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ProcessingThread,
      qt_meta_data_ProcessingThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessingThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessingThread))
        return static_cast<void*>(const_cast< ProcessingThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ProcessingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ProcessingThread::newFrame(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
