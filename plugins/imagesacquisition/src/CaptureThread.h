
#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

// Qt header files
#include <QThread>
#include <QtGui>
// OpenCV header files
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class ImageBuffer;
class Controller;

class CaptureThread : public QThread
{
	Q_OBJECT

public:
	CaptureThread(ImageBuffer *buffer);
	bool connectToCamera(QString inputVideoPath);
	void disconnectCamera();
	void stopCaptureThread();
	int getAvgFPS();
	bool isCameraConnected();
	int getInputSourceWidth();
	int getInputSourceHeight();
private:
	void updateFPS(int);
	ImageBuffer *imageBuffer;
	VideoCapture cap;
	Mat grabbedFrame;
	QTime t;
	QMutex stoppedMutex;
	int captureTime;
	int avgFPS;
	QQueue<int> fps;
    QString videoPath;
	int sampleNo;
	int fpsSum;
	volatile bool stopped;
protected:
	void run();
};

#endif // CAPTURETHREAD_H
