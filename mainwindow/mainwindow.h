#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QObject>
#include <QtGui>
#include <memory>
#include "../plant/plant.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
public slots:
   void about();
   void instruction();
   void runFlies();
   void onFlyInfoFromPlant(QString &icon, QString &text);
   void onAllDead();
private:
   void createTextEdit(
      shared_ptr<QLineEdit> &line, 
      shared_ptr<QLabel>    &label, 
      QString                name, 
      QString                text, 
      int                    x, 
      int                    y, 
      int                    width, 
      int                    height
   );
private:
   shared_ptr<Plant>       _plant;            //поле с ячейками
   shared_ptr<QAction>     _aboutAction;      //о приложении
   shared_ptr<QAction>     _instruction;      //о приложении
   shared_ptr<QMenu>       _helpMenu;         //помощь пользователю
   shared_ptr<QPushButton> _running;          //кнопка запуска
   shared_ptr<QLineEdit>   _rangeEdit;        //настройка уровня размерности поля
   shared_ptr<QLineEdit>   _minRoomEdit;      //настройка минимальной мухоемкости для ячейки
   shared_ptr<QLineEdit>   _maxRoomEdit;      //настройка максимальной мухоемкости для ячейки
   shared_ptr<QLineEdit>   _minFlyAmEdit;     //настройка минимального количества мух в ячейке
   shared_ptr<QLineEdit>   _maxFlyAmEdit;     //настройка максимального количества мух в ячейке
   shared_ptr<QLineEdit>   _minFlyStEdit;     //настройка минимальной тупости мухи, в секундах
   shared_ptr<QLineEdit>   _maxFlyStEdit;     //настройка максимальной тупости мухи, в секундах
   shared_ptr<QLabel>      _rangeLabel;       //настройка уровня размерности поля
   shared_ptr<QLabel>      _minRoomLabel;     //настройка минимальной мухоемкости для ячейки
   shared_ptr<QLabel>      _maxRoomLabel;     //настройка максимальной мухоемкости для ячейки
   shared_ptr<QLabel>      _minFlyAmLabel;    //настройка минимального количества мух в ячейке
   shared_ptr<QLabel>      _maxFlyAmLabel;    //настройка максимального количества мух в ячейке
   shared_ptr<QLabel>      _minFlyStLabel;    //настройка минимальной тупости мухи, в секундах
   shared_ptr<QLabel>      _maxFlyStLabel;    //настройка максимальной тупости мухи, в секундах
   shared_ptr<QLabel>      _flyInfo;          //информация о мухе
   shared_ptr<QLabel>      _flyIcon;          //аватарка мухи
};
#endif
