#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private:
  Ui::MainWindow *ui;                   //Интерфейс
  QTimer timer;

  //Параметры маятника
  double  l,      //Длина
          B,      //Коэффициент трения
          alpha,  //Угол отклонения маятника - обобщенная координата
          alpha2,
          omega,  //Угловая скорость
          omega2,
          t,      //Время
          T,      // период
          gamma,// коофицент затухания
          alpha_0,
           w0,
           m,//Масса маятника
      // Рунге-Кутт
          f1,
          f2,
          f3,
          f4,
          l1,
           l2,
           l3,
           l4,
          dom,
          dalph;
  //График
    double a =0,
      b =  100,
      h =0.01;
    int N=(b-a)/h + 2;


    double func(double Angl,double Z);

  //Начальные условия
 const double  omega_0 =1,t_0 = 0,dt =0.1,g = 9.81;

  void ConnectSignalsWithSlots();
  void paintEvent(QPaintEvent *event);
public slots:
  void PushButtonClicked();
  void PushButton_2Clicked();
  void OnTimer();
};

#endif // MAINWINDOW_H
