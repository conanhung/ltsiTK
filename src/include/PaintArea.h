
#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QColor>
#include <QImage>
#include <QPainterPath>
#include <QWidget>
// Qt header files
#include <QtGui>

#include "ImagePlus.h"

class DrawingToolsInterface;

class PaintArea : public QLabel
{
    Q_OBJECT

public:
    virtual ~PaintArea() {};
    PaintArea(QWidget *parent = 0);
    
    void setMouseCursorPos(QPoint);
    void setMouseCursorPos(QMouseEvent *event);
    QPoint getMouseCursorPos(void);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    
    void setImage(const ImagePlus &inputImage);
    
    void setDrawingsTool(DrawingToolsInterface *drawingToolsInterface, const QString &drawingTool);

    QImage image() const { return theImage; }
    QColor brushColor() const { return color; }
    int brushWidth() const { return thickness; }
    QSize sizeHint() const;
    
    void drawPoint(const QPoint &m_Point, QPainter &painter);
    void drawPoints(const QList<QPoint> &m_Points, QPainter &painter);
    
    void computeScale(float & scale_);
    void computeOffsets(float & offsetX_, float & offsetY_);
    void zoomIn();
    void zoomOut();
    void zoomFullSize();
    void changeOffsets();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *ev);

private:
    void setupPainter(QPainter &painter);
    
    ImagePlus imagePlus;
    
    QImage base, overlay;
    QImage theImage;
    
    QList<QLine> lines;
    QList<QPoint> points;
    QList<QRect> rects;
    QList<QPolygon> polygons;
    
    QPoint selectedPoint;
    
    QColor color;
    int thickness;
    
    float scale;
    float offsetX;
    float offsetY;
    
    bool isOffsetsModified;

    DrawingToolsInterface *drawingToolsInterface;
    QString drawingTool;
    QPoint lastPos;
    QPoint currentPos;
    
    bool drawRect;

    QPainterPath pendingPath;
};

#endif
