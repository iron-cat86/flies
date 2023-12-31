#include "cell.h"
#include <cstdlib>

using namespace std;

Cell::Cell(
      int          x, 
      int          y, 
      unsigned int flyRoominess,
      unsigned int flyAmount,
      unsigned int id,
      unsigned int height,
      QWidget     *parent
   ):
   QLabel(parent)
{
   _x=x;
   _y=y;
   _flyRoominess=flyRoominess;
   _id=id;
   setStyleSheet(QString("color: rgb(255, 127, 50);"
                                     "font-size: %1px").arg(height));
   setStyleSheet("QLabel { border: 1px solid gray;"
                            "border-radius: 3px;"
                            "background-color: #ffffff;}");
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
         _flies.erase(_flies.begin()+i);
         return;
      }
   }
}

void Cell::insertFly(shared_ptr<Fly> fly)
{
   _flies.push_back(fly);
}
