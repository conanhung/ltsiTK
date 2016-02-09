
#include <QtGui>
#include <QMessageBox>

#include <math.h>
#include <stdlib.h>

#include "CaptureManager.h"
#include "Controller.h"
#include "ImageConversion.h"
#include "ImagesAcquisitionPlugin.h"

using namespace cv;
using namespace std;

// ------------- WorkerThread for the acquisition --------------

Worker::Worker(const QString &fn, QObject *parent) : QObject(parent), totalImages(0)
{
    _working = false;
    _abort = false;
    videoPath = fn;
}

Worker::~Worker()
{
    
}

void Worker::doWork()
{
    // Check if videoPath contains a number
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(videoPath))
        cap.open(videoPath.toInt());
    else
        cap.open(videoPath.toStdString());
    
    if(!cap.isOpened()) {  // check if we succeeded
        mutex.lock();
        _abort = true;
        mutex.unlock();
    }
    
    for (;;)
    {
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();
        
        if (abort) {
            break;
        }
        
        // get image
        cap >> img;
        if (!img.empty()) {
            //qDebug() << "Got new image";
            emit gotNewImage();
        }
        
        // wait 10ms
        QEventLoop loop;
        QTimer::singleShot(10, &loop, SLOT(quit()));
        loop.exec();
    }
    
    mutex.lock();
    _working = false;
    mutex.unlock();
    
    emit finished();
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug() << "Request worker start in Thread " << thread()->currentThreadId();
    mutex.unlock();
    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug() << "Request worker aborting in Thread " << thread()->currentThreadId();
    }
    mutex.unlock();
}

Mat Worker::getLastFrame()
{
    return img;
}

// -----------------  ImagesAcquisitionPlugin -------------------

ImagesAcquisitionPlugin::ImagesAcquisitionPlugin() : ActionInterface()
{
    setName("Images Acquisition");
    setDescription("Load images from capture devices or from files");
    
    theWidget = NULL;
    frameCount = 0;
}

ImagesAcquisitionPlugin::~ImagesAcquisitionPlugin()
{
    // Check if camera is connected
    if (controller->captureThread->isCameraConnected())
    {
        disconnect(controller->processingThread, SIGNAL(newFrame( QImage )), this, SLOT(slotGotNewImage( QImage )));
        disconnect(this, SIGNAL(newAcquisitionFlag( bool )), controller->processingThread, SLOT(updateAcquisitionFlag( bool )));
        disconnect(this, SIGNAL(newAcquisitionFolder( QString )), controller->processingThread, SLOT(updateAcquisitionFolder( QString )));
        
        // Disconnect camera
        controller->disconnectCamera();
    }
    // Display error dialog
    else
        qDebug() << "Camera already disconnected.";
    
    delete controller;
}

void ImagesAcquisitionPlugin::init()
{
    theWidget = new QWidget();
    ui.setupUi(theWidget);
    
    // Create controller
    controller = new Controller;
    
    connect(ui.connectPushButton, SIGNAL(clicked(bool)), this, SLOT(connectToCamera(bool)));
    connect(ui.startPushButton, SIGNAL(released()), this, SLOT(startAcquisition()));
    connect(ui.stopPushButton, SIGNAL(released()), this, SLOT(stopAcquisition()));
    connect(ui.loadFilesButton, SIGNAL(released()), this, SLOT(loadFiles()));
    connect(ui.acquisitionDirsListWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updateCaptureManager(QListWidgetItem *)));
    
    isAcquiring = false;
    
    acquisitionFolder = QDir(qApp->applicationDirPath());
    acquisitionFolder.cd("acquisition");
    
    updateAcquisitionDirsList();
}

QWidget * ImagesAcquisitionPlugin::getWidget()
{
    if (!theWidget)
        init();
    
    return theWidget;
}

ActionInterface::ApplyStatus ImagesAcquisitionPlugin::apply()
{
    return SUCCESS;
}

void ImagesAcquisitionPlugin::createAcquisitionFolder(QDir &folder)
{
    // Save images to the acquisition folder
    if(QDir("acquisition").exists())
        qDebug() << "Acquisition folder is existing";
    else if(QDir().mkdir("acquisition"))
        qDebug() << "Acquisition folder is created";
    
    // Get current date and time
    time_t t = time(0);   // get time now
    struct tm * now = localtime(&t);
    
    QString currentDateTime;
    currentDateTime = QString("%1_%2_%3_%4_%5_%6").arg(now->tm_year + 1900).arg(now->tm_mon + 1,2,'f',0,'0').arg(now->tm_mday,2,'f',0,'0').arg(now->tm_hour,2,'f',0,'0').arg(now->tm_min,2,'f',0,'0').arg(now->tm_sec,2,'f',0,'0');
    
    QDir currentAcquisitionFolder = acquisitionFolder;
    
    if(!currentAcquisitionFolder.exists(QString(currentDateTime)))
        currentAcquisitionFolder.mkdir(QString(currentDateTime));
    
    currentAcquisitionFolder.cd(QString(currentDateTime));
    
    folder = currentAcquisitionFolder;
    
    qDebug() << "Images will be saved to" << folder.absolutePath();
}

void ImagesAcquisitionPlugin::connectToCamera(bool isConnecting)
{
    if(isConnecting)
    {
        // Connect to camera
        qDebug() << "Connect to the camera";
        
        videoPath = ui.videoPathLineEdit->text();
        //videoPath = "/Users/longhung/dev/test/data/helma_deploy.mov";
        
        qDebug() << videoPath;
        
        if ((controller->connectToCamera(videoPath, 10, false, QThread::HighPriority, QThread::HighPriority)))
        {
            connect(controller->processingThread, SIGNAL(newFrame( QImage )), this, SLOT(slotGotNewImage( QImage )));
            connect(this, SIGNAL(newAcquisitionFlag( bool )), controller->processingThread, SLOT(updateAcquisitionFlag( bool )));
            connect(this, SIGNAL(newAcquisitionFolder( QString )), controller->processingThread, SLOT(updateAcquisitionFolder( QString )));
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            qDebug() << "Could not connect to camera.";
        }
    }
    else {
        // Check if camera is connected
        if (controller->captureThread->isCameraConnected())
        {
            disconnect(controller->processingThread, SIGNAL(newFrame( QImage )), this, SLOT(slotGotNewImage( QImage )));
            disconnect(this, SIGNAL(newAcquisitionFlag( bool )), controller->processingThread, SLOT(updateAcquisitionFlag( bool )));
            disconnect(this, SIGNAL(newAcquisitionFolder( QString )), controller->processingThread, SLOT(updateAcquisitionFolder( QString )));
            
            // Disconnect camera
            controller->disconnectCamera();
        }
        // Display error dialog
        else
            qDebug() << "Camera already disconnected.";
    }
}

void ImagesAcquisitionPlugin::startAcquisition()
{
    qDebug() << "Start acquisition";
    
    // Reset the frame counter
    frameCount = 0;
    
    // Create acsuisition folder
    QDir currentAcquisitionFolder;
    createAcquisitionFolder(currentAcquisitionFolder);
        
    isAcquiring = true;
    emit newAcquisitionFlag(isAcquiring);
    emit newAcquisitionFolder(currentAcquisitionFolder.absolutePath());
}

void ImagesAcquisitionPlugin::stopAcquisition()
{
    qDebug() << "Stop acquisition";
    
    isAcquiring = false;
    emit newAcquisitionFlag(isAcquiring);
    
    updateAcquisitionDirsList();
}

void ImagesAcquisitionPlugin::slotGotNewImage(const QImage &frame)
{
    // Got new image
    ImagePlus newImage(frame);
    CaptureManager::SetLiveImage(newImage);
    
    // Update statistics
    int frameRate = controller->processingThread->getAvgFPS();
    QSize frameSize = controller->processingThread->getFrameSize();
    int bufferStatus = controller->processingThread->getCurrentSizeOfBuffer();
    
    ui.frameRateLabel->setText(QString::number(frameRate));
    ui.frameSizeLabel->setText(QString("%1x%2").arg(frameSize.width()).arg(frameSize.height()));
    ui.bufferProgressBar->setMaximum(10);
    ui.bufferProgressBar->setMinimum(0);
    ui.bufferProgressBar->setValue(bufferStatus);
}

void ImagesAcquisitionPlugin::loadFiles(void)
{
    QString fileName = QFileDialog::getOpenFileName();
    ui.videoPathLineEdit->setText(fileName);
}

void ImagesAcquisitionPlugin::updateAcquisitionDirsList()
{
    acquisitionDirsList.clear();
    
    QDirIterator directories(acquisitionFolder.absolutePath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    
    while(directories.hasNext()){
        directories.next();
        acquisitionDirsList << directories.fileName();
    }
    
    ui.acquisitionDirsListWidget->clear();
    ui.acquisitionDirsListWidget->addItems(acquisitionDirsList);
}

void ImagesAcquisitionPlugin::updateCaptureManager(QListWidgetItem *item)
{
    qDebug() << "Update capture Manager called";
    qDebug() << item->text();
    
    QString choosenDir = item->text();
    
    QDir currentAcquisitionDir = acquisitionFolder;
    currentAcquisitionDir.cd(choosenDir);
    
    // Read all image files in the selected folder
    QStringList imgFiles;
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    imgFiles = currentAcquisitionDir.entryList(filters, QDir::Files|QDir::NoDotAndDotDot);
    
    //for(int i = 0; i < imgFiles.size(); i++)
    //    qDebug() << imgFiles.at(i);
    
    CaptureManager::LoadImages(currentAcquisitionDir.absolutePath(), imgFiles);
}



Q_EXPORT_PLUGIN2(imagesacquisition, ImagesAcquisitionPlugin)
