
#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

// Qt header files
#include <QtGui>
#include <QDebug>
// OpenCV header files
#include <opencv2/opencv.hpp>

using namespace cv;

QImage MatToQImage(const Mat&);

cv::Mat QImageToMatCopy(QImage const &img, bool swap = true);

cv::Mat QImageToMatRef(QImage &img, bool swap = true);

#endif // MATTOQIMAGE_H
