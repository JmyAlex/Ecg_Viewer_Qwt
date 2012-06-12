#include "mainwindow.h"
#include "Plot/plot.h"
#include "Plot/zoomer.h"
#include "Plot/panner.h"

#include <qwt_plot_zoomer.h>

#include <QtGui>  //!!!

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _plot = new Plot;
    setCentralWidget(_plot);

    createActions();
    createMenus();
    createToolbars();

    setWindowTitle(tr("Ecg Viewer - untitled"));
    setWindowIcon(QIcon(":/images/ecg.png"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAction = new QAction(tr("&ZoomIn"), this);
    zoomInAction->setIcon(QIcon(":/images/zoom_in.png"));
    zoomInAction->setStatusTip(tr("ZoomIn Signal"));
    zoomInAction->setCheckable(true);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("&ZoomOut"), this);
    zoomOutAction->setIcon(QIcon(":/images/zoom_out.png"));
    zoomOutAction->setStatusTip(tr("ZoomOut Signal"));
    zoomOutAction->setDisabled(true);
    //zoomOutAction->setCheckable(true);
    connect(_plot, SIGNAL(modifiedPlot()), this, SLOT(zoomOut()));
    connect(zoomOutAction, SIGNAL(triggered()), _plot, SLOT(zoomOut()));

    panAction = new QAction(tr("&Pan"), this);
    panAction->setIcon(QIcon(":/images/pan.png"));
    panAction->setStatusTip(tr("Move Signal"));
    panAction->setCheckable(true);
    connect(panAction, SIGNAL(triggered()), this, SLOT(pan()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);

    plotMenu = menuBar()->addMenu(tr("&Plot"));
    plotMenu->addAction(zoomInAction);
    plotMenu->addAction(zoomOutAction);
    plotMenu->addAction(panAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolbars()
{
    fileToolBar = addToolBar(tr("&File"));
    QMainWindow::addToolBar(Qt::TopToolBarArea, fileToolBar);
    fileToolBar->addAction(openAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(zoomInAction);
    fileToolBar->addAction(zoomOutAction);
    fileToolBar->addAction(panAction);
    fileToolBar->setIconSize(QSize(20, 20));
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString showName = "Untitled";
    if(!curFile.isEmpty())
    {
        showName = strippedName(curFile);
    }

    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Ecg Viewer")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::loadFile(const QString &fileName)
{
    if(_plot->ReadFile(fileName) == false)
    {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
    }
    setCurrentFile(fileName);
}

void MainWindow::open()
{
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Ecg files (*.dat)"), &selectedFilter);

    if(!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::zoomIn()
{
    panAction->setChecked(false);
    zoomOutAction->setChecked(false);
    _plot->panner()->setEnabled(false);
    _plot->zoom(true);
    _plot->canvas()->setCursor(QCursor(QPixmap(":/images/lens.png"), -1, -1));
    if (zoomInAction->isChecked() == false)
    {
        _plot->zoom(false);
        _plot->canvas()->setCursor(Qt::ArrowCursor);
    }
    //zoomOutAction->setEnabled(true);
}

void MainWindow::zoomOut()
{
    //panAction->setChecked(false);
    //_plot->panner()->setEnabled(false);
    if (_plot->zommer()->zoomRectIndex() > 0)
        zoomOutAction->setEnabled(true);
    //zoomInAction->setChecked(false);
    //_plot->zoom(true);
    else if (_plot->zommer()->zoomRectIndex() == 0)
        zoomOutAction->setEnabled(false);
    //_plot->zoomOut();
}

void MainWindow::pan()
{
    zoomInAction->setChecked(false);
    //zoomOutAction->setChecked(false);
    _plot->zommer()->setEnabled(false);
    _plot->panner()->setEnabled(true);
    _plot->canvas()->setCursor(Qt::OpenHandCursor);
    if (panAction->isChecked() == false)
    {
        _plot->panner()->setEnabled(false);
        _plot->canvas()->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About EcgTest"), tr("<h2>Ecg Viewer 0.0</h2>"
                                                 "<p> Copyright &copy; Alexander Solovov ^_^ 2011"
                                                 "<p> Ecg test viewer"
                                                 "<p> <h2>Help</h2>"
                                                 "<p> Navigating on signal : keyboard arrows(up, down, left, right)"
                                                 "<p> Zoom in '+', zoom out '-'"));
}
