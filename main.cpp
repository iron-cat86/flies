#include "plant/plant.h"
#include <QApplication>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
   QApplication app( argc, argv );
   unsigned int range=1;
   
   if(argc>1)
      range=atoi(argv[1]);
   shared_ptr<Plant> plant=shared_ptr<Plant>(new Plant(range));
   return app.exec();
}
