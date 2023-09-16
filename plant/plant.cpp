#include "plant.h"
#include <cstdlib>
#include <QString>

using namespace std;

Plant::Plant(
   unsigned int M, 
   unsigned int expRoominess, 
   unsigned int expFlyAmount, 
   unsigned int expStupit, 
   QWidget *parent):
   QGroupBox(parent)
{
   _M=M;
   _expRoominess=expRoominess; 
   _expFlyAmount=expFlyAmount;
   _expStupit=expStupit;
   unsigned int idStep=1; 
  // qDebug()<<"I'm plant!";
   
   for(int i=0; i<_expRoominess; ++i)
      idStep*=10;
   unsigned int idCell=idStep;
   //qDebug()<<"My range="<<_M;
   unsigned int maxRoominess=0;
   setGeometry(50, 150, 1400, 800); 
   setStyleSheet("QGroupBox { border: 1px solid gray;"
                 "border-radius: 3px;"
                 "margin-top: 1ex; }");
   int cellX=1370/(2*_M+1);
   int cellY=770/(2*_M+1);
   int startX=15;
   int startY=15;
   
   for(int it=0; it<=2*_M; ++it)
   {
      int j=it-_M;
      QString axisLabelYtxt=QString::number(j);
      shared_ptr<QLabel> axisLabelY=shared_ptr<QLabel>(new QLabel(this));
      _axisLabelY.push_back(axisLabelY);
      _axisLabelY.back()->setGeometry(startX, 5, cellX, 15);
      _axisLabelY.back()->setStyleSheet("QLabel { border: 0px solid gray;"
                                        "border-radius: 0px;"
                                        "margin-top: 0ex; }");
      _axisLabelY.back()->setText(axisLabelYtxt);
      _axisLabelY.back()->show();
      startX+=cellX;
   }
   startX=15;
   unsigned int flySum=0;
      
   for(int it=0; it<=2*_M; ++it)
   {
      int i=it-_M;
      QString axisLabelXtxt=QString::number(i);
      shared_ptr<QLabel> axisLabelX=shared_ptr<QLabel>(new QLabel(this));
      _axisLabelX.push_back(axisLabelX);
      _axisLabelX.back()->setGeometry(5, startY, 15, cellY);
      _axisLabelX.back()->setStyleSheet("QLabel { border: 0px solid gray;"
                                        "border-radius: 0px;"
                                        "margin-top: 0ex; }");
      _axisLabelX.back()->setText(axisLabelXtxt);
      _axisLabelX.back()->show();
      
      for(int jt=0; jt<=2*_M; ++jt)
      {
         int j=jt-_M;
         qDebug()<<"["<<i<<"]["<<j<<"]";
         unsigned int roominess=(unsigned int)abs(rand());
         
         for(unsigned int n=0; n<10-_expRoominess; ++n)
            roominess/=10;
         
         if(maxRoominess<roominess)
            maxRoominess=roominess;
         unsigned int flyAmount=(unsigned int)abs(rand());
         for(unsigned int n=0; n<10-_expFlyAmount; ++n)
            flyAmount/=10;
         int trueFlyAmount=flyAmount;
         
         if(flyAmount>roominess)
            trueFlyAmount=roominess;
         flySum+=trueFlyAmount;
         
         /*if(flySum>1)
         {
            flySum-=trueFlyAmount;
            trueFlyAmount=0;
         } */           
         qDebug()<<"Cell["<<i<<"]["<<j<<"]: roominess="<<roominess<<", fly amount="<<trueFlyAmount;
         shared_ptr<Cell> cell=shared_ptr<Cell>(new Cell(i, j, roominess, trueFlyAmount, _M, idCell, cellY/4, this));
         cell->setGeometry(startX, startY, cellX, cellY);
         cell->setAlignment(Qt::AlignCenter);
         QString cellName=QString::number(idCell);
         cellName+="(r=";
         cellName+=QString::number(roominess);
         cellName+=")";
         cell->setText(cellName);
         startX+=cellX; 
         qDebug()<<"Cell with id "<<idCell<<" is created.";
         
         for(unsigned int k=0; k<trueFlyAmount; ++k)
         {
            unsigned int T=(unsigned int)(abs(rand()));
            
            for(int n=0; n<10-_expStupit; ++n)
               T/=10;
            shared_ptr<Fly> curfly=shared_ptr<Fly>(new Fly(idCell+k, T, cell->getX(), cell->getY(), _M, idCell));
            curfly->_clickButton=shared_ptr<QPushButton>(new QPushButton(cell.get()));
            qDebug()<<"Fly wwith id "<<curfly->getID()<<"and time of stupid="<<curfly->getStupit()<<" is created in cell with coordinate: x="<<curfly->getX()<<", y="<<curfly->getY();
            cell->_flies.push_back(curfly);         
            cell->_flies.back()->_clickButton->setText(QString::number(idCell+k));  
            cell->_flies.back()->_clickButton->setEnabled(true); 
            //qDebug()<<"Fly is gave to cell, size="<<cell->getFlyAmount();
         }
         cell->setFlyAmount(trueFlyAmount);
         cell->show();
         _cells.push_back(cell);
         //qDebug()<<"Cell with id "<<_cells.back()->getID()<<" is added suxessfully.";
         idCell+=idStep;
      }
      startY+=cellY;
      startX=15;
   }
   _size=(unsigned int)(sqrt((double)min(flySum, maxRoominess)));
   _flySizeX=(cellX+3)/(_size+1);
   _flySizeY=(cellY+3)/_size;
   qDebug()<<"flySum="<<flySum<<", maxRoominess="<<maxRoominess<<", size="<<_size<<", _flySizeX="<<_flySizeX<<", _flySizeY="<<_flySizeY;
   
   for(shared_ptr<Cell> c :_cells)
   {
      qDebug()<<"Cell "<<c->getID()<<": fl amount="<<c->_flies.size();
      unsigned int it=0;
      unsigned int jt=0;
      unsigned int innercellid=0;
      
      for(unsigned int i=0; i<c->_flies.size(); ++i)
      {
         connectAndSetFlyWithPlant(c->_flies[i], it, jt);
         //qDebug()<<"i="<<i<<": connect";
         shared_ptr<InnerCell> innercell=shared_ptr<InnerCell>(new InnerCell(innercellid, false, it, jt));
         //qDebug()<<"i="<<i<<": innercell";
         c->_innerCell.push_back(innercell);
         //qDebug()<<"i="<<i<<": push back inner cell";
         c->_flies[i]->setInnerCellID(innercellid);
         //qDebug()<<"Set cell "<<c->getID()<<": innerCellID="<<innercellid<<", it="<<it<<", jt="<<jt;
         it+=_flySizeX+3;
         
         if(it>=(_flySizeX+3)*(_size+1))
         {
            it=0;
            jt+=_flySizeY+3;
         }
         ++innercellid;
      }
      
      while(jt<(_flySizeY+3)*_size)
      {
         shared_ptr<InnerCell> innercell=shared_ptr<InnerCell>(new InnerCell(innercellid, true, it, jt));
         //qDebug()<<"innercellid="<<innercellid<<": new it="<<it<<", jt="<<jt;
         c->_innerCell.push_back(innercell);
         //qDebug()<<"innercellid="<<innercellid<<": push_back";
         it+=_flySizeX+3;
         //qDebug()<<"innercellid="<<innercellid<<": ch it";
         
         if(it>=(_flySizeX+3)*(_size+1))
         {
            it=0;
            jt+=_flySizeY+3;
           // qDebug()<<"innercellid="<<innercellid<<": ch it & jt";
         }
         //qDebug()<<"innercellid="<<innercellid<<": if";
         ++innercellid;
         //qDebug()<<"innercellid="<<innercellid<<": incr id";
      }
      //qDebug()<<"cycle over";
      c->update();
      //qDebug()<<"c update";
      c->show();
      //qDebug()<<"c show";
   }
   //qDebug()<<"cells over";
   show();
   //qDebug()<<"show";
}

void Plant::connectAndSetFlyWithPlant(shared_ptr<Fly> f, unsigned int it, unsigned int jt)
{
   f->_clickButton->setGeometry(it, jt, _flySizeX, _flySizeY); 
   //qDebug()<<"set geometry";
   f->_clickButton->setEnabled(true); 
   //qDebug()<<"set enabled";
   f->_clickButton->show(); 
   //qDebug()<<"show";
   connect(f.get(), SIGNAL(questionInfo(unsigned int, int, int)), this, SLOT(giveCellInfo(unsigned int, int, int))); 
  // qDebug()<<"connect1";
   connect(
      f.get(), 
      SIGNAL(allreadyChanging(unsigned int, unsigned int, unsigned int)), 
      this, 
      SLOT(changeCell(unsigned int, unsigned int, unsigned int))
   );
   //qDebug()<<"connect2";
   connect(
      this, 
      SIGNAL(giveCell(unsigned int, unsigned int, unsigned int, unsigned int, int, int)), 
      f.get(), 
      SLOT(getCellInfo(unsigned int, unsigned int, unsigned int, unsigned int, int, int))
   );
   //qDebug()<<"connect3";
   f->start();
   //qDebug()<<"start";
}

void Plant::disconnectFlyWithPlant(shared_ptr<Fly> f)
{
   f->exit();
   disconnect(f.get(), SIGNAL(questionInfo(unsigned int, int, int)), this, SLOT(giveCellInfo(unsigned int, int, int)));
   disconnect(
      f.get(), 
      SIGNAL(allreadyChanging(unsigned int, unsigned int, unsigned int)), 
      this, 
      SLOT(changeCell(unsigned int, unsigned int, unsigned int))
   );
   disconnect(
      this, 
      SIGNAL(giveCell(unsigned int, unsigned int, unsigned int, unsigned int, int, int)), 
      f.get(), 
      SLOT(getCellInfo(unsigned int, unsigned int, unsigned int, unsigned int, int, int))
   );
}

Plant::~Plant()
{
}

void Plant::giveCellInfo(unsigned int qID, int x, int y)
{
   shared_ptr<Cell> newcell=findCellWithCoordinates(x, y);
   
   if(newcell->isExist())
      emit giveCell(
         qID, 
         newcell->getFlyAmount(), 
         newcell->getFlyRoominess(), 
         newcell->getID(),  
         newcell->getX(), 
         newcell->getY()
      ); 
}

void Plant::changeCell(unsigned int flyID, unsigned int oldCellID, unsigned int newCellID)
{
   unsigned int it=0;
   
   while(it<_cells.size()&&_cells[it]->getID()!=oldCellID)
      ++it;
      
   if(it<_cells.size()&&flyID!=0)
   {
      shared_ptr<Fly> curFly=_cells[it]->findFlyForID(flyID);
      disconnectFlyWithPlant(curFly);
      shared_ptr<Fly> curfly=curFly;
      //qDebug()<<"PlANT: curfly";
      
      if(_cells[it]->decrFlyAmount())
      { 
         _cells[it]->_innerCell[curFly->getInnerCellID()]->setFree();
         _cells[it]->deleteFly(flyID);
         //qDebug()<<"PlANT: delete fly";
         unsigned int it_1=0;
         
         while(it_1<_cells.size()&&_cells[it_1]->getID()!=newCellID)
            ++it_1;
         //qDebug()<<"PlANT: it_1="<<it_1;
            
         if(it_1<_cells.size()&&_cells[it_1]->incrFlyAmount())
         {
            unsigned int inner_it=0;
            
            while(inner_it<_cells[it_1]->_innerCell.size()&&!_cells[it_1]->_innerCell[inner_it]->isFree())
               ++inner_it;
            
            if(inner_it<_cells[it_1]->_innerCell.size())
            {
               _cells[it_1]->_innerCell[inner_it]->setLock();
               _cells[it_1]->insertFly(curfly);
               // qDebug()<<"PlANT: insert fly";
               _cells[it_1]->_flies.back()->_clickButton=shared_ptr<QPushButton>(new QPushButton(_cells[it_1].get())); 
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": click Button created;";      
               _cells[it_1]->_flies.back()->_clickButton->setText(QString::number(_cells[it_1]->_flies.back()->getID())); 
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": click Button setText="<<(QString::number(_cells[it_1]->_flies.back()->getID()));  
               _cells[it_1]->_flies.back()->_clickButton->setEnabled(true); 
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": click Button set enabled true;";      
               _cells[it_1]->_flies.back()->changeCellFromCell(_cells[it_1]->getX(), _cells[it_1]->getY(), newCellID); 
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": click Button change cell from cell;";      
               _cells[it_1]->_flies.back()->setInnerCellID(_cells[it_1]->_innerCell[inner_it]->getID());
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": set inner cell;";      
               connectAndSetFlyWithPlant(_cells[it_1]->_flies.back(), _cells[it_1]->_innerCell[inner_it]->getX(), _cells[it_1]->_innerCell[inner_it]->getY());
               //qDebug()<<"Fly "<<_cells[it_1]->_flies.back()->getID()<<"is in cell "<<newCellID<<" from cell "<<oldCellID<<" with coord x="<<_cells[it_1]->_innerCell[inner_it]->getX()<<", y="<<_cells[it_1]->_innerCell[inner_it]->getY()<<": connect;";
            }
            else
               qDebug()<<"Error-3";
         }
         else
            qDebug()<<"Error-2";
      }         
      else
         qDebug()<<"Error-1";
   }
   else
      qDebug()<<"fly is dead";    
}  


shared_ptr<Cell> Plant::findCellWithCoordinates(int x, int y)
{
   for(shared_ptr<Cell> value: _cells)
   {
      if(value->getX()==x&&value->getY()==y)
         return value;
   }
   shared_ptr<Cell> notExist=shared_ptr<Cell>(new Cell(x, y, 0, 0, _M, 0, 0));
   return notExist; 
}
