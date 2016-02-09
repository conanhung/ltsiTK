
#include "ImagePlus.h"
#include "ImageConversion.h"

ImagePlus::ImagePlus()
{
    opacity = 100;
}

ImagePlus::~ImagePlus(void)
{
    ReleaseAll();
}

ImagePlus::ImagePlus(QImage inputImg)
{
    original = inputImg;
}

ImagePlus::ImagePlus(const ImagePlus &copy)
{
    ReleaseAll();
    original = copy.original;
    overlay = copy.overlay;
    lines = copy.lines;
    points = copy.points;
    rects = copy.rects;
    polygons = copy.polygons;
}

ImagePlus & ImagePlus::operator = (const ImagePlus &copy)
{
	ReleaseAll();
    original = copy.original;
    overlay = copy.overlay;
    lines = copy.lines;
    points = copy.points;
    rects = copy.rects;
    polygons = copy.polygons;
    
	return *this;
}

void ImagePlus::ReleaseAll()
{
    overlay = QImage();
    lines.clear();
    points.clear();
    rects.clear();
    polygons.clear();
}

bool ImagePlus::setImage(const cv::Mat &inputImage)
{
    original = ImageConversion::MatToQImage(inputImage);
    
    return true;
}

bool ImagePlus::setImage(const QImage &inputImage)
{
    original = inputImage;
    
    return true;
}

bool ImagePlus::addLine(const QLine &inputLine)
{
    lines.push_back(inputLine);
    
    return true;
}

bool ImagePlus::addPoint(const QPoint &inputPoint)
{
    points.push_back(inputPoint);
    
    return true;
}

bool ImagePlus::addRect(const QRect &inputRect)
{
    rects.push_back(inputRect);
    
    return true;
}

bool ImagePlus::addPolygon(const QPolygon &inputPolygon)
{
    polygons.push_back(inputPolygon);
    
    return true;
}

bool ImagePlus::replaceLine(int index, const QLine &inputLine)
{
    lines.replace(index, inputLine);
    return true;
}

bool ImagePlus::replacePoint(int index, const QPoint &inputPoint)
{
    points.replace(index, inputPoint);
    return true;
}

bool ImagePlus::replaceRect(int index, const QRect &inputRect)
{
    rects.replace(index, inputRect);
    return true;
}

bool ImagePlus::replacePolygon(int index, const QPolygon &inputPolygon)
{
    polygons.replace(index, inputPolygon);
    return true;
}


bool ImagePlus::removeLine(int index)
{
    lines.removeAt(index);
    return true;
}

bool ImagePlus::removePoint(int index)
{
    points.removeAt(index);
    return true;
}

bool ImagePlus::removeRect(int index)
{
    rects.removeAt(index);
    return true;
}

bool ImagePlus::removePolygon(int index)
{
    polygons.removeAt(index);
    return true;
}