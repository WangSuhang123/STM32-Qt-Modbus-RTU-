#include "qtserialportembedded.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //加载qss样式表
    QFile file(":/Style/ant.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);

   

    QTSerialPortEmbedded window;
    window.show();
    return app.exec();
}
