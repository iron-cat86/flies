#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <vector>
#include "../fly/fly.h"
#include <algorithm>
#include <iterator>
#include <memory>

using namespace std;

class Cell: public QLabel
{
Q_OBJECT
public:
   Cell(
      int          x, 
      int          y, 
      unsigned int flyRoominess, 
      unsigned int flyAmount, 
      unsigned int range,
      unsigned int id,
      unsigned int height,
      QWidget     *parent=nullptr
   );
   Cell(shared_ptr<Cell> cell, QWidget *parent=nullptr);
   ~Cell();
   int          getX()            const {return _x;}           
   int          getY()            const {return _y;}           
   unsigned int getFlyAmount()    const {return _flies.size();}
   unsigned int getFlyRoominess() const {return _flyRoominess;}
   unsigned int getID()           const {return _id;}   
   unsigned int getRange()        const {return _range;}
   unsigned int getFreeX()        const {return _freeX;}
   unsigned int getFreeY()        const {return _freeY;}
   bool         isExist()         const {return _exist;}
   shared_ptr<Fly>& findFlyForID(unsigned int id); 
   void deleteFly(unsigned int id);
   void insertFly(shared_ptr<Fly>);
   void setFreeX(unsigned int freeX) {_freeX=freeX;}
   void setFreeY(unsigned int freeY) {_freeY=freeY;}
public:
   vector<shared_ptr<Fly>> _flies;         //мухи
private:
   int                    _x=0;           //х-координата
   int                    _y=0;           //у-координата
   unsigned int           _flyRoominess=0;//мухоемкость
   unsigned int           _range=0;       //размер поля
   unsigned int           _id;            //идентификатор ячейки
   unsigned int           _freeX=0;       //первая свободная для мухи Х-координата
   unsigned int           _freeY=0;       //первая свободная для мухи Y-координата
   bool                   _exist=true;    //существование ячейки на поле
};

#endif //CELL_H
