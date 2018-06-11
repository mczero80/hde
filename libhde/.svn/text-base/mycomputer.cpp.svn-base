/****************************************************************************
 **
 **			     hmycomputer.cpp
 **			=========================
 **
 **  begin                : Wed Jun 21 2003
 **  copyright            : (C) 2003-2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/

#include <qfile.h> 
#include <qfileinfo.h> 
#include <qmime.h>
//#include <qdragobject.h>
#include <qfiledialog.h> 

#include "mycomputer.h"
#include <libhde.h> 
#include <QTextStream>

#ifdef Q_WS_WIN 
#include <windows.h>
#else

#endif 

#include <iostream>
using std:: cout; using std::endl;using std::cerr;

static QIcon load_icon( const QString &name )
{
  //  QString nam = ":/images/" + name;
  QIcon icn;
  icn.addFile(":/images/" + name + ".png", QSize(48,48));
  icn.addFile(":/images/" + name + "32.png", QSize(32,32));
  icn.addFile(":/images/" + name + "16.png", QSize(16,16));
  return icn;
}

/*****************************************************************************
 *
 * Class HDrive
 *
 *****************************************************************************/

HDrive::HDrive(QString path, QString type, QIcon ico)
{
    drivePath = path;
    driveType = type;
    driveIcon = ico;
}

/*****************************************************************************
 *
 * Class MyComputer
 *
 *****************************************************************************/
QList<HDrive> MyComputer::driveList;

MyComputer::MyComputer()
{
  rebuildDrives();
}

void MyComputer::rebuildDrives()
{
    driveList.clear();
    
#ifdef Q_WS_WIN 
    QFileInfo fi;
    QFileInfoList roots = QDir::drives();

    for (int i = 0; i < roots.size(); ++i) {
      fi = roots.at(i);
	  if(GetDriveTypeA(fi.filePath().left(2).toAscii()) == 2){
        QIcon fddpix = load_icon("fdd");
	    driveList.append( HDrive(fi.filePath(), "Fdd", fddpix));
      }else if(GetDriveTypeA(fi.filePath().left(2).toAscii()) == 3){
        QIcon hddpix = load_icon("hdd");
	    driveList.append( HDrive(fi.filePath(), "Hdd", hddpix));
      }else if(GetDriveTypeA(fi.filePath().left(2).toAscii()) > 4){
	    QIcon cdpix = load_icon("cd");
	    driveList.append( HDrive(fi.filePath(), "CD", cdpix));
      }
    }
    /*
    QPtrListIterator<QFileInfo> i(*roots);
    QFileInfo* fi;
    while ( (fi = *i) ) {
        ++i;

	if(GetDriveTypeA(fi->filePath().left(2).ascii()) == 2){
	  QIcon fddpix = load_icon("fdd");
	  driveList.append( new HDrive(fi->filePath(), "Fdd", fddpix));
	}else if(GetDriveTypeA(fi->filePath().left(2).ascii()) == 3){

	  QIcon hddpix = uic_load_icon_fileWidget("hdd");
	  driveList.append( new HDrive(fi->filePath(), "Hdd", 
				       hddpix));
	}else if(GetDriveTypeA(fi->filePath().left(2).toAscii()) > 4){
	  QIcon cdpix = uic_load_icon_fileWidget("cd");
	  driveList.append( new HDrive(fi->filePath(), "CD", 
				       cdpix));
	}
 */
//(void) new HFileListItem( this, fi, "Drive");
    //}
#else
    QFileInfo *fi = new QFileInfo(QDir::home().path());
    QIcon homepix = QIcon(get_ifile("folder_home.png", 
					       "large", "filesystems"));
    if(homepix.isNull())
      homepix = load_icon("home");
	      
    driveList.append( HDrive(fi->filePath(), "Home", homepix));

    QString fstabFile;

    if (QFile::exists(QString::fromLatin1("/etc/fstab"))) { // Linux, ...
      fstabFile = "/etc/fstab";
    } else if (QFile::exists(QString::fromLatin1("/etc/vfstab"))) {
      fstabFile = "/etc/vfstab";
    }

    if ( !fstabFile.isEmpty() ) {
      QFile f( fstabFile );
      f.open( QIODevice::ReadOnly );
      QTextStream stream( &f );
      stream.setCodec( QTextCodec::codecForName("ISO-8859-1") );
      
      while ( !stream.atEnd() ) {
	
	QString line = stream.readLine();
	line = line.simplified();
	
	if (!line.isEmpty() && line[0] == '/') { 
	  
	  QStringList lst = line.split( ' ' );
	  
	  QString it;
	  it = lst.at(1);
	  
	  if(it[0] == '/'){  
	    if( (lst.at(2)).contains( "ext" )){
	      
	      QFileInfo *fi = new QFileInfo(it);
	      QIcon hddpix =QIcon(get_ifile("hdd_linux_unmount.png", 
						"large", "devices"));
	      
	      if(hddpix.isNull())
		hddpix =QIcon(get_ifile("hdd_unmount.png", 
					  "large", "devices"));
	      if(hddpix.isNull())
		hddpix = load_icon("hdd");
	      
	      driveList.append( HDrive(fi->filePath(), "LHdd", hddpix));
	    }else if((lst.at(2)).contains( "vfat" )){
	      
	      QFileInfo *fi = new QFileInfo(it);
	      QIcon hddpix =QIcon(get_ifile("hdd_windows_unmount.png", 
						"large", "devices"));

	      if(hddpix.isNull())
		hddpix =QIcon(get_ifile("hdd_unmount.png", 
					  "large", "devices"));
	      if(hddpix.isNull())
		hddpix = load_icon("hdd");
	      
	      driveList.append( HDrive(fi->filePath(), "WHdd", hddpix));
      
	    }else if( (lst.at(2)).contains("iso9660") 
		      ||  (lst.at(0)).contains("cdrom") || 
		      (lst.at(1)).contains("cdrom") ){
	      
	      QFileInfo *fi = new QFileInfo(it);
	      QIcon cdpix =QIcon(get_ifile("cdrom_unmount.png", 
					       "large", "devices"));
	      if(cdpix.isNull())
		cdpix = load_icon("cd");
	      
	      driveList.append( HDrive(fi->filePath(), "CD", cdpix));
	      
	      
	    }else if( (lst.at(0)).contains("fd") || 
		      (lst.at(0)).contains("floppy") ){
	      
	      QFileInfo *fi = new QFileInfo(it);
	      QIcon fddpix =QIcon(get_ifile("3floppy_unmount.png", 
						"large", "devices"));
	      if(fddpix.isNull())
		fddpix = load_icon("fdd");
	      
	      driveList.append( HDrive(fi->filePath(), "Fdd", fddpix));

	       
	    }else{
	      
	      QFileInfo *fi = new QFileInfo(it);
	      QIcon hddpix =QIcon(get_ifile("hdd_unmount.png", 
						"large", "devices"));
	      if(hddpix.isNull())
		hddpix = load_icon("hdd");
	      
	      driveList.append( HDrive(fi->filePath(), "Hdd", hddpix));
	      
	    }
	      	    
	  } // if(it[0] == '/')

	} // if (!line.isEmpty() && line[0] == '/')
	
      } // TextStream
	
      
      f.close();
      
    }
#endif
}



QIcon MyComputer::getDriveIcon( HDrive *drive )
{
  QIcon icn;
  
  if( !drive->icon().isNull() )
      return drive->icon();
  return icn;
        /*
    QPixmap pix;
    if(size == "large")
	return drive->pixmap();

    else if(size == "mid"){
	if(drive->type() == "Fdd"){
	    pix =QPixmap(get_ifile("3floppy_unmount.png", "mid", "devices"));
	    if(pix.isNull())
		pix = load_icon("fdd32.png");
	}else if(drive->type() == "CD"){
	    pix =QPixmap(get_ifile("cdrom_unmount.png", "mid", "devices"));
	    if(pix.isNull())
		pix = load_icon("cd32.png");
	}else if(drive->type() == "Hdd"){
	    pix =QPixmap(get_ifile("hdd_unmount.png", "mid", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd32.png");
	}else if(drive->type() == "LHdd"){
	    pix =QPixmap(get_ifile("hdd_linux_unmount.png", "mid", "devices"));

	    if(pix.isNull())
		pix =QPixmap(get_ifile("hdd_unmount.png", "mid", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd32.png");

	}else if(drive->type() == "WHdd"){
	    pix =QPixmap(get_ifile("hdd_windows_unmount.png","mid","devices"));

	    if(pix.isNull())
		pix =QPixmap(get_ifile("hdd_unmount.png", "mid", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd32.png");

	}else if(drive->type() == "Home"){
	  pix = QPixmap(get_ifile("folder_home.png","mid","filesystems"));

	  if(pix.isNull())
	    pix = load_icon("home32.png");
	}
    }else{
	if(drive->type() == "Fdd"){
	    pix =QPixmap(get_ifile("3floppy_unmount.png", "mini", "devices"));
	    if(pix.isNull())
		pix = load_icon("fdd16.png");

	}else if(drive->type() == "CD"){
	    pix =QPixmap(get_ifile("cdrom_unmount.png", "mini", "devices"));
	    if(pix.isNull())
		pix = load_icon("cd16.png");

	}else if(drive->type() == "Hdd"){
	    pix =QPixmap(get_ifile("hdd_unmount.png", "mini", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd16.png");

	}else if(drive->type() == "LHdd"){
	    pix =QPixmap(get_ifile("hdd_linux_unmount.png", "mini","devices"));

	    if(pix.isNull())
		pix =QPixmap(get_ifile("hdd_unmount.png", "mini", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd16.png");

	}else if(drive->type() == "WHdd"){
	    pix=QPixmap(get_ifile("hdd_windows_unmount.png","mini","devices"));

	    if(pix.isNull())
		pix =QPixmap(get_ifile("hdd_unmount.png", "mini", "devices"));
	    if(pix.isNull())
		pix = load_icon("hdd16.png");

	}else if(drive->type() == "Home"){
	    pix = QPixmap(get_ifile("folder_home.png","mini","filesystems"));

	    if(pix.isNull())
		pix = load_icon("home16.png");
	}


    }
    return pix;
    */
}

QIcon MyComputer::getDirIcon( QString filename )
{
    QIcon pix;
  
    return pix;
}

QIcon MyComputer::getFileIcon( QString filename )
{
    QIcon pix;

    return pix;
}

QIcon MyComputer::getIcon( QString filename )
{
    QIcon icn;
    //    cout << filename << endl;
   
    
    for ( int i = 0; i < driveList.count(); ++i ){
      HDrive *tmpDrive = (HDrive *)&driveList.at(i);
      if ( tmpDrive ){
	     if( ((HDrive)driveList.at( i )).path() == filename){
	         return getDriveIcon( tmpDrive );
         }
      }
    }
    
    return icn;
}

