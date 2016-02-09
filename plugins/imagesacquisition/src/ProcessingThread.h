
#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <iostream>
#include <sstream>

// Qt header files
#include <QThread>
#include <QtGui>
// OpenCV header files
#include <opencv/highgui.h>

// FPS statistics queue lengths
#define DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH 32
#define DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH 32

using namespace cv;

class ImageBuffer;

class ProcessingThread : public QThread
{
	Q_OBJECT

public:
	ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight);
	~ProcessingThread();
	void stopProcessingThread();
	int getAvgFPS();
	QSize getFrameSize();
	int getCurrentSizeOfBuffer();

private:
	void updateFPS(int);
	ImageBuffer *imageBuffer;
	volatile bool stopped;
	int inputSourceWidth;
	int inputSourceHeight;
	int currentSizeOfBuffer;
	Mat currentFrame;
	QImage frame;
	QTime t;
	int processingTime;
	QQueue<int> fps;
    int frames;
	int fpsSum;
	int sampleNo;
	int avgFPS;
	QMutex stoppedMutex;
	QMutex updateMembersMutex;
	QSize frameSize;
    
    // For images acquisition
    bool isAcquiring;
    QString acquisitionFolder;

protected:
	void run();

private slots:
	void updateAcquisitionFlag(bool isAcquiring);
    void updateAcquisitionFolder(QString folder);

signals:
	void newFrame(const QImage &frame);
};

#endif // PROCESSINGTHREAD_H
