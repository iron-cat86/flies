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
}

MainWindow::~MainWindow()
{
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
}
