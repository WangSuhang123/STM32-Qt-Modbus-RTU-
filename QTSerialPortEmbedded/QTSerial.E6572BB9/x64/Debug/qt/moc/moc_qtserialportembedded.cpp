/****************************************************************************
** Meta object code from reading C++ file 'qtserialportembedded.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../qtserialportembedded.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtserialportembedded.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
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
struct qt_meta_stringdata_CLASSQTSerialPortEmbeddedENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQTSerialPortEmbeddedENDCLASS = QtMocHelpers::stringData(
    "QTSerialPortEmbedded",
    "scanSerial",
    "",
    "on_openPort_clicked",
    "on_closePort_clicked",
    "on_openLED_clicked",
    "on_closeLED_clicked",
    "on_clearLogBtn_clicked",
    "onReadyRead",
    "handleError",
    "QSerialPort::SerialPortError",
    "error",
    "drawTable",
    "CRC16_Modbus",
    "uint16_t",
    "const uint8_t*",
    "data",
    "length",
    "packFrame",
    "uint8_t",
    "addr",
    "func"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQTSerialPortEmbeddedENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    0,   84,    2, 0x08,    5 /* Private */,
       7,    0,   85,    2, 0x08,    6 /* Private */,
       8,    0,   86,    2, 0x08,    7 /* Private */,
       9,    1,   87,    2, 0x08,    8 /* Private */,
      12,    0,   90,    2, 0x08,   10 /* Private */,
      13,    2,   91,    2, 0x08,   11 /* Private */,
      18,    3,   96,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    0x80000000 | 14, 0x80000000 | 15, 0x80000000 | 14,   16,   17,
    QMetaType::QByteArray, 0x80000000 | 19, 0x80000000 | 19, QMetaType::QByteArray,   20,   21,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject QTSerialPortEmbedded::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSQTSerialPortEmbeddedENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQTSerialPortEmbeddedENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQTSerialPortEmbeddedENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QTSerialPortEmbedded, std::true_type>,
        // method 'scanSerial'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_openPort_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_closePort_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_openLED_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_closeLED_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clearLogBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>,
        // method 'drawTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'CRC16_Modbus'
        QtPrivate::TypeAndForceComplete<uint16_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const uint8_t *, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint16_t, std::false_type>,
        // method 'packFrame'
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>
    >,
    nullptr
} };

void QTSerialPortEmbedded::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QTSerialPortEmbedded *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->scanSerial(); break;
        case 1: _t->on_openPort_clicked(); break;
        case 2: _t->on_closePort_clicked(); break;
        case 3: _t->on_openLED_clicked(); break;
        case 4: _t->on_closeLED_clicked(); break;
        case 5: _t->on_clearLogBtn_clicked(); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->handleError((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        case 8: _t->drawTable(); break;
        case 9: { uint16_t _r = _t->CRC16_Modbus((*reinterpret_cast< std::add_pointer_t<const uint8_t*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint16_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        case 10: { QByteArray _r = _t->packFrame((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *QTSerialPortEmbedded::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTSerialPortEmbedded::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQTSerialPortEmbeddedENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QTSerialPortEmbedded::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
