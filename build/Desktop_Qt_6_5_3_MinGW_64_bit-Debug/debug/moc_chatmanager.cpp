/****************************************************************************
** Meta object code from reading C++ file 'chatmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../chatmanager.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatmanager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSChatmanagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSChatmanagerENDCLASS = QtMocHelpers::stringData(
    "Chatmanager",
    "onSendButtonClicked",
    "",
    "onEmojiButtonClicked",
    "insertEmoji",
    "emoji",
    "executeSimpleQuery",
    "insertMessageToDatabase",
    "time",
    "from_id",
    "to_id",
    "message",
    "scrollToBottom",
    "loadChatHistoryForSpecificUser",
    "myChoseUser",
    "updateReadStatus",
    "messageId",
    "isSender",
    "isRead"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatmanagerENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[12];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[12];
    char stringdata5[6];
    char stringdata6[19];
    char stringdata7[24];
    char stringdata8[5];
    char stringdata9[8];
    char stringdata10[6];
    char stringdata11[8];
    char stringdata12[15];
    char stringdata13[31];
    char stringdata14[12];
    char stringdata15[17];
    char stringdata16[10];
    char stringdata17[9];
    char stringdata18[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChatmanagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChatmanagerENDCLASS_t qt_meta_stringdata_CLASSChatmanagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "Chatmanager"
        QT_MOC_LITERAL(12, 19),  // "onSendButtonClicked"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 20),  // "onEmojiButtonClicked"
        QT_MOC_LITERAL(54, 11),  // "insertEmoji"
        QT_MOC_LITERAL(66, 5),  // "emoji"
        QT_MOC_LITERAL(72, 18),  // "executeSimpleQuery"
        QT_MOC_LITERAL(91, 23),  // "insertMessageToDatabase"
        QT_MOC_LITERAL(115, 4),  // "time"
        QT_MOC_LITERAL(120, 7),  // "from_id"
        QT_MOC_LITERAL(128, 5),  // "to_id"
        QT_MOC_LITERAL(134, 7),  // "message"
        QT_MOC_LITERAL(142, 14),  // "scrollToBottom"
        QT_MOC_LITERAL(157, 30),  // "loadChatHistoryForSpecificUser"
        QT_MOC_LITERAL(188, 11),  // "myChoseUser"
        QT_MOC_LITERAL(200, 16),  // "updateReadStatus"
        QT_MOC_LITERAL(217, 9),  // "messageId"
        QT_MOC_LITERAL(227, 8),  // "isSender"
        QT_MOC_LITERAL(236, 6)   // "isRead"
    },
    "Chatmanager",
    "onSendButtonClicked",
    "",
    "onEmojiButtonClicked",
    "insertEmoji",
    "emoji",
    "executeSimpleQuery",
    "insertMessageToDatabase",
    "time",
    "from_id",
    "to_id",
    "message",
    "scrollToBottom",
    "loadChatHistoryForSpecificUser",
    "myChoseUser",
    "updateReadStatus",
    "messageId",
    "isSender",
    "isRead"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatmanagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    1,   64,    2, 0x08,    3 /* Private */,
       6,    0,   67,    2, 0x08,    5 /* Private */,
       7,    4,   68,    2, 0x08,    6 /* Private */,
      12,    0,   77,    2, 0x08,   11 /* Private */,
      13,    1,   78,    2, 0x08,   12 /* Private */,
      15,    3,   81,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Bool,   16,   17,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject Chatmanager::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSChatmanagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChatmanagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChatmanagerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Chatmanager, std::true_type>,
        // method 'onSendButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEmojiButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertEmoji'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'executeSimpleQuery'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertMessageToDatabase'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'scrollToBottom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadChatHistoryForSpecificUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateReadStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void Chatmanager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Chatmanager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onSendButtonClicked(); break;
        case 1: _t->onEmojiButtonClicked(); break;
        case 2: _t->insertEmoji((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->executeSimpleQuery(); break;
        case 4: _t->insertMessageToDatabase((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 5: _t->scrollToBottom(); break;
        case 6: _t->loadChatHistoryForSpecificUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->updateReadStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject *Chatmanager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chatmanager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChatmanagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Chatmanager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
