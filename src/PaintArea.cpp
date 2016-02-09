
#include "interfaces.h"
#include "PaintArea.h"

#include <QPainter>
#include <QMouseEvent>

PaintArea::PaintArea(QWidget *parent) :
    QLabel(parent),
    theImage(QImage()),
    color(Qt::blue),
    thickness(2),
    drawingToolsInterface(0),
    lastPos(-1, -1),
    currentPos(-1, -1)
{
    scale = 1.0;
    offsetX = 0.0;
    offsetY = 0.0;
    
    selectedPoint = QPoint(-1,-1);
    
    isOffsetsModified = false;
    drawRect = false;
}

void PaintArea::setMouseCursorPos(QPoint input)
{
    currentPos = input;
} // setMouseCursorPos()

void PaintArea::setMouseCursorPos(QMouseEvent *event)
{
    setMouseCursorPos(QPoint((event->pos().x() - offsetX) / scale, (event->pos().y() - offsetY) / scale));
}

QPoint PaintArea::getMouseCursorPos()
{
    return currentPos;
} // getMouseXPos()

bool PaintArea::openImage(const QString &fileName)
{
    QImage image;
    if (!image.load(fileName))
        return false;

    setImage(image);
    return true;
}


// Save the current image in the paint area
bool PaintArea::saveImage(const QString &fileName, const char *fileFormat)
{
    
    theImage = QImage(base.width(), base.height(), QImage::Format_RGB32);
    theImage.fill(Qt::transparent); // force alpha channel
    
    QPainter painter(&theImage);
    
    painter.drawImage(0, 0, base);
    
    painter.setOpacity(0.5);
    painter.drawImage(0, 0, overlay);
    
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::white, thickness);
    painter.setPen(pen);
    
    if (lines.size()) {
        for (int i = 0; i < lines.size(); i++) {
            painter.drawLine(lines.at(i));
        }
    }
    
    if (points.size()) {
        pen = QPen(Qt::yellow, 4);
        painter.setPen(pen);
        
        for (int i = 0; i < points.size(); i++) {
            painter.drawPoint(points.at(i));
        }
        
        pen = QPen(Qt::white, thickness);
        painter.setPen(pen);
    }
    
    if (rects.size()) {
        for (int i = 0; i < rects.size(); i++) {
            painter.drawRect(rects.at(i));
        }
    }
    
    if (polygons.size()) {
        for (int i = 0; i < polygons.size(); i++) {
            painter.drawPolygon(polygons.at(i));
        }
    }
    
    return theImage.save(fileName, fileFormat);
}

void PaintArea::setImage(const ImagePlus &inputImage)
{
    this->imagePlus = inputImage;
    
    base = imagePlus.original;
    overlay = imagePlus.overlay;
    lines = imagePlus.lines;
    points = imagePlus.points;
    rects = imagePlus.rects;
    polygons = imagePlus.polygons;
    
    if(!isOffsetsModified) {
        offsetX = (-base.width()*scale + this->width()) / 2;
        offsetY = (-base.height()*scale + this->height()) / 2;
    }
    
    update();
    updateGeometry();
}

//! [0]
void PaintArea::setDrawingsTool(DrawingToolsInterface *drawingToolsInterface, const QString &drawingTool)
{
    this->drawingToolsInterface = drawingToolsInterface;
    this->drawingTool = drawingTool;
}
//! [0]

QSize PaintArea::sizeHint() const
{
    return theImage.size();
}

void PaintArea::drawPoint(const QPoint &m_Point, QPainter &painter)
{
    QPen pen = QPen(Qt::yellow, 4);
    painter.setPen(pen);
    
    painter.drawPoint(m_Point);
    
    pen = QPen(Qt::white, thickness);
    painter.setPen(pen);
}

void PaintArea::drawPoints(const QList<QPoint> &m_Points, QPainter &painter)
{
    QPen pen = QPen(Qt::yellow, 4);
    painter.setPen(pen);
    
    for (int i = 0; i < m_Points.size(); i++) {
        painter.drawPoint(m_Points.at(i));
    }
    
    pen = QPen(Qt::white, thickness);
    painter.setPen(pen);
}

// Paint event
void PaintArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    
    if(!isOffsetsModified) {
        offsetX = (-base.width()*scale + this->width()) / 2;
        offsetY = (-base.height()*scale + this->height()) / 2;
    }
    
    painter.translate(offsetX, offsetY);
    painter.scale(scale, scale);
    
    painter.drawImage(0, 0, base);
    
    painter.setOpacity(0.5);
    painter.drawImage(0, 0, overlay);
    
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::white, thickness);
    painter.setPen(pen);
    
    if (lines.size()) {
        for (int i = 0; i < lines.size(); i++) {
            // Line
            painter.drawLine(lines.at(i));
            // Control points
            drawPoint(lines.at(i).p1(),painter);
            drawPoint(lines.at(i).p2(),painter);
        }
    }
    
    if (points.size()) {
        drawPoints(points, painter);
    }
    
    if (rects.size()) {
        for (int i = 0; i < rects.size(); i++) {
            painter.drawRect(rects.at(i));
            // Control points
            drawPoint(rects.at(i).topLeft(),painter);
            drawPoint(rects.at(i).topRight(),painter);
            drawPoint(rects.at(i).bottomLeft(),painter);
            drawPoint(rects.at(i).bottomRight(),painter);
        }
    }
    
    if (polygons.size()) {
        for (int i = 0; i < polygons.size(); i++) {
            painter.drawPolygon(polygons.at(i));
            // Control points
            drawPoints(polygons.at(i).toList(),painter);
        }
    }
    
    // Update drawing data from DrawingToolsPlugin
    if (drawingToolsInterface) {
        drawingToolsInterface->updateDrawingData(drawingTool, painter, lastPos, currentPos);
    }
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    if (event->button() == Qt::LeftButton) {
        setMouseCursorPos(event);
        
        if (drawingToolsInterface) {
            
            selectedPoint = drawingToolsInterface->mousePress(drawingTool, currentPos, lines, points, rects, polygons);
            
            update();
        }
        
        lastPos = getMouseCursorPos();
    }
}

//! [1]
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && lastPos != QPoint(-1, -1)) {
        setMouseCursorPos(event);
        
        if (drawingToolsInterface) {
            
            drawingToolsInterface->mouseMove(drawingTool, lastPos, getMouseCursorPos());
            
            // Specially to change the offsets
            if (drawingTool == tr("Change offsets"))
                changeOffsets();
            
            update();
        }
    }
}
//! [1]

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && lastPos != QPoint(-1, -1)) {
        if (drawingToolsInterface) {
            
            drawingToolsInterface->mouseRelease(drawingTool, getMouseCursorPos());
            update();
        }

        lastPos = getMouseCursorPos();
    }
}

void PaintArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "mouseDoubleClickEvent";
    if (event->button() == Qt::LeftButton) {
        qDebug() << "left button";
        if (drawingToolsInterface) {
            
            drawingToolsInterface->mouseDoubleClickEvent(drawingTool, currentPos, lines, points, rects, polygons);
            update();
        }
        lastPos = getMouseCursorPos();
    }
}

void PaintArea::setupPainter(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::green, 1);
    painter.setPen(pen);
}

void PaintArea::resizeEvent(QResizeEvent *ev)
{
    // Compute offset
    this->computeOffsets(offsetX, offsetY);
    // Update the display
    this->update();
}

void PaintArea::computeScale(float & scale)
{
    scale = 1.0f;
    
    if (!base.isNull())
    {
        float w = base.width();
        float h = base.height();
        float widthRatio = float(this->width()) / w;
        float heightRatio = float(this->height()) / h;
        
        //printf("w=%f, h=%f, wR=%f, hR=%f, sW=%d, sH=%d\n", w, h, widthRatio, heightRatio, this->width(), this->height());
        if (widthRatio < heightRatio)
        {
            scale = widthRatio;
        }
        else
        {
            scale = heightRatio;
        }
    }
}

void PaintArea::computeOffsets(float & offsetX, float & offsetY)
{
    if (!base.isNull())
    {
        if (!isOffsetsModified) {
            float w = base.width();
            float h = base.height();
            //printf("ratio=%f\n",ratio);
            
            w *= scale;
            h *= scale;
            
            if (w < this->width())
            {
                offsetX = (this->width() - w) / 2.0f;
            }
            if (h < this->height())
            {
                offsetY = (this->height() - h) / 2.0f;
            }
            //printf("offsetX=%f, offsetY=%f\n",offsetX, offsetY);
        }
    } else {
        offsetX = 0.0f;
        offsetY = 0.0f;
    }
}

void PaintArea::zoomIn()
{
    scale += (float)0.3;
    this->update();
}

void PaintArea::zoomOut()
{
    scale -= (float)0.3;
    if (scale <= (float)0.3)
        scale = (float)0.3;
    this->update();
}

void PaintArea::zoomFullSize()
{
    scale = 1.0;
    isOffsetsModified = false;
    this->update();
}

void PaintArea::changeOffsets()
{
    QPoint shift;
    shift.setX(getMouseCursorPos().x() - lastPos.x());
    shift.setY(getMouseCursorPos().y() - lastPos.y());
    
    //qDebug() << shift;
    
    offsetX += shift.x();
    offsetY += shift.y();
    
    isOffsetsModified = true;
}