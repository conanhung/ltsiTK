
#ifndef EXAMPLEACTIONPLUGIN_H
#define EXAMPLEACTIONPLUGIN_H

// Qt
#include <QObject>
#include <QStringList>
#include <QImage>
#include <QWidget>
#include <QDir>

// OpenCV
#include "opencv2/opencv.hpp"

#include "interfaces.h"
#include "ui_ExampleAction.h"

// ExampleActionPlugin

class ExampleActionPlugin : public ActionInterface
{
    Q_OBJECT
    Q_INTERFACES(ActionInterface)

public:
    
    ExampleActionPlugin();
    ~ExampleActionPlugin();
    
    virtual QWidget * getWidget();
    
private:
    void init();
    
public slots:
    /** this method is automatically called when the action is triggered.
     * Use getTargets() QList to get the list of component to use.
     * \note getTargets() is automatically filtered so that it only contains compatible components,
     * i.e., instances of ImageComponent (or a subclass).
     */
    virtual ApplyStatus apply();
    
protected:
    Ui::ExampleActionPluginWidget ui;
    QWidget * theWidget;
    
signals:
    // All signals go here
};

#endif // EXAMPLEACTIONPLUGIN_H
