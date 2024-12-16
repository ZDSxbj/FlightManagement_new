/****************************************************************************
** Meta object code from reading C++ file 'userinfo.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../userinfo.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userinfo.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSUserInfoENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSUserInfoENDCLASS = QtMocHelpers::stringData(
    "UserInfo",
    "onEditAvatar",
    "",
    "onEditPhone",
    "onEditEmail",
    "onEditGender",
    "onEditBirthday",
    "onEditPassword"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSUserInfoENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[9];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[12];
    char stringdata5[13];
    char stringdata6[15];
    char stringdata7[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSUserInfoENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSUserInfoENDCLASS_t qt_meta_stringdata_CLASSUserInfoENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "UserInfo"
        QT_MOC_LITERAL(9, 12),  // "onEditAvatar"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 11),  // "onEditPhone"
        QT_MOC_LITERAL(35, 11),  // "onEditEmail"
        QT_MOC_LITERAL(47, 12),  // "onEditGender"
        QT_MOC_LITERAL(60, 14),  // "onEditBirthday"
        QT_MOC_LITERAL(75, 14)   // "onEditPassword"
    },
    "UserInfo",
    "onEditAvatar",
    "",
    "onEditPhone",
    "onEditEmail",
    "onEditGender",
    "onEditBirthday",
    "onEditPassword"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSUserInfoENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject UserInfo::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSUserInfoENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSUserInfoENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSUserInfoENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<UserInfo, std::true_type>,
        // method 'onEditAvatar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditPhone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditEmail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditGender'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditBirthday'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditPassword'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void UserInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserInfo *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEditAvatar(); break;
        case 1: _t->onEditPhone(); break;
        case 2: _t->onEditEmail(); break;
        case 3: _t->onEditGender(); break;
        case 4: _t->onEditBirthday(); break;
        case 5: _t->onEditPassword(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *UserInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSUserInfoENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
