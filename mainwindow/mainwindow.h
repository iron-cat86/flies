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
   void runFlies();
   void onFlyInfoFromPlant(QString &icon, QString &text);
   void onAllDead();
private:
   shared_ptr<QAction>     _aboutAction;      //о приложении
   shared_ptr<QMenu>       _helpMenu;         //помощь пользователю
   shared_ptr<QPushButton> _running;          //кнопка запуска
   shared_ptr<QLabel>      _flyInfo;          //информация о мухе
   shared_ptr<QLabel>      _flyIcon;          //аватарка мухи
   shared_ptr<Plant>       _plant;            //поле с ячейками
};
#endif
