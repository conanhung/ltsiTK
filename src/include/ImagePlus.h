
#ifndef IMAGEPLUS_H
#define IMAGEPLUS_H

// Qt header files
#include <QImage>
#include <QDebug>
#include <QList>
#include <QLine>
#include <QPoint>
#include <QRect>
#include <QPolygon>
// OpenCV header files
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QVector>

using namespace cv;

class ImagePlus
{
public:
    QImage original;
    QImage overlay;
    
    QList<QLine> lines;
    QList<QPoint> points;
    QList<QRect> rects;
    QList<QPolygon> polygons;
    
    int opacity;
    
    ImagePlus();
    ~ImagePlus();
    
    ImagePlus(QImage inputImg);
    // copy constructor
    ImagePlus(const ImagePlus &copy);
    // assignment operator
    ImagePlus & operator = (const ImagePlus &copy);
    
    bool setImage(const Mat &inputImage);
    bool setImage(const QImage &inputImage);
    
    bool addLine(const QLine &inputLine);
    bool addPoint(const QPoint &inputPoint);
    bool addRect(const QRect &inputRect);
    bool addPolygon(const QPolygon &inputPolygon);
    
    bool replaceLine(int index, const QLine &inputLine);
    bool replacePoint(int index, const QPoint &inputPoint);
    bool replaceRect(int index, const QRect &inputRect);
    bool replacePolygon(int index, const QPolygon &inputPolygon);
    
    bool removeLine(int index);
    bool removePoint(int index);
    bool removeRect(int index);
    bool removePolygon(int index);
    
    void ReleaseAll();
};

#endif // IMAGEPLUS_H
