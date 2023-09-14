#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include "../fly/fly.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

using namespace std;

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
      QWidget     *parent=nullptr
   );
   Cell(shared_ptr<Cell> cell);
   ~Cell();
   int          getX()            const {return _x;}           
   int          getY()            const {return _y;}           
   unsigned int getFlyAmount()    const {return _flies.size();}
   unsigned int getFlyRoominess() const {return _flyRoominess;}
   unsigned int getID()           const {return _id;}   
   unsigned int getRange()        const {return _range;}
   bool         isExist()         const {return _exist;}
   shared_ptr<Fly> findFlyForID(unsigned int id); 
   void deleteFly(unsigned int id);
   void insertFly(shared_ptr<Fly> fly);
public:
   vector<shared_ptr<Fly>> _flies;//мухи
private:
   int                     _x=0;//х-координата
   int                     _y=0;//у-координата
   unsigned int            _flyRoominess=0;//мухоемкость
   unsigned int            _range=0;//размер поля
   unsigned int            _id;//идентификатор ячейки
   bool                    _exist=true;//существование ячейки на поле
};

#endif //CELL_H
