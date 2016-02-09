
#include "ImageBuffer.h"
#include "ImageConversion.h"
#include "ProcessingThread.h"

// Qt header files
#include <QDebug>
// OpenCV header files
#include <opencv/cv.h>
#include <opencv/highgui.h>

ProcessingThread::ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight) : QThread(),
    imageBuffer(imageBuffer),
    inputSourceWidth(inputSourceWidth),
    inputSourceHeight(inputSourceHeight)
{
    // Initialize variables
    frames = 0;
    stopped = false;
    sampleNo = 0;
    fpsSum = 0;
    avgFPS = 0;
    fps.clear();
    isAcquiring = false;
} // ProcessingThread constructor

ProcessingThread::~ProcessingThread()
{
    
} // ProcessingThread destructor

void ProcessingThread::run()
{
    while (1)
    {
        /////////////////////////////////
        // Stop thread if stopped=TRUE //
        /////////////////////////////////
STOPPROCESSINGTHREAD:
        stoppedMutex.lock();
        if (stopped)
        {
            stopped = false;
            stoppedMutex.unlock();
            break;
        }
        stoppedMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        // Save processing time
        processingTime = t.elapsed();
        // Start timer (used to calculate processing rate)
        t.start();
        
        // Get images
        imageBuffer->getFrame().copyTo(currentFrame);

        // stop acquire if there is no image
        if (currentFrame.rows == 3 && currentFrame.cols == 3)
        {
            stopped = true;
            goto STOPPROCESSINGTHREAD;
        }
        
        // set frame size
        frameSize = QSize(currentFrame.cols, currentFrame.rows);

        updateMembersMutex.lock();
        ///////////////////
        // PERFORM TASKS //
        ///////////////////

        ////////////////////////
        // Pre-processing here
        ////////////////////////

        ////////////////////////
        // Pre-processing end
        ////////////////////////

        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING BELOW //
        ////////////////////////////////////
        
        if( isAcquiring )
            qDebug() << "isAcquiring on";
        
        if( isAcquiring) {
            
            frames++;
            
            // Save image to the acquisition folder
            QString acquisitionDir = acquisitionFolder;
            QString fn = acquisitionDir + QString("/%1.png").arg(frames,5,'f',0,'0');
            
            qDebug() << fn;
            
            frame.save(fn);
        }
        
        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING ABOVE //
        ////////////////////////////////////

        updateMembersMutex.unlock();

        // Update statistics
        updateFPS(processingTime);
        currentSizeOfBuffer = imageBuffer->getSizeOfImageBuffer();
        // Inform GUI thread of new frame
        frame = ImageConversion::MatToQImage(currentFrame);
        emit newFrame(frame);
    }
    qDebug() << "Stopping processing thread...";
}

void ProcessingThread::updateFPS(int timeElapsed)
{
    // Add instantaneous FPS value to queue
    if (timeElapsed > 0)
    {
        fps.enqueue((int)1000 / timeElapsed);
        // Increment sample number
        sampleNo++;
    }
    // Maximum size of queue is DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH
    if (fps.size() > DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH)
        fps.dequeue();
    // Update FPS value every DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH samples
    if ((fps.size() == DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH) && (sampleNo == DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH))
    {
        // Empty queue and store sum
        while (!fps.empty())
            fpsSum += fps.dequeue();
        // Calculate average FPS
        avgFPS = fpsSum / DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH;
        // Reset sum
        fpsSum = 0;
        // Reset sample number
        sampleNo = 0;
    }
} // updateFPS()

void ProcessingThread::stopProcessingThread()
{
    stoppedMutex.lock();
    stopped = true;
    stoppedMutex.unlock();
} // stopProcessingThread()

int ProcessingThread::getAvgFPS()
{
    return avgFPS;
}

QSize ProcessingThread::getFrameSize()
{
    return frameSize;
}

int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
}

void ProcessingThread::updateAcquisitionFlag(bool isAcquiring)
{
    QMutexLocker locker(&updateMembersMutex);
    this->isAcquiring = isAcquiring;
}

void ProcessingThread::updateAcquisitionFolder(QString folder)
{
    QMutexLocker locker(&updateMembersMutex);
    this->acquisitionFolder = folder;
}
