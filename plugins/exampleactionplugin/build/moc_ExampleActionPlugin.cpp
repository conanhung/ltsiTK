/****************************************************************************
** Meta object code from reading C++ file 'ExampleActionPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ExampleActionPlugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExampleActionPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExampleActionPlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   28,   29,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExampleActionPlugin[] = {
    "ExampleActionPlugin\0apply()\0\0ApplyStatus\0"
};

void ExampleActionPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExampleActionPlugin *_t = static_cast<ExampleActionPlugin *>(_o);
        switch (_id) {
        case 0: { ApplyStatus _r = _t->apply();
            if (_a[0]) *reinterpret_cast< ApplyStatus*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExampleActionPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExampleActionPlugin::staticMetaObject = {
    { &ActionInterface::staticMetaObject, qt_meta_stringdata_ExampleActionPlugin,
      qt_meta_data_ExampleActionPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExampleActionPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExampleActionPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExampleActionPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExampleActionPlugin))
        return static_cast<void*>(const_cast< ExampleActionPlugin*>(this));
    if (!strcmp(_clname, "com.ltsi.EndoTrack.ActionInterface/1.0"))
        return static_cast< ActionInterface*>(const_cast< ExampleActionPlugin*>(this));
    return ActionInterface::qt_metacast(_clname);
}

int ExampleActionPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ActionInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
