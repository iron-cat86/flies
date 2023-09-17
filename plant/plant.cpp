#include "plant.h"
#include <cstdlib>
#include <QString>

using namespace std;

Plant::Plant(
   unsigned int range,          //размер квадрата от 0 (при 1: от -1 до 1, то есть 3 на 3)
   unsigned int minRoominess,  //минимальная мухоемкость
   unsigned int maxRoominess, //максимальная мухоемкость
   unsigned int minFlyAmount,   //минимальное количество мух в одной ячейке
   unsigned int maxFlyAmount,  //максимальное количество мух в одной ячейке
   unsigned int minStupidity,   //минимальная тупость мухи, в секундах
   unsigned int maxStupidity, 
   QWidget *parent):
   QGroupBox(parent)
{
   unsigned int idStep=1;
   
   while(maxFlyAmount%idStep>0)
      idStep*=10;
   idStep*=100;
   unsigned int idCell=idStep;
   unsigned int maximumRoominess=0;
   setGeometry(50, 150, 1400, 800); 
   setStyleSheet("QGroupBox { border: 1px solid gray;"
                 "border-radius: 3px;"
                 "margin-top: 1ex; }");
   int cellX=1370/(2*range+1);
   int cellY=770/(2*range+1);
   int startX=15;
   int startY=15;
   
   for(int it=0; it<=2*range; ++it)
   {
      int j=it-range;
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
   int numName=0;   
   for(int it=0; it<=2*range; ++it)
   {
      int i=it-range;
      QString axisLabelXtxt=QString::number(i);
      shared_ptr<QLabel> axisLabelX=shared_ptr<QLabel>(new QLabel(this));
      _axisLabelX.push_back(axisLabelX);
      _axisLabelX.back()->setGeometry(5, startY, 15, cellY);
      _axisLabelX.back()->setStyleSheet("QLabel { border: 0px solid gray;"
                                        "border-radius: 0px;"
                                        "margin-top: 0ex; }");
      _axisLabelX.back()->setText(axisLabelXtxt);
      _axisLabelX.back()->show();
      
      for(int jt=0; jt<=2*range; ++jt)
      {
         int j=jt-range;
         unsigned int roominess=(unsigned int)abs((int)minRoominess+rand()%((int)maxRoominess-(int)minRoominess));
         
         if(maximumRoominess<roominess)
            maximumRoominess=roominess;
         unsigned int flyAmount=(unsigned int)abs((int)minFlyAmount+rand()%((int)maxFlyAmount-(int)minFlyAmount));
         int trueFlyAmount=flyAmount;
         
         if(flyAmount>roominess)
            trueFlyAmount=roominess;
         _flySum+=trueFlyAmount;         
         shared_ptr<Cell> cell=shared_ptr<Cell>(new Cell(i, j, roominess, trueFlyAmount, idCell, cellY/4, this));
         cell->setGeometry(startX, startY, cellX, cellY);
         cell->setAlignment(Qt::AlignCenter);
         QString cellName=QString::number(idCell);
         cellName+="(r=";
         cellName+=QString::number(roominess);
         cellName+=")";
         cell->setText(cellName);
         startX+=cellX; 
                  
         for(unsigned int k=0; k<trueFlyAmount; ++k)
         {
            unsigned int T=(unsigned int)(abs((int)minStupidity+rand()%((int)maxStupidity-(int)minStupidity)));
            shared_ptr<Fly> curfly=shared_ptr<Fly>(new Fly(idCell+k, T, cell->getX(), cell->getY(), range, idCell));
            curfly->_clickButton=shared_ptr<QPushButton>(new QPushButton(cell.get()));
            cell->_flies.push_back(curfly);         
            cell->_flies.back()->_clickButton->setEnabled(true);
            QString iconName="../mainwindow/icon";
            iconName+=QString::number(numName);
            iconName+=".jpg";
            cell->_flies.back()->setIconName(iconName);
            ++numName;
            
            if(numName>30)
               numName=0; 
         }
         cell->setFlyAmount(trueFlyAmount);
         cell->show();
         _cells.push_back(cell);
         idCell+=idStep;
      }
      startY+=cellY;
      startX=15;
   }
   unsigned int size=(unsigned int)(sqrt((double)min(_flySum, maximumRoominess)));
   _flySizeX=(cellX+3)/(size+1);
   _flySizeY=(cellY+3)/size;
   qDebug()<<"flySum="<<_flySum<<", maxRoominess="<<maximumRoominess<<", size="<<size<<", _flySizeX="<<_flySizeX<<", _flySizeY="<<_flySizeY;
   
   for(shared_ptr<Cell> c :_cells)
   {
      unsigned int it=0;
      unsigned int jt=0;
      unsigned int innercellid=0;
      
      for(unsigned int i=0; i<c->_flies.size(); ++i)
      {
         connectAndSetFlyWithPlant(c->_flies[i], it, jt);
         shared_ptr<InnerCell> innercell=shared_ptr<InnerCell>(new InnerCell(innercellid, false, it, jt));
         c->_innerCell.push_back(innercell);
         c->_flies[i]->setInnerCellID(innercellid);
         it+=_flySizeX+3;
         
         if(it>=(_flySizeX+3)*(size+1))
         {
            it=0;
            jt+=_flySizeY+3;
         }
         ++innercellid;
      }
      
      while(jt<(_flySizeY+3)*size)
      {
         shared_ptr<InnerCell> innercell=shared_ptr<InnerCell>(new InnerCell(innercellid, true, it, jt));
         c->_innerCell.push_back(innercell);
         it+=_flySizeX+3;
         
         if(it>=(_flySizeX+3)*(size+1))
         {
            it=0;
            jt+=_flySizeY+3;
         }
         ++innercellid;
      }
      c->update();
      c->show();
   }
   show();
}

Plant::~Plant()
{
   for(shared_ptr<Cell> c :_cells)
   {
      for(shared_ptr<Fly> f: c->_flies)
         disconnectFlyWithPlant(f);
   }
}

void Plant::connectAndSetFlyWithPlant(shared_ptr<Fly> f, unsigned int it, unsigned int jt)
{
   f->_clickButton->setGeometry(it, jt, _flySizeX, _flySizeY); 
   QString styleButton=QString(
            "QAbstractButton {"
                    "color: rgb(255, 255, 255);"
                    "border: 0px solid rgb(100,200,200); "
                    "border-radius: 5px;"
                    "background: rgba(0,0,0,0);"
            "}");
   f->_clickButton->setStyleSheet(styleButton);
   f->_clickButton->setIcon(QIcon(f->getIconName()));
   f->_clickButton->setEnabled(true); 
   connect(f->_clickButton.get(), SIGNAL(clicked()), f.get(), SLOT(onClicked()));
   f->_clickButton->show(); 
   connect(f.get(), SIGNAL(questionInfo(unsigned int, int, int)), this, SLOT(giveCellInfo(unsigned int, int, int))); 
   connect(
      f.get(), 
      SIGNAL(allreadyChanging(unsigned int, unsigned int, unsigned int)), 
      this, 
      SLOT(changeCell(unsigned int, unsigned int, unsigned int))
   );
   connect(
      this, 
      SIGNAL(giveCell(unsigned int, unsigned int, unsigned int, unsigned int, int, int)), 
      f.get(), 
      SLOT(getCellInfo(unsigned int, unsigned int, unsigned int, unsigned int, int, int))
   );
   connect(f.get(), SIGNAL(infoFromFly(QString&, QString&)), this, SLOT(onInfoFromFly(QString&, QString&)));
   connect(f.get(), SIGNAL(died()), this, SLOT(onDeadFly()));
   f->start();
}

void Plant::disconnectFlyWithPlant(shared_ptr<Fly> f)
{
   disconnect(f.get(), SIGNAL(questionInfo(unsigned int, int, int)), this, SLOT(giveCellInfo(unsigned int, int, int)));
   disconnect(f->_clickButton.get(), SIGNAL(clicked()), f.get(), SLOT(onClicked()));
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
   disconnect(f.get(), SIGNAL(infoFromFly(QString&, QString&)), this, SLOT(onInfoFromFly(QString&, QString&)));
   disconnect(f.get(), SIGNAL(died()), this, SLOT(onDeadFly()));
}

void Plant::giveCellInfo(unsigned int qID, int x, int y)
{
   shared_ptr<Cell> newcell=findCellWithCoordinates(x, y);
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
      
      if(_cells[it]->decrFlyAmount())
      { 
         _cells[it]->_innerCell[curFly->getInnerCellID()]->setFree();
         _cells[it]->deleteFly(flyID);
         unsigned int it_1=0;
         
         while(it_1<_cells.size()&&_cells[it_1]->getID()!=newCellID)
            ++it_1;
            
         if(it_1<_cells.size()&&_cells[it_1]->incrFlyAmount())
         {
            unsigned int inner_it=0;
            
            while(inner_it<_cells[it_1]->_innerCell.size()&&!_cells[it_1]->_innerCell[inner_it]->isFree())
               ++inner_it;
            
            if(inner_it<_cells[it_1]->_innerCell.size())
            {
               _cells[it_1]->_innerCell[inner_it]->setLock();
               _cells[it_1]->insertFly(curfly);
               _cells[it_1]->_flies.back()->_clickButton=shared_ptr<QPushButton>(new QPushButton(_cells[it_1].get())); 
               _cells[it_1]->_flies.back()->_clickButton->setEnabled(true); 
               _cells[it_1]->_flies.back()->changeCellFromCell(_cells[it_1]->getX(), _cells[it_1]->getY(), newCellID); 
               _cells[it_1]->_flies.back()->setInnerCellID(_cells[it_1]->_innerCell[inner_it]->getID());
               connectAndSetFlyWithPlant(_cells[it_1]->_flies.back(), _cells[it_1]->_innerCell[inner_it]->getX(), _cells[it_1]->_innerCell[inner_it]->getY());
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

void Plant::onInfoFromFly(QString &icon, QString &text)
{
   emit flyInfoIsGetted(icon, text);
}
shared_ptr<Cell> Plant::findCellWithCoordinates(int x, int y)
{
   for(shared_ptr<Cell> value: _cells)
   {
      if(value->getX()==x&&value->getY()==y)
         return value;
   }
   shared_ptr<Cell> notExist=shared_ptr<Cell>(new Cell(0, 0, 0, 0, 0, 0, 0));
   return notExist; 
}

void Plant::onDeadFly()
{
   ++_deadFlySum;
   
   if(_deadFlySum==_flySum)
      emit allFliesDead();
}
