#ifndef FLY_H
#define FLY_H

#include <QObject>
#include <memory>
#include <cmath>
#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QtWidgets>
#include <QWidget>

using namespace std;

struct CellInfo
{
   unsigned int flyAmount=0;
   unsigned int flyRoominess=0;
   unsigned int ID=0;
   unsigned int freeX=0;
   unsigned int freeY=0;
   int          x=0;
   int          y=0;
};

class Fly: public QThread
{
   Q_OBJECT
public:
   Fly(
      unsigned int id, 
      unsigned int T, 
      int          x, 
      int          y, 
      unsigned int range, 
      unsigned int cellID
      );
   Fly(shared_ptr<Fly> fly);
   ~Fly();
   unsigned int getStupit()   const {return _T;}       
   unsigned int getAge()      const {return _age;}   
   unsigned int getRange()    const {return _range;}  
   unsigned int getMilage()   const {return _milage;}  
   unsigned int getID()       const {return _id;}   
   unsigned int getCellID()   const {return _cellID;}
   unsigned int getXinCell()  const {return _xInCell;}
   unsigned int getYinCell()  const {return _yInCell;}      
   bool         isDead()      const {return _death;}   
   int          getVelocity() const {return _velocity;}
   int          getX()        const {return _x;}
   int          getY()        const {return _y;}
   CellInfo     getCellInfo() const {return _info;}
   void changeCellFromCell(int x, int y, unsigned int cellID);
   void setXinCell(unsigned int xInCell) {_xInCell=xInCell;}
   void setYinCell(unsigned int yInCell) {_yInCell=yInCell;}
   Q_SIGNAL void questionInfo(unsigned int myID, int x, int y);
Q_SIGNAL void allreadyChanging(unsigned int myID, unsigned int alldCellID, unsigned int cellID);
protected:
   virtual void run();
public slots:
   void getCellInfo(
      unsigned int myID, 
      unsigned int flyAmount,
      unsigned int flyRoominess,
      unsigned int ID,
      unsigned int freeX,
      unsigned int freeY,
      int          x,
      int          y
      );
private:
   bool cellIsMine(int x, int y);//клетка моя
   bool cellIsExist(int x, int y);//проверить существование клетки
   bool changeCell(int x, int y);//сменить клетку
   bool tryTop(int x, int y);
   bool tryTopRight(int x, int y);
   bool tryRight(int x, int y);
   bool tryRightDown(int x, int y);
   bool tryDown(int x, int y);
   bool tryLeftDown(int x, int y);
   bool tryLeft(int x, int y);
   bool tryLeftTop(int x, int y);
   bool tryCell(int x, int y);
   void beFoolish();//тупить
private:
   unsigned int _id=0;//идентификатор мухи
   unsigned int _cellID=0;//идентификатор ячейки в которой муха
   unsigned int _T=0;//степень врожденной тупости
   unsigned int _age=0;//возраст
   unsigned int _range=0;//размерность поля
   unsigned int _xInCell=0;//Х-координата в ячейке
   unsigned int _yInCell=0;//Y-координата в ячейке
   double       _milage=0.;//пробег   
   bool         _death=false;//дохлость
   double       _velocity=0.;//скорость 
   int          _x=0;//клетка, в которой муха находится
   int          _y=0;
   CellInfo     _info;//информация о потенциальной ячейке
};

#endif//FLY_H
