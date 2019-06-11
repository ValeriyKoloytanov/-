#include "pendulum.h"
#include "ui_pendulum.h"
#include <QPainter>
#include <cmath>
#include <qmath.h>
MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConnectSignalsWithSlots();
    timer.setInterval(5);
    timer.stop();
}

MainWindow :: ~MainWindow()
{
    delete ui;
}
//Соединяем сигналы со слотами
void MainWindow :: ConnectSignalsWithSlots()
{
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(PushButtonClicked()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(PushButton_2Clicked()));
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
}
//Процедура отрисовки
void MainWindow :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    double  lp = l*10,   //Отображаемая длина маятника
            x0 = 300,
            y0 = 0,
            x = lp * sin(alpha),       //Координаты
            y = lp * cos(alpha);

    //Рисуем маятник
    QPen pen(QBrush(QColor(64,64,64)), 2);
    painter.setPen(pen);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::gray));
    painter.drawLine(x0, y0,x0 + x, y0 + y);
    painter.drawEllipse(QPoint(x0 + x, y0 + y),int(m*4),int(m*4));
    QPen pen2(QBrush(QColor(64,64,64)), 5);
    painter.setPen(pen2);
    painter.drawLine(230,0,355,0);
}
//Кнопка построить модель
void MainWindow :: PushButtonClicked()
//получение данных.
{l = ui->Dlina->text().toDouble();
    B = ui->Zatuhanie->text().toDouble();
    m = ui->Massa->text().toDouble();
    alpha_0= ui->Ugol->text().toDouble();
    alpha = alpha_0/180*3.14;//перевод из радиан в градусы
    omega = omega_0;
    omega2=omega_0;
    alpha2 = alpha_0/180*3.14;
    w0 = g/l;
    gamma = B/(m);
    t = t_0;
    T=6.28/(sqrt((w0*w0)-(gamma*gamma)));
    QString TString = QString::number(T);
    ui->Period->setText(TString);
    timer.start();
    int i=0;
    QVector<double> x(N), y(N);
    for (double t=a; t<=b;t+=h)
    {   f1 = func(alpha2,omega2) * dt;
        l1= omega * dt;
        f2= func(alpha2+f1/2,omega2+l1/2) * dt;
        l2=  (omega+l1/2)* dt;
        f3=func(alpha2+f2/2,omega2+l2/2) * dt;
        l3=  (omega2+l2/2) * dt;
        f4= func(alpha2+f3,omega2+l3) * dt;
        l4= (omega2+l3) * dt;
        dom=(f1 + 2*f2+ 2*f3 + f4)/6;
        dalph=(l1 + 2*l2 + 2*l3 + l4)/6;
        alpha2=alpha2+dalph*dt;
        omega2= omega2+dom*dt;
        x[i] = t;
        y[i] =l*sin(alpha2);
        i++;
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->xAxis->setRange(a, b);
    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    ui->customPlot->yAxis->setRange(minY, maxY);
    ui->customPlot->replot();
}
//Кнопка сброс
void MainWindow :: PushButton_2Clicked()
{
    ui->Massa->clear();
    ui->Dlina->clear();
    ui->Ugol->clear();
    ui->Zatuhanie->clear();
     ui->Period->clear();
     ui->customPlot->graph(0)->data()->clear();
     ui->customPlot->replot();
    timer.stop();
}
//Рунге-Кутт
double MainWindow::func(double Angl, double Z)
{double out;
   out= - pow(w0, 2.) * sin(Angl) - gamma * Z;
   return out;
}
void MainWindow :: OnTimer()
// Процедура обратываемая таймером
{   f1 = func(alpha,omega) * dt;
    l1= omega * dt;
    f2= func(alpha+f1/2,omega+l1/2) * dt;
    l2=  (omega+l1/2)* dt;
    f3=func(alpha+f2/2,omega+l2/2) * dt;
    l3=  (omega+l2/2) * dt;
    f4= func(alpha+f3,omega+l3) * dt;
    l4= (omega+l3) * dt;
    dom=(f1 + 2*f2+ 2*f3 + f4)/6;
    dalph=(l1 + 2*l2 + 2*l3 + l4)/6;
    alpha=alpha+dalph*dt;
    omega= omega+dom*dt;
    this->repaint();
}
