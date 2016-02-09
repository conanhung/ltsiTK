/************************************************************************/
/* tavi-tracking:                                                       */
/* A multithreaded OpenCV application using the Qt framework.           */
/* An object tracking for TAVI Imaging-guided.                          */
/*                                                                      */
/* DucLongHung NGUYEN <duclonghung.nguyen@gmail.com>                    */
/*                                                                      */
/* Copyright (c) 2012 DucLongHung NGUYEN                                */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#include "interfaces.h"
#include "parameterstoolbox.h"
#include "ImageConversion.h"
#include "Util.h"
#include "Settings.h"
#include "MainWindow.h"

// basic file operations
#include <iostream>
#include <fstream>

// Qt header files
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QPluginLoader>

//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	// Setup user interface
	setupUi(this);
    
	// Load settings
	QByteArray geometry;
	QByteArray state;
	Settings::loadSettings(Settings::iniDefaultPath(), &geometry, &state);
	this->restoreGeometry(geometry);
	this->restoreState(state);
    
	// Setup Parameters toolBox
	toolBox_Parameters->setupUi();
    settingsPushButton->setDefaultAction(dockWidget_parameters->toggleViewAction());
    
    // Icons for the buttons
    QDir appDirPath = QDir(qApp->applicationDirPath());
    
    qDebug() << appDirPath.absolutePath();
    
    QIcon icon;
    icon.addFile(QString::fromUtf8("images/zoom_in.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    zoomInPushButton->setIcon(icon);
    
    QIcon icon1;
    icon1.addFile(QString::fromUtf8("images/zoom_out.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    zoomOutPushButton->setIcon(icon1);
    
    QIcon icon2;
    icon2.addFile(QString::fromUtf8("images/zoom_fullsize.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    zoomMaximizePushButton->setIcon(icon2);
    
    QIcon icon3;
    icon3.addFile(QString::fromUtf8("images/play.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    playButton->setIcon(icon3);
    
    QIcon icon4;
    icon4.addFile(QString::fromUtf8("images/stop.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    stopButton->setIcon(icon4);
    
    QIcon icon5;
    icon5.addFile(QString::fromUtf8("images/back.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    prevButton->setIcon(icon5);
    
    QIcon icon6;
    icon6.addFile(QString::fromUtf8("images/forward.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    nextButton->setIcon(icon6);
    
    QIcon icon7;
    icon7.addFile(QString::fromUtf8("images/settings.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    settingsPushButton->setIcon(icon7);
    settingsPushButton->setAttribute(Qt::WA_TranslucentBackground);
    
    QIcon icon8;
    icon8.addFile(QString::fromUtf8("images/saveAs.png"), QSize(16,16), QIcon::Normal, QIcon::Off);
    saveImageButton->setIcon(icon8);
    saveImageButton->setAttribute(Qt::WA_TranslucentBackground);
    
    // navigation buttons
    connect(playButton, SIGNAL(released()), this, SLOT(onPlay()));
    connect(stopButton, SIGNAL(released()), this, SLOT(onStop()));
    connect(prevButton, SIGNAL(released()), this, SLOT(onPrev()));
    connect(nextButton, SIGNAL(released()), this, SLOT(onNext()));
    connect(bookPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(onScroll()));
    // display tools
    // Zoom
    connect(zoomInPushButton, SIGNAL(released()), this, SLOT(zoomIn()));
    connect(zoomOutPushButton, SIGNAL(released()), this, SLOT(zoomOut()));
    connect(zoomMaximizePushButton, SIGNAL(released()), this, SLOT(zoomFullSize()));
    connect(saveImageButton, SIGNAL(released()), this, SLOT(saveAs()));
    
    // Create capture manager
    captureManager = new CaptureManager;
    // Connect Paint area
    captureManager->paintArea1 = paintArea1;
    captureManager->paintArea2 = paintArea2;
    
    // Filter Menu
    actionsMenu = menubar->addMenu(tr("&Actions"));
    
    // Filter Menu
    drawingToolsMenu = menubar->addMenu(tr("&Drawing Tools"));
    
    // Toolbar
    //drawingToolbar = addToolBar("Drawing toolbar");
    
    drawingToolsActionGroup = new QActionGroup(this);
    
    // Plugin
    loadPlugins();
    
} // MainWindow constructor

MainWindow::~MainWindow()
{
	// Save settings to config.ini in current working directory
	Settings::saveSettings(Settings::iniDefaultPath(), this->saveGeometry(), this->saveState());
    
} // MainWindow destructor

void MainWindow::centerWidget(QWidget *w, bool useSizeHint)
{
	if (w->isFullScreen())
		return;

	QSize size;
	if (useSizeHint)
		size = w->sizeHint();
	else
		size = w->size();

	QDesktopWidget *d = QApplication::desktop();
	int ws = d->width();   // returns screen width
	int h = d->height();  // returns screen height
	int mw = size.width();
	int mh = size.height();
	int cw = (ws / 2) - (mw / 2);
	int ch = (h / 2) - (mh / 2);
	w->move(cw, ch);
}

void MainWindow::loadPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances())
    populateMenus(plugin);
    
    pluginsDir = QDir(qApp->applicationDirPath());
    
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    pluginsDir.cd("Debug");
    
    qDebug() << pluginsDir;
    
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        qDebug() << pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            populateMenus(plugin);
            pluginFileNames += fileName;
        }
    }
    
    drawingToolsMenu->setEnabled(!drawingToolsActionGroup->actions().isEmpty());
    actionsMenu->setEnabled(!actionsMenu->actions().isEmpty());
}

void MainWindow::populateMenus(QObject *plugin)
{
    DrawingToolsInterface *iDrawingTools = qobject_cast<DrawingToolsInterface *>(plugin);
    if (iDrawingTools)
        addToMenu(plugin, iDrawingTools->drawingTools(), drawingToolsMenu, SLOT(changeDrawingTools()), drawingToolsActionGroup);
    
    ActionInterface *iAction = qobject_cast<ActionInterface *>(plugin);
    if (iAction) {
        iAction->setQStackedWidget(actionWidgetStack);
        actionsMenu->addAction(iAction->getQAction());
    }
    
}

void MainWindow::addToMenu(QObject *plugin, const QStringList &texts,
                           QMenu *menu, const char *member,
                           QActionGroup *actionGroup)
{
    foreach (QString text, texts) {
        
        QAction *action = new QAction(text, plugin);
        connect(action, SIGNAL(triggered()), this, member);
        menu->addAction(action);
        
        if (actionGroup) {
            action->setCheckable(true);
            actionGroup->addAction(action);
        }
    }
}

// Todo
void MainWindow::applyFilter()
{
    //QAction *action = qobject_cast<QAction *>(sender());
    //FilterInterface *iFilter =
    //qobject_cast<FilterInterface *>(action->parent());
    
    
    qDebug() << "apply filter called";
    
    //const QImage image = iFilter->filterImage(action->text(), paintArea->image(),
    //                                          this);
    //paintArea->setImage(image);
}

void MainWindow::changeDrawingTools()
{
    // Change the current drawing tool
    
    QAction *action = qobject_cast<QAction *>(sender());
    DrawingToolsInterface *iDrawingTools = qobject_cast<DrawingToolsInterface *>(action->parent());
    const QString drawingTools = action->text();
    
    qDebug() << "Change the current drawing tool to" << drawingTools;
    
    captureManager->paintArea1->setDrawingsTool(iDrawingTools, drawingTools);
}

void MainWindow::notifyParametersChanged(const QStringList & paramChanged)
{
	//Selective update (to not update all objects for a simple camera's parameter modification)
	for (QStringList::const_iterator iter = paramChanged.begin(); iter != paramChanged.end(); ++iter)
	{
		qDebug() << "Parameter changed:" << iter->toStdString().c_str();
	}
}

void MainWindow::actionSaveParameters()
{
	// Save settings to config.ini in current working directory
	Settings::saveSettings(Settings::iniDefaultPath(), this->saveGeometry(), this->saveState());
}

void MainWindow::onPlay()
{
    playButton->setDisabled(true);
    iTimer = new QTimer(this);
    connect(iTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
    isPlaying = true;
    qDebug("Playing CaptureManager with Fps = %d", captureManager->fps);
    iTimer->start(1000 / 15);
} // onPlay()

void MainWindow::onStop()
{
    // Update GUI
    if(captureManager->frameCount != bookPositionSlider->maximum()) {
        
        bookPositionSlider->setMinimum(0);
        bookPositionSlider->setMaximum(captureManager->frameCount);
    }
    
    if (isPlaying)
    {
        playButton->setDisabled(false);
        isPlaying = false;
        iTimer->stop();
    }
    else if (captureManager->SetPos(0))
    {
        onNavigate();
        bookPositionSlider->setValue(captureManager->GetPos());
    }
} // onStop()

void MainWindow::onPrev()
{
    // Update GUI
    if(captureManager->frameCount != bookPositionSlider->maximum()) {
        
        bookPositionSlider->setMinimum(0);
        bookPositionSlider->setMaximum(captureManager->frameCount);
    }
    
    if (captureManager->OnPrev())
    {
        onNavigate();
        bookPositionSlider->setValue(captureManager->GetPos());
    }
} // onPrev()

void MainWindow::onNext()
{
    // Update GUI
    if(captureManager->frameCount != bookPositionSlider->maximum()) {
        
        bookPositionSlider->setMinimum(0);
        bookPositionSlider->setMaximum(captureManager->frameCount);
    }
    
    if (captureManager->OnNext())
    {
        onNavigate();
        bookPositionSlider->setValue(captureManager->GetPos());
    }
} // onNext()

void MainWindow::onScroll()
{
    // Update GUI
    if(captureManager->frameCount != bookPositionSlider->maximum()) {
        
        bookPositionSlider->setMinimum(0);
        bookPositionSlider->setMaximum(captureManager->frameCount);
    }
    
    // Update book postion label
    bookPositionLabel->setText(QString("%1/%2").arg(bookPositionSlider->value()).arg(captureManager->frameCount));
    
    if (captureManager->SetPos(bookPositionSlider->value()))
        onNavigate();
} // onScroll()

void MainWindow::onNavigate()
{
    int pos = captureManager->GetPos();
    if (pos == 0)
        prevButton->setDisabled(true);
    else
        prevButton->setDisabled(false);
    if (pos == captureManager->frameCount - 1) // last frame is not valid
        nextButton->setDisabled(true);
    else
        nextButton->setDisabled(false);
}

void MainWindow::onTimer()
{
    if (isPlaying)
    {
        if (nextButton->isEnabled())
            onNext();
        else
        {
            onStop();
            if (captureManager->SetPos(0))
            {
                onNavigate();
                bookPositionSlider->setValue(captureManager->GetPos());
            }
        }
    }
    else
    {
        return;
    }
}

void MainWindow::zoomIn()
{
    paintArea1->zoomIn();
    paintArea2->zoomIn();
}

void MainWindow::zoomOut()
{
    paintArea1->zoomOut();
    paintArea2->zoomOut();
}

void MainWindow::zoomFullSize()
{
    paintArea1->zoomFullSize();
    paintArea2->zoomFullSize();
}

void MainWindow::toggleLiveViewMode(bool separateMode)
{
    liveViewDialog = new LiveViewDialog(this);
    QPalette m_pal(palette());
    // set black background
    m_pal.setColor(QPalette::Background, Qt::black);
    liveViewDialog->setAutoFillBackground(true);
    liveViewDialog->setPalette(m_pal);
    liveViewDialog->show();
}

bool MainWindow::saveAs()
{
    const QString initialPath = QDir::currentPath() + "/untitled.png";
    
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                          initialPath);
    if (fileName.isEmpty()) {
        return false;
    } else {
        return captureManager->paintArea1->saveImage(fileName, "png");
    }
}
