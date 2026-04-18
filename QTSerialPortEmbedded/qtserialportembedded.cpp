#include "qtserialportembedded.h"

QTSerialPortEmbedded::QTSerialPortEmbedded(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTSerialPortEmbeddedClass())
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);
    Photochart = new PhotosensitiveChart(this);

    //图表
    drawTable();

    //默认禁用关闭串口、关闭
    ui->closePort->setEnabled(false);
    ui->closeLED->setEnabled(false);
    
    //获取所有串口加入到下拉框
    scanSerial();

    //信号槽
    //连接打开串口按钮
    connect(serialPort,&QSerialPort::readyRead,this,&QTSerialPortEmbedded::onReadyRead);    
    //连接关闭串口按钮
    connect(serialPort,&QSerialPort::errorOccurred,this,&QTSerialPortEmbedded::handleError);


}   

QTSerialPortEmbedded::~QTSerialPortEmbedded()
{
    delete ui;
}

void QTSerialPortEmbedded::scanSerial()
{
    //获取当前电脑所有可用串口 → 加到下拉框
    ui->port->clear();
    foreach(auto info, QSerialPortInfo::availablePorts()) {
        ui->port->addItem(info.portName());
    }
}


void QTSerialPortEmbedded::on_openPort_clicked()
{
    /* 串口设置 */
    serialPort->setPortName(ui->port->currentText());
    serialPort->setBaudRate(ui->baudRate->currentText().toInt());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    /* 打开串口提示框 */
    if (true == serialPort->open(QIODevice::ReadWrite))
    {

        QMessageBox::information(this, "提示", "串口打开成功");
        ui->connectStatus->setText("串口连接成功");
        ui->openPort->setEnabled(false);
        ui->closePort->setEnabled(true);
    }
    else
    {
        QMessageBox::critical(this, "提示", "串口打开失败");
        ui->connectStatus->setText("串口连接失败");
        
    }
}

void QTSerialPortEmbedded::on_closePort_clicked()
{
    serialPort->close();
    ui->connectStatus->setText("串口连接关闭");
    ui->openPort->setEnabled(true);
    ui->closePort->setEnabled(false);
}

void QTSerialPortEmbedded::on_openLED_clicked()
{
    //明文串口发送
    //serialPort->write("ON\n");
    //qDebug("ON\n");
    //使用modbus协议来进行控制

    QByteArray data;
    data.append(char(0x01));  //开启
    QByteArray frame = packFrame(0x01, 0x01, data);
    serialPort->write(frame);
    qDebug()<<"发送开启命令："<<frame.toHex();

    ui->closeLED->setEnabled(true);
    ui->openLED->setEnabled(false);
}

void QTSerialPortEmbedded::on_closeLED_clicked()
{
    //明文串口发送
    //serialPort->write("OFF\n");
    //qDebug("OFF\n");

    QByteArray data; 
    data.append(char(0x00));  // 关闭
    QByteArray frame = packFrame(0x01, 0x02, data);
    serialPort->write(frame);

    ui->closeLED->setEnabled(false);
    ui->openLED->setEnabled(true);
}

void QTSerialPortEmbedded::on_clearLogBtn_clicked()
{
    ui->receivedSTM32Date->clear();
}

void QTSerialPortEmbedded::onReadyRead()
{
    QByteArray data = serialPort->readAll();    //一次读完所以的可用数据

    if (data.isEmpty())
    {
        return;
    }

    //不为空就追加到缓冲区里
    m_receiveBuffer.append(data);

    ////简单处理：假设以\n结尾，当前的STM32发送的是字符串
    //int pos;
    //while ((pos = m_receiveBuffer.indexOf("\n")) != -1) {
    //    QByteArray line = m_receiveBuffer.left(pos).trimmed();
    //    m_receiveBuffer.remove(0, pos + 1);
    //    //处理接收到的字符串
    //    QString received = QString::fromUtf8(line.trimmed());
    //    qDebug() << "收到STM32数据: " << received;
    //    ui->receivedSTM32Date->append(received);
    //}

    //循环解析完所有帧
    while (m_receiveBuffer.size() >= 7) {   //最短帧长度，包括帧头2、地址码1、功能码1、数据长度1、数据段2、CRC
        if (m_receiveBuffer[0] != (char)0xAA || m_receiveBuffer[1] != (char)0x55)
        {
            m_receiveBuffer.remove(0, 1);
            continue;
        }
        uint8_t dataLen = (uint8_t)m_receiveBuffer[4];
        int frameLen = 7 + dataLen;     //完整帧长度

        if (m_receiveBuffer.size()<frameLen)    //数据不够，等一下句
        {
            break;
        }

        //提取完整帧
        QByteArray frame = m_receiveBuffer.left(frameLen);

        //CRC校验
        uint16_t receivedCRC = (uint8_t)frame[frameLen - 2] | ((uint8_t)frame[frameLen - 1] << 8);
        uint16_t calcCRC = CRC16_Modbus((const uint8_t*)frame.constData(), frame.size() - 2);

        if (receivedCRC == calcCRC)
        {
            //校验通过
            uint8_t addr = (uint8_t)frame[2];
            uint8_t func = (uint8_t)frame[3];

            QByteArray payload = frame.mid(5, dataLen);

            qDebug() << "有效帧！功能码为：" << func << "数据：" << payload.toHex();

            //根据功能码处理
            if (func == 0x81)   //stm32状态应答
            {
                uint8_t enable = payload[0];
                
                uint8_t sensor = payload[1];        //光敏值
                QString status = (enable == 1) ?
                    QString("监测开启 - 光敏值: %1").arg(sensor) :
                    QString("监测关闭");
                ui->receivedSTM32Date->append(status);

                qDebug() << "enable:" << enable<<"status:" << status;
                //自动刷新曲线
                Photochart->addData(sensor);
            }
        }
        else
        {
            qDebug() << "❌ CRC校验失败！收到CRC:" << Qt::hex << receivedCRC
                << " 计算CRC:" << calcCRC;
            qDebug() << "完整帧:" << frame.toHex();
        }
        m_receiveBuffer.remove(0, frameLen);    //处理已经移除的帧
    }

    // 防止缓冲区无限增长
    if (m_receiveBuffer.size() > 4096) {
        m_receiveBuffer.clear();
    }
}
//处理错误
void QTSerialPortEmbedded::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError)
    {
        return;
    }
    QMessageBox::critical(this, "错误", "串口发生错误：" + serialPort->errorString());
    ui->connectStatus->setText("串口连接失败");
    serialPort->close();
}

void QTSerialPortEmbedded::drawTable()
{
    Photochart->initChart();

    // 把图表显示到界面上
    ui->PhotosensitiveChart->setChart(Photochart->getChart());
}

// CRC16-Modbus (0xA001 多项式，低字节在前)
uint16_t QTSerialPortEmbedded::CRC16_Modbus(const uint8_t* data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

QByteArray QTSerialPortEmbedded::packFrame(uint8_t addr, uint8_t func, const QByteArray& data)
{
    QByteArray frame;
    frame.append(0xAA);          // 帧头
    frame.append(0x55);
    frame.append(addr);          // 地址码
    frame.append(func);          // 功能码
    frame.append(data.size());   // 数据长度
    frame.append(data);          // 数据段

    // 计算 CRC（只对 帧头后到数据段结束 的内容）
    uint16_t crc = CRC16_Modbus((const uint8_t*)frame.constData(), frame.size());
    frame.append(crc & 0xFF);    // CRC Low
    frame.append((crc >> 8) & 0xFF); // CRC High

    return frame;
}
