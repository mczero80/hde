/* defs.h */

#include <qapplication.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qframe.h>
#include <qlist.h>
#include <qstack.h>
#include <qmap.h>
//#include <qintdict.h>
#include <qmenu.h>
#include <qtimer.h>
#include <qlabel.h>
#include <qdatetime.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qcheckbox.h>
#include <qvariant.h>
#include <qcursor.h>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qnamespace.h>
//#include <qaccel.h>
#include <qcolor.h>
#include <qregion.h>
#include <qbitmap.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qmatrix.h>

//#include <hinifile.h>
//#include <libhde.h>

//#include <iostream.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
using std:: cout; using std::endl;using std::cerr;
#ifdef Q_WS_X11
#include <sys/wait.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>
#endif

// virtual desktops
#define MAXDESKS 10
