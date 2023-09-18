#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->setGeometry(50,50, 1500, 1000);
    setWindowIcon(QIcon("../images/icon.jpg"));
    createAction(_aboutAction, "About", "About application");
    connect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(helpAbout()));
    createAction(_manualAction, "Manual", "Manual");
    connect(_manualAction.get(), SIGNAL(triggered()), this, SLOT(helpManual()));
    _helpMenu=shared_ptr<QMenu>(new QMenu(this));
    _helpMenu=shared_ptr<QMenu>(menuBar()->addMenu(tr("&Help")));
    _helpMenu->addAction(_aboutAction.get());
    _helpMenu->addAction(_manualAction.get());
    _running=shared_ptr<QPushButton>(new QPushButton(this));
    _running->setGeometry(50, 50, 200, 100);
    _running->setUpdatesEnabled(true);
    _running->setEnabled(true);
    _running->setText("&Run");
    _running->show();
    connect(_running.get(), SIGNAL(clicked()), this, SLOT(runFlies()));
    createTextEdit(_rangeEdit,    _rangeLabel,    "Range level:                 ", "1",  530, 50,  50, 25);
    createTextEdit(_minRoomEdit,  _minRoomLabel,  "Minimal roominess:           ", "0",  530, 75,  50, 25);
    createTextEdit(_maxRoomEdit,  _maxRoomLabel,  "Maximal roominess:           ", "10", 895, 75,  50, 25);
    createTextEdit(_minFlyAmEdit, _minFlyAmLabel, "Minimal fly amount:          ", "0",  530, 100, 50, 25);
    createTextEdit(_maxFlyAmEdit, _maxFlyAmLabel, "Maximal fly amount:          ", "10", 895, 100, 50, 25);
    createTextEdit(_minFlyStEdit, _minFlyStLabel, "Minimal stupidity level, sec:", "0",  530, 125, 50, 25);
    createTextEdit(_maxFlyStEdit, _maxFlyStLabel, "Maximal stupidity level, sec:", "10", 895, 125, 50, 25);
    setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::createAction(shared_ptr<QAction> &action, QString header, QString status)
{
   action=shared_ptr<QAction>(new QAction(tr(header.toStdString().data()), this));
   action->setStatusTip(tr(status.toStdString().data()));
}

MainWindow::~MainWindow()
{
   disconnect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
   disconnect(_plant.get(), SIGNAL(allFliesDead()), this, SLOT(onAllDead()));
   disconnect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(helpAbout()));
   disconnect(_manualAction.get(), SIGNAL(triggered()), this, SLOT(helpManual()));
   disconnect(_running.get(), SIGNAL(clicked()), this, SLOT(runFlies()));
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

void MainWindow::helpAbout()
{
   about("About flies lifes", 
   "<h2>Flies Lifes,</h2>"
   "<p>Copyright in 2023 by Anna Belova.<p>"
   "The application ''Flies Lifes'' tells about life of flies in cell.");
}

void MainWindow::helpManual()
{
   about("Manual",
   "<h2>Manual</h2>"
   "Set range level more then zero, and plant range will be equal to 2*range + 1,"
   " coordinate diapazon will be from -range to +range.\n"
   "Run fly life with help by randomizer. When all flies die, you can repeet it.\n"
   "Click on fly to get all information about it.");
}

void MainWindow::about(QString header, QString text)
{
    QMessageBox::about(this, tr(header.toStdString().data()), tr(text.toStdString().data()));
}

void MainWindow::checkEditValueLessZero(shared_ptr<QLineEdit> &edit, ValueForEdit value)
{
   switch(value)
   {
   default:
   case(ValueForEdit::Zero):
      if(edit->text().toInt()<0)
         edit->setText("0");
      break;
   case(ValueForEdit::Abs):
      if(edit->text().toInt()<0)      
         edit->setText(QString::number(abs(edit->text().toInt())));
      break;
   case(ValueForEdit::Single):
      if(edit->text().toInt()<=0)      
         edit->setText("1");
      break;
   }
}

void MainWindow::checkMinMaxValue(shared_ptr<QLineEdit> &minedit, shared_ptr<QLineEdit> &maxedit)
{   
   checkEditValueLessZero(minedit, ValueForEdit::Zero);
   checkEditValueLessZero(maxedit, ValueForEdit::Abs); 
   
   if(minedit->text().toInt()>maxedit->text().toInt())
   {   
      QString maxR=minedit->text();
      minedit->setText(maxedit->text());
      maxedit->setText(maxR);
   }
   
   if(minedit->text().toInt()==maxedit->text().toInt())
      maxedit->setText(QString::number(maxedit->text().toInt()+1));
}

void MainWindow::runFlies()
{
   _flyInfo.reset();
   _flyIcon.reset();
   _flyIcon=shared_ptr<QLabel>(new QLabel(this));
   _flyIcon->setGeometry(950, 50, 100, 100);
   _flyIcon->setUpdatesEnabled(true);
   QPixmap pix=QPixmap("../images/avatar.png");
   setPixmapOnFlyIcon(pix);
   _flyInfo=shared_ptr<QLabel>(new QLabel(this));
   _flyInfo->setGeometry(1050, 50, 400, 100);
   _flyInfo->setUpdatesEnabled(true);
   _flyInfo->setStyleSheet("QLabel {  border: 1px solid gray;"
                           "border-radius: 3px;"
                           "background-color: #ffffff; }");
   _flyInfo->show();
   _plant.reset();
   checkEditValueLessZero(_rangeEdit, ValueForEdit::Single);
   checkMinMaxValue(_minRoomEdit, _maxRoomEdit);
   checkMinMaxValue(_minFlyAmEdit,_maxFlyAmEdit);
   checkMinMaxValue(_minFlyStEdit, _maxFlyStEdit);
   _plant=shared_ptr<Plant>(new Plant(
      (unsigned int)_rangeEdit->text().toInt(), 
      (unsigned int)_minRoomEdit->text().toInt(), (unsigned int)_maxRoomEdit->text().toInt(), 
      (unsigned int)_minFlyAmEdit->text().toInt(), (unsigned int)_maxFlyAmEdit->text().toInt(), 
      (unsigned int)_minFlyStEdit->text().toInt(), (unsigned int)_maxFlyStEdit->text().toInt(), 
      this));
   setWidgetsEnabled(false);
   connect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
   connect(_plant.get(), SIGNAL(allFliesDead()), this, SLOT(onAllDead()));
}

void MainWindow::setPixmapOnFlyIcon(QPixmap pix)
{
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
   setPixmapOnFlyIcon(pix);
   _flyInfo->setText(text);
   _flyInfo->update();
}

void MainWindow::setWidgetsEnabled(bool enabled)
{
   _running->setEnabled(enabled);
   _rangeEdit->setEnabled(enabled);
   _minRoomEdit->setEnabled(enabled);
   _maxRoomEdit->setEnabled(enabled);
   _minFlyAmEdit->setEnabled(enabled);
   _maxFlyAmEdit->setEnabled(enabled);
   _minFlyStEdit->setEnabled(enabled);
   _maxFlyStEdit->setEnabled(enabled);
}

void MainWindow::onAllDead()
{
   setWidgetsEnabled(true);
}
