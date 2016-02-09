/************************************************************************/
/* tavi-tracking:                                                       */
/* A multithreaded OpenCV application using the Qt framework.           */
/* An object tracking for TAVI Imaging-guided.                          */
/*                                                                      */
/* DucLongHung NGUYEN <duclonghung.nguyen@gmail.com>                    */
/*                                                                      */
/* Copyright (c) 2012 DucLongHung NGUYEN                                */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CaptureThread.h"
#include "ProcessingThread.h"

// Qt header files
#include <QtGui>
// OpenCV header files
#include <opencv/highgui.h>

class ImageBuffer;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();
    ImageBuffer *imageBuffer;
    ProcessingThread *processingThread;
    CaptureThread *captureThread;
    bool connectToCamera(QString,int,bool,int,int);
    void disconnectCamera();
    void stopCaptureThread();
    void stopProcessingThread();
    void deleteCaptureThread();
    void deleteProcessingThread();
    void clearImageBuffer();
    void deleteImageBuffer();
private:
    int imageBufferSize;
};

#endif // CONTROLLER_H
