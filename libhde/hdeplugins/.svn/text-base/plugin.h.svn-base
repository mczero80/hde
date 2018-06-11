
#include <QtDesigner/QDesignerCustomWidgetInterface>
//#include <qwidgetplugin.h>




class hdePlugin : public QDesignerCustomWidgetInterface {
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    bool m_initialized;
  
 public:
  hdePlugin() : m_initialized(false) { };
    virtual bool isContainer() const     { return false;         };
    bool isInitialized() const   { return m_initialized; };
    //QIcon icon() const           { return QIcon();       };
    virtual QString codeTemplate() const { return QString();     };
    QString whatsThis() const    { return name();     };
    QString toolTip() const      { return name();     };
    QString group() const        { return "HDE Widgets"; };
    virtual QString name() const        { return QString(); };
    void initialize(QDesignerFormEditorInterface *) {
      if (m_initialized)
	return;
      m_initialized = true;
    };
};

/*********************************************************************
 *
 * HCloseFramePlugin
 *
 ********************************************************************/
class HCloseFramePlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HCloseFramePlugin(QObject* parent = 0) : QObject(parent) {};
  virtual bool isContainer() const     { return true;         };
  QString includeFile() const { return QString("hcloseframe.h"); };
  virtual QString name() const        { return "HCloseFrame"; };
  QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};



/*********************************************************************
 *
 * HCalenderPlugin
 *
 ********************************************************************/
class HCalenderPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HCalenderPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("hcalender.h"); };
  QString name() const        { return "HCalender"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};


/*********************************************************************
 *
 * HClockPlugin
 *
 ********************************************************************/
class HClockPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HClockPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("hclock.h"); };
  QString name() const        { return "HClock"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};


/*********************************************************************
 *
 * HFileListPlugin
 *
 ********************************************************************/
class HFileListPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HFileListPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("hfilelist.h"); };
  QString name() const        { return "HFileList"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};



/*********************************************************************
 *
 * HDirListPlugin
 *
 ********************************************************************/
/*
class HDirListPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HDirListPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("hdirlist.h"); };
  QString name() const        { return "HDirList"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};
*/



/*********************************************************************
 *
 * fileWidgetPlugin
 *
 ********************************************************************/
class fileWidgetPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  fileWidgetPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("hfilewidget.h"); };
  virtual QString name() const        { return "HFileWidget"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};


/*********************************************************************
 *
 *  HImageViewPlugin
 *
 ********************************************************************/
class HImageViewPlugin : public QObject, public hdePlugin {
  Q_OBJECT   
 public:
  HImageViewPlugin(QObject* parent = 0) : QObject(parent) {};
  QString includeFile() const { return QString("himagevw.h"); };
  virtual QString name() const        { return "HImageView"; };
  virtual QIcon icon() const;
  QWidget* createWidget(QWidget* parent);;
};



/*********************************************************************
 *
 * HdePlugins
 *
 ********************************************************************/
class HdePlugins: public QObject,
  public QDesignerCustomWidgetCollectionInterface 
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
 public:
  QList<QDesignerCustomWidgetInterface*> customWidgets() const;
};
