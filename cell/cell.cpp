#include "cell.h"
#include <cstdlib>

using namespace std;

Cell::Cell(
      int          x, 
      int          y, 
      unsigned int flyRoominess,
      unsigned int flyAmount, 
      unsigned int range, 
      unsigned int id,
      unsigned int height,
      QWidget     *parent
   ):
   QLabel(parent)
{
   _x=x;
   _y=y;
   _flyRoominess=flyRoominess;
   _range=range;
   _id=id;
   setStyleSheet(QString("color: rgb(255, 127, 50);"
                                     "font-size: %1px").arg(height));
   setStyleSheet("QLabel { border: 1px solid gray;"
                            "border-radius: 3px;"
                            "margin-top: 1ex; }");
   if(
      abs(_x)>abs((int)_range)||
      abs(_y)>abs((int)_range)
   )
      _exist=false;
}

Cell::Cell(shared_ptr<Cell> cell, QWidget *parent):
   QLabel(parent)
{
   _x=cell->getX();//х-координата
   _y=cell->getY();//у-координата
   _flyRoominess=cell->getFlyRoominess();//мухоемкость
   _range=cell->getRange();//размер поля
   _id=cell->getID();//идентификатор ячейки
   _exist=cell->isExist();
   setFreeX(cell->getFreeX());
   setFreeY(cell->getFreeY());
   
   for(shared_ptr<Fly> f: cell->_flies)
      _flies.push_back(f);
}

Cell::~Cell()
{
}

shared_ptr<Fly>& Cell::findFlyForID(unsigned int id)
{
   for(shared_ptr<Fly> &value: _flies)
   {
      if(value->getID()==id)
         return value;
   }
   shared_ptr<Fly> fly=shared_ptr<Fly>(new Fly(0, 0, 0, 0, 0, 0));
   return fly; 
}

void Cell::deleteFly(unsigned int id)
{
   for(unsigned int i=0; i<_flies.size(); ++i)
   {
      if (_flies[i]->getID()==id)
      {
         //setFreeX(_flies[i]->getXinCell());
         //setFreeY(_flies[i]->getYinCell());
         _flies.erase(_flies.begin()+i);
         return;
      }
   }
}

void Cell::insertFly(shared_ptr<Fly> fly)
{
   _flies.push_back(fly);
}
