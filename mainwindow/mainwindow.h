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
    MainWindow(unsigned int range, unsigned int expRoominess, unsigned int expFlyAmount, unsigned int expStupit);
    ~MainWindow();
public slots:
   void about();
   void runFlies();
   void onFlyInfoFromPlant(QString &icon, QString &text);
   void onAllDead();
private:
   unsigned int            _range=0;        //размер квадрата
   unsigned int            _expRoominess=0; //порядок мухоемкостей
   unsigned int            _expFlyAmount=0; //порядок количеств мух в ячейках
   unsigned int            _expStupit=0;    //порядок тупостей мух, в секундах
   shared_ptr<QAction>     _aboutAction;
   shared_ptr<QMenu>       _helpMenu;
   shared_ptr<QPushButton> _running;
   shared_ptr<QLabel>      _flyInfo;
   shared_ptr<QLabel>      _flyIcon;
   shared_ptr<Plant>       _plant;
};
#endif
