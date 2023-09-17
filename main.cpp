#include <QApplication>
#include <QSplashScreen>
#include <memory>
#include <QTime>
#include "mainwindow/mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
   QApplication app( argc, argv );   
   shared_ptr<QTime> ti=shared_ptr<QTime>(new QTime);
   ti->start();
   shared_ptr<QSplashScreen> splash=shared_ptr<QSplashScreen>(new QSplashScreen(QPixmap("../mainwindow/splash.png")));
   splash->show();
   while(ti->elapsed()<=3000);
   shared_ptr<MainWindow> window=shared_ptr<MainWindow>(new MainWindow());
   window->show();
   app.processEvents();
   splash->finish(window.get());
   return app.exec();
}
