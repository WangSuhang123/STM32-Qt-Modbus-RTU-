#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtserialportembedded.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include "photosensitivechart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QTSerialPortEmbeddedClass; };
QT_END_NAMESPACE

class QTSerialPortEmbedded : public QMainWindow
{
    Q_OBJECT

public:
    QTSerialPortEmbedded(QWidget *parent = nullptr);
    ~QTSerialPortEmbedded();

private:
    Ui::QTSerialPortEmbeddedClass *ui;
    QByteArray m_receiveBuffer; //设置缓冲区，防止分包
    QSerialPort *serialPort;
    PhotosensitiveChart *Photochart;

private slots:
    void scanSerial();          //扫描端口
    void on_openPort_clicked();
    void on_closePort_clicked();
    void on_openLED_clicked();
    void on_closeLED_clicked();
    void on_clearLogBtn_clicked();

    void onReadyRead();          //接收数据，
    void handleError(QSerialPort::SerialPortError error); //错误处理

    //画表
    void drawTable();

    //crc16
    uint16_t CRC16_Modbus(const uint8_t* data, uint16_t length);

    //构造协议帧
    QByteArray packFrame(uint8_t addr, uint8_t func, const QByteArray& data);

};

