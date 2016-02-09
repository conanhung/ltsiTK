
#include "CaptureThread.h"
#include "ImageBuffer.h"
#include "Controller.h"

// Qt header files
#include <QDebug>

CaptureThread::CaptureThread(ImageBuffer *imageBuffer) : QThread(),
	imageBuffer(imageBuffer)
{
	// Initialize variables
	stopped=false;
	sampleNo=0;
	fpsSum=0;
	avgFPS=0;
    videoPath = "-1"; // any device
	fps.clear();
} // CaptureThread constructor

void CaptureThread::run()
{
	while(1)
	{
		/////////////////////////////////
		// Stop thread if stopped=TRUE //
		/////////////////////////////////
STOPCAPTURETHREAD:
		stoppedMutex.lock();
		if (stopped)
		{
			stopped=false;
			stoppedMutex.unlock();
			break;
		}
		stoppedMutex.unlock();
		/////////////////////////////////
		/////////////////////////////////
		// Save capture time
		captureTime=t.elapsed();
		// Start timer (used to calculate capture rate)
		t.start();
		// Capture and add frame to buffer
		cap >> grabbedFrame;

		if( grabbedFrame.empty() ){
            // Check if videoPath contains a number
            QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
            if (!re.exactMatch(videoPath)) {
                cap.open(videoPath.toStdString());
                cap >> grabbedFrame;
                printf("Repeat the video stream from file...\n");
            }
			else {
				imageBuffer->addFrame(Mat::zeros(3, 3, CV_32S)); // frame signal processing thread to exit
				stopped=true;
				goto STOPCAPTURETHREAD;
			}
		}

		imageBuffer->addFrame(grabbedFrame);
		// Update statistics
		updateFPS(captureTime);
		this->msleep(1000/15); // frame per second
	}
	qDebug() << "Stopping capture thread...";
} // run()

bool CaptureThread::connectToCamera(QString inputVideoPath)
{
    videoPath = inputVideoPath;
    // Check if videoPath contains a number
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(videoPath))
        return cap.open(videoPath.toInt());
    else
        return cap.open(videoPath.toStdString());
} // connectToCamera()

void CaptureThread::disconnectCamera()
{
	// Check if camera is connected
	if(cap.isOpened())
	{
		// Disconnect camera
		cap.release();
		qDebug() << "Camera successfully disconnected.";
	}
} // disconnectCamera()

void CaptureThread::updateFPS(int timeElapsed)
{
	// Add instantaneous FPS value to queue
	if(timeElapsed>0)
	{
		fps.enqueue((int)1000/timeElapsed);
		// Increment sample number
		sampleNo++;
	}
	// Maximum size of queue is DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH
	if(fps.size()>DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH)
		fps.dequeue();
	// Update FPS value every DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH samples
	if((fps.size()==DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH)&&(sampleNo==DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH))
	{
		// Empty queue and store sum
		while(!fps.empty())
			fpsSum+=fps.dequeue();
		// Calculate average FPS
		avgFPS=fpsSum/DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH;
		// Reset sum
		fpsSum=0;
		// Reset sample number
		sampleNo=0;
	}
} // updateFPS()

void CaptureThread::stopCaptureThread()
{
	stoppedMutex.lock();
	stopped=true;
	stoppedMutex.unlock();
} // stopCaptureThread()

int CaptureThread::getAvgFPS()
{
	return avgFPS;
} // getAvgFPS()

bool CaptureThread::isCameraConnected()
{
	if(cap.isOpened())
		return true;
	else
		return false;
} // isCameraConnected()

int CaptureThread::getInputSourceWidth()
{
	return cap.get(CV_CAP_PROP_FRAME_WIDTH);
} // getInputSourceWidth()

int CaptureThread::getInputSourceHeight()
{
	return cap.get(CV_CAP_PROP_FRAME_HEIGHT);
} // getInputSourceHeight()