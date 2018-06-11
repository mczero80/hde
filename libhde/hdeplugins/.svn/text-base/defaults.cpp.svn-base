
/*
*  File      : defaults.cpp
*  Written by: haydar@haydar.net
*  Copyright : GPL
*
*  reads the defaults file and makes information statically
*  accessible
*/


//#include "defs.h"
#include "lhdeconf.h"
#include "defaults.h"
#include "hinifile.h"
//#include "libhde.h"

QString defaults::cfdir = NULL;                 // config directory
QStringList defaults::imagesDirs;
QString defaults::coding = "";

QString defaults::get_cfile(char *name){
    QString fname;

    if(cfdir.isNull()){
	QString fname(getenv("HOME"));

	if(! fname.isNull())
	    cfdir = fname + "/.hde";
    }

    // user config dir
    fname = defaults::cfdir;
    fname += '/';
    fname += name;
    
    QFileInfo fil(fname);
	
    if(fil.isReadable())
	return(fname);
	
    fname = CONFDIR;   // system config dir
    fname += "/";
    fname += name;
	
    QFileInfo fi(fname);

    if(fi.isReadable())
	return(fname);
		
    //    perror((const char *)fname);
    fname = QString();
    return(fname);
}

hdeItem defaults::readItem(QString path){
    hdeItem item;
    return item;
}
void defaults::addToRecentPrograms(QString path)
{
}
