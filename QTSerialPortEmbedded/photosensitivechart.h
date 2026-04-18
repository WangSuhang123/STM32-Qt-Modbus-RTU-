#pragma once

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>
#include <QSerialPort>

class PhotosensitiveChart  : public QObject
{
	Q_OBJECT

public:
	PhotosensitiveChart(QObject *parent);
	~PhotosensitiveChart();

public slots:
	//画图表
	void initChart();

	//获取chart指针（给主界面用
	QChart* getChart();

	//添加数据
	void addData(int value);

private slots:

private:

	//构建图表
	QChart* chart;
	QLineSeries* series;
	QValueAxis* axisX;
	QValueAxis* axisY;

	//数据点计数
	int pointCount = 0;

};

