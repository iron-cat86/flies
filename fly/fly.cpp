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
   wait();
}

void Fly::changeCellFromCell(int x, int y, unsigned int cellID)
{
   _x=x;
   _y=y;
   _cellID=cellID;
}

bool Fly::tryCell()
{
   int x=-_range+rand()%(_range+1);
   int y=-_range+rand()%(_range+1);
   
   while(abs(x)>(int)_range||abs(y)>(int)_range||(x==_x&&y==_y))
   {
      x=-_range+rand()%(_range+1);
      y=-_range+rand()%(_range+1);
   }   
   beFoolish();
   return changeCell(x, y);
}

void Fly::run()
{ 
   while(!(tryCell()||_death));
   return;
}

bool Fly::changeCell(int x, int y)
{
   while(!(_info.x==x&&_info.y==y))
      emit questionInfo(_id, x, y);
   qDebug()<<"Past x="<<x<<", y="<<y<<". info: "<<_info.x<<", "<<_info.y;
         
   if(
      !_death&&//я не дохлая
      _info.flyAmount+1<=_info.flyRoominess//с моим прибытием мухоемкость новой клетки не превысится
   )
   {
      _milage+=sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));
      _velocity=_milage/((double)_age);
      //qDebug()<<"emit "<<_id<<"("<<_cellID<<"->"<<_info.ID<<")";
      emit allreadyChanging(_id, _cellID, _info.ID);
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
   {
      _death=true;
      _clickButton->setIcon(QIcon("../mainwindow/dead.jpg"));
   }
   qDebug()<<"I'm fly, id-"<<_id<<": age="<<_age<<", milage="<<_milage<<", velocity="<<_velocity<<", my cell now: x="<<_x<<", y="<<_y<<"(cell-id="<<_cellID<<") on plant with range="<<_range<<". Am I alive? "<<(_death?"No":"Yes");
}

void Fly::onClicked()
{
   QString text="I'm fly, id-";
   text+=QString::number(_id);
   text+=": age=";
   text+=QString::number(_age);
   text+=", stupit level=";
   text+=QString::number(_T);
   text+=", milage=";
   text+=QString::number(_milage);
   text+=", velocity=";
   text+=QString::number(_velocity);
   text+=", my cell now: x=";
   text+=QString::number(_x);
   text+=", y=";
   text+=QString::number(_y);
   text+="(cell-id=";
   text+=QString::number(_cellID);
   text+=") on plant with range=";
   text+=QString::number(_range);
   text+=". Am I alive? ";
   text+=(_death?"No":"Yes");
   emit infoFromFly(_iconName, text);
}
