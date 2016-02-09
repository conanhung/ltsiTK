
#ifndef DRAWINGTOOLSPLUGIN_H
#define DRAWINGTOOLSPLUGIN_H

#include <QRect>
#include <QObject>
#include <QStringList>
#include <QPainterPath>
#include <QImage>

//! [0]
#include "interfaces.h"

//! [1]
class DrawingToolsPlugin : public QObject,
public DrawingToolsInterface
{
    Q_OBJECT
    Q_INTERFACES(DrawingToolsInterface)
    
public:
    
    // DrawingToolsInterface
    QStringList drawingTools() const;
    
    QPoint mousePress(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons);
    
    QRect mouseMove(const QString &drawingTool, const QPoint &oldPos, const QPoint &newPos);
    QRect mouseRelease(const QString &drawingTool, const QPoint &pos);
    QPoint mouseDoubleClickEvent(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons);
    QRect updateDrawingData(const QString &drawingTool, QPainter &painter,
                            const QPoint &oldPos, const QPoint &newPos);
    
    bool isPointHit(const QPoint &testPoint, const QPoint &mousePos, int tolerance);
    bool isEditing();
    
    QPoint getPointHit(const QPoint &pos); // return (contour,vertex) pair
    
    QPoint getPointHit(const QList<QPolygon> &intputPoly, const QPoint &pos); // return (polygon,vertex) pair
    QPoint getPointHit(const QList<QRect> &inputRects, const QPoint &pos);
    QPoint getPointHit(const QList<QPoint> &inputPoints, const QPoint &pos);
    QPoint getPointHit(const QList<QLine> &inputLines, const QPoint &pos);
    
    int getShapeHit(const QList<QPolygon> &intputPoly, const QPoint &pos);
    int getShapeHit(const QList<QRect> &inputRects, const QPoint &pos);
    
private:
    QPoint oldPos;
    QPoint newPos;
    
    bool isDoubleClickEvent;
    
    int selectedShape;
    QPoint selectedPoint;
    QVector<QPoint> m_points;
    
    QLine m_line;
    QPoint m_point;
    QRect m_rect;
    QPolygon m_polygon;
    
    QRect newRect;
    QPolygon newPolygon;
    
    QList<QLine> lines;
    QList<QPoint> points;
    QList<QRect> rects;
    QList<QPolygon> polygons;
};

#endif // DRAWINGTOOLSPLUGIN_H
