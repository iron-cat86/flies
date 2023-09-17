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
      unsigned int M, 
      unsigned int expRoominess, 
      unsigned int expFlyAmount, 
      unsigned int expStupit, 
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
public slots:
   void giveCellInfo(unsigned int qID, int x, int y);
   void changeCell(unsigned int flyID, unsigned int oldCellID, unsigned int newCellID);
   void onInfoFromFly(QString &icon, QString &text);
private:
   void connectAndSetFlyWithPlant(shared_ptr<Fly> f, unsigned int it, unsigned int jt);
   void disconnectFlyWithPlant(shared_ptr<Fly> f);
   shared_ptr<Cell> findCellWithCoordinates(int x, int y);
private:
   unsigned int _M=10;                    //размер квадрата
   unsigned int _expRoominess=0;          //порядок мухоемкостей
   unsigned int _expFlyAmount=0;          //порядок количеств мух в ячейках
   unsigned int _expStupit=0;             //порядок тупостей мух, в секундах
   unsigned int _flySizeX=0;              //размер мухи по Х
   unsigned int _flySizeY=0;              //размер мухи по Y
   unsigned int _size=0;                  //размер ячейи в мухах
   vector<shared_ptr<Cell>>   _cells;     //ячейки
   vector<shared_ptr<QLabel>> _axisLabelY;//подписи по оси Y
   vector<shared_ptr<QLabel>> _axisLabelX;//подписи по оси Х
};

#endif // PLANT_H
