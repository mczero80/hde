/****************************************************************************
 **
 **				hcloseframe.h
 **			=========================
 **
 **  begin                : Tue Jul 02 2002
 **  copyright            : (C) 2002-2006 by Haydar Alkaduhimi, under GPL
 **  email                : haydar@haydarnet.nl
 **
****************************************************************************/
#ifndef HCLOSEFRAME_H
#define HCLOSEFRAME_H

#include <qvariant.h>
#include <qwidget.h>
#include <qlist.h> 
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QtDesigner/QDesignerExportWidget>

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QToolButton;


class QDESIGNER_WIDGET_EXPORT HCloseFrame : public QWidget
{ 
    Q_OBJECT
    Q_PROPERTY( QString caption READ caption WRITE changeCaption )

 public:
    HCloseFrame( QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~HCloseFrame();

    void changeCaption(const QString &cap);
    void addWidget(QWidget *w);

    void hideWidgets();
    void showWidgets();

    QLabel* captionLable;
    QToolButton* closeBtn;
    QToolButton* hideBtn;

    bool hidden;
    QString caption() const;

 protected:
    QList<QWidget*> widgetList;
    QVBoxLayout* wdgetLayout;
    QHBoxLayout* captionLayout;

 public slots:
    void showHideWidgets();


};

#endif // HCLOSEFRAME_H
