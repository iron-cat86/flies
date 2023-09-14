#include "plant.h"
#include <cstdlib>

using namespace std;

Plant::Plant(
   unsigned int M, 
   unsigned int expRoominess, 
   unsigned int expFlyAmount, 
   unsigned int expStupit, 
   QWidget *parent):
   QLabel(parent)
{
   _M=M;
   _expRoominess=expRoominess; 
   _expFlyAmount=expFlyAmount;
   _expStupit=expStupit;
  // qDebug()<<"I'm plant!";
   unsigned int idCell=1000;
   //qDebug()<<"My range="<<_M;
   unsigned int flySum=0;
   setGeometry(50, 150, 1400, 800); 
   setStyleSheet("QLabel { border: 1px solid gray;"
                            "border-radius: 3px;"
                            "margin-top: 1ex; }");
   int cellX=1370/(2*_M+1);
   int cellY=770/(2*_M+1);
   int startX=15;
   int startY=15;
   
   for(int it=0; it<=2*_M; ++it)
   {
      int i=it-_M;
      
      for(int jt=0; jt<=2*_M; ++jt)
      {
         int j=jt-_M;
         qDebug()<<"["<<i<<"]["<<j<<"]";
         unsigned int roominess=(unsigned int)abs(rand());
         
         for(unsigned int n=0; n<10-_expRoominess; ++n)
            roominess/=10;
         unsigned int flyAmount=(unsigned int)abs(rand());
         
         for(unsigned int n=0; n<10-_expFlyAmount; ++n)
            flyAmount/=10;
         int trueFlyAmount=flyAmount;
         
         if(flyAmount>roominess)
            trueFlyAmount=roominess;
            
         qDebug()<<"Cell["<<i<<"]["<<j<<"]: roominess="<<roominess<<", fly amount="<<trueFlyAmount;
         flySum+=trueFlyAmount;
         shared_ptr<Cell> cell=shared_ptr<Cell>(new Cell(i, j, roominess, trueFlyAmount, _M, idCell, this));
         cell->setGeometry(startX, startY, cellX, cellY);
         startX+=cellX; 
         qDebug()<<"Cell with id "<<idCell<<" is created.";
         
         for(unsigned int k=0; k<trueFlyAmount; ++k)
         {
            unsigned int T=(unsigned int)(abs(rand()));
            
            for(int n=0; n<10-_expStupit; ++n)
               T/=10;
            shared_ptr<Fly> curfly=shared_ptr<Fly>(new Fly(idCell+k, T, cell->getX(), cell->getY(), _M, idCell));
            qDebug()<<"Fly wwith id "<<curfly->getID()<<"and time of stupid="<<curfly->getStupit()<<" is created in cell with coordinate: x="<<curfly->getX()<<", y="<<curfly->getY();
            cell->_flies.push_back(curfly);            
            //qDebug()<<"Fly is gave to cell, size="<<cell->getFlyAmount();
         }
         cell->show();
         _cells.push_back(cell);
         //qDebug()<<"Cell with id "<<_cells.back()->getID()<<" is added suxessfully.";
         idCell+=1000;
      }
      startY+=cellY;
      startX=15;
   }
   qDebug()<<"sum="<<flySum;
   
   for(shared_ptr<Cell> c :_cells)
   {
      qDebug()<<"Cell "<<c->getID()<<":";
      
      for(shared_ptr<Fly> f: c->_flies)
      {
         connectFlyWithPlant(f);
         qDebug()<<"Fly "<<f->getID()<<" is suxess";
      }
   }
   show();
}

void Plant::connectFlyWithPlant(shared_ptr<Fly> f)
{
   QObject::connect(f.get(), SIGNAL(questionInfo(unsigned int, int, int)), this, SLOT(giveCellInfo(unsigned int, int, int)));
   QObject::connect(f.get(), SIGNAL(allreadyChanging(unsigned int, unsigned int, unsigned int)), this, SLOT(changeCell(unsigned int, unsigned int, unsigned int)));
   QObject::connect(this, SIGNAL(giveCell(unsigned int, unsigned int, unsigned int, unsigned int, int, int)), f.get(), SLOT(getCellInfo(unsigned int, unsigned int, unsigned int, unsigned int, int, int)));
   f->start();
}

Plant::~Plant()
{
}

void Plant::giveCellInfo(unsigned int qID, int x, int y)
{
   shared_ptr<Cell> newcell=findCellWithCoordinates(x, y);
   
   if(newcell->isExist())
      emit giveCell(qID, newcell->getFlyAmount(), newcell->getFlyRoominess(), newcell->getID(), newcell->getX(), newcell->getY()); 
}

void Plant::changeCell(unsigned int flyID, unsigned int oldCellID, unsigned int newCellID)
{
   unsigned int it=0;
   
   while(it<_cells.size()&&_cells[it]->getID()!=oldCellID)
      ++it;
      
   if(it<_cells.size())
   {
      shared_ptr<Fly> curFly=_cells[it]->findFlyForID(flyID);
      //qDebug()<<"PlANT: curfly";
      
      if(!curFly->isDead())
      {
         _cells[it]->deleteFly(flyID);
         //qDebug()<<"PlANT: delete fly";
         unsigned int it_1=0;
         
         while(it_1<_cells.size()&&_cells[it_1]->getID()!=newCellID)
            ++it_1;
         //qDebug()<<"PlANT: it_1="<<it_1;
            
         if(it_1<_cells.size())
         {
            _cells[it_1]->insertFly(curFly);
           // qDebug()<<"PlANT: insert fly";
            unsigned int curFlyID=curFly->getID();
            unsigned int it_2=0;
            
            while(it_2<_cells[it_1]->_flies.size()&&_cells[it_1]->_flies[it_2]->getID()!=curFlyID)
               ++it_2;
             //qDebug()<<"PlANT: it_2="<<it_2;
            
            if(it_2<_cells[it_1]->_flies.size())
            {
               connectFlyWithPlant(_cells[it_1]->_flies[it_2]);
               //qDebug()<<"PlANT: connect";
            }
            else
               qDebug()<<"Error-0";         
         }
         else
            qDebug()<<"Error-1";
      }
      else
         qDebug()<<"fly is dead";
   }
   else
     qDebug()<<"Error-2";         
}  


shared_ptr<Cell> Plant::findCellWithCoordinates(int x, int y)
{
   for(shared_ptr<Cell> value: _cells)
   {
      if(value->getX()==x&&value->getY()==y)
         return value;
   }
   shared_ptr<Cell> notExist=shared_ptr<Cell>(new Cell(x, y, 0, 0, _M, 0));
   return notExist; 
}
