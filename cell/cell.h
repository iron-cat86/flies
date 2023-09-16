#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <vector>
#include "../fly/fly.h"
#include <algorithm>
#include <iterator>
#include <memory>

using namespace std;

class InnerCell//Ячейка внутри клетки для одной мухи (зависит от мухоемкости)
{
public:
   InnerCell(unsigned int id, bool f, unsigned int i, unsigned j) {_ID=id, _free=f; _x=i; _y=j;}
   ~InnerCell(){}
   inline void         setFree() {_free=true;}
   inline void         setLock() {_free=false;}
   unsigned int        getX()   const {return _x;}
   unsigned int        getY()   const {return _y;}
   inline unsigned int getID()  const {return _ID;} 
   inline bool         isFree() const {return _free;}
private:
   unsigned int _ID=0;
   bool         _free=true;//свободна
   unsigned int _x=0;
   unsigned int _y=0;
};

class Cell: public QLabel
{
Q_OBJECT
public:
   Cell(
      int          x, 
      int          y, 
      unsigned int flyRoominess, 
      unsigned int flyAmount, 
      unsigned int range,
      unsigned int id,
      unsigned int height,
      QWidget     *parent=nullptr
   );
   ~Cell();
   int          getX()            const {return _x;}           
   int          getY()            const {return _y;}           
   unsigned int getFlyAmount()    const {return _flyAmount;}
   unsigned int getFlyRoominess() const {return _flyRoominess;}
   unsigned int getID()           const {return _id;}   
   unsigned int getRange()        const {return _range;}
   bool         isExist()         const {return _exist;}
   shared_ptr<Fly>& findFlyForID(unsigned int id); 
   void setFlyAmount(unsigned int flyAmount) {_flyAmount=flyAmount;}
   void deleteFly(unsigned int id);
   void insertFly(shared_ptr<Fly>);
   inline bool incrFlyAmount() 
   {
      if(_flyAmount<_flyRoominess)
      {
         ++_flyAmount; 
         return true;
      } 
      return false;
   }

   inline bool decrFlyAmount() 
   {
      if(_flyAmount>0) 
      {
         --_flyAmount; 
         return true;
      } 
      return false;
   }
public:
   vector<shared_ptr<Fly>> _flies;         //мухи
   vector<shared_ptr<InnerCell>> _innerCell;//внутренние ячейки
private:
   int                    _x=0;           //х-координата
   int                    _y=0;           //у-координата
   unsigned int           _flyRoominess=0;//мухоемкость
   unsigned int           _flyAmount=0;   //количество мух
   unsigned int           _range=0;       //размер поля
   unsigned int           _id;            //идентификатор ячейки
   bool                   _exist=true;    //существование ячейки на поле
};

#endif //CELL_H
