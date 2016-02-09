
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include "ui_MainWindow.h"
#include "ui_LiveViewDialog.h"
#include "CaptureManager.h"

#define QUOTE_(x) #x
#define QUOTE(x) QUOTE_(x)

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void centerWidget(QWidget *w, bool useSizeHint);
    
private:
    // Menu
    QMenu *actionsMenu;
    QMenu *drawingToolsMenu;
    
    QToolBar *drawingToolbar;
    
    QActionGroup *drawingToolsActionGroup;
    
    // Plugins
    void loadPlugins();
    void populateMenus(QObject *plugin);
    void addToMenu(QObject *plugin, const QStringList &texts, QMenu *menu,
                   const char *member, QActionGroup *actionGroup = 0);
    QDir pluginsDir;
    QStringList pluginFileNames;
    
    CaptureManager *captureManager;
    // timer
    QTimer* iTimer;
    bool isPlaying;
    
private slots:
    void applyFilter();
    void changeDrawingTools();
    
public slots:
    
	void notifyParametersChanged(const QStringList & paramChanged);
    void actionSaveParameters();
    
    // navigation
    void onPlay();
    void onStop();
    void onPrev();
    void onNext();
    void onScroll();
    void onNavigate();
    void onTimer();
    
    // display tools
    void zoomIn();
    void zoomOut();
    void zoomFullSize();
    
    void toggleLiveViewMode(bool separateMode);
    
    bool saveAs();
    
};

#endif // MAINWINDOW_H
