#include "fly.h"

Fly::Fly(unsigned int id, unsigned int T, int x, int y, unsigned int range, unsigned int cellID):
_id(id),
_T(T),
_x(x),
_y(y),
_range(range),
_cellID(cellID)
{
}

Fly::Fly(shared_ptr<Fly> fly)
{
   _id=fly->getID();
   _T=fly->getStupit();
   _x=fly->getX();
   _y=fly->getY();
   _range=fly->getRange();
   _age=fly->getAge();
   _milage=fly->getMilage();
   _velocity=fly->getVelocity();
   _death=fly->isDead();
   _info=fly->getCellInfo();
   _cellID=fly->getCellID();
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

bool Fly::cellIsMine(int x, int y)
{
   if(x==_x&&y==_y)
      return true;
   return false;
}

bool Fly::cellIsExist(int x, int y)
{
   //qDebug()<<"x="<<x<<", y="<<y<<", abs(x)="<<abs(x)<<", abs(y)="<<abs(y)<<", abs(range)="<<abs((int)_range);
   if(
      abs(x)>abs((int)_range)||
      abs(y)>abs((int)_range)
   )
      return false;
   return true;
}
/*
x, y+1   top
x+1, y+1 topright
x+1, y   right
x+1, y-1 rightdown
x, y-1   down
x-1, y-1 leftdown
x-1, y   left
x-1, y+1 lefttop//circle=true
*/
bool Fly::tryTop(int x, int y)
{
   return tryCell(x, y+1);
}

bool Fly::tryTopRight(int x, int y)
{
   return tryCell(x+1, y+1);
}

bool Fly::tryRight(int x, int y)
{
   return tryCell(x+1, y);
}

bool Fly::tryRightDown(int x, int y)
{
   return tryCell(x+1, y-1);
}

bool Fly::tryDown(int x, int y)
{
   return tryCell(x, y-1);
}

bool Fly::tryLeftDown(int x, int y)
{
   return tryCell(x-1, y-1);
}

bool Fly::tryLeft(int x, int y)
{
   return tryCell(x-1, y);
}

bool Fly::tryLeftTop(int x, int y)
{
   return tryCell(x-1, y+1);
}

bool Fly::tryCell(int x, int y)
{
   if(!_death)
   {
      beFoolish();
      bool exist=cellIsExist(x, y);
      bool change=exist?changeCell(x, y):false;
     // qDebug()<<"("<<x<<", "<<y<<"): exist="<<exist<<", change="<<change;
      return exist&&change;
   }
   return false;
}

void Fly::run()
{
   int x=_x;
   int y=_y;
   bool found=false;
   //qDebug()<<"I'm started!";
   
   while(!found&&!_death)
   {
      found=tryCell(x, y);
      
      if(!found)
         found=tryTop(x, y);
      
      if(!found)
         found=tryTopRight(x, y);
      
      if(!found)
         found=tryRight(x, y);
         
      if(!found)
         found=tryRightDown(x, y);
      
      if(!found)
         found=tryDown(x, y);
      
      if(!found)
         found=tryLeftDown(x, y);
      
      if(!found)
         found=tryLeft(x, y);
      
      if(!found)
         found=tryLeftTop(x, y);

      if(!found)
      {
         y+=2;//top x y+
         
         if(!cellIsExist(x, y))
         {
            x+=2;//topright x+ y+
            
            if(!cellIsExist(x, y))
            {
               y-=2;//y  right x+ y
               
               if(!cellIsExist(x, y))
               {
                  y-=2;//rightdown x+ y-
                  
                  if(!cellIsExist(x, y))
                  {
                     x-=2;//x
                     y-=2;// down  x y-
                     
                     if(!cellIsExist(x, y))
                     {
                        x-=2;// leftdown x- y-
                        
                        if(!cellIsExist(x, y))
                        {
                           y+=2; //y  //left x- y
                           
                           if(!cellIsExist(x, y))
                           {
                              y+=2; //lefttop x- y+ 
                              
                              if(!cellIsExist(x, y))
                              {
                                 x=_x;
                                 y=_y;
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

bool Fly::changeCell(int x, int y)
{
   unsigned int alldID=_cellID;
  // qDebug()<<"alld id...";
   
   if(cellIsExist(x, y))
   {//клетка лежит на поле
      while(!(_info.x==x&&_info.y==y))
         emit questionInfo(_id, x, y);
      //qDebug()<<"Cell info: flyAmount="<<_info.flyAmount<<", roominess="<<_info.flyRoominess<<", ID="<<_info.ID<<", x="<<_info.x<<", y="<<_info.y<<", cell is mine? "<<cellIsMine(x, y)<<" My x="<<_x<<", my y="<<_y<<",my ID="<<_cellID<<", (x==_y&&y==_y)? "<<(x==_y&&y==_y);
   
      if(
         !_death&&//я не дохлая
         !cellIsMine(x, y)&&//клетка не является моей
         _info.flyAmount+1<=_info.flyRoominess//с моим прибытием мухоемкость новой клетки не превысится
      )
      {
         _milage+=sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));
         _velocity=_milage/((double)_age);
         //qDebug()<<"emit";
         emit allreadyChanging(_id, alldID, _info.ID);
         return true;
      }
      //qDebug()<<"false-1";
      return false;
   }
   //qDebug()<<"false-2";
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
 //  qDebug()<<_id<<": be foolish... T="<<_T;
   sleep(_T);
   //qDebug()<<_id<<": End sleep";
   _age+=_T;
   //qDebug()<<_id<<": age="<<_age;
      
   if(_age>=(2*_range+1)*_T)
      _death=true;
   qDebug()<<"I'm fly, id-"<<_id<<": age="<<_age<<", milage="<<_milage<<", velocity="<<_velocity<<", my cell now: x="<<_x<<", y="<<_y<<"(cell-id="<<_cellID<<") on plant with range="<<_range<<". Am I alive? "<<(_death?"No":"Yes");
}
