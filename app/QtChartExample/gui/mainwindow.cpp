#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();

    //Router& router = Router::getInstance();

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    showAreaChart();
    showLineChart();
    showBarChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLineChart()
{
    QtCharts::QLineSeries *series0 = new QtCharts::QLineSeries();
    series0->setName("FirstLine");
    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);
    *series0 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QtCharts::QLineSeries *series1 = new QtCharts::QLineSeries();
    series1->setName("SecondLine");
    for(int i = 0; i < 20; i++)
    {
       series1->append(i, i);
    }

    QtCharts::QLineSeries *series2 = new QtCharts::QLineSeries();
    series2->setName("ThirdLine");
    for(int i = 0; i < 5; i++)
    {
       series2->append(i, i*i);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->lineChartFrame->setLayout(new QVBoxLayout(ui->lineChartFrame));
    ui->lineChartFrame->layout()->addWidget(chartView);
}

void MainWindow::showAreaChart()
{
    QtCharts::QLineSeries* series0 = new QtCharts::QLineSeries();
    QtCharts::QLineSeries* series1 = new QtCharts::QLineSeries();

    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
                 << QPointF(16, 7) << QPointF(18, 5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
                 << QPointF(16, 4) << QPointF(18, 3);

    QtCharts::QAreaSeries *series = new QtCharts::QAreaSeries(series0, series1);
    series->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Simple areachart example");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    chart->axes(Qt::Vertical).first()->setRange(0, 10);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->areaChartFrame->setLayout(new QVBoxLayout(ui->areaChartFrame));
    ui->areaChartFrame->layout()->addWidget(chartView);
}

void MainWindow::showBarChart()
{
    QtCharts::QBarSet *set0 = new QtCharts::QBarSet("First");
    QtCharts::QBarSet *set1 = new QtCharts::QBarSet("Second");
    QtCharts::QBarSet *set2 = new QtCharts::QBarSet("Third");
    QtCharts::QBarSet *set3 = new QtCharts::QBarSet("Fourth");
    QtCharts::QBarSet *set4 = new QtCharts::QBarSet("Fifth");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);


    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->barChartFrame->setLayout(new QVBoxLayout(ui->barChartFrame));
    ui->barChartFrame->layout()->addWidget(chartView);
}
