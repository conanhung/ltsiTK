
#ifndef IMAGESACQUISITIONPLUGIN_H
#define IMAGESACQUISITIONPLUGIN_H

// Qt
#include <QObject>
#include <QStringList>
#include <QImage>
#include <QMutex>
#include <QWidget>
#include <QDir>

// OpenCV
#include "opencv2/opencv.hpp"

#include "interfaces.h"
#include "ui_ImagesAcquisition.h"

class Controller;

// WorkerThread for the acquisition
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(const QString &fn, QObject *parent = 0);
    ~Worker();
    
    void requestWork();
    void abort();
    
    int totalImages;
    
    cv::Mat getLastFrame();
    
private:
    bool _working;
    bool _abort;
    QMutex mutex;
    
    cv::VideoCapture cap;
    cv::Mat img;
    QString videoPath;
    
public slots:
    void doWork();
    
signals:
    void workRequested();
    void finished();
    void gotNewImage();
};

// ImagesAcquisitionPlugin

class ImagesAcquisitionPlugin : public ActionInterface
{
    Q_OBJECT
    Q_INTERFACES(ActionInterface)

public:
    
    ImagesAcquisitionPlugin();
    ~ImagesAcquisitionPlugin();
    
    virtual QWidget * getWidget();
    
private:
    void init();
    void createAcquisitionFolder(QDir &folder);
    void updateAcquisitionDirsList();
    
    QString videoPath;
    QDir acquisitionFolder;
    QStringList acquisitionDirsList;
    int frameCount;
    bool isAcquiring;
    
    Controller * controller;
    
    // Image acquisition thread
    QThread * workerThread;
    Worker * worker;
    
public slots:
    /** this method is automatically called when the action is triggered.
     * Use getTargets() QList to get the list of component to use.
     * \note getTargets() is automatically filtered so that it only contains compatible components,
     * i.e., instances of ImageComponent (or a subclass).
     */
    virtual ApplyStatus apply();
    
    void connectToCamera(bool);
    void startAcquisition(void);
    void stopAcquisition(void);
    void loadFiles(void);
    void slotGotNewImage(const QImage &frame);
    void updateCaptureManager(QListWidgetItem *item);
    
protected:
    Ui::ImagesAcquisitionPluginWidget ui;
    QWidget * theWidget;
    
signals:
    void newAcquisitionFlag(bool isAcquiring);
    void newAcquisitionFolder(QString folder);
};

#endif // IMAGESACQUISITIONPLUGIN_H
