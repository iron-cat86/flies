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
   unsigned int        getStupit()      const {return _T;}       
   unsigned int        getAge()         const {return _age;}   
   unsigned int        getRange()       const {return _range;}  
   unsigned int        getMilage()      const {return _milage;}  
   unsigned int        getID()          const {return _id;}   
   unsigned int        getCellID()      const {return _cellID;}
   inline unsigned int getInnerCellID() const {return _innerCellID;}
   bool                isDead()         const {return _death;}   
   int                 getVelocity()    const {return _velocity;}
   int                 getX()           const {return _x;}
   int                 getY()           const {return _y;}
   CellInfo            getCellInfo()    const {return _info;}
   void changeCellFromCell(int x, int y, unsigned int cellID);
   void setInnerCellID(unsigned int innerCellID) {_innerCellID=innerCellID;}
signals:
   void questionInfo(unsigned int myID, int x, int y);
   void allreadyChanging(unsigned int myID, unsigned int alldCellID, unsigned int cellID);
protected:
   virtual void run();
public slots:
   void getCellInfo(
      unsigned int myID, 
      unsigned int flyAmount,
      unsigned int flyRoominess,
      unsigned int ID,
      int          x,
      int          y
      );
public:
   shared_ptr<QPushButton> _clickButton;
private:
   bool changeCell(int x, int y); //сменить клетку
   bool tryCell(int x, int y);
   void beFoolish();              //тупить
private:
   unsigned int _id=0;         //идентификатор мухи
   unsigned int _cellID=0;     //идентификатор ячейки в которой муха
   unsigned int _T=0;          //степень врожденной тупости
   unsigned int _age=0;        //возраст
   unsigned int _range=0;      //размерность поля
   unsigned int _innerCellID=0;//идентификатор внутренненй ячейки для мухи
   double       _milage=0.;    //пробег   
   bool         _death=false;  //дохлость
   double       _velocity=0.;  //скорость 
   int          _x=0;          //клетка, в которой муха находится
   int          _y=0;
   CellInfo     _info;         //информация о потенциальной ячейке
};

#endif//FLY_H
