
#include "interfaces.h"

// -------------------- constructor --------------------
ActionInterface::ActionInterface () : QObject() {
    
    qAction = NULL;
    actionWidget = NULL;
}

// -------------------- destructor --------------------
ActionInterface::~ActionInterface() {
    
}

// -------------------- setName --------------------
void ActionInterface::setName ( QString name ) {
    this->name = name;
    setObjectName ( name );
}

// -------------------- setDescription --------------------
void ActionInterface::setDescription ( QString description ) {
    this->description = description;
}

// -------------------- setIcon --------------------
void ActionInterface::setIcon ( QPixmap icon ) {
    this->icon = icon;
}

// -------------------- getIcon --------------------
QPixmap ActionInterface::getIcon() {
    return icon;
}

// -------------------- getWidget --------------------
QWidget* ActionInterface::getWidget() {
    
    return actionWidget;
}

void ActionInterface::setQStackedWidget (QStackedWidget *actionWidgetStack)
{
    this->actionWidgetStack = actionWidgetStack;
}

// -------------------- getQAction --------------------
QAction* ActionInterface::getQAction() {
    if ( !qAction ) {
        // create the corresponding QAction (using the icon, name and descriptions)
        qAction = new QAction ( getIcon(), getName(), this );
        qAction->setStatusTip ( getDescription() );
        qAction->setWhatsThis ( getName() + "\n" + getDescription() );
        // connect it to the trigger slot
        connect ( qAction, SIGNAL ( triggered() ), this, SLOT ( trigger() ) );
    }
    
    return qAction;
}

// -------------------- trigger --------------------
ActionInterface::ApplyStatus ActionInterface::trigger ( QWidget * parent ) {
    
    // if there are no parents to use use the action viewer
    if ( !parent ) {
        //-- check history
        QWidget * actionWidget = this->getWidget();
        int actionWidgetIndex = actionWidgetStack->indexOf(actionWidget);
        
        if (actionWidgetIndex == -1 && actionWidget) {
            // add the widget (beware that actionWidgetStack then takes ownership of the widget!)
            actionWidgetIndex = actionWidgetStack->addWidget(actionWidget);
        }
        
        // Update the panel
        actionWidgetStack->setCurrentIndex(actionWidgetIndex);
        actionWidgetStack->update();
        // ignore size policy of widget so that it can be resized
        //actionWidgetStack->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else {
        getWidget()->setParent ( parent );
        getWidget()->show();
    }
    
    return TRIGGERED;
    
}