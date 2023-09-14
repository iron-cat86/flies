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
   unsigned int expRoominess=2;
   unsigned int expFlyAmount=1;
   unsigned int expFlyStupit=1;
   
   if(argc>1)
      range=atoi(argv[1]);
   
   if(argc>2)
      expRoominess=atoi(argv[2]);
   
   if(argc>3)
      expFlyAmount=atoi(argv[3]);
   
   if(argc>4)
      expFlyStupit=atoi(argv[4]);
   shared_ptr<QTime> ti=shared_ptr<QTime>(new QTime);
   ti->start();
   shared_ptr<QSplashScreen> splash=shared_ptr<QSplashScreen>(new QSplashScreen(QPixmap("../mainwindow/splash.png")));
   splash->show();
   while(ti->elapsed()<=3000);
   shared_ptr<MainWindow> window=shared_ptr<MainWindow>(new MainWindow(range, expRoominess, expFlyAmount, expFlyStupit));
   window->show();
   app.processEvents();
   splash->finish(window.get());
   return app.exec();
}
