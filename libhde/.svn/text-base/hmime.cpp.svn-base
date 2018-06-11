/****************************************************************************
 **
 **				hmime.cpp
 **			=========================
 **
 **  begin                : Fri Aug 01 2003
 **  copyright            : (C) 2003 - 2005 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A class for reading and storing Mimetypes.
 **
 ****************************************************************************/
#include "hmime.h"
#include "conf.h"
#include <qdir.h>
#include <qfileinfo.h>
#include <qstringlist.h> 

#include <qpixmapcache.h>
#include <qmime.h>

#include <libhde.h> 
#include <defaults.h>
#include <hinifile.h>

QList<mimeItem> HMimeTypes::mimeList;

static QPixmap load_pixmap( const QString &name )
{
  //  QString nam = ":/images/" + name;
  QPixmap pix(":/images/" + name);
  return pix;
}

static QPixmap uic_load_pixmap_fileWidget( const QString &name )
{/*
    const QMimeSource *m = QMimeSourceFactory::defaultFactory()->data( name );
    if ( !m )
	return QPixmap();
    QPixmap pix;
    QImageDrag::decode( m, pix );
    return pix;
 */
  return load_pixmap( name );
}

void HMimeTypes::readMimeTypes()
{
    filepix16 =QPixmap(get_ifile("unknown.png", "mini", "mime"));
    if(filepix16.isNull())
	    filepix16 = uic_load_pixmap_fileWidget("file16.png");  
    
    filepix32 =QPixmap(get_ifile("unknown.png", "mid", "mime"));
    if(filepix32.isNull())
	    filepix32 = uic_load_pixmap_fileWidget("file32.png");  
    
    filepix48 =QPixmap(get_ifile("unknown.png", "large", "mime"));
    if(filepix48.isNull())
	    filepix48 = uic_load_pixmap_fileWidget("file.png");  
    
    
    folderpix16 =QPixmap(get_ifile("folder_yellow.png", "mini", "mime"));
    if(folderpix16.isNull())
	    folderpix16 = uic_load_pixmap_fileWidget("folder16.png");  
    
    folderpix32 =QPixmap(get_ifile("folder_yellow.png", "mid", "mime"));
    if(folderpix32.isNull())
	    folderpix32 = uic_load_pixmap_fileWidget("folder32.png");  
    
    folderpix48 =QPixmap(get_ifile("folder_yellow.png", "large", "mime"));
    if(folderpix48.isNull())
	    folderpix48 = uic_load_pixmap_fileWidget("folder.png");  
    
    readDir( "/usr/share/mimelnk", "" );
    readDir( "/usr/share/applications", "" );
    QString fname(getenv("HOME"));
    readDir( fname + "/.hde/applnk", "" );
    readDir(  CONFDIR + QString("/applnk"), "" );

}

void HMimeTypes::readDir( QString path, QString dir)
{
    if(dir == "." | dir == ".." | dir == "CVS")
	return;

    QDir d( path + "/" + dir );

    if(d.exists()){
      /*
     QDir dir;
     dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
     dir.setSorting(QDir::Size | QDir::Reversed);

     QFileInfoList list = dir.entryInfoList();
     std::cout << "     Bytes Filename" << std::endl;
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                 .arg(fileInfo.fileName()));
         std::cout << std::endl;
     }
      */

	d.setFilter( QDir::Dirs | QDir::Files);
	d.setSorting(QDir::Name | QDir::DirsFirst );
	QFileInfoList list = d.entryInfoList();
	QFileInfo fi;
	
     for (int i = 0; i < list.size(); ++i) {
       //	while ( (fi=it.current()) ) {
       fi = list.at(i);
       if(fi.isDir()){
	 readDir( d.path(), fi.fileName());
	 
       }else if(fi.isFile() && (fi.suffix()  == "hdelnk" || 
				 fi.suffix() == "kdelnk" ||
				 fi.suffix() == "desktop" ))
	 readFile( d.path(), fi.fileName() );
     }
    }


    //    cout << dir << endl;
}


void HMimeTypes::readFile( QString path, QString file)
{
    QString svar, name, patterns, exec, icon, mimeType;
    HIniFile lnkIni(path + "/" + file);

    //lnkIni.read();
    lnkIni.setGroup("Desktop Entry");

    svar = lnkIni.readString("MimeType", "");

    mimeType = svar.left( svar.indexOf('/') );

    //    if(! mimeType.isNull() )
    //cout << mimeType << endl;

//    name = lnkIni.readString("Name["+ defaults::lng + "]" , 
//			     lnkIni.readString("Name["+ defaults::lng.left(2) 
//					       + "]", name));
//    if(name.isNull())
	name = lnkIni.readString("Name", file );

    exec = lnkIni.readString("Exec", "" );

    icon = lnkIni.readString("Icon", "" );

    if(svar != ""){
	svar = "/usr/share/mimelnk/" + svar;
	if( !QFileInfo::QFileInfo(svar).isFile())
	    svar = svar + ".desktop";


	if(QFileInfo::QFileInfo(svar).isFile()){
	    HIniFile mimeIni(svar);
	    //mimeIni.read();
	    mimeIni.setGroup("Desktop Entry");

//	    name = mimeIni.readString("Comment["+ defaults::lng + "]" , 
//				mimeIni.readString("Comment["+ 
//						  defaults::lng.left(2) + "]", 
//						  name));
//	    if(name.isNull())
		name = mimeIni.readString("Comment", name );

	    patterns = mimeIni.readString("Patterns", "");

	    
	    exec = mimeIni.readString("BinaryPattern", exec );

	    icon = mimeIni.readString("Icon", icon );

	    //cout << name << endl;

	}
    }

    exec = lnkIni.readString("BinaryPattern", exec );
    patterns = lnkIni.readString("Patterns", patterns);

    QStringList patternList = patterns.split( ";" );

    for ( QStringList::Iterator it = patternList.begin(); 
	  it != patternList.end(); ++it ) {
	QString pattern = *it;
	pattern.replace( "*.", "" );

	mimeItem *item = findMime( pattern );
	if(item == NULL){
	    item = new mimeItem;
	    item->ext = pattern;
	    item->name = name;
	    item->exec = exec;
	    item->mimeType = mimeType;
	    item->iconName = icon;
	    mimeList.append( *item );
	    //	    cout << pattern << endl;
    
	}else if(item->mimeType == "all"){
	    item->mimeType = mimeType;
	}else{
	  if( !name.isNull() )
	    item->name = name;
	  if( !exec.isNull() )
	    item->exec = exec;
	  if( !mimeType.isNull() )
	    item->mimeType = mimeType;
	  if( !icon.isNull() )
	    item->iconName = icon;
	  /*
	  int i =  mimeList.indexOf( *item );
	  if(i >= 0)
	    mimeList.removeAt( i );
	  */
	  mimeList.removeAll ( *item );
	  mimeList.append( *item );
	}

    }


    //    mimeItem item = new mimeItem;

    //cout << file << endl;
}

mimeItem *HMimeTypes::findMime(QString ext)
{
    mimeItem *slectedItem = NULL;

 for (int i = 0; i < mimeList.size(); ++i) {
     if (mimeList.at(i).ext == ext )
       slectedItem = (mimeItem*)&mimeList.at(i);
 }
 /*
 for ( mimeItem *item = mimeList.first(); item; item = mimeList.next() ){
	if( item->ext == ext )
	    slectedItem = item;
    }
 */
    return slectedItem;
}

QString HMimeTypes::findIconName(QString ext)
{
    //cout << ext << endl;
    QString iconName;
    mimeItem *mime = findMime(ext);

    if(mime)
	iconName = mime->iconName;

    //    if(! iconName.isNull() )
    //cout << iconName << endl;

    return iconName;
}

QPixmap HMimeTypes::findIcon(QString ext, bool exec, QString size)
{
    QPixmap filepix;
    
    QString iconName = findIconName(ext);
    if( !iconName.isNull() )
	filepix = QPixmap(iconName);
    
    if( filepix.isNull() ){
	if(! iconName.isNull())
	{
	    if(iconName.indexOf('.') < 0)
		iconName = iconName + ".png";
	    iconName = get_ifile(iconName.toAscii(), size.toAscii(), "mime");
	    if(! iconName.isNull()){
		//		cout << iconName << endl;
		filepix = QPixmap(iconName);
	    }
	}
    }
    
    if( filepix.isNull() )
	if(exec)
	    filepix = QPixmap(get_ifile("exec.png", size.toAscii(),
					"filesystems"));
    
    if( filepix.isNull() ){    
	if(size == "large")
	    filepix = filepix48;
	else if(size == "mid")
	    filepix = filepix32;
	else
	    filepix = filepix16;
   }
    return filepix;
}

bool HMimeTypes::hasType( QString ext, QString type)
{
 for (int i = 0; i < mimeList.size(); ++i) {
   if (mimeList.at(i).ext == ext && ( (mimeList.at(i).ext == type ) ))
	 return true;//slectedItem = (mimeItem*)&mimeList.at(i);
 }

  /*
    for ( mimeItem *item = &mimeList.first(); item; item = &mimeList.next() ){
	if( ( item->ext == ext ) && ( item->mimeType == type ) )
	    return true;
    }
  */
    return false;
}

