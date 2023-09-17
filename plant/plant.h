#ifndef PLANT_H
#define PLANT_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QString>
#include "../cell/cell.h"
#include <vector>
#include <memory>

using namespace std;

class Plant: public QGroupBox
{
Q_OBJECT
public:
   Plant(
      unsigned int range=1,          //размер квадрата от 0 (при 1: от -1 до 1, то есть 3 на 3)
      unsigned int minRoominess=10,  //минимальная мухоемкость
      unsigned int maxRoominess=100, //максимальная мухоемкость
      unsigned int minFlyAmount=0,   //минимальное количество мух в одной ячейке
      unsigned int maxFlyAmount=10,  //максимальное количество мух в одной ячейке
      unsigned int minStupidity=0,   //минимальная тупость мухи, в секундах
      unsigned int maxStupidity=10,  //максимальная тупость мухи, в секундах 
      QWidget *parent = nullptr);
   ~Plant();
signals:
   void giveCell(
      unsigned int qID, 
      unsigned int flyAmount,
      unsigned int flyRoominess,
      unsigned int ID,
      int          x,
      int          y);
   void flyInfoIsGetted(QString &icon, QString &text);
   void allFliesDead();
public slots:
   void giveCellInfo(unsigned int qID, int x, int y);
   void changeCell(unsigned int flyID, unsigned int oldCellID, unsigned int newCellID);
   void onInfoFromFly(QString &icon, QString &text);
   void onDeadFly();
private:
   void connectAndSetFlyWithPlant(shared_ptr<Fly> f, unsigned int it, unsigned int jt);
   void disconnectFlyWithPlant(shared_ptr<Fly> f);
   shared_ptr<Cell> findCellWithCoordinates(int x, int y);
private:
   unsigned int _flySizeX=0;              //размер мухи по Х
   unsigned int _flySizeY=0;              //размер мухи по Y
   unsigned int _flySum=0;                //общее колличество мух
   unsigned int _deadFlySum=0;            //количество дохлых мух
   vector<shared_ptr<Cell>>   _cells;     //ячейки
   vector<shared_ptr<QLabel>> _axisLabelY;//подписи по оси Y
   vector<shared_ptr<QLabel>> _axisLabelX;//подписи по оси Х
};

#endif // PLANT_H
