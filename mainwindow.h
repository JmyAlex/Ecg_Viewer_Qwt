#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class Plot;

class QAction;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void pan();
    void about();

private:
    void createActions();
    void createMenus();
    void createToolbars();

    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    void loadFile(const QString &fileName);

    Plot *_plot;

    QString curFile;

    QMenu *fileMenu;
    QMenu *plotMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QAction *openAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *panAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif // MAINWINDOW_H
