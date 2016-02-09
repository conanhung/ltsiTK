
#ifndef CAPTUREMANAGER_H
#define CAPTUREMANAGER_H

// Qt header files
#include <QtGui>
#include <QDebug>
#include <QMutex>
#include <QQueue>
#include <QSemaphore>
#include <QObject>
#include <QVector>

#include <iostream>

#include "Util.h"
#include "ImageConversion.h"
#include "ImagePlus.h"
#include "PaintArea.h"

#ifndef CAPTUREMANAGER_API_H
#define CAPTUREMANAGER_API_H

#if defined(_WIN32) // MSVC and mingw
#ifdef COMPILE_CAPTUREMANAGER_API
#define CAPTUREMANAGER_API __declspec(dllexport)
#else
#define CAPTUREMANAGER_API __declspec(dllimport)
#endif
#else
// for all other platforms CAMITK_API is defined to be "nothing"
#ifndef CAPTUREMANAGER_API
#define CAPTUREMANAGER_API
#endif
#endif // MSVC and mingw

#if defined(_WIN32) && !defined(__MINGW32__) // MSVC only
#pragma warning( disable : 4290 )
#endif // MSVC only

#endif // CAPTUREMANAGER_API_H

using namespace std;

class CAPTUREMANAGER_API CaptureManager :  public QObject
{
    Q_OBJECT // Enable slots and signals
    
public:
    
    static QList<ImagePlus> getBook();
    static QStringList getBookList();
    static ImagePlus getImg();
    
    virtual ~CaptureManager();
    CaptureManager();
    
    void Reset();

    int GetFrameCount();
    QSize GetSize();
    static int GetPos();
    static bool SetPos(int newpos, bool reload=false);
    bool OnPrev();
    bool OnNext();
    static void PushbackCurrentFrame();
    static void ReloadCurrentFrame(bool redraw=true);
    void ReloadCurrentFrameOverlay(bool redraw=true);
    static void Redraw();
    static void SetImage(const ImagePlus &inputImage);
    static void SetLiveImage(const ImagePlus &inputImage);
    static void SetImage(const QImage &inputImage);
    static void LoadImages(const QString &inputAcquisitionDir, const QStringList &inputFiles);
    
    static bool addLine(const QLine &inputLine);
    static bool addPoint(const QPoint &inputPoint);
    static bool addRect(const QRect &inputRect);
    static bool addPolygon(const QPolygon &inputPolygon);
    
    static bool replaceLine(int index, const QLine &inputLine);
    static bool replacePoint(int index, const QPoint &inputPoint);
    static bool replaceRect(int index, const QRect &inputRect);
    static bool replacePolygon(int index, const QPolygon &inputPolygon);
    
    static bool removeLine(int index);
    static bool removePoint(int index);
    static bool removeRect(int index);
    static bool removePolygon(int index);
    
    void Clear();
	void SetRoi(const Point2f inputROI[]);
	void GetRoi(Point2f outputROI[]);
	void ClearRoi();
    
	static bool useVirtualStack;

public:
    static PaintArea *paintArea1;
    static PaintArea *paintArea2;
    static QList<ImagePlus> book;
    static ImagePlus img;
	static QStringList bookList;
    static int frameCount;
    static int fps;
    static int pos;
    static QSize size;
};


#endif // CAPTUREMANAGER_H