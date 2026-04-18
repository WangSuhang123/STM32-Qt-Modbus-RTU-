/********************************************************************************
** Form generated from reading UI file 'qtserialportembedded.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSERIALPORTEMBEDDED_H
#define UI_QTSERIALPORTEMBEDDED_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTSerialPortEmbeddedClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *connectStatus;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *port;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *baudRate;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QPushButton *openPort;
    QPushButton *closePort;
    QPushButton *openLED;
    QPushButton *closeLED;
    QWidget *tab_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QPushButton *clearLogBtn;
    QTextEdit *receivedSTM32Date;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QChartView *PhotosensitiveChart;

    void setupUi(QMainWindow *QTSerialPortEmbeddedClass)
    {
        if (QTSerialPortEmbeddedClass->objectName().isEmpty())
            QTSerialPortEmbeddedClass->setObjectName("QTSerialPortEmbeddedClass");
        QTSerialPortEmbeddedClass->resize(536, 467);
        centralWidget = new QWidget(QTSerialPortEmbeddedClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        widget_4 = new QWidget(tab);
        widget_4->setObjectName("widget_4");
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        connectStatus = new QLabel(widget_4);
        connectStatus->setObjectName("connectStatus");
        connectStatus->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Microsoft YaHei UI\";\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(connectStatus);


        verticalLayout->addWidget(widget_4);

        widget = new QWidget(tab);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        port = new QComboBox(widget);
        port->setObjectName("port");

        horizontalLayout->addWidget(port);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        baudRate = new QComboBox(widget_2);
        baudRate->addItem(QString());
        baudRate->addItem(QString());
        baudRate->setObjectName("baudRate");

        horizontalLayout_2->addWidget(baudRate);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(tab);
        widget_3->setObjectName("widget_3");
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        openPort = new QPushButton(widget_3);
        openPort->setObjectName("openPort");

        gridLayout->addWidget(openPort, 0, 0, 1, 1);

        closePort = new QPushButton(widget_3);
        closePort->setObjectName("closePort");

        gridLayout->addWidget(closePort, 0, 1, 1, 1);

        openLED = new QPushButton(widget_3);
        openLED->setObjectName("openLED");

        gridLayout->addWidget(openLED, 1, 0, 1, 1);

        closeLED = new QPushButton(widget_3);
        closeLED->setObjectName("closeLED");

        gridLayout->addWidget(closeLED, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 3);
        verticalLayout->setStretch(2, 3);
        verticalLayout->setStretch(3, 3);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        widget_5 = new QWidget(tab_2);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(10, 10, 274, 361));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName("widget_6");
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(widget_6);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        clearLogBtn = new QPushButton(widget_6);
        clearLogBtn->setObjectName("clearLogBtn");

        horizontalLayout_4->addWidget(clearLogBtn);


        verticalLayout_3->addWidget(widget_6);

        receivedSTM32Date = new QTextEdit(widget_5);
        receivedSTM32Date->setObjectName("receivedSTM32Date");

        verticalLayout_3->addWidget(receivedSTM32Date);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        PhotosensitiveChart = new QChartView(tab_3);
        PhotosensitiveChart->setObjectName("PhotosensitiveChart");

        verticalLayout_4->addWidget(PhotosensitiveChart);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget);

        QTSerialPortEmbeddedClass->setCentralWidget(centralWidget);

        retranslateUi(QTSerialPortEmbeddedClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QTSerialPortEmbeddedClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTSerialPortEmbeddedClass)
    {
        QTSerialPortEmbeddedClass->setWindowTitle(QCoreApplication::translate("QTSerialPortEmbeddedClass", "QTSerialPortEmbedded", nullptr));
        label_3->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\347\212\266\346\200\201\357\274\232", nullptr));
        connectStatus->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "Status", nullptr));
        label->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\344\270\262\345\217\243\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        baudRate->setItemText(0, QCoreApplication::translate("QTSerialPortEmbeddedClass", "9600", nullptr));
        baudRate->setItemText(1, QCoreApplication::translate("QTSerialPortEmbeddedClass", "115200", nullptr));

        openPort->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        closePort->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        openLED->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\345\220\257\345\212\250", nullptr));
        closeLED->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\345\205\263\351\227\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QTSerialPortEmbeddedClass", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        label_4->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\346\216\245\346\224\266\345\210\260STM32\346\225\260\346\215\256\357\274\232", nullptr));
        clearLogBtn->setText(QCoreApplication::translate("QTSerialPortEmbeddedClass", "\346\270\205\351\231\244\346\227\245\345\277\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QTSerialPortEmbeddedClass", "\346\225\260\346\215\256\345\261\225\347\244\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("QTSerialPortEmbeddedClass", "\345\205\211\346\225\217\345\233\276\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTSerialPortEmbeddedClass: public Ui_QTSerialPortEmbeddedClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSERIALPORTEMBEDDED_H
