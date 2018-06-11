#include <QPluginLoader>
#include <QtCore/qplugin.h>
#include <QtPlugin>

#include "plugin.h"
#include "../../include/hcloseframe.h"
#include "../../include/hcalender.h"
#include "../../include/hclock.h"
#include "../../include/hfilelist.h"
//#include "../../include/hdirlist.h"
#include "../../include/hfilewidget.h"
#include "../../include/himagevw.h"
#include <QPixmap>




/*********************************************************************
 *
 * HCloseFramePlugin
 *
 ********************************************************************/
QWidget* HCloseFramePlugin::createWidget(QWidget* parent)
{
  return new HCloseFrame( parent );
}

QIcon HCloseFramePlugin::icon() const
{
  return QIcon( QPixmap(":/images/hcloseframe.png" ) );
}




/*********************************************************************
 *
 * HCalenderPlugin
 *
 ********************************************************************/
QWidget* HCalenderPlugin::createWidget(QWidget* parent)
{
  return new HCalender( parent );
}

QIcon HCalenderPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/hcalender.png" ) );
}



/*********************************************************************
 *
 * HClockPlugin
 *
 ********************************************************************/
QWidget* HClockPlugin::createWidget(QWidget* parent)
{
  return new HClock( parent , "name", QTime::currentTime());
}

QIcon HClockPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/hclock.png" ) );
}



/*********************************************************************
 *
 * HFileListPlugin
 *
 ********************************************************************/
QWidget* HFileListPlugin::createWidget(QWidget* parent)
{
  return new HFileList( "/", parent );
}

QIcon HFileListPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/hfilelist.png" ) );
}



/*********************************************************************
 *
 * HDirListPlugin
 *
 ********************************************************************/
/*
QWidget* HDirListPlugin::createWidget(QWidget* parent)
{
  return new HDirList( "/", parent );
}

QIcon HDirListPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/hdirlist.png" ) );
}
*/




/*********************************************************************
 *
 * fileWidgetPlugin
 *
 ********************************************************************/
QWidget* fileWidgetPlugin::createWidget(QWidget* parent)
{
  return new HFileWidget( parent );
}

QIcon fileWidgetPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/filewidget.png" ) );
}




/*********************************************************************
 *
 * HImageViewPlugin
 *
 ********************************************************************/
QWidget* HImageViewPlugin::createWidget(QWidget* parent)
{
  return new HImageView( parent );
}

QIcon HImageViewPlugin::icon() const
{
  return QIcon( QPixmap( ":/images/himagevw.png" ) );
}




/*********************************************************************
 *
 * HdePlugins
 *
 ********************************************************************/
QList<QDesignerCustomWidgetInterface*> HdePlugins::customWidgets() const
{
  QList<QDesignerCustomWidgetInterface*> plugins;
  plugins
    << new HCloseFramePlugin
    << new HCalenderPlugin
    << new HClockPlugin
    << new HFileListPlugin
    << new fileWidgetPlugin
    << new HImageViewPlugin;
  return plugins;

  /*
    << new HDirListPlugin

   */
}

Q_EXPORT_PLUGIN(HdePlugins)
