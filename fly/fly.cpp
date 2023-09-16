#include "fly.h"

Fly::Fly(
      unsigned int id, 
      unsigned int T, 
      int          x, 
      int          y, 
      unsigned int range, 
      unsigned int cellID):
_id(id),
_T(T),
_x(x),
_y(y),
_range(range),
_cellID(cellID)
{
}

Fly::Fly(shared_ptr<Fly> fly):
_id(fly->getID()),
_T(fly->getStupit()),
_x(fly->getX()),
_y(fly->getY()),
_range(fly->getRange()),
_age(fly->getAge()),
_milage(fly->getMilage()),
_velocity(fly->getVelocity()),
_death(fly->isDead()),
_info(fly->getCellInfo()),
_cellID(fly->getCellID()),
_innerCellID(fly->getInnerCellID())
{
}

Fly::~Fly()
{
}

void Fly::changeCellFromCell(int x, int y, unsigned int cellID)
{
   _x=x;
   _y=y;
   _cellID=cellID;
}

bool Fly::tryCell(int x, int y)
{
   if(!_death)
   {
      beFoolish();
      bool change=changeCell(x, y);
      //qDebug()<<"("<<x<<", "<<y<<"): change="<<change;
      return change;
   }
   return false;
}

void Fly::run()
{
   int x=rand()%10-2*_range-1;
   int y=rand()%10-2*_range-1;
   
   while(abs(x)>(int)_range||x==_x)
      x=rand()%10-2*_range-1;
         
   while(abs(y)>(int)_range||y==_y)
      y=rand()%10+2*_range-1;
   bool found=false;
   
   while(!found&&!_death)
   {
      found=tryCell(x, y);
      
      if(!found)
      {
         x=rand()%10-2*_range-1;
         y=rand()%10-2*_range-1;
         
         while(abs(x)>(int)_range||x==_x)
            x=rand()%10-2*_range-1;
         
         while(abs(y)>(int)_range||y==_y)
            y=rand()%10+2*_range-1;
      }
   }
}

bool Fly::changeCell(int x, int y)
{
   unsigned int alldID=_cellID;
  // qDebug()<<"alld id...";
   if(_death)
   {
      exit();
      return false;
   }
   
   while(!(_info.x==x&&_info.y==y))
      emit questionInfo(_id, x, y);
      
   if(
      !_death&&//я не дохлая
      _info.flyAmount+1<=_info.flyRoominess//с моим прибытием мухоемкость новой клетки не превысится
   )
   {
      if(isRunning())
         exit();
      _milage+=sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));
      _velocity=_milage/((double)_age);
      //qDebug()<<"emit "<<_id<<"("<<alldID<<"->"<<_info.ID<<")";
      emit allreadyChanging(_id, alldID, _info.ID);
      return true;
   }
   return false;
}

void Fly::getCellInfo(
      unsigned int myID, 
      unsigned int flyAmount,
      unsigned int flyRoominess,
      unsigned int ID,
      int          x,
      int          y
      )
{
   if(myID==_id)
   {
      _info.flyAmount=flyAmount;
      _info.flyRoominess=flyRoominess;
      _info.ID=ID;
      _info.x=x;
      _info.y=y;
   }
}

void Fly::beFoolish()
{
   sleep(_T);
   _age+=_T;
      
   if(_age>=(2*_range+1)*_T)
      _death=true;
   qDebug()<<"I'm fly, id-"<<_id<<": age="<<_age<<", milage="<<_milage<<", velocity="<<_velocity<<", my cell now: x="<<_x<<", y="<<_y<<"(cell-id="<<_cellID<<") on plant with range="<<_range<<". Am I alive? "<<(_death?"No":"Yes");
}
