/*
// Including the ui generated form
#ifndef UI_HIMAGEVW_H
#define UI_HIMAGEVW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_HImageView
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QFrame *leftFrame;
    QHBoxLayout *hboxLayout1;
    QSplitter *splitter;
    QTreeView *dirTree;
    QListWidget *imagesList;
    QFrame *splitterFrame;
    QVBoxLayout *vboxLayout1;
    QPushButton *splitcloseBtn;
    QSpacerItem *spacerItem;
    QPushButton *resizesplitBtn;
    QSpacerItem *spacerItem1;
    QLabel *imageLabel;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem2;
    QPushButton *prevBtn;
    QPushButton *nextBtn;
    QFrame *frame;
    QPushButton *bestfitBtn;
    QPushButton *actualsizeBtn;
    QFrame *frame_2;
    QPushButton *magplusBtn;
    QPushButton *magminBtn;
    QFrame *frame_3;
    QPushButton *rotatecclockBtn;
    QPushButton *rotateclickBtn;
    QFrame *frame_4;
    QPushButton *closeBtn;
    QPushButton *aboutBtn;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *HImageView)
    {
    if (HImageView->objectName().isEmpty())
        HImageView->setObjectName(QString::fromUtf8("HImageView"));
    QSize size(708, 500);
    size = size.expandedTo(HImageView->minimumSizeHint());
    HImageView->resize(size);
    vboxLayout = new QVBoxLayout(HImageView);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    leftFrame = new QFrame(HImageView);
    leftFrame->setObjectName(QString::fromUtf8("leftFrame"));
    leftFrame->setMinimumSize(QSize(0, 0));
    leftFrame->setMaximumSize(QSize(176, 16777215));
    leftFrame->setFrameShape(QFrame::StyledPanel);
    leftFrame->setFrameShadow(QFrame::Raised);
    hboxLayout1 = new QHBoxLayout(leftFrame);
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    splitter = new QSplitter(leftFrame);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setMinimumSize(QSize(160, 16));
    splitter->setMaximumSize(QSize(16777215, 16777215));
    splitter->setOrientation(Qt::Vertical);
    dirTree = new QTreeView(splitter);
    dirTree->setObjectName(QString::fromUtf8("dirTree"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(10);
    sizePolicy.setHeightForWidth(dirTree->sizePolicy().hasHeightForWidth());
    dirTree->setSizePolicy(sizePolicy);
    dirTree->setFocusPolicy(Qt::NoFocus);
    splitter->addWidget(dirTree);
    imagesList = new QListWidget(splitter);
    imagesList->setObjectName(QString::fromUtf8("imagesList"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(20);
    sizePolicy1.setHeightForWidth(imagesList->sizePolicy().hasHeightForWidth());
    imagesList->setSizePolicy(sizePolicy1);
    imagesList->setFocusPolicy(Qt::NoFocus);
    splitter->addWidget(imagesList);

    hboxLayout1->addWidget(splitter);

    splitterFrame = new QFrame(leftFrame);
    splitterFrame->setObjectName(QString::fromUtf8("splitterFrame"));
    splitterFrame->setMinimumSize(QSize(16, 30));
    splitterFrame->setMaximumSize(QSize(16, 16777215));
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(171, 170, 173, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    QBrush brush2(QColor(213, 212, 214, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
    QBrush brush3(QColor(85, 85, 86, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Dark, brush3);
    QBrush brush4(QColor(114, 113, 115, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
    palette.setBrush(QPalette::Active, QPalette::Text, brush);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    QBrush brush5(QColor(255, 255, 255, 255));
    brush5.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush5);
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
    palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush5);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
    palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
    palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
    palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
    splitterFrame->setPalette(palette);
    splitterFrame->setAutoFillBackground(true);
    splitterFrame->setFrameShape(QFrame::StyledPanel);
    splitterFrame->setFrameShadow(QFrame::Sunken);
    vboxLayout1 = new QVBoxLayout(splitterFrame);
    vboxLayout1->setSpacing(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(0, 0, 0, 0);
    splitcloseBtn = new QPushButton(splitterFrame);
    splitcloseBtn->setObjectName(QString::fromUtf8("splitcloseBtn"));
    splitcloseBtn->setMinimumSize(QSize(14, 14));
    splitcloseBtn->setMaximumSize(QSize(14, 14));
    splitcloseBtn->setIcon(QIcon(QString::fromUtf8(":/images/close.png")));
    splitcloseBtn->setFlat(true);

    vboxLayout1->addWidget(splitcloseBtn);

    spacerItem = new QSpacerItem(20, 161, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem);

    resizesplitBtn = new QPushButton(splitterFrame);
    resizesplitBtn->setObjectName(QString::fromUtf8("resizesplitBtn"));
    resizesplitBtn->setMinimumSize(QSize(14, 30));
    resizesplitBtn->setMaximumSize(QSize(14, 30));
    resizesplitBtn->setFocusPolicy(Qt::NoFocus);

    vboxLayout1->addWidget(resizesplitBtn);

    spacerItem1 = new QSpacerItem(16, 190, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem1);


    hboxLayout1->addWidget(splitterFrame);


    hboxLayout->addWidget(leftFrame);

    imageLabel = new QLabel(HImageView);
    imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
    imageLabel->setSizePolicy(sizePolicy2);
    imageLabel->setFocusPolicy(Qt::StrongFocus);
    imageLabel->setAlignment(Qt::AlignCenter);

    hboxLayout->addWidget(imageLabel);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    hboxLayout2->setContentsMargins(5, 5, 5, 5);
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem2);

    prevBtn = new QPushButton(HImageView);
    prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
    prevBtn->setMinimumSize(QSize(22, 22));
    prevBtn->setMaximumSize(QSize(22, 22));
    prevBtn->setFocusPolicy(Qt::NoFocus);
    prevBtn->setIcon(QIcon(QString::fromUtf8(":/images/back.png")));
    prevBtn->setIconSize(QSize(22, 22));
    prevBtn->setFlat(true);

    hboxLayout2->addWidget(prevBtn);

    nextBtn = new QPushButton(HImageView);
    nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
    nextBtn->setMinimumSize(QSize(22, 22));
    nextBtn->setMaximumSize(QSize(22, 22));
    nextBtn->setFocusPolicy(Qt::NoFocus);
    nextBtn->setIcon(QIcon(QString::fromUtf8(":/images/forward.png")));
    nextBtn->setIconSize(QSize(22, 22));
    nextBtn->setFlat(true);

    hboxLayout2->addWidget(nextBtn);

    frame = new QFrame(HImageView);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::VLine);
    frame->setFrameShadow(QFrame::Sunken);

    hboxLayout2->addWidget(frame);

    bestfitBtn = new QPushButton(HImageView);
    bestfitBtn->setObjectName(QString::fromUtf8("bestfitBtn"));
    bestfitBtn->setEnabled(false);
    bestfitBtn->setMinimumSize(QSize(22, 22));
    bestfitBtn->setMaximumSize(QSize(22, 22));
    bestfitBtn->setFocusPolicy(Qt::NoFocus);
    bestfitBtn->setIcon(QIcon(QString::fromUtf8(":/images/bestfit.png")));
    bestfitBtn->setIconSize(QSize(22, 22));
    bestfitBtn->setFlat(true);

    hboxLayout2->addWidget(bestfitBtn);

    actualsizeBtn = new QPushButton(HImageView);
    actualsizeBtn->setObjectName(QString::fromUtf8("actualsizeBtn"));
    actualsizeBtn->setEnabled(false);
    actualsizeBtn->setMinimumSize(QSize(22, 22));
    actualsizeBtn->setMaximumSize(QSize(22, 22));
    actualsizeBtn->setFocusPolicy(Qt::NoFocus);
    actualsizeBtn->setIcon(QIcon(QString::fromUtf8(":/images/actualsize.png")));
    actualsizeBtn->setIconSize(QSize(22, 22));
    actualsizeBtn->setFlat(true);

    hboxLayout2->addWidget(actualsizeBtn);

    frame_2 = new QFrame(HImageView);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setFrameShape(QFrame::VLine);
    frame_2->setFrameShadow(QFrame::Sunken);

    hboxLayout2->addWidget(frame_2);

    magplusBtn = new QPushButton(HImageView);
    magplusBtn->setObjectName(QString::fromUtf8("magplusBtn"));
    magplusBtn->setMinimumSize(QSize(22, 22));
    magplusBtn->setMaximumSize(QSize(22, 22));
    magplusBtn->setFocusPolicy(Qt::NoFocus);
    magplusBtn->setIcon(QIcon(QString::fromUtf8(":/images/viewmag+.png")));
    magplusBtn->setIconSize(QSize(22, 22));
    magplusBtn->setFlat(true);

    hboxLayout2->addWidget(magplusBtn);

    magminBtn = new QPushButton(HImageView);
    magminBtn->setObjectName(QString::fromUtf8("magminBtn"));
    magminBtn->setMinimumSize(QSize(22, 22));
    magminBtn->setMaximumSize(QSize(22, 22));
    magminBtn->setFocusPolicy(Qt::NoFocus);
    magminBtn->setIcon(QIcon(QString::fromUtf8(":/images/viewmag-.png")));
    magminBtn->setIconSize(QSize(22, 22));
    magminBtn->setFlat(true);

    hboxLayout2->addWidget(magminBtn);

    frame_3 = new QFrame(HImageView);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    frame_3->setFrameShape(QFrame::VLine);
    frame_3->setFrameShadow(QFrame::Sunken);

    hboxLayout2->addWidget(frame_3);

    rotatecclockBtn = new QPushButton(HImageView);
    rotatecclockBtn->setObjectName(QString::fromUtf8("rotatecclockBtn"));
    rotatecclockBtn->setMinimumSize(QSize(22, 22));
    rotatecclockBtn->setMaximumSize(QSize(22, 22));
    rotatecclockBtn->setFocusPolicy(Qt::NoFocus);
    rotatecclockBtn->setIcon(QIcon(QString::fromUtf8(":/images/undo.png")));
    rotatecclockBtn->setIconSize(QSize(22, 22));
    rotatecclockBtn->setFlat(true);

    hboxLayout2->addWidget(rotatecclockBtn);

    rotateclickBtn = new QPushButton(HImageView);
    rotateclickBtn->setObjectName(QString::fromUtf8("rotateclickBtn"));
    rotateclickBtn->setMinimumSize(QSize(22, 22));
    rotateclickBtn->setMaximumSize(QSize(22, 22));
    rotateclickBtn->setFocusPolicy(Qt::NoFocus);
    rotateclickBtn->setIcon(QIcon(QString::fromUtf8(":/images/redo.png")));
    rotateclickBtn->setIconSize(QSize(22, 22));
    rotateclickBtn->setFlat(true);

    hboxLayout2->addWidget(rotateclickBtn);

    frame_4 = new QFrame(HImageView);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    frame_4->setMinimumSize(QSize(10, 16));
    frame_4->setFrameShape(QFrame::VLine);
    frame_4->setFrameShadow(QFrame::Sunken);

    hboxLayout2->addWidget(frame_4);

    closeBtn = new QPushButton(HImageView);
    closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
    closeBtn->setMinimumSize(QSize(22, 22));
    closeBtn->setMaximumSize(QSize(22, 22));
    closeBtn->setIcon(QIcon(QString::fromUtf8(":/images/cancel.png")));
    closeBtn->setIconSize(QSize(22, 22));
    closeBtn->setFlat(true);

    hboxLayout2->addWidget(closeBtn);

    aboutBtn = new QPushButton(HImageView);
    aboutBtn->setObjectName(QString::fromUtf8("aboutBtn"));
    aboutBtn->setMinimumSize(QSize(22, 22));
    aboutBtn->setMaximumSize(QSize(22, 22));
    aboutBtn->setFocusPolicy(Qt::NoFocus);
    aboutBtn->setIcon(QIcon(QString::fromUtf8(":/images/info.png")));
    aboutBtn->setIconSize(QSize(22, 22));
    aboutBtn->setFlat(true);

    hboxLayout2->addWidget(aboutBtn);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem3);


    vboxLayout->addLayout(hboxLayout2);


    retranslateUi(HImageView);
    //QObject::connect(closeBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    QMetaObject::connectSlotsByName(HImageView);
    } // setupUi

    void retranslateUi(QWidget *HImageView)
    {
    HImageView->setWindowTitle(QApplication::translate("HImageView", "Haydar Image Viewer", 0, QApplication::UnicodeUTF8));
    splitcloseBtn->setText(QString());
    resizesplitBtn->setText(QApplication::translate("HImageView", "<", 0, QApplication::UnicodeUTF8));
    imageLabel->setText(QString());
    prevBtn->setText(QString());
    prevBtn->setShortcut(QApplication::translate("HImageView", "Left", 0, QApplication::UnicodeUTF8));
    nextBtn->setText(QString());
    nextBtn->setShortcut(QApplication::translate("HImageView", "Right", 0, QApplication::UnicodeUTF8));
    bestfitBtn->setToolTip(QApplication::translate("HImageView", "Best Fit", 0, QApplication::UnicodeUTF8));
    bestfitBtn->setText(QString());
    magplusBtn->setText(QString());
    magplusBtn->setShortcut(QApplication::translate("HImageView", "+", 0, QApplication::UnicodeUTF8));
    magminBtn->setText(QString());
    magminBtn->setShortcut(QApplication::translate("HImageView", "-", 0, QApplication::UnicodeUTF8));
    rotatecclockBtn->setText(QString());
    rotateclickBtn->setText(QString());
    closeBtn->setText(QString());
    closeBtn->setShortcut(QApplication::translate("HImageView", "Ctrl+S", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(HImageView);
    } // retranslateUi

};

namespace Ui {
    class HImageView: public Ui_HImageView {};
} // namespace Ui

#endif // UI_HIMAGEVW_H

*/




#ifndef HIMAGEVW_H
#define HIMAGEVW_H

#include <QtGui>


class HImageView: public QWidget
{
    Q_OBJECT

 public:
  HImageView(QWidget *parent = 0);
  ~HImageView(){};
  void load( QString file);
  QPushButton *closeBtn;

 public slots:
  void closeLeftSide();
  void resizeLeftSide();
  void dirActivated ( const QModelIndex & );
  void currentFileChanged ( QListWidgetItem *, QListWidgetItem * );
  void prevClicked();
  void nextClicked();
  void magplusClicked();
  void magminClicked();
  void rotatecclockClicked();
  void rotateclickClicked();
  void aboutClicked();
  
 private:
  void initUi();
  void retranslateUi();
  void buildDirTree();
  QFrame *leftFrame;
  QSplitter *splitter;
  QPushButton *splitcloseBtn;
  QPushButton *resizesplitBtn;
  QTreeView *dirTree;
  QListWidget *imagesList;
  QLabel *imageLabel;
  QPushButton *prevBtn;
  QPushButton *nextBtn;
  QPushButton *bestfitBtn;
  QPushButton *actualsizeBtn;
  QPushButton *magplusBtn;
  QPushButton *magminBtn;
  QPushButton *rotatecclockBtn;
  QPushButton *rotateclickBtn;
  QPushButton *aboutBtn;
  bool leftsideHidden;
  QString curDir;
};

#endif
