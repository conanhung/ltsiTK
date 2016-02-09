
#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

#include <QSet>
#include <QWidget>
#include <QString>
#include <QAction>
#include <QStackedWidget>

class BrushInterface
{
public:
    virtual ~BrushInterface() {}

    virtual QStringList brushes() const = 0;
    virtual QRect mousePress(const QString &brush, QPainter &painter,
                             const QPoint &pos) = 0;
    virtual QRect mouseMove(const QString &brush, QPainter &painter,
                            const QPoint &oldPos, const QPoint &newPos) = 0;
    virtual QRect mouseRelease(const QString &brush, QPainter &painter,
                               const QPoint &pos) = 0;
    
};

class DrawingToolsInterface
{
public:
    virtual ~DrawingToolsInterface() {}
    
    virtual QStringList drawingTools() const = 0;
    
    virtual QPoint mousePress(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons) = 0; // return (contour index, control point index)
    
    virtual QRect mouseMove(const QString &drawingTool, const QPoint &oldPos, const QPoint &newPos) = 0;
    
    virtual QRect mouseRelease(const QString &drawingTool, const QPoint &pos) = 0;
    
    virtual QRect updateDrawingData(const QString &drawingTool, QPainter &painter,
                                   const QPoint &oldPos, const QPoint &newPos) = 0;
    
    virtual QPoint mouseDoubleClickEvent(const QString &drawingTool, const QPoint &pos, const QList<QLine> &lines, const QList<QPoint> &points, const QList<QRect> &rects, const QList<QPolygon> &polygons) = 0;
    
};


class ShapeInterface
{
public:
    virtual ~ShapeInterface() {}

    virtual QStringList shapes() const = 0;
    virtual QPainterPath generateShape(const QString &shape,
                                       QWidget *parent) = 0;
};


class FilterInterface
{
public:
    virtual ~FilterInterface() {}
    
    virtual QStringList filters() const = 0;
    virtual QImage filterImage(const QString &filter, const QImage &image,
                               QWidget *parent) = 0;
};

class ActionInterface : public QObject
{
    Q_OBJECT
    
public:
    
    ActionInterface();
    virtual ~ActionInterface();
    
    /// \enum ApplyStatus describes what happened during the application of an algorithm (i.e. results of the apply method)
    enum ApplyStatus {
        SUCCESS,    ///< everything went according to plan
        ERROR,      ///< apply() failed : an error occured (usually it means that the apply() was interrupted)
        WARNING,    ///< some (partial) error occured during the application of the algorithm
        ABORTED,    ///< the action was aborted before completion
        TRIGGERED  ///< the action was triggered only, but not applied
    };
    
public slots:
    
    /**
     * This method triggers the action.
     * The parent widget is used if the action is embedded, see class description for more information about the algorithm.
     * This method cannot be redefined in inherited class.
     */
    ApplyStatus trigger(QWidget * parent = NULL);
    
    /**
     * This method is called when the action has to be applied on the target list (get the target lists using getTargets())
     *  It calls the algorithm of your action on the target list of components
     * \note it should never be empty!
     * \note if you wish to call your action and register it within the application history, prefer
     * using the \see Action::applyAndRegister()
     * method
     * @return The status of the apply method.
     */
    virtual ApplyStatus apply() = 0;
    
public:
    
    /** Get the corresponding QAction.
     *  The corresponding QAction has its triggered() signal connected to the trigger() slot of the action.
     *  It shares the action icon (as the QAction's icon) and name (as the QAction's text).
     *  It also use the descriptions of the action for the tooltip/whatsThis text.
     *
     *  To add a shortcut, simply call getQAction()->setShortcut(..) in the action constructor.
     *  To make this shortcut available for any windows of the application, call getQAction()->setShortcutContext(Qt::ApplicationShortcut);
     */
    QAction *getQAction();
    
    // get the name of the action
    QString getName() const {
        return name;
    };
    
    // the description of the action
    QString getDescription() const {
        return description;
    };
    
    virtual QWidget * getWidget();
    
    /// the icon to personalize the action (no icon by default)
    virtual QPixmap getIcon();
    
    void setQStackedWidget (QStackedWidget *actionWidgetStack);
    
protected:
    
    /// set the name of the action class
    void setName(QString name);
    
    /// the description of the action
    void setDescription(QString description);
    
    /// set the Pixmap
    void setIcon(QPixmap);
    
    /// the action widget
    QWidget *actionWidget;
    
private:
    
    QString name;
    QString description;
    /// the Action pixmap icon
    QPixmap icon;
    
    /// the corresponding QAction
    QAction *qAction;
    
    // actions stacked widget of the viewer
    QStackedWidget *actionWidgetStack;
};


QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(BrushInterface,
                    "com.ltsi.EndoTrack.BrushInterface/1.0")

Q_DECLARE_INTERFACE(ShapeInterface,
                    "com.ltsi.EndoTrack.ShapeInterface/1.0")

Q_DECLARE_INTERFACE(FilterInterface,
                    "com.ltsi.EndoTrack.FilterInterface/1.0")

Q_DECLARE_INTERFACE(DrawingToolsInterface,
                    "com.ltsi.EndoTrack.DrawingToolsInterface/1.0")

Q_DECLARE_INTERFACE(ActionInterface,
                    "com.ltsi.EndoTrack.ActionInterface/1.0")

QT_END_NAMESPACE

#endif
