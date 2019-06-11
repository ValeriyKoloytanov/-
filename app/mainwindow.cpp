#include "mainwindow.h"
#include "rungekutt4.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <cmath>
MainWindow :: MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ConnectSignalsWithSlots();
  timer.setInterval(50);
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
          y0 = 10,
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
  painter.drawLine(230,5,355,5);
}
//Обработка нажатия на кнопку "Расчет"
void MainWindow :: PushButtonClicked()
{l = ui->lineEdit_2->text().toDouble();
  B = ui->lineEdit_3->text().toDouble();
  m = ui->lineEdit->text().toDouble();
  alpha_0= ui->lineEdit_4->text().toDouble();
  alpha = alpha_0;
  omega = omega_0;
  w0 = g/l;
  k=B/2*m;
  gamma = B/m;
  t = t_0;
  int N=(b-a)/h + 2,   i=0;
  QVector<double> x(N), y(N);
  T=6.28*(sqrt((l*0.01)/g));
   QString TString = QString::number(T);
   ui->textEdit_5->append(TString);
  //Запускаем таймер
  timer.start();
      for (double X=a; X<=b; X+=h)
      {
          x[i] = X;
          y[i] = 2*X;
          i++;
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->xAxis->setLabel("x");
      ui->widget->yAxis->setLabel("y");
      ui->widget->xAxis->setRange(a, b);//Для оси Ox
      double minY = y[0], maxY = y[0];
      for (int i=1; i<N; i++)
      {
          if (y[i]<minY) minY = y[i];
          if (y[i]>maxY) maxY = y[i];
      }
      ui->widget->yAxis->setRange(minY, maxY);
      ui->widget->replot();

}

//Обработка нажатия на кнопку "Cброс"
void MainWindow :: PushButton_2Clicked()
{ ui->textEdit_5->clear();
   ui->lineEdit->clear();
    ui->lineEdit_2->clear();
     ui->lineEdit_3->clear();
     ui->lineEdit_4->clear();
     ui->widget->graph(0)->data()->clear();
     ui->widget->replot();
  timer.stop();
}

//Процедура, вызываемая таймером
void MainWindow :: OnTimer()
{
  this->repaint();
}
