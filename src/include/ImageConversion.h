
#ifndef IMAGECONVERSION_H
#define IMAGECONVERSION_H

// Qt header files
#include <QtGui>
#include <QDebug>
// OpenCV header files
#include <opencv2/opencv.hpp>

class ImageConversion
{
    
public:
    
    static QImage MatToQImage(const cv::Mat& mat);
    
    static cv::Mat qimage_to_mat_ref(QImage &img, int format);
    
    /**
     *@brief transform QImage to cv::Mat by sharing the buffer
     *@param img : input image
     *@param swap : true : swap RGB to BGR; false, do nothing
     */
    static cv::Mat QImageToMat(QImage &img, bool swap = true);
    
};

#endif // IMAGECONVERSION_H
