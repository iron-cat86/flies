#ifndef PLANT_H
#define PLANT_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include "../cell/cell.h"
#include <vector>
#include <memory>

using namespace std;

class Plant: public QWidget
{
Q_OBJECT
public:
   Plant(unsigned int M);
   ~Plant();
signals:
   void giveCell(
      unsigned int qID, 
      unsigned int flyAmount,
      unsigned int flyRoominess,
      unsigned int ID,
      int          x,
      int          y);
   void startCmd();
public slots:
   void giveCellInfo(unsigned int qID, int x, int y);
   void changeCell(unsigned int flyID, unsigned int oldCellID, unsigned int newCellID);
private:
   void connectFlyWithPlant(shared_ptr<Fly> f);
   shared_ptr<Cell> findCellWithCoordinates(int x, int y);
private:
   unsigned int _M=10;//размер квадрата
   vector<shared_ptr<Cell>> _cells;//ячейки
};

#endif // PLANT_H
