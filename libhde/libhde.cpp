/****************************************************************************
 **
 **				libhde.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Some base functions for libhde.
 **
 ****************************************************************************/

#include <qprocess.h>
#include <QPixmap>


#include <libhde.h>
#include <defaults.h>


#include <lhdeconf.h>
#ifdef Q_WS_X11
#include <QX11Info>
#if __GNUC__ >= 3
#include <iostream>
using std:: cout; using std::endl;using std::cerr;
#else
#include <iostream.h>
#endif
#endif

/**************************************************************************
 *
 * Render string for encoding
 *
 *************************************************************************/
QString render(QString txt, char *coding){
  if (coding != ""){
    QTextCodec* codec = QTextCodec::codecForName( coding);
    
    QString UniString =  codec->toUnicode( txt.toAscii().data() );
    
    return(UniString);
  }else{
    return(txt);
  }
}

QString render(QString txt, QString coding){
  if (coding != ""){
    QTextCodec* codec = QTextCodec::codecForName( coding.toAscii().data() );
    
    QString UniString = codec->toUnicode( txt.toAscii().data() );
    
    return(UniString);
  }else{
    return(txt);
  }
}

/**************************************************************************
 *
 * Get config file:
 * It gives you the path to the config file by searching in ~/.config/hde2 
 * first and if not found there, it searchs in the default hde dir such as:
 * /usr/share/hde
 *
 *************************************************************************/
QString get_cfile(char *name){
  if(defaults::cfdir.isNull()){
    QString dname(getenv("HOME"));

    if(! dname.isNull())
      defaults::cfdir = dname + "/.config/hde2";
  }

  QString fname;
	
  // user config dir
  if(! defaults::cfdir.isNull()){
    fname = defaults::cfdir;
    fname += '/';
    fname += name;
    
    QFileInfo fi(fname);
    
    if(fi.isReadable())
      return(fname);
  }
  
  fname = CONFDIR;   // system config dir
  fname += "/";
  fname += name;
  
  QFileInfo fi(fname);
  
  if(fi.isReadable())
    return(fname);
  
  perror( fname.toAscii().data() );
  fname = QString();
  return(fname);
}


/**************************************************************************
 *
 * Get Image file:
 * It gives you the path to the image file by searching in defauld images
 * directories related to image size.
 *
 *************************************************************************/
QString get_ifile(QString name, QString size){
    if(QFile(name).exists())
	return name;
	

    //if(QString::compare(size , "large") == 0){
    if(size == "large"){
	for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	      it != defaults::imagesDirs.end(); ++it ) {
	    if(QFile::exists( *it + "/large/" + name ))
		return *it + "/large/" + name;
	    if(QFile::exists(*it + "/48x48/apps/" + name))
		return *it + "/48x48/apps/" + name;
	    if(QFile::exists(*it + "/48x48/actions/" + name))
		return *it + "/48x48/actions/" + name;
	    if(QFile::exists(*it + "/48x48/devices/" + name))
		return *it + "/48x48/devices/" + name;
	    if(QFile::exists(*it + "/48x48/filesystems/" + name))
		return *it + "/48x48/filesystems/" + name;
	    if(QFile::exists(*it + "/48x48/mimetypes/" + name))
		return *it + "/48x48/mimetypes/" + name;

	    if(QFile::exists(*it + "/64x64/apps/" + name))
		return *it + "/64x64/apps/" + name;
	    if(QFile::exists(*it + "/64x64/actions/" + name))
		return *it + "/64x64/actions/" + name;
	    if(QFile::exists(*it + "/64x64/devices/" + name))
		return *it + "/64x64/devices/" + name;
	    if(QFile::exists(*it + "/64x64/filesystems/" + name))
		return *it + "/64x64/filesystems/" + name;
	    if(QFile::exists(*it + "/64x64/mimetypes/" + name))
		return *it + "/64x64/mimetypes/" + name;
	}
	//    }else if(QString::compare(size , "mid") == 0){
    }else if(size == "mid"){
	for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	      it != defaults::imagesDirs.end(); ++it ) {
	    if(QFile::exists(*it + "/" + name ))
		return *it + "/" + name;
	    if(QFile::exists(*it + "/32x32/apps/" + name))
		return *it + "/32x32/apps/" + name;
	    if(QFile::exists(*it + "/32x32/actions/" + name))
		return *it + "/32x32/actions/" + name;
	    if(QFile::exists(*it + "/32x32/devices/" + name))
		return *it + "/32x32/devices/" + name;
	    if(QFile::exists(*it + "/32x32/filesystems/" + name))
		return *it + "/32x32/filesystems/" + name;
	    if(QFile::exists(*it + "/32x32/mimetypes/" + name))
		return *it + "/32x32/mimetypes/" + name;
	}
	//    }else if(QString::compare(size , "mini") == 0){
    }else if(size == "mini"){
      for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	      it != defaults::imagesDirs.end(); ++it ) {
	    if(QFile::exists(*it + "/mini/" + name ))
		return *it + "/mini/" + name;
	    if(QFile::exists(*it + "/22x22/apps/" + name))
		return *it + "/22x22/apps/" + name;
	    if(QFile::exists(*it + "/22x22/actions/" + name))
		return *it + "/22x22/actions/" + name;
	    if(QFile::exists(*it + "/22x22/devices/" + name))
		return *it + "/22x22/devices/" + name;
	    if(QFile::exists(*it + "/22x22/filesystems/" + name))
		return *it + "/22x22/filesystems/" + name;
	    if(QFile::exists(*it + "/22x22/mimetypes/" + name))
		return *it + "/22x22/mimetypes/" + name;

	    if(QFile::exists(*it + "/16x16/apps/" + name))
		return *it + "/16x16/apps/" + name;
	    if(QFile::exists(*it + "/16x16/actions/" + name))
		return *it + "/16x16/actions/" + name;
	    if(QFile::exists(*it + "/16x16/devices/" + name))
		return *it + "/16x16/devices/" + name;
	    if(QFile::exists(*it + "/16x16/filesystems/" + name))
		return *it + "/16x16/filesystems/" + name;
	    if(QFile::exists(*it + "/16x16/mimetypes/" + name))
		return *it + "/16x16/mimetypes/" + name;
	}
    }

    for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	  it != defaults::imagesDirs.end(); ++it ) {
      if(QFile::exists(*it + "/" + name ))
	return *it + "/" + name;
    }

    return QString();
}


/**************************************************************************
 *
 * Get Image file:
 * It gives you the path to the image file by searching in defauld images
 * directories related to image size and mime type.
 *
 *************************************************************************/
QString get_ifile( QString name, QString size, QString type)
{
    if(QFile(name).exists())
	return name;

    if(size == "large"){
      for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	    it != defaults::imagesDirs.end(); ++it ) {
	if(QFile::exists( *it + "/large/" + name ))
	  return *it + "/large/" + name;

	if(QFile::exists(*it + "/48x48/" + type + "/"  + name))
	  return *it + "/48x48/" + type + "/"  + name;

	if(QFile::exists(*it + "/64x64/" + type + "/"  + name))
	  return *it + "/64x64/" + type + "/"  + name;

      }
    }else if(size == "mid"){
      for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	    it != defaults::imagesDirs.end(); ++it ) {
	if(QFile::exists(*it + "/" + name ))
	  return *it + "/" + name;

	if(QFile::exists(*it + "/32x32/" + type  + "/" + name))
	  return *it + "/32x32/"+ type + "/" + name;
      }
    
    }else if(size == "mini"){
      for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	    it != defaults::imagesDirs.end(); ++it ) {

	if(QFileInfo(*it + "/mini/" + name ).exists())
	  return *it + "/mini/" + name;

	if(QFile::exists(*it + "/22x22/" + type + "/" + name))
		    return *it + "/22x22/" + type + "/" + name;

	if(QFile::exists(*it + "/16x16/" + type + "/" + name))
		    return *it + "/16x16/" + type + "/" + name;

      }
    }

    for ( QStringList::Iterator it = defaults::imagesDirs.begin(); 
	  it != defaults::imagesDirs.end(); ++it ) {
      if(QFile::exists(*it + "/" + name ))
	return *it + "/" + name;
    }
    return QString();
}



/* locale names mostly copied from XFree86 */
static const char * const iso8859_2locales[] = {
    "croatian", "cs", "cs_CS", "cs_CZ","cz", "cz_CZ", "czech", "hr",
    "hr_HR", "hu", "hu_HU", "hungarian", "pl", "pl_PL", "polish", "ro",
    "ro_RO", "rumanian", "serbocroatian", "sh", "sh_SP", "sh_YU", "sk",
    "sk_SK", "sl", "sl_CS", "sl_SI", "slovak", "slovene", "sr_SP", 0 };

static const char * const iso8859_3locales[] = {
    "eo", 0 };

static const char * const iso8859_4locales[] = {
    "ee", "ee_EE", "lv", "lv_LV", 0 };

static const char * const iso8859_5locales[] = {
    "mk", "mk_MK", "sp", "sp_YU", 0 };

static const char * const cp_1251locales[] = {
    "be", "be_BY", "bg", "bg_BG", "bulgarian", 0 };

static const char * const pt_154locales[] = {
    "ba", "ba_RU", "ky", "ky_KG", "kk", "kk_KZ", 0 };
/*
static const char * const iso8859_6locales[] = {
    "ar", "ar_AA", "ar_SA", "arabic", 0 };
*/
static const char * const iso8859_7locales[] = {
    "el", "el_GR", "greek", 0 };

static const char * const iso8859_9locales[] = {
    "tr", "tr_TR", "turkish", 0 };

static const char * const iso8859_13locales[] = {
    "lt", "lt_LT", 0 };

static const char * const iso8859_15locales[] = {
    "fr", "fi", "french", "finnish", "et", "et_EE", 0 };

static const char * const koi8_ulocales[] = {
    "uk", "uk_UA", "ru_UA", "ukrainian", 0 };

static const char * const tis_620locales[] = {
    "th", "th_TH", "thai", 0 };

static const char * const utf8locales[] = {
    "ar", "ar_AA", "ar_BH", "ar_DZ", "ar_EG", "ar_IQ", "ar_JO", "ar_KW", 
    "ar_LB", "ar_LY", "ar_MA", "ar_OM", "ar_QA", "ar_SA", "ar_TN", "ar_YE", 
    "arabic", "ara", 0 };

static bool try_locale_list( const char * const locale[], const char * lang )
{
    int i;
    for( i=0; locale[i] && qstrcmp(locale[i], lang); i++ )
    { }
    return locale[i] != 0;
}

/**************************************************************************
 *
 * Get Encoding from locale
 *
 *************************************************************************/
QString hde_langinfo(QString lng){
    if(defaults::coding != "")
	return defaults::coding;

    if ( try_locale_list( iso8859_2locales, lng.toAscii().data() ) )
    return QString("ISO 8859-2") ;
  else if ( try_locale_list( iso8859_3locales, lng.toAscii().data() ) )
    return QString("ISO 8859-3");
  else if ( try_locale_list( iso8859_4locales, lng.toAscii().data() ) )
    return QString("ISO 8859-4");
  else if ( try_locale_list( iso8859_5locales, lng.toAscii().data() ) )
    return QString("ISO 8859-5");
  /*
  else if ( try_locale_list( iso8859_6locales, lng.toAscii().data() ) )
    return QString("ISO 8859-6");
  */
  else if ( try_locale_list( iso8859_7locales, lng.toAscii().data() ) )
    return QString("ISO 8859-7");
  else if ( try_locale_list( iso8859_9locales, lng.toAscii().data() ) )
    return QString("ISO 8859-9") ;
  else if ( try_locale_list( iso8859_13locales, lng.toAscii().data() ) )
    return QString("ISO 8859-13");
  else if ( try_locale_list( iso8859_15locales, lng.toAscii().data() ) )
    return QString("ISO 8859-15");
  else if ( try_locale_list( tis_620locales, lng.toAscii().data() ) )
    return QString("ISO 8859-11");
  else if ( try_locale_list( koi8_ulocales, lng.toAscii().data() ) )
    return QString("KOI8-U") ;
  else if ( try_locale_list( utf8locales, lng.toAscii().data() ) )
    return QString("utf-8") ;
  else if ( try_locale_list( cp_1251locales, lng.toAscii().data() ) )
    return QString("CP 1251") ;
  else if ( try_locale_list( pt_154locales, lng.toAscii().data() ) )
    return QString("PT 154");
  //  else if ( try_locale_list( probably_koi8_rlocales, lang ) )
  //return lng;

  //  return QString("default");
  return QString("utf-8");
}

/**************************************************************************
 *
 * Execute a Command.
 *
 *************************************************************************/
void execCmd(QString cmd){
#ifdef Q_WS_X11
    pid_t child_pid;     /* i.e., int  pid; */
    bool isDesktop =false;
    hdeItem hi;
    QString cmd1 = cmd;
    //    if( (cmd1.right(8) == ".desktop") || (cmd1.right(7) == ".hdelnk") ){
	hi = defaults::readItem(cmd);
	if(!hi.exec.isNull()){
	    isDesktop = true;
	    cmd = hi.exec;

	    // temp
	    cmd.replace("%f", "");
	    cmd.replace("%F", "");
	    cmd.replace("%u", "");
	    cmd.replace("%U", "");
	    cmd.replace("%d", "");
	    cmd.replace("%D", "");
	    cmd.replace("%n", "");
	    cmd.replace("%N", "");
	    cmd.replace("%i", "");
	    cmd.replace("%c", "");
	    cmd.replace("%k", "");
	    cmd.replace("%m", "");
	    cmd.replace("%v", "");
	}

    child_pid = fork();

    if (child_pid == 0) {
	//	qApp->setOverrideCursor( Qt::waitCursor );
      execl("/bin/sh", "sh", "-c", cmd.toAscii().data(), NULL);
	//execl("/bin/sh", "ss","-c", (const char*)cmd,  NULL);
	/* if execl succeeds, this code is never used */
	//qApp->restoreOverrideCursor();
	cout << "Could not execl file /bin/ls" << endl;
	exit(1);
	/* this exit stops only the child process */
    } else if (child_pid > 0){
	/* this code is only executed in the parent process */
	if(isDesktop)
	    defaults::addToRecentPrograms(cmd1);
	//	cout << "Executed\n";
	//	//qApp->restoreOverrideCursor();
    }else{
	//qApp->restoreOverrideCursor();
	cout 	<< "The fork system call failed to create a new process"
		<< endl;
	exit(1);
    }



    /*
    QApplication::setOverrideCursor( Qt::waitCursor );
    //QApplication::setOverrideCursor( waitCursor );
    //QTimer::singleShot( 5000, qApp, SLOT(restoreOverrideCursor()));
    QApplication::restoreOverrideCursor();
    */
    //execl("/bin/sh", "sh", "-c", (const char*)cmd, NULL);
    //perror("cannot run /bin/sh");
    //exit(1);
#endif
}

/***************************************************************************
 *
 * Get the opposite color of a given color
 *
 **************************************************************************/
QColor getOppositeColor(const QColor &color)
{
  QColor oColor = Qt::black;

  int r = color.red();
  int g = color.green();
  int b = color.blue();

  int r2 = r -255;
  if(r2 < 0)
    r2 = r2 * -1;
    
  int g2 = g -255;
  if(g2 < 0)
    g2 = g2 * -1;
  
  int b2 = b -255;
  if(b2 < 0)
    b2 = b2 * -1;
  
  oColor.setRgb(r2,g2,b2);

  return oColor;
}


/**************************************************************************
 *
 * Draw gradient
 *
 *************************************************************************/
void gradient(QPixmap &pixmap, const QColor &ca, const QColor &cb){
    int rDiff, gDiff, bDiff;
    int rca, gca, bca /*, rcb, gcb, bcb*/;
    
    //    register int x, y;
    register int x;
    
    rDiff = (/*rcb = */ cb.red())   - (rca = ca.red());
    gDiff = (/*gcb = */ cb.green()) - (gca = ca.green());
    bDiff = (/*bcb = */ cb.blue())  - (bca = ca.blue());

    register int rl = rca << 16;
    register int gl = gca << 16;
    register int bl = bca << 16;

    int rcdelta = ((1<<16) /  pixmap.width())  * rDiff;
    int gcdelta = ((1<<16) /  pixmap.width())  * gDiff;
    int bcdelta = ((1<<16) /  pixmap.width())  * bDiff;
    
    QPainter p(&pixmap);

    // these for-loops could be merged, but the if's in the inner loop
    // would make it slow
	for( x = 0; x < pixmap.width(); x++) {
	    rl += rcdelta;
	    gl += gcdelta;
	    bl += bcdelta;
	    
	    p.setPen(QColor(rl>>16, gl>>16, bl>>16));
	    p.drawLine(x, 0, x, pixmap.height()-1);
	}



}

void makeTray(WId win)
{
#ifdef Q_WS_X11
    Display *dsp = QX11Info::display(); // get the display
    int r;
    int data = 1;
    r = XInternAtom(dsp, "KWM_DOCKWINDOW", false);
    XChangeProperty(dsp, win, r, r, 32, 0, (uchar *)&data, 1);
    r = XInternAtom(dsp, "_KDE_NET_WM_SYSTEM_TRAY_WINDOW_FOR", false);
    XChangeProperty(dsp, win, r, XA_WINDOW, 32, 0, (uchar *)&data, 1);
#endif
}

/**************************************************************************
 *
 * Get Image file:
 * It gives you the path to the image file by searching in defauld images
 * directories related to image size.
 * The Diference between this and get_ifile is that you can give only the
 * name of the icon here without extention.
 *
 *************************************************************************/
QString getIconFile(QString icn, const char *size)
{
    QString icn1 = icn;
    if(icn[0] != '/'){
      icn1 = get_ifile( icn, size);

      if(icn1.isNull())
	icn1 = get_ifile( icn + ".png", size);

      if(icn.isNull())
	icn1 = get_ifile( icn + ".xpm", size);
    }

    return icn1;
}

/**************************************************************************
 *
 * Get Icon file:
 * It gives you the path to the image file by searching in defauld images
 * directories related to image size and mime type.
 * The Diference between this and get_ifile is that you can give only the
 * name of the icon here without extention.
 *
 *************************************************************************/
QString getIconFile(QString icn, const char *size, const char *type)
{
    QString icn1 = icn;
    if(icn[0] != '/'){
      icn1 = get_ifile( icn, size, type);

      if(icn1.isNull())
	icn1 = get_ifile( (icn + ".png"), size, type);

      if(icn.isNull())
	icn1 = get_ifile( (icn + ".xpm"), size, type);
    }

    return icn1;
}
