
#pragma once
#ifndef UTIL_H
#define UTIL_H

// OpenCV header files
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
// Qt header files
#include <QVector>
#include <QPoint>
#include <QStringList>
#include <QThread>

using namespace cv;
using namespace std;

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

void setContrastBrightness(const Mat& src, Mat& dst, int _contrast=100, int _brightness=100);

QVector<QPoint> PointToQPoint(const vector<Point2f> &src);

Point2f getCentroidFromSetPoints(vector<Point2f> points);

QStringList stdListStringToQStringList(const std::list<std::string> & stringList);

void shiftPoints(const QVector<QPoint> &inputArrayPoints, const Point2f &inputOffset, QVector<QPoint> &outputArrayPoints);

void shiftImg(const cv::Mat& src, cv::Mat& dst, cv::Point2f delta, int fill=cv::BORDER_CONSTANT, cv::Scalar value=cv::Scalar(0,0,0,0));

void overlapImg(const cv::Mat& img1, const cv::Mat& img2, cv::Mat& dst);

vector<Point2f> Read2DPoints(const string& filename);

vector<Point3f> Read3DPoints(const string& filename);

#endif // UTIL_H
