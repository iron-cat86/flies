#include <QApplication>
#include <QSplashScreen>
#include <memory>
#include <QTime>
#include "mainwindow/mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
   QApplication app( argc, argv );
   unsigned int range=1;
   
   if(argc>1)
      range=atoi(argv[1]);
    //shared_ptr<QSplashScreen> splash=shared_ptr<QSplashScreen>(new QSplashScreen(QPixmap("zemlyatka.jpg")));
    //shared_ptr<QTime> ti=shared_ptr<QTime>(new QTime);
    shared_ptr<MainWindow> window=shared_ptr<MainWindow>(new MainWindow(range));
    window->show();
    /*ti->start();
    while(ti->elapsed()<=3000) 
       splash->show();*/
   return app.exec();
}
