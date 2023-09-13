#include "mainwindow.h"

MainWindow::MainWindow(unsigned int range):
_range(range)
{
    this->setGeometry(50,50, 355, 478);
    _plant=shared_ptr<Plant>(new Plant(_range));
    setCentralWidget(_plant.get());
    //setWindowIcon(QIcon("zemlyatka.jpg"));

    _aboutAction=shared_ptr<QAction>(new QAction(tr("About"), this));
    _aboutAction->setStatusTip(tr("about application"));
    connect(_aboutAction.get(), SIGNAL(triggered()), this, SLOT(about()));
    _helpMenu=shared_ptr<QMenu>(new QMenu);
    _helpMenu->addMenu(tr("&Help"));
    _helpMenu->addAction(_aboutAction.get());
    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About flies lifes"),
                       tr("<h2>Flies Lifes,</h2>"
                          "<p>Copyright in 2023 by Anna Belova."
                          "<p>The application ''Flies Lifes'' tells about life of flies in cell. "));
}
