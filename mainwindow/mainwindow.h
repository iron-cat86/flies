#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QObject>
#include <QtGui>
#include <memory>
#include "../plant/plant.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(unsigned int range);
    ~MainWindow();
public slots:
   void about();
private:
   unsigned int        _range=0;
   shared_ptr<QAction> _aboutAction;
   shared_ptr<QMenu>   _helpMenu;
   shared_ptr<Plant>   _plant;
};
#endif
