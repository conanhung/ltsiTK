/********************************************************************************
** Form generated from reading UI file 'ImagesAcquisition.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESACQUISITION_H
#define UI_IMAGESACQUISITION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagesAcquisitionPluginWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QFrame *line;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *acquisitionDirsListWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *videoPathLineEdit;
    QToolButton *loadFilesButton;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *connectPushButton;
    QPushButton *startPushButton;
    QPushButton *stopPushButton;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *frameSizeLabel;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *frameRateLabel;
    QLabel *label_7;
    QProgressBar *bufferProgressBar;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ImagesAcquisitionPluginWidget)
    {
        if (ImagesAcquisitionPluginWidget->objectName().isEmpty())
            ImagesAcquisitionPluginWidget->setObjectName(QString::fromUtf8("ImagesAcquisitionPluginWidget"));
        ImagesAcquisitionPluginWidget->resize(295, 554);
        verticalLayout = new QVBoxLayout(ImagesAcquisitionPluginWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 12, -1, -1);
        label_5 = new QLabel(ImagesAcquisitionPluginWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_5);

        line = new QFrame(ImagesAcquisitionPluginWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox = new QGroupBox(ImagesAcquisitionPluginWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        acquisitionDirsListWidget = new QListWidget(groupBox);
        acquisitionDirsListWidget->setObjectName(QString::fromUtf8("acquisitionDirsListWidget"));

        horizontalLayout->addWidget(acquisitionDirsListWidget);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ImagesAcquisitionPluginWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        videoPathLineEdit = new QLineEdit(groupBox_2);
        videoPathLineEdit->setObjectName(QString::fromUtf8("videoPathLineEdit"));

        horizontalLayout_3->addWidget(videoPathLineEdit);

        loadFilesButton = new QToolButton(groupBox_2);
        loadFilesButton->setObjectName(QString::fromUtf8("loadFilesButton"));

        horizontalLayout_3->addWidget(loadFilesButton);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        connectPushButton = new QPushButton(groupBox_2);
        connectPushButton->setObjectName(QString::fromUtf8("connectPushButton"));
        connectPushButton->setCheckable(true);

        horizontalLayout_2->addWidget(connectPushButton);

        startPushButton = new QPushButton(groupBox_2);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));

        horizontalLayout_2->addWidget(startPushButton);

        stopPushButton = new QPushButton(groupBox_2);
        stopPushButton->setObjectName(QString::fromUtf8("stopPushButton"));

        horizontalLayout_2->addWidget(stopPushButton);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 10);
        frameSizeLabel = new QLabel(groupBox_2);
        frameSizeLabel->setObjectName(QString::fromUtf8("frameSizeLabel"));

        gridLayout->addWidget(frameSizeLabel, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        frameRateLabel = new QLabel(groupBox_2);
        frameRateLabel->setObjectName(QString::fromUtf8("frameRateLabel"));

        gridLayout->addWidget(frameRateLabel, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        bufferProgressBar = new QProgressBar(groupBox_2);
        bufferProgressBar->setObjectName(QString::fromUtf8("bufferProgressBar"));
        bufferProgressBar->setValue(0);

        gridLayout->addWidget(bufferProgressBar, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ImagesAcquisitionPluginWidget);

        QMetaObject::connectSlotsByName(ImagesAcquisitionPluginWidget);
    } // setupUi

    void retranslateUi(QWidget *ImagesAcquisitionPluginWidget)
    {
        ImagesAcquisitionPluginWidget->setWindowTitle(QApplication::translate("ImagesAcquisitionPluginWidget", "Extra Filters", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Images Acquisition", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImagesAcquisitionPluginWidget", "Acquisition folder", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ImagesAcquisitionPluginWidget", "New acquisition", 0, QApplication::UnicodeUTF8));
        videoPathLineEdit->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "0", 0, QApplication::UnicodeUTF8));
        loadFilesButton->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "...", 0, QApplication::UnicodeUTF8));
        connectPushButton->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Connect", 0, QApplication::UnicodeUTF8));
        startPushButton->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Start", 0, QApplication::UnicodeUTF8));
        stopPushButton->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Stop", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Video path", 0, QApplication::UnicodeUTF8));
        frameSizeLabel->setText(QString());
        label_4->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Size", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "FPS", 0, QApplication::UnicodeUTF8));
        frameRateLabel->setText(QString());
        label_7->setText(QApplication::translate("ImagesAcquisitionPluginWidget", "Buffer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImagesAcquisitionPluginWidget: public Ui_ImagesAcquisitionPluginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESACQUISITION_H
