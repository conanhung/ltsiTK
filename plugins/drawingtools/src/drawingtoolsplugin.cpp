
#include <QtGui>

#include <math.h>
#include <stdlib.h>

#include "CaptureManager.h"
#include "drawingtoolsplugin.h"

QStringList DrawingToolsPlugin::drawingTools() const
{
    return QStringList() << tr("None")  << tr("Change offsets") << tr("Rectangular") << tr("Polygon")
                         << tr("Straight Line") << tr("Points");
}

bool DrawingToolsPlugin::isEditing()
{
    return (selectedPoint != QPoint(-1,-1) || (selectedShape != -1));
}

QPoint DrawingToolsPlugin::mousePress(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons)
{
    this->oldPos = pos;
    
    selectedPoint = QPoint(-1,-1);
    selectedShape = -1;
    
    this->lines = lines;
    this->rects = rects;
    this->points = points;
    this->polygons = polygons;
    
    if (drawingTool == tr("Straight Line")) {
        
        selectedPoint = getPointHit(lines,pos);
        
        if(selectedPoint != QPoint(-1,-1))
            m_line = lines.at(selectedPoint.x());
        
    } else if (drawingTool == tr("Rectangular")) {
        
        selectedPoint = getPointHit(rects,pos);
        selectedShape = getShapeHit(rects,pos);
        
        if(selectedPoint != QPoint(-1,-1)) {
            m_rect = rects.at(selectedPoint.x());
            selectedShape = -1; // force select a point only
        }
        else if (selectedShape != -1)
            m_rect = rects.at(selectedShape);
        
    } else if (drawingTool == tr("Points")) {
        
        selectedPoint = getPointHit(points,pos);
        
        if(selectedPoint != QPoint(-1,-1))
            m_point = points.at(selectedPoint.x());
        
    } else if (drawingTool == tr("Polygon")) {
        
        selectedPoint = getPointHit(polygons,pos);
        selectedShape = getShapeHit(polygons,pos);
        
        if(selectedPoint != QPoint(-1,-1)) {
            m_polygon = polygons.at(selectedPoint.x());
            selectedShape = -1; // force select a point only
        }
        else if (selectedShape != -1)
            m_polygon = polygons.at(selectedShape);
    }
    
    isDoubleClickEvent = false;
    
    return selectedPoint;
}

QPoint DrawingToolsPlugin::mouseDoubleClickEvent(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons)
{
    
    isDoubleClickEvent = true;
    
    selectedPoint = QPoint(-1,-1);
    
    this->lines = lines;
    this->rects = rects;
    this->points = points;
    this->polygons = polygons;
    
    if (drawingTool == tr("Straight Line")) {
        
        selectedPoint = getPointHit(lines,pos);
        //qDebug() << selectedPoint;
        
        if(selectedPoint != QPoint(-1,-1)) {
            CaptureManager::removeLine(selectedPoint.x());
        }
        
    } else if (drawingTool == tr("Rectangular")) {
        
        selectedPoint = getPointHit(rects,pos);
        //qDebug() << selectedPoint;
        
        if(selectedPoint != QPoint(-1,-1)) {
            CaptureManager::removeRect(selectedPoint.x());
        }
        
    } else if (drawingTool == tr("Points")) {
        
        selectedPoint = getPointHit(points,pos);
        //qDebug() << selectedPoint;
        
        if(selectedPoint != QPoint(-1,-1)) {
            CaptureManager::removePoint(selectedPoint.x());
        }
        
    } else if (drawingTool == tr("Polygon")) {
        
        selectedPoint = getPointHit(polygons,pos);
        //qDebug() << selectedPoint;
        
        if(selectedPoint != QPoint(-1,-1)) {
            CaptureManager::removePolygon(selectedPoint.x());
        }
    }
    
    selectedPoint = QPoint(-1,-1);
    return selectedPoint;
}

QRect DrawingToolsPlugin::mouseMove(const QString &drawingTool, const QPoint &oldPos, const QPoint &newPos)
{
    
    QRect boundingRect = QRect(oldPos, newPos);
    
    return boundingRect;
}

QRect DrawingToolsPlugin::mouseRelease(const QString &drawingTool, const QPoint &pos)
{
    if(!isDoubleClickEvent) {
        
        newPos = pos;
        
        if (drawingTool == tr("Straight Line")) {
            
            if(!isEditing()) { // not in editing mode
                
                if(newPos!=oldPos)
                    CaptureManager::addLine(QLine(oldPos,newPos));
                
            } else { // editing mode
                
                CaptureManager::replaceLine(selectedPoint.x(), m_line);
                selectedPoint = QPoint(-1,-1);
                
            }
            
        } else if (drawingTool == tr("Rectangular")) {
            
            if(!isEditing()) { // not in editing mode
                
                if(newPos!=oldPos)
                    CaptureManager::addRect(QRect(oldPos,newPos));
                
            } else if (selectedShape == -1) { // editing mode
                
                CaptureManager::replaceRect(selectedPoint.x(), m_rect);
                selectedPoint = QPoint(-1,-1);
                
            } else if (selectedShape != -1) {
                
                CaptureManager::replaceRect(selectedShape, newRect);
                selectedPoint = QPoint(-1,-1);
                selectedShape = -1;
                
            }
            
        } else if (drawingTool == tr("Points")) {
            
            if(!isEditing()) { // not in editing mode
                
                CaptureManager::addPoint(newPos);
                
            } else { // editing mode
                
                CaptureManager::replacePoint(selectedPoint.x(), m_point);
                selectedPoint = QPoint(-1,-1);
                
            }
            
        } else if (drawingTool == tr("Polygon")) {
            
            if(!isEditing()) { // not in editing mode
                
                if(getPointHit(newPos) == QPoint(0,0)) // the first point of polygon
                {
                    CaptureManager::addPolygon(QPolygon(m_points));
                    m_points.clear();
                } else
                    m_points.push_back(newPos);
                
            } else if (selectedShape == -1) {
                
                CaptureManager::replacePolygon(selectedPoint.x(), m_polygon);
                selectedPoint = QPoint(-1,-1);
                
            } else if (selectedShape != -1) {
                
                CaptureManager::replacePolygon(selectedShape, newPolygon);
                selectedPoint = QPoint(-1,-1);
                selectedShape = -1;
                
            }
        }
        
    }
    
    return QRect(0, 0, 0, 0);
}

QRect DrawingToolsPlugin::updateDrawingData(const QString &drawingTool, QPainter &painter,
                                           const QPoint &oldPos, const QPoint &newPos)
{
    painter.save();
    
    
    QPen pen1(Qt::green, 1);
    painter.setPen(pen1);
    
    int rad = painter.pen().width() / 2;
    QRect boundingRect = QRect(oldPos, newPos).normalized()
    .adjusted(-rad, -rad, +rad, +rad);
    
    if (drawingTool == tr("Straight Line")) {
        
        if(!isEditing()) { // not in editing mode
            
            if(newPos!=oldPos)
                painter.drawLine(oldPos, newPos);
            
        }
        else { // editing mode
            
            if (selectedPoint.y()) {
                m_line.setP2(newPos);
            }
            else {
                m_line.setP1(newPos);
            }
            painter.drawLine(m_line);
        }
        
    } else if (drawingTool == tr("Rectangular")) {
        
        if(!isEditing()) { // not in editing mode
            
            if(newPos!=oldPos){
                QRect rect(oldPos,newPos);
                painter.drawRect(rect);
            }
            
        }
        else if (selectedShape == -1) { // editing mode
            
            switch (selectedPoint.y())
            {
                case 0: m_rect.setTopLeft(newPos);
                    break;
                case 1: m_rect.setTopRight(newPos);
                    break;
                case 2: m_rect.setBottomRight(newPos);
                    break;
                case 3: m_rect.setBottomLeft(newPos);
                    break;
                default:
                    break;
            }
            
            painter.drawRect(m_rect);
            
        } else {
            
            QPoint shift = QPoint(newPos.x()-oldPos.x(), newPos.y()-oldPos.y());
            
            newRect = m_rect;
            newRect.translate(shift);
            painter.drawRect(newRect);
            
        }
        
    } else if (drawingTool == tr("Points")) {
        
        if(!isEditing()) { // not in editing mode
            if(newPos!=oldPos)
                painter.drawPoint(newPos);
        }
        else { // editing mode
            
            m_point = newPos;
            painter.drawPoint(newPos);
            
        }
        
    } else if (drawingTool == tr("Polygon")) {
        
        if(!isEditing()) { // not in editing mode
            if(m_points.size()) {
                
                for(int i = 0; i < m_points.size()-1; i++)
                    painter.drawLine(m_points.at(i), m_points.at(i+1));
                
                painter.drawLine(m_points.last(), newPos);
                
                pen1 = QPen(Qt::yellow, 5);
                painter.setPen(pen1);
                
                painter.drawPoint(m_points.at(0));
                
                pen1 = QPen(Qt::green, 1);
                painter.setPen(pen1);
            }
            
            // Draw the first point if the mouse is over
            if(getPointHit(newPos) == QPoint(0,0)) // QPoint(the current polygon = 0, the first point = 0)
            {
                pen1 = QPen(Qt::red, 5);
                painter.setPen(pen1);
                
                painter.drawPoint(m_points.at(0));
                
                pen1 = QPen(Qt::green, 1);
                painter.setPen(pen1);
            }
        }
        else if( selectedShape == -1 ){ // editing mode
            
            m_polygon.setPoint(selectedPoint.y(), newPos);
            painter.drawPolygon(m_polygon);
            
        } else {
            
            QPoint shift = QPoint(newPos.x()-oldPos.x(), newPos.y()-oldPos.y());
            
            newPolygon = m_polygon;
            newPolygon.translate(shift);
            painter.drawPolygon(newPolygon);
            
        }
        
    }
    
    painter.restore();
    return boundingRect;
}

bool DrawingToolsPlugin::isPointHit(const QPoint &testPoint, const QPoint &mousePos, int tolerance)
{
    QPolygon polygon;
    polygon << QPoint(testPoint.x() - tolerance, testPoint.y() - tolerance);
    polygon << QPoint(testPoint.x() + tolerance, testPoint.y() - tolerance);
    polygon << QPoint(testPoint.x() + tolerance, testPoint.y() + tolerance);
    polygon << QPoint(testPoint.x() - tolerance, testPoint.y() + tolerance);
    if (polygon.containsPoint(mousePos, Qt::WindingFill))
        return true;
    else
        return false;
}

QPoint DrawingToolsPlugin::getPointHit(const QPoint &pos)
{
    int numOfPts = m_points.size();
    
    for (int j = 0; j < numOfPts; j++) {
        
        if (isPointHit(m_points[j], pos, 8))
            return QPoint(0, j);
    }
    return QPoint(-1, -1);
}

QPoint DrawingToolsPlugin::getPointHit(const QList<QPolygon> &inputPoly, const QPoint &pos)
{
    int numPoly = inputPoly.size();
    
    for (int i = 0; i < numPoly; i++)
    {
        int numPt = inputPoly.at(i).size();
        for (int j = 0; j < numPt; j++) {
            
            if (isPointHit(inputPoly.at(i)[j], pos, 8))
                return QPoint(i, j);
        }
    }
    return QPoint(-1,-1);
}

QPoint DrawingToolsPlugin::getPointHit(const QList<QRect> &inputRects, const QPoint &pos)
{
    int numRects = inputRects.size();
    
    for (int i = 0; i < numRects; i++)
    {
        if (isPointHit(inputRects.at(i).topLeft(), pos, 8))
            return QPoint(i, 0);
        if (isPointHit(inputRects.at(i).topRight(), pos, 8))
            return QPoint(i, 1);
        if (isPointHit(inputRects.at(i).bottomRight(), pos, 8))
            return QPoint(i, 2);
        if (isPointHit(inputRects.at(i).bottomLeft(), pos, 8))
            return QPoint(i, 3);
    }
    return QPoint(-1,-1);
}

QPoint DrawingToolsPlugin::getPointHit(const QList<QPoint> &inputPoints, const QPoint &pos)
{
    int numPoints = inputPoints.size();
    
    for (int i = 0; i<numPoints; i++) {
        if (isPointHit(inputPoints.at(i), pos, 8))
            return QPoint(i, 0);
    }
    
    return QPoint(-1,-1);
}

QPoint DrawingToolsPlugin::getPointHit(const QList<QLine> &inputLines, const QPoint &pos)
{
    int numLines = inputLines.size();
    
    for (int i = 0; i < numLines; i++)
    {
        if (isPointHit(inputLines.at(i).p1(), pos, 8))
            return QPoint(i, 0);
        if (isPointHit(inputLines.at(i).p2(), pos, 8))
            return QPoint(i, 1);
    }
    
    return QPoint(-1,-1);
}

int DrawingToolsPlugin::getShapeHit(const QList<QPolygon> &intputPoly, const QPoint &pos)
{
    int numPoly = intputPoly.size();
    
    //qDebug() << "getShapeHit numPoly" << numPoly;
    
    for (int i = 0; i < numPoly; i++)
    {
        if(intputPoly.at(i).containsPoint(pos, Qt::WindingFill)) {
            //qDebug() << "getShapeHit" << i;
            return i;
        }
    }
    return -1;
}

int DrawingToolsPlugin::getShapeHit(const QList<QRect> &inputRects, const QPoint &pos)
{
    int numRects = inputRects.size();
    
    for (int i = 0; i < numRects; i++)
    {
        if(inputRects.at(i).contains(pos))
            return i;
    }
    return -1;
}

QT_BEGIN_NAMESPACE
//! [9]
Q_EXPORT_PLUGIN2(drawingtools, DrawingToolsPlugin)
//! [9]
QT_END_NAMESPACE
