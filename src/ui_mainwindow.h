/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Wed May 14 23:10:57 2008
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <glwidget.h>

class Ui_MainWindow
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frameTop;
    QHBoxLayout *hboxLayout;
    QGroupBox *groupBoxBrush;
    QHBoxLayout *hboxLayout1;
    QRadioButton *radioButtonDraw;
    QRadioButton *radioButtonSmooth;
    QRadioButton *radioButtonPinch;
    QGridLayout *gridLayout1;
    QLabel *labelSize;
    QSpinBox *spinBoxSize;
    QSlider *horizontalSliderSize;
    QLabel *labelIntencity;
    QSpinBox *spinBoxIntencity;
    QSlider *horizontalSliderIntencity;
    QLabel *labelStrength;
    QSpinBox *spinBoxStrength;
    QSlider *horizontalSliderStrength;
    PZSculpt::GLWidget *canvas;
    QFrame *frameRight;
    QVBoxLayout *vboxLayout;
    QLabel *labelGeometry;
    QHBoxLayout *hboxLayout2;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonSubd;
    QSpacerItem *spacerItem;
    QLabel *labelMeshInfo;
    QTextEdit *textEditMeshInfo;
    QSpacerItem *spacerItem1;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(650, 510);
    actionImport = new QAction(MainWindow);
    actionImport->setObjectName(QString::fromUtf8("actionImport"));
    actionExport = new QAction(MainWindow);
    actionExport->setObjectName(QString::fromUtf8("actionExport"));
    actionQuit = new QAction(MainWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionQuit->setMenuRole(QAction::TextHeuristicRole);
    actionUndo = new QAction(MainWindow);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
    actionUndo->setEnabled(false);
    actionRedo = new QAction(MainWindow);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
    actionRedo->setEnabled(false);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    gridLayout = new QGridLayout(centralwidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    frameTop = new QFrame(centralwidget);
    frameTop->setObjectName(QString::fromUtf8("frameTop"));
    frameTop->setFrameShape(QFrame::StyledPanel);
    hboxLayout = new QHBoxLayout(frameTop);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    groupBoxBrush = new QGroupBox(frameTop);
    groupBoxBrush->setObjectName(QString::fromUtf8("groupBoxBrush"));
    hboxLayout1 = new QHBoxLayout(groupBoxBrush);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    radioButtonDraw = new QRadioButton(groupBoxBrush);
    radioButtonDraw->setObjectName(QString::fromUtf8("radioButtonDraw"));
    radioButtonDraw->setChecked(true);

    hboxLayout1->addWidget(radioButtonDraw);

    radioButtonSmooth = new QRadioButton(groupBoxBrush);
    radioButtonSmooth->setObjectName(QString::fromUtf8("radioButtonSmooth"));

    hboxLayout1->addWidget(radioButtonSmooth);

    radioButtonPinch = new QRadioButton(groupBoxBrush);
    radioButtonPinch->setObjectName(QString::fromUtf8("radioButtonPinch"));

    hboxLayout1->addWidget(radioButtonPinch);


    hboxLayout->addWidget(groupBoxBrush);

    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    labelSize = new QLabel(frameTop);
    labelSize->setObjectName(QString::fromUtf8("labelSize"));

    gridLayout1->addWidget(labelSize, 0, 0, 1, 1);

    spinBoxSize = new QSpinBox(frameTop);
    spinBoxSize->setObjectName(QString::fromUtf8("spinBoxSize"));
    spinBoxSize->setMaximum(255);
    spinBoxSize->setValue(100);

    gridLayout1->addWidget(spinBoxSize, 0, 1, 1, 1);

    horizontalSliderSize = new QSlider(frameTop);
    horizontalSliderSize->setObjectName(QString::fromUtf8("horizontalSliderSize"));
    horizontalSliderSize->setMaximum(255);
    horizontalSliderSize->setValue(100);
    horizontalSliderSize->setOrientation(Qt::Horizontal);

    gridLayout1->addWidget(horizontalSliderSize, 0, 2, 1, 1);

    labelIntencity = new QLabel(frameTop);
    labelIntencity->setObjectName(QString::fromUtf8("labelIntencity"));

    gridLayout1->addWidget(labelIntencity, 1, 0, 1, 1);

    spinBoxIntencity = new QSpinBox(frameTop);
    spinBoxIntencity->setObjectName(QString::fromUtf8("spinBoxIntencity"));
    spinBoxIntencity->setValue(50);

    gridLayout1->addWidget(spinBoxIntencity, 1, 1, 1, 1);

    horizontalSliderIntencity = new QSlider(frameTop);
    horizontalSliderIntencity->setObjectName(QString::fromUtf8("horizontalSliderIntencity"));
    horizontalSliderIntencity->setValue(50);
    horizontalSliderIntencity->setOrientation(Qt::Horizontal);

    gridLayout1->addWidget(horizontalSliderIntencity, 1, 2, 1, 1);

    labelStrength = new QLabel(frameTop);
    labelStrength->setObjectName(QString::fromUtf8("labelStrength"));

    gridLayout1->addWidget(labelStrength, 2, 0, 1, 1);

    spinBoxStrength = new QSpinBox(frameTop);
    spinBoxStrength->setObjectName(QString::fromUtf8("spinBoxStrength"));
    spinBoxStrength->setValue(25);

    gridLayout1->addWidget(spinBoxStrength, 2, 1, 1, 1);

    horizontalSliderStrength = new QSlider(frameTop);
    horizontalSliderStrength->setObjectName(QString::fromUtf8("horizontalSliderStrength"));
    horizontalSliderStrength->setValue(25);
    horizontalSliderStrength->setOrientation(Qt::Horizontal);

    gridLayout1->addWidget(horizontalSliderStrength, 2, 2, 1, 1);


    hboxLayout->addLayout(gridLayout1);


    gridLayout->addWidget(frameTop, 0, 0, 1, 2);

    canvas = new PZSculpt::GLWidget(centralwidget);
    canvas->setObjectName(QString::fromUtf8("canvas"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(canvas->sizePolicy().hasHeightForWidth());
    canvas->setSizePolicy(sizePolicy);

    gridLayout->addWidget(canvas, 1, 0, 1, 1);

    frameRight = new QFrame(centralwidget);
    frameRight->setObjectName(QString::fromUtf8("frameRight"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(frameRight->sizePolicy().hasHeightForWidth());
    frameRight->setSizePolicy(sizePolicy1);
    frameRight->setMinimumSize(QSize(200, 16));
    frameRight->setMaximumSize(QSize(200, 16777215));
    frameRight->setFrameShape(QFrame::StyledPanel);
    vboxLayout = new QVBoxLayout(frameRight);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    labelGeometry = new QLabel(frameRight);
    labelGeometry->setObjectName(QString::fromUtf8("labelGeometry"));

    vboxLayout->addWidget(labelGeometry);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    pushButtonDown = new QPushButton(frameRight);
    pushButtonDown->setObjectName(QString::fromUtf8("pushButtonDown"));

    hboxLayout2->addWidget(pushButtonDown);

    pushButtonUp = new QPushButton(frameRight);
    pushButtonUp->setObjectName(QString::fromUtf8("pushButtonUp"));

    hboxLayout2->addWidget(pushButtonUp);


    vboxLayout->addLayout(hboxLayout2);

    pushButtonSubd = new QPushButton(frameRight);
    pushButtonSubd->setObjectName(QString::fromUtf8("pushButtonSubd"));

    vboxLayout->addWidget(pushButtonSubd);

    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    vboxLayout->addItem(spacerItem);

    labelMeshInfo = new QLabel(frameRight);
    labelMeshInfo->setObjectName(QString::fromUtf8("labelMeshInfo"));

    vboxLayout->addWidget(labelMeshInfo);

    textEditMeshInfo = new QTextEdit(frameRight);
    textEditMeshInfo->setObjectName(QString::fromUtf8("textEditMeshInfo"));
    textEditMeshInfo->setReadOnly(true);

    vboxLayout->addWidget(textEditMeshInfo);

    spacerItem1 = new QSpacerItem(20, 281, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem1);


    gridLayout->addWidget(frameRight, 1, 1, 1, 1);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 650, 25));
    menu_File = new QMenu(menubar);
    menu_File->setObjectName(QString::fromUtf8("menu_File"));
    menu_Edit = new QMenu(menubar);
    menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    QWidget::setTabOrder(radioButtonDraw, radioButtonSmooth);
    QWidget::setTabOrder(radioButtonSmooth, radioButtonPinch);
    QWidget::setTabOrder(radioButtonPinch, spinBoxSize);
    QWidget::setTabOrder(spinBoxSize, horizontalSliderSize);
    QWidget::setTabOrder(horizontalSliderSize, spinBoxStrength);
    QWidget::setTabOrder(spinBoxStrength, horizontalSliderStrength);
    QWidget::setTabOrder(horizontalSliderStrength, pushButtonDown);
    QWidget::setTabOrder(pushButtonDown, pushButtonUp);
    QWidget::setTabOrder(pushButtonUp, pushButtonSubd);

    menubar->addAction(menu_File->menuAction());
    menubar->addAction(menu_Edit->menuAction());
    menu_File->addAction(actionImport);
    menu_File->addAction(actionExport);
    menu_File->addSeparator();
    menu_File->addAction(actionQuit);
    menu_Edit->addAction(actionUndo);
    menu_Edit->addAction(actionRedo);

    retranslateUi(MainWindow);
    QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
    QObject::connect(horizontalSliderSize, SIGNAL(valueChanged(int)), spinBoxSize, SLOT(setValue(int)));
    QObject::connect(horizontalSliderStrength, SIGNAL(valueChanged(int)), spinBoxStrength, SLOT(setValue(int)));
    QObject::connect(spinBoxSize, SIGNAL(valueChanged(int)), horizontalSliderSize, SLOT(setValue(int)));
    QObject::connect(spinBoxStrength, SIGNAL(valueChanged(int)), horizontalSliderStrength, SLOT(setValue(int)));
    QObject::connect(spinBoxIntencity, SIGNAL(valueChanged(int)), horizontalSliderIntencity, SLOT(setValue(int)));
    QObject::connect(horizontalSliderIntencity, SIGNAL(valueChanged(int)), spinBoxIntencity, SLOT(setValue(int)));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    MainWindow->setStyleSheet(QApplication::translate("MainWindow", "QWidget{\n"
"	background-color: #9c978c;\n"
"	color: #fff;\n"
"	font-size: 12px;\n"
"}\n"
"\n"
"\n"
"QFrame{\n"
"	border: 1px solid #675f4b;\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"QGroupBox{\n"
"	border: 1px solid #675f4b;\n"
"	border-radius: 5px;\n"
"	padding: 5px 0px;\n"
"	margin-top: 6px;\n"
"	font-weight: bold;\n"
"}\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: center top;\n"
"	padding: 0px 10px;\n"
"} \n"
"\n"
"\n"
"QPushButton{\n"
"	border-width: 1px;\n"
"	border-style: solid;\n"
"	border-color:  #534b3a;\n"
"	border-radius: 10px;\n"
"	height: 22px;\n"
"	min-height: 22px;\n"
"	max-height: 22px;\n"
"	padding: 0px 15px;\n"
"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                  stop: 0 #6f644b, stop: 1 #3f3828);\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                  stop: 0 #6f644b,\n"
"                                      stop: 0.5 #6f644b,\n"
""
        "                                      stop: 1 #3f3828);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: #534b3a;\n"
"}\n"
"\n"
"\n"
"QMenuBar{\n"
"	background-color: #7d796f;\n"
"}\n"
"QMenuBar::item{\n"
"	background-color: #7d796f;\n"
"}\n"
"QMenuBar::item:selected{\n"
"	background-color: #8f8f8f;\n"
"}\n"
"\n"
"\n"
"QMenu {\n"
"	background-color: #7d796f;\n"
"	border: 1px solid #8f8f8f;\n"
"}\n"
"QMenu::item {\n"
"	padding: 0px 30px 0px 10px;\n"
"	background-color: transparent;\n"
"}\n"
"QMenu::item:selected{\n"
"	background-color: #8f8f8f;\n"
"}\n"
"QMenu::item:disabled{\n"
"	color: #aaa;\n"
"}\n"
"QMenu::separator{\n"
"	height: 1px;\n"
"	margin: 2px 5px;\n"
"	background-color: #534b3a;\n"
"}\n"
"\n"
"\n"
"QSpinBox{\n"
"	background-color: #e9e9e9;\n"
"	color: #000;\n"
"	border: 1px solid #000;\n"
"	border-radius: 2px;\n"
"	padding-right: 20px;\n"
"}\n"
"QSpinBox::up-button {\n"
"	subcontrol-position: top right;\n"
"	width: 18px;\n"
"	border-image: url(:/images/res/spinboxup.png) 1;\n"
"}\n"
"QSpinBox:"
        ":down-button {\n"
"	subcontrol-position: bottom right;\n"
"	width: 18px;\n"
"	border-image: url(:/images/res/spinboxdown.png) 1;\n"
"}\n"
"QSpinBox::up-arrow {\n"
"	image: url(:/images/res/arrowup.png);\n"
"	width: 5px;\n"
"	height: 5px;\n"
"}\n"
"QSpinBox::down-arrow {\n"
"	image: url(:/images/res/arrowdown.png);\n"
"	width: 5px;\n"
"	height: 5px;\n"
"}\n"
"QSpinBox::up-arrow:pressed{\n"
"	image: url(:/images/res/arrowup_pressed.png);\n"
"}\n"
"QSpinBox::down-arrow:pressed{\n"
"	image: url(:/images/res/arrowdown_pressed.png);\n"
"}\n"
"\n"
"\n"
"QLabel{\n"
"	background-color: #9c927b;\n"
"	height: 15px;\n"
"	min-height: 15px;\n"
"	max-height: 15px;\n"
"	padding: 0px 10px;\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"\n"
"QSlider::groove:horizontal {\n"
"	border: 1px solid #000;\n"
"	height: 2px;\n"
"	background-color: #fff;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	border: 1px solid #000;\n"
"	border-radius: 4px;\n"
"	height: 5px;\n"
"	width: 20px;\n"
"	background-color: #86734e;\n"
"	margin: -5px 0px;\n"
"}\n"
""
        "\n"
"\n"
"QRadioButton::indicator {\n"
"	width: 15px;\n"
"	height: 15px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"	image: url(:/images/res/radiobutton_unchecked.png);\n"
"}\n"
"QRadioButton::indicator:unchecked:pressed {\n"
"	image: url(:/images/res/radiobutton_unchecked_pressed.png);\n"
"}\n"
"QRadioButton::indicator::checked {\n"
"	image: url(:/images/res/radiobutton_checked.png);\n"
"}\n"
"QRadioButton::indicator:checked:pressed {\n"
"	image: url(:/images/res/radiobutton_checked_pressed.png);\n"
"} \n"
"\n"
"\n"
"QCheckBox::indicator {\n"
"	width: 15px;\n"
"	height: 15px;\n"
"}\n"
"QCheckBox::indicator::unchecked {\n"
"	image: url(:/images/res/checkbox_unchecked.png);\n"
"}\n"
"QCheckBox::indicator:unchecked:pressed {\n"
"	image: url(:/images/res/checkbox_unchecked_pressed.png);\n"
"}\n"
"QCheckBox::indicator::checked {\n"
"	image: url(:/images/res/checkbox_checked.png);\n"
"}\n"
"QCheckBox::indicator:checked:pressed {\n"
"	image: url(:/images/res/checkbox_checked_pressed.png);\n"
"} \n"
"\n"
"QAc"
        "tion{\n"
"	background-color: #f00;\n"
"}\n"
"\n"
"QTextEdit{\n"
"	padding: 20px 10px;\n"
"	max-height: 60px;\n"
"}", 0, QApplication::UnicodeUTF8));
    actionImport->setText(QApplication::translate("MainWindow", "&Import", 0, QApplication::UnicodeUTF8));
    actionExport->setText(QApplication::translate("MainWindow", "&Export", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
    actionUndo->setText(QApplication::translate("MainWindow", "&Undo", 0, QApplication::UnicodeUTF8));
    actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
    actionRedo->setText(QApplication::translate("MainWindow", "&Redo", 0, QApplication::UnicodeUTF8));
    actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
    groupBoxBrush->setTitle(QApplication::translate("MainWindow", "Brush", 0, QApplication::UnicodeUTF8));
    radioButtonDraw->setText(QApplication::translate("MainWindow", "&Draw", 0, QApplication::UnicodeUTF8));
    radioButtonSmooth->setText(QApplication::translate("MainWindow", "&Smooth", 0, QApplication::UnicodeUTF8));
    radioButtonPinch->setText(QApplication::translate("MainWindow", "&Pinch", 0, QApplication::UnicodeUTF8));
    labelSize->setText(QApplication::translate("MainWindow", "Size", 0, QApplication::UnicodeUTF8));
    labelIntencity->setText(QApplication::translate("MainWindow", "Intencity", 0, QApplication::UnicodeUTF8));
    labelStrength->setText(QApplication::translate("MainWindow", "Strength", 0, QApplication::UnicodeUTF8));
    labelGeometry->setText(QApplication::translate("MainWindow", "Geometry", 0, QApplication::UnicodeUTF8));
    pushButtonDown->setText(QApplication::translate("MainWindow", "down", 0, QApplication::UnicodeUTF8));
    pushButtonUp->setText(QApplication::translate("MainWindow", "up", 0, QApplication::UnicodeUTF8));
    pushButtonSubd->setText(QApplication::translate("MainWindow", "subdivide", 0, QApplication::UnicodeUTF8));
    labelMeshInfo->setText(QApplication::translate("MainWindow", "Mesh Info", 0, QApplication::UnicodeUTF8));
    menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
