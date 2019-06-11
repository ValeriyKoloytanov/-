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
          omega,  //Угловая скорость
          t,      //Время
          w0,     //
          gamma,  //
          T,
          alpha_0,
          k,
           a = -1, //Начало интервала, где рисуем график по оси Ox
          b =  1,
          h = 0.01;
         int  m;//Масса маятника

  //Начальные условия
 const double  omega_0 = 1,t_0 = 0,dt = 0.01, g = 9.81;

  void ConnectSignalsWithSlots();       //Соединяем сигналы со слотами
  void paintEvent(QPaintEvent *event);  //Процедура отрисовки
public slots:
  void PushButtonClicked();             //Обработка нажатия на кнопку "Расчет"
  void PushButton_2Clicked();           //Обработка нажатия на кнопку "Остановить"
  void OnTimer();                       //Процедура, вызываемая таймером
};

#endif // MAINWINDOW_H
