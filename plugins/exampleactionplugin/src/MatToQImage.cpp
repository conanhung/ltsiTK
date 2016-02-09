
#include "MatToQImage.h"

QImage MatToQImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
} // MatToQImage()

/**
 *@brief transform QImage to cv::Mat by sharing the buffer
 *@param img : input image
 *@param swap : true : swap RGB to BGR; false, do nothing
 */
cv::Mat QImageToMatRef(QImage &img, bool swap)
{
    if(img.isNull()){
        return cv::Mat();
    }
    
    switch (img.format()) {
        case QImage::Format_RGB888:{
            auto result = QImageToMatRef(img, CV_8UC3);
            if(swap){
                cv::cvtColor(result, result, CV_RGB2BGR);
            }
            return result;
        }
        case QImage::Format_Indexed8:{
            return QImageToMatRef(img, CV_8U);
        }
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:{
            return QImageToMatRef(img, CV_8UC4);
        }
        default:
            break;
    }
    
    return Mat();
}

/**
 *@brief transform QImage to cv::Mat by copy QImage to cv::Mat
 *@param img : input image
 *@param swap : true : swap RGB to BGR; false, do nothing
 */
cv::Mat QImageToMatCopy(QImage const &img, bool swap)
{
    return QImageToMatRef(const_cast<QImage&>(img), swap).clone();
}