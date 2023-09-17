#include "mainwindow.h"

MainWindow::MainWindow(unsigned int range, unsigned int expRoominess, unsigned int expFlyAmount, unsigned int expStupit):
_range(range),
_expRoominess(expRoominess), 
_expFlyAmount(expFlyAmount), 
_expStupit(expStupit)
{
    this->setGeometry(50,50, 1500, 1000);
    setWindowIcon(QIcon("../mainwindow/icon.jpg"));
    _aboutAction=shared_ptr<QAction>(new QAction(tr("About"), this));
    _aboutAction->setStatusTip(tr("about application"));
    connect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(about()));
    _helpMenu=shared_ptr<QMenu>(new QMenu(this));
    _helpMenu=shared_ptr<QMenu>(menuBar()->addMenu(tr("&Help")));
    _helpMenu->addAction(_aboutAction.get());
    setAttribute(Qt::WA_DeleteOnClose);
    _running=shared_ptr<QPushButton>(new QPushButton(this));
    _running->setGeometry(50, 50, 200, 100);
    _running->setUpdatesEnabled(true);
    _running->setEnabled(true);
    _running->setText("&Run");
    _running->show();
    connect(_running.get(), SIGNAL(clicked()), this, SLOT(runFlies()));
    _flyIcon=shared_ptr<QLabel>(new QLabel(this));
    _flyIcon->setGeometry(300, 50, 100, 100);
    _flyIcon->setUpdatesEnabled(true);
    _flyIcon->show();
    _flyInfo=shared_ptr<QLabel>(new QLabel(this));
    _flyInfo->setGeometry(450, 50, 1000, 100);
    _flyInfo->setUpdatesEnabled(true);
    _flyInfo->setStyleSheet("QLabel {  border: 1px solid gray;"
                            "border-radius: 3px;"
                            "background-color: #ffffff; }");
    _flyInfo->show();
}

MainWindow::~MainWindow()
{
   disconnect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About flies lifes"),
                       tr("<h2>Flies Lifes,</h2><p>Copyright in 2023 by Anna Belova.<p>The application ''Flies Lifes'' tells about life of flies in cell. "));
}

void MainWindow::runFlies()
{
   _plant=shared_ptr<Plant>(new Plant(_range, _expRoominess, _expFlyAmount, _expStupit, this));
   _running->setEnabled(false);
   connect(_plant.get(), SIGNAL(flyInfoIsGetted(QString&, QString&)), this, SLOT(onFlyInfoFromPlant(QString&, QString&)));
}

void MainWindow::onFlyInfoFromPlant(QString &icon, QString &text)
{
   QPixmap pix=QPixmap(icon);
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
