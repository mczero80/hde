/****************************************************************************
**
**	hmime.h
**
****************************************************************************/
#include <qpixmap.h>
#include <qstring.h>
#include <qlist.h>

struct mimeItem
{
  QString ext;
  QString name;
  QString exec;
  QString mimeType;
  QString iconName;
  bool operator== ( const mimeItem & other ) const
   {
     if( (other.ext == ext) && (other.name == name) && (other.exec == exec)
	 && (other.mimeType == mimeType)  && (other.iconName == iconName))
       return true;

     return false;
   };
};

/*****************************************************************************
 *
 * Class HMimeTypes
 *
 *****************************************************************************/

class HMimeTypes
{
 public:
  QPixmap filepix16;
  QPixmap filepix32;
  QPixmap filepix48;
  QPixmap folderpix16;
  QPixmap folderpix32;
  QPixmap folderpix48;
  void readMimeTypes();
  mimeItem *findMime(QString ext);
  QPixmap findIcon(QString ext, bool exec, QString size = QString::null); 
  bool hasType( QString ext, QString type);

 private:
  QString findIconName(QString ext);
  void readDir( QString path, QString dir);
  void readFile( QString path, QString file);
  static QList<mimeItem> mimeList;

};
