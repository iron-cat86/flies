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
   int x=-_range+rand()%(2*_range+1);
   int y=-_range+rand()%(2*_range+1);
   
   while(abs(x)>(int)_range||abs(y)>(int)_range||(x==_x&&y==_y))
   {
      x=-_range+rand()%(2*_range+1);
      y=-_range+rand()%(2*_range+1);
   }   
   beFoolish();
   return changeCell(x, y);
}

void Fly::run()
{ 
   while(!(tryCell()||_death));
   
   if(_death)
      emit died();
   return;
}

bool Fly::changeCell(int x, int y)
{
   while(!(_info.x==x&&_info.y==y))
      emit questionInfo(_id, x, y);
   //qDebug()<<"Past x="<<x<<", y="<<y<<". info: "<<_info.x<<", "<<_info.y;
         
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
      _clickButton->setIcon(QIcon("../images/dead.jpg"));
   }
}

void Fly::onClicked()
{
   QString text;
   QTextStream strm(&text);
   strm<<"I'm fly, id-"<<QString::number(_id)<<": \nage="
       <<QString::number(_age)<<", \nstupit level="
       <<QString::number(_T)<<", \nmilage="
       <<QString::number(_milage)<<", \nvelocity="
       <<QString::number(_velocity)<<", \nmy cell now: x="
       <<QString::number(_x)<<", y="<<QString::number(_y)<<"(cell-id="<<QString::number(_cellID)<<") on plant with range="<<QString::number(2*_range+1)<<". \nAm I alive? "
       <<(_death?"No":"Yes");
   emit infoFromFly(_iconName, text);
}
