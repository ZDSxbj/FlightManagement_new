/****************************************************************************
** Meta object code from reading C++ file 'homewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../homewidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homewidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSHomeWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSHomeWidgetENDCLASS = QtMocHelpers::stringData(
    "HomeWidget",
    "toggleAddressListVisibility",
    "",
    "QLineEdit*",
    "input",
    "QListWidget*",
    "list",
    "setAddressFromList",
    "QListWidgetItem*",
    "item",
    "swapDepartureAndDestination",
    "searchFlights",
    "checkAndSearchFlights",
    "refresh",
    "hideAddressListIfApplicable"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHomeWidgetENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[11];
    char stringdata1[28];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[6];
    char stringdata5[13];
    char stringdata6[5];
    char stringdata7[19];
    char stringdata8[17];
    char stringdata9[5];
    char stringdata10[28];
    char stringdata11[14];
    char stringdata12[22];
    char stringdata13[8];
    char stringdata14[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHomeWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHomeWidgetENDCLASS_t qt_meta_stringdata_CLASSHomeWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "HomeWidget"
        QT_MOC_LITERAL(11, 27),  // "toggleAddressListVisibility"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 10),  // "QLineEdit*"
        QT_MOC_LITERAL(51, 5),  // "input"
        QT_MOC_LITERAL(57, 12),  // "QListWidget*"
        QT_MOC_LITERAL(70, 4),  // "list"
        QT_MOC_LITERAL(75, 18),  // "setAddressFromList"
        QT_MOC_LITERAL(94, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(111, 4),  // "item"
        QT_MOC_LITERAL(116, 27),  // "swapDepartureAndDestination"
        QT_MOC_LITERAL(144, 13),  // "searchFlights"
        QT_MOC_LITERAL(158, 21),  // "checkAndSearchFlights"
        QT_MOC_LITERAL(180, 7),  // "refresh"
        QT_MOC_LITERAL(188, 27)   // "hideAddressListIfApplicable"
    },
    "HomeWidget",
    "toggleAddressListVisibility",
    "",
    "QLineEdit*",
    "input",
    "QListWidget*",
    "list",
    "setAddressFromList",
    "QListWidgetItem*",
    "item",
    "swapDepartureAndDestination",
    "searchFlights",
    "checkAndSearchFlights",
    "refresh",
    "hideAddressListIfApplicable"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHomeWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   56,    2, 0x08,    1 /* Private */,
       7,    3,   61,    2, 0x08,    4 /* Private */,
      10,    0,   68,    2, 0x08,    8 /* Private */,
      11,    0,   69,    2, 0x08,    9 /* Private */,
      12,    0,   70,    2, 0x08,   10 /* Private */,
      13,    0,   71,    2, 0x08,   11 /* Private */,
      14,    1,   72,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 8,    4,    6,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject HomeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSHomeWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHomeWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHomeWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HomeWidget, std::true_type>,
        // method 'toggleAddressListVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>,
        // method 'setAddressFromList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'swapDepartureAndDestination'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchFlights'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkAndSearchFlights'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideAddressListIfApplicable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>
    >,
    nullptr
} };

void HomeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleAddressListVisibility((*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[2]))); break;
        case 1: _t->setAddressFromList((*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QListWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[3]))); break;
        case 2: _t->swapDepartureAndDestination(); break;
        case 3: _t->searchFlights(); break;
        case 4: _t->checkAndSearchFlights(); break;
        case 5: _t->refresh(); break;
        case 6: _t->hideAddressListIfApplicable((*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListWidget* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *HomeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHomeWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HomeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
