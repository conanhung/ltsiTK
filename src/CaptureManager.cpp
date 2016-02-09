
#include <QProgressDialog>
#include "Settings.h"
#include "CaptureManager.h"

// For static variables
ImagePlus CaptureManager::img = ImagePlus();
QList<ImagePlus> CaptureManager::book;
PaintArea *CaptureManager::paintArea1;
PaintArea *CaptureManager::paintArea2;
QStringList CaptureManager::bookList;
int CaptureManager::frameCount = 0;
int CaptureManager::fps = 15;
int CaptureManager::pos = 0;
QSize CaptureManager::size = QSize(-1,-1);
bool CaptureManager::useVirtualStack = false;

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Build my CaptureManager object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CaptureManager::CaptureManager() : QObject()
{
	Reset();
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Destroy my CaptureManager object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CaptureManager::~CaptureManager()
{
	Reset();
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Reset all parameters of the book and free the memory
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CaptureManager::Reset()
{
	qDebug() << "Reset all book data";
	useVirtualStack=false;
    book.clear();
    img.ReleaseAll();
	frameCount = 0;
	fps = 0;
	pos = 0;
	size = QSize(0,0);
	bookList.clear();
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Get the number of frame in the book data
// Input:	nothing
// Output:	number of frame
////////////////////////////////////////////////////////////////////
int CaptureManager::GetFrameCount()
{
	return frameCount;
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Get the size of image in the book data
// Input:	nothing
// Output:	image size
////////////////////////////////////////////////////////////////////
QSize CaptureManager::GetSize()
{
	return size;
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Get the position of current image displayed in the canvas
// Input:	nothing
// Output:	index of image in the book data
////////////////////////////////////////////////////////////////////
int CaptureManager::GetPos()
{
	return pos;
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Jump to the image in the book data
// Input:	newpos : new index of image to be jumped
//			reload : reload the canvas or not
// Output:	return true if the process if successful
////////////////////////////////////////////////////////////////////
bool CaptureManager::SetPos(int newpos, bool reload)
{
	if (newpos<0 || newpos>=frameCount || (newpos==pos && !img.original.isNull() && !reload))
		return false;
	pos = newpos;
	ReloadCurrentFrame();
	return true;
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Back one image
// Input:	nothing
// Output:	return true if the process if successful
////////////////////////////////////////////////////////////////////
bool CaptureManager::OnPrev()
{
	return SetPos(pos-1);
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Next one image
// Input:	nothing
// Output:	return true if the process if successful
////////////////////////////////////////////////////////////////////
bool CaptureManager::OnNext()
{
	return SetPos(pos+1);
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Push back current image
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CaptureManager::PushbackCurrentFrame()
{
	book[pos] = img;
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Reload current frame
// Input:	redraw : redraw current frame
//			callPlugin : call the plugin if any
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CaptureManager::ReloadCurrentFrame(bool redraw)
{
	img=ImagePlus(book.at(pos));
    
	if (redraw)
		Redraw();
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Reload current frame contour
// Input:	redraw : redraw current frame
//			callPlugin : call the plugin if any
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CaptureManager::ReloadCurrentFrameOverlay(bool redraw)
{
    Redraw();
}

////////////////////////////////////////////////////////////////////
// Method:	CaptureManager
// Class:	CaptureManager
// Purose:	Redraw current frame
// Input:	callPlugin : call the plugin if any
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CaptureManager::Redraw()
{
    paintArea1->setImage(img);
}

void CaptureManager::SetImage(const ImagePlus &inputImage)
{
    img = inputImage;
    Redraw();
}

void CaptureManager::SetLiveImage(const ImagePlus &inputImage)
{
    paintArea2->setImage(inputImage);
}

void CaptureManager::SetImage(const QImage &inputImage)
{
    img.original = inputImage;
    Redraw();
}

void CaptureManager::LoadImages(const QString &inputAcquisitionDir, const QStringList &inputFiles)
{
    qDebug() << "Loading files..";
    
    int maxNumFrames = inputFiles.size();
    fps = 15;
    pos = 0;
    book.clear();
    bookList.clear();
    
    QProgressDialog progress("Loading files...", "Cancel", 0, frameCount);
    progress.setWindowModality(Qt::WindowModal);
    
    for(int i = 0; i < maxNumFrames; i++)
    {
        progress.setValue(i);
        
        if (progress.wasCanceled())
            break;
        
        QString currentFilePath = inputAcquisitionDir + "/" + inputFiles.at(i);
        bookList << currentFilePath;
        
        ImagePlus frame;
        frame.original.load(currentFilePath);
        book.push_back(frame);
        
        SetPos(i);
        
        frameCount = i+1;
        
        // Just for test the progress dialog
        /*QTime dieTime= QTime::currentTime().addMSecs(10);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);*/
    }
    
    progress.setValue(frameCount);
    SetPos(0);
}

bool CaptureManager::addLine(const QLine &inputLine)
{
    img.addLine(inputLine);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::addPoint(const QPoint &inputPoint)
{
    img.addPoint(inputPoint);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::addPolygon(const QPolygon &inputPolygon)
{
    img.addPolygon(inputPolygon);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::addRect(const QRect &inputRect)
{
    img.addRect(inputRect);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::replaceLine(int index, const QLine &inputLine)
{
    img.replaceLine(index, inputLine);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::replacePoint(int index, const QPoint &inputPoint)
{
    img.replacePoint(index, inputPoint);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::replaceRect(int index, const QRect &inputRect)
{
    img.replaceRect(index, inputRect);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::replacePolygon(int index, const QPolygon &inputPolygon)
{
    img.replacePolygon(index, inputPolygon);
    PushbackCurrentFrame();
    Redraw();
    return true;
}


bool CaptureManager::removeLine(int index)
{
    img.removeLine(index);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::removePoint(int index)
{
    img.removePoint(index);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::removeRect(int index)
{
    img.removeRect(index);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

bool CaptureManager::removePolygon(int index)
{
    img.removePolygon(index);
    PushbackCurrentFrame();
    Redraw();
    return true;
}

void CaptureManager::Clear()
{
	qDebug() << "Clear frame " << pos << "/" << frameCount;

    img.ReleaseAll();
    Redraw();
}

void CaptureManager::SetRoi(const Point2f inputROI[])
{
	// todo
}

void CaptureManager::GetRoi(Point2f outputROI[])
{
	// todo
}

void CaptureManager::ClearRoi()
{
	// todo
}

QList<ImagePlus> CaptureManager::getBook()
{
    return book;
}

QStringList CaptureManager::getBookList()
{
    return bookList;
}

ImagePlus CaptureManager::getImg()
{
    return img;
}