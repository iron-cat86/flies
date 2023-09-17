#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->setGeometry(50,50, 1500, 1000);
    setWindowIcon(QIcon("../images/icon.jpg"));
    _aboutAction=shared_ptr<QAction>(new QAction(tr("About"), this));
    _aboutAction->setStatusTip(tr("about application"));
    connect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(about()));
    _instruction=shared_ptr<QAction>(new QAction(tr("Manual"), this));
    _instruction->setStatusTip(tr("Manual"));
    connect(_instruction.get(), SIGNAL(triggered()), this, SLOT(instruction()));
    _helpMenu=shared_ptr<QMenu>(new QMenu(this));
    _helpMenu=shared_ptr<QMenu>(menuBar()->addMenu(tr("&Help")));
    _helpMenu->addAction(_aboutAction.get());
    _helpMenu->addAction(_instruction.get());
    setAttribute(Qt::WA_DeleteOnClose);
    _running=shared_ptr<QPushButton>(new QPushButton(this));
    _running->setGeometry(50, 50, 200, 100);
    _running->setUpdatesEnabled(true);
    _running->setEnabled(true);
    _running->setText("&Run");
    _running->show();
    createTextEdit(_rangeEdit,    _rangeLabel,    "Range level:                 ", "1",  530, 50,  50, 25);
    createTextEdit(_minRoomEdit,  _minRoomLabel,  "Minimal roominess:           ", "0",  530, 75,  50, 25);
    createTextEdit(_maxRoomEdit,  _maxRoomLabel,  "Maximal roominess:           ", "10", 895, 75,  50, 25);
    createTextEdit(_minFlyAmEdit, _minFlyAmLabel, "Minimal fly amount:          ", "0",  530, 100, 50, 25);
    createTextEdit(_maxFlyAmEdit, _maxFlyAmLabel, "Maximal fly amount:          ", "10", 895, 100, 50, 25);
    createTextEdit(_minFlyStEdit, _minFlyStLabel, "Minimal stupidity level, sec:", "0",  530, 125, 50, 25);
    createTextEdit(_maxFlyStEdit, _maxFlyStLabel, "Maximal stupidity level, sec:", "10", 895, 125, 50, 25);
    connect(_running.get(), SIGNAL(clicked()), this, SLOT(runFlies()));
}

void MainWindow::createTextEdit(
   shared_ptr<QLineEdit> &line, 
   shared_ptr<QLabel>    &label, 
   QString                name, 
   QString                text, 
   int                    x, 
   int                    y, 
   int                    width, 
   int                    height
)
{
   line=shared_ptr<QLineEdit>(new QLineEdit(this));
   label=shared_ptr<QLabel>(new QLabel(this));
   label->setGeometry(x-270, y, 270, height);
   label->setText(name);
   line->setGeometry(x, y, width, height);
   line->setText(text);
   line->setUpdatesEnabled(true);
   line->show();
} 

MainWindow::~MainWindow()
{
   disconnect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
   disconnect(_plant.get(), SIGNAL(allFliesDead()), this, SLOT(onAllDead()));
   disconnect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(about()));
   disconnect(_instruction.get(), SIGNAL(triggered()), this, SLOT(instruction()));
   disconnect(_running.get(), SIGNAL(clicked()), this, SLOT(runFlies()));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About flies lifes"),
                       tr("<h2>Flies Lifes,</h2><p>Copyright in 2023 by Anna Belova.<p>The application ''Flies Lifes'' tells about life of flies in cell. "));
}

void MainWindow::instruction()
{
    QMessageBox::about(this, tr("Manual"),
                       tr("<h2>Manual</h2>Set range level more then zero, and plant range will be equal to 2*range + 1, coordinate diapazon will be from -range to +range.\n Run fly life with help by randomizer. When all flies die, you can repeet it. \n Click on fly to get all information about it."));
}

void MainWindow::runFlies()
{
   _flyInfo.reset();
   _flyIcon.reset();
   _flyIcon=shared_ptr<QLabel>(new QLabel(this));
   _flyIcon->setGeometry(950, 50, 100, 100);
   _flyIcon->setUpdatesEnabled(true);
   QPixmap pix=QPixmap("../images/avatar.png");
   pix.scaled(100, 100);
   _flyIcon->setPixmap(pix);
   _flyIcon->setScaledContents(true);
   int pixW = pix.width();
   int labelW =_flyIcon->width();
   double factor = double(labelW)/pixW;
   _flyIcon->setFixedWidth(factor*_flyIcon->pixmap()->width());
   _flyIcon->setFixedHeight(factor*_flyIcon->pixmap()->height());
   _flyIcon->update();
   _flyIcon->show();
   _flyInfo=shared_ptr<QLabel>(new QLabel(this));
   _flyInfo->setGeometry(1050, 50, 400, 100);
   _flyInfo->setUpdatesEnabled(true);
   _flyInfo->setStyleSheet("QLabel {  border: 1px solid gray;"
                           "border-radius: 3px;"
                           "background-color: #ffffff; }");
   _flyInfo->show();
   _plant.reset();
   
   if(_rangeEdit->text().toInt()<0)
      _rangeEdit->setText(QString::number(abs(_rangeEdit->text().toInt())));
      
   if(_rangeEdit->text().toInt()==0)
      _rangeEdit->setText("1");
      
   if(_minRoomEdit->text().toInt()<0)
      _minRoomEdit->setText("0");
      
   if(_maxRoomEdit->text().toInt()<0)
      _maxRoomEdit->setText(QString::number(abs(_maxRoomEdit->text().toInt())));
      
   if(_minFlyAmEdit->text().toInt()<0)
      _minFlyAmEdit->setText("0");
      
   if(_maxFlyAmEdit->text().toInt()<0)
      _maxFlyAmEdit->setText(QString::number(abs(_maxFlyAmEdit->text().toInt())));
      
   if(_minFlyStEdit->text().toInt()<0)
      _minFlyStEdit->setText("0");
      
   if(_maxFlyStEdit->text().toInt()<0)
      _maxFlyStEdit->setText(QString::number(abs(_maxFlyStEdit->text().toInt())));
   
   if(_minRoomEdit->text().toInt()>_maxRoomEdit->text().toInt())
   {   
      QString maxR=_minRoomEdit->text();
      _minRoomEdit->setText(_maxRoomEdit->text());
      _maxRoomEdit->setText(maxR);
   }
      
   if(_minFlyAmEdit->text().toInt()>_maxFlyAmEdit->text().toInt())
   {   
      QString maxR=_minFlyAmEdit->text();
      _minFlyAmEdit->setText(_maxFlyAmEdit->text());
      _maxFlyAmEdit->setText(maxR);
   }   
   if(_minFlyStEdit->text().toInt()>_maxFlyStEdit->text().toInt())
   {   
      QString maxR=_minFlyStEdit->text();
      _minFlyStEdit->setText(_maxFlyStEdit->text());
      _maxFlyStEdit->setText(maxR);
   }
   
   if(_minRoomEdit->text().toInt()==_maxRoomEdit->text().toInt())
      _maxRoomEdit->setText(QString::number(_maxRoomEdit->text().toInt()+1));
      
   if(_minFlyAmEdit->text().toInt()==_maxFlyAmEdit->text().toInt())
      _maxFlyAmEdit->setText(QString::number(_maxFlyAmEdit->text().toInt()+1));
   
   if(_minFlyStEdit->text().toInt()==_maxFlyStEdit->text().toInt())
      _maxFlyStEdit->setText(QString::number(_maxFlyStEdit->text().toInt()+1));
   _plant=shared_ptr<Plant>(new Plant(
      (unsigned int)_rangeEdit->text().toInt(), 
      (unsigned int)_minRoomEdit->text().toInt(), (unsigned int)_maxRoomEdit->text().toInt(), 
      (unsigned int)_minFlyAmEdit->text().toInt(), (unsigned int)_maxFlyAmEdit->text().toInt(), 
      (unsigned int)_minFlyStEdit->text().toInt(), (unsigned int)_maxFlyStEdit->text().toInt(), 
      this));
   _running->setEnabled(false);
   _rangeEdit->setEnabled(false);
   _minRoomEdit->setEnabled(false);
   _maxRoomEdit->setEnabled(false);
   _minFlyAmEdit->setEnabled(false);
   _maxFlyAmEdit->setEnabled(false);
   _minFlyStEdit->setEnabled(false);
   _maxFlyStEdit->setEnabled(false);
   connect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
   connect(_plant.get(), SIGNAL(allFliesDead()), this, SLOT(onAllDead()));
}

void MainWindow::onFlyInfoFromPlant(QString &icon, QString &text)
{
   QPixmap pix;
   
   if(text.back()=='o')
   {
      QPixmap pix1(icon);
      QPixmap pix2("../images/black.png");
      QPixmap pix3(pix1.rect().united(pix2.rect()).size());
      pix3.fill("#00000000");
      QPainter p(&pix3);
      p.drawPixmap(pix3.rect(),pix1,pix1.rect());
      p.drawPixmap(pix3.rect(),pix2,pix2.rect());
      p.end();
      pix=pix3;
   }
   else
      pix=QPixmap(icon);
   pix.scaled(100, 100);    
   _flyIcon->setPixmap(pix);
   _flyIcon->setScaledContents(true);
   int pixW = pix.width();
   int labelW =_flyIcon->width();
   double factor = double(labelW)/pixW;
   _flyIcon->setFixedWidth(factor*_flyIcon->pixmap()->width());
   _flyIcon->setFixedHeight(factor*_flyIcon->pixmap()->height());
   _flyIcon->update();
   _flyIcon->show();
   _flyInfo->setText(text);
   _flyInfo->update();
}

void MainWindow::onAllDead()
{
   _running->setEnabled(true);
   _rangeEdit->setEnabled(true);
   _minRoomEdit->setEnabled(true);
   _maxRoomEdit->setEnabled(true);
   _minFlyAmEdit->setEnabled(true);
   _maxFlyAmEdit->setEnabled(true);
   _minFlyStEdit->setEnabled(true);
   _maxFlyStEdit->setEnabled(true);
}
