/********************************************************************************
** Form generated from reading UI file 'ExampleAction.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMPLEACTION_H
#define UI_EXAMPLEACTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExampleActionPluginWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ExampleActionPluginWidget)
    {
        if (ExampleActionPluginWidget->objectName().isEmpty())
            ExampleActionPluginWidget->setObjectName(QString::fromUtf8("ExampleActionPluginWidget"));
        ExampleActionPluginWidget->resize(295, 554);
        verticalLayout = new QVBoxLayout(ExampleActionPluginWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 12, -1, -1);
        label = new QLabel(ExampleActionPluginWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(ExampleActionPluginWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ExampleActionPluginWidget);

        QMetaObject::connectSlotsByName(ExampleActionPluginWidget);
    } // setupUi

    void retranslateUi(QWidget *ExampleActionPluginWidget)
    {
        ExampleActionPluginWidget->setWindowTitle(QApplication::translate("ExampleActionPluginWidget", "Extra Filters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ExampleActionPluginWidget", "Example Action", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExampleActionPluginWidget: public Ui_ExampleActionPluginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMPLEACTION_H
