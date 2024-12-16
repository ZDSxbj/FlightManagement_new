/****************************************************************************
** Meta object code from reading C++ file 'Mine_indent.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Mine_indent.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mine_indent.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMine_indentENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMine_indentENDCLASS = QtMocHelpers::stringData(
    "Mine_indent",
    "handledeleteRequest",
    "",
    "name",
    "plane",
    "uclass",
    "time",
    "price",
    "id_card",
    "handlecomplete",
    "checkAndSearchFlights"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMine_indentENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[12];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[6];
    char stringdata5[7];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[8];
    char stringdata9[15];
    char stringdata10[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMine_indentENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMine_indentENDCLASS_t qt_meta_stringdata_CLASSMine_indentENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "Mine_indent"
        QT_MOC_LITERAL(12, 19),  // "handledeleteRequest"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 4),  // "name"
        QT_MOC_LITERAL(38, 5),  // "plane"
        QT_MOC_LITERAL(44, 6),  // "uclass"
        QT_MOC_LITERAL(51, 4),  // "time"
        QT_MOC_LITERAL(56, 5),  // "price"
        QT_MOC_LITERAL(62, 7),  // "id_card"
        QT_MOC_LITERAL(70, 14),  // "handlecomplete"
        QT_MOC_LITERAL(85, 21)   // "checkAndSearchFlights"
    },
    "Mine_indent",
    "handledeleteRequest",
    "",
    "name",
    "plane",
    "uclass",
    "time",
    "price",
    "id_card",
    "handlecomplete",
    "checkAndSearchFlights"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMine_indentENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    6,   32,    2, 0x08,    1 /* Private */,
       9,    0,   45,    2, 0x08,    8 /* Private */,
      10,    0,   46,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QDateTime, QMetaType::Double, QMetaType::QString,    3,    4,    5,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Mine_indent::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMine_indentENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMine_indentENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMine_indentENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Mine_indent, std::true_type>,
        // method 'handledeleteRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const double &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handlecomplete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkAndSearchFlights'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Mine_indent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mine_indent *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handledeleteRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 1: _t->handlecomplete(); break;
        case 2: _t->checkAndSearchFlights(); break;
        default: ;
        }
    }
}

const QMetaObject *Mine_indent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mine_indent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMine_indentENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Mine_indent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
