/****************************************************************************
** Meta object code from reading C++ file 'ImagesAcquisitionPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ImagesAcquisitionPlugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImagesAcquisitionPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Worker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,   23,   23,   23, 0x05,
      24,   23,   23,   23, 0x05,
      35,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Worker[] = {
    "Worker\0workRequested()\0\0finished()\0"
    "gotNewImage()\0doWork()\0"
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Worker *_t = static_cast<Worker *>(_o);
        switch (_id) {
        case 0: _t->workRequested(); break;
        case 1: _t->finished(); break;
        case 2: _t->gotNewImage(); break;
        case 3: _t->doWork(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Worker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker,
      qt_meta_data_Worker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Worker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Worker))
        return static_cast<void*>(const_cast< Worker*>(this));
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Worker::workRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Worker::gotNewImage()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_ImagesAcquisitionPlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   49,   61,   61, 0x05,
      62,   92,   61,   61, 0x05,

 // slots: signature, parameters, type, tag, flags
      99,   61,  107,   61, 0x0a,
     119,   61,   61,   61, 0x0a,
     141,   61,   61,   61, 0x0a,
     160,   61,   61,   61, 0x0a,
     178,   61,   61,   61, 0x0a,
     190,  214,   61,   61, 0x0a,
     220,  259,   61,   61, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImagesAcquisitionPlugin[] = {
    "ImagesAcquisitionPlugin\0"
    "newAcquisitionFlag(bool)\0isAcquiring\0"
    "\0newAcquisitionFolder(QString)\0folder\0"
    "apply()\0ApplyStatus\0connectToCamera(bool)\0"
    "startAcquisition()\0stopAcquisition()\0"
    "loadFiles()\0slotGotNewImage(QImage)\0"
    "frame\0updateCaptureManager(QListWidgetItem*)\0"
    "item\0"
};

void ImagesAcquisitionPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImagesAcquisitionPlugin *_t = static_cast<ImagesAcquisitionPlugin *>(_o);
        switch (_id) {
        case 0: _t->newAcquisitionFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->newAcquisitionFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { ApplyStatus _r = _t->apply();
            if (_a[0]) *reinterpret_cast< ApplyStatus*>(_a[0]) = _r; }  break;
        case 3: _t->connectToCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->startAcquisition(); break;
        case 5: _t->stopAcquisition(); break;
        case 6: _t->loadFiles(); break;
        case 7: _t->slotGotNewImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 8: _t->updateCaptureManager((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImagesAcquisitionPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImagesAcquisitionPlugin::staticMetaObject = {
    { &ActionInterface::staticMetaObject, qt_meta_stringdata_ImagesAcquisitionPlugin,
      qt_meta_data_ImagesAcquisitionPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImagesAcquisitionPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImagesAcquisitionPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImagesAcquisitionPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImagesAcquisitionPlugin))
        return static_cast<void*>(const_cast< ImagesAcquisitionPlugin*>(this));
    if (!strcmp(_clname, "com.ltsi.EndoTrack.ActionInterface/1.0"))
        return static_cast< ActionInterface*>(const_cast< ImagesAcquisitionPlugin*>(this));
    return ActionInterface::qt_metacast(_clname);
}

int ImagesAcquisitionPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ActionInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ImagesAcquisitionPlugin::newAcquisitionFlag(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImagesAcquisitionPlugin::newAcquisitionFolder(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
