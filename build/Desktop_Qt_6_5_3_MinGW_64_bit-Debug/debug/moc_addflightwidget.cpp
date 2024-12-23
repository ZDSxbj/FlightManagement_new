/****************************************************************************
** Meta object code from reading C++ file 'addflightwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../addflightwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addflightwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS = QtMocHelpers::stringData(
    "AddFlightWidget",
    "flightAdded",
    "",
    "submitFlight",
    "updateDepartureAirports",
    "city",
    "updateArrivalAirports"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[16];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[24];
    char stringdata5[5];
    char stringdata6[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS_t qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "AddFlightWidget"
        QT_MOC_LITERAL(16, 11),  // "flightAdded"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 12),  // "submitFlight"
        QT_MOC_LITERAL(42, 23),  // "updateDepartureAirports"
        QT_MOC_LITERAL(66, 4),  // "city"
        QT_MOC_LITERAL(71, 21)   // "updateArrivalAirports"
    },
    "AddFlightWidget",
    "flightAdded",
    "",
    "submitFlight",
    "updateDepartureAirports",
    "city",
    "updateArrivalAirports"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAddFlightWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    1,   40,    2, 0x08,    3 /* Private */,
       6,    1,   43,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject AddFlightWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAddFlightWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AddFlightWidget, std::true_type>,
        // method 'flightAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'submitFlight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateDepartureAirports'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateArrivalAirports'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void AddFlightWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddFlightWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->flightAdded(); break;
        case 1: _t->submitFlight(); break;
        case 2: _t->updateDepartureAirports((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->updateArrivalAirports((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddFlightWidget::*)();
            if (_t _q_method = &AddFlightWidget::flightAdded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *AddFlightWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddFlightWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAddFlightWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AddFlightWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AddFlightWidget::flightAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
