
#include <QtGui>
#include <QMessageBox>

#include <math.h>
#include <stdlib.h>

#include "CaptureManager.h"
#include "MatToQImage.h"
#include "ExampleActionPlugin.h"

using namespace cv;
using namespace std;

// -----------------  Aortic root registration Plugin -------------------

ExampleActionPlugin::ExampleActionPlugin() : ActionInterface()
{
    setName("Example Action");
    setDescription("This is a simple interface for an action plugin");
    
    theWidget = NULL;
}

ExampleActionPlugin::~ExampleActionPlugin()
{
    // nothing for instant
}

void ExampleActionPlugin::init()
{
    theWidget = new QWidget();
    ui.setupUi(theWidget);
}

QWidget * ExampleActionPlugin::getWidget()
{
    if (!theWidget)
        init();
    
    return theWidget;
}

ActionInterface::ApplyStatus ExampleActionPlugin::apply()
{
    return SUCCESS;
}

Q_EXPORT_PLUGIN2(exampleaction, ExampleActionPlugin)
