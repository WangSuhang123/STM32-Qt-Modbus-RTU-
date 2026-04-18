#include "photosensitivechart.h"

PhotosensitiveChart::PhotosensitiveChart(QObject *parent)
	: QObject(parent)
{}

PhotosensitiveChart::~PhotosensitiveChart()
{}


void PhotosensitiveChart::initChart()
{
    series = new QLineSeries();

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Photosensitive Chart");

    // X轴
    axisX = new QValueAxis();
    axisX->setRange(0, 50);
    axisX->setLabelFormat("%d");

    // Y轴
    axisY = new QValueAxis();
    axisY->setRange(0, 100);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ⭐⭐⭐关键：绑定！！！⭐⭐⭐
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // 美化
    chart->legend()->hide();
    chart->setBackgroundRoundness(0);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
}


QChart* PhotosensitiveChart::getChart()
{
	return chart;
}

void PhotosensitiveChart::addData(int value)
{
	series->append(pointCount++,value);
	if (pointCount > 50)
	{
		axisX->setRange(pointCount - 50,pointCount);
	}
}