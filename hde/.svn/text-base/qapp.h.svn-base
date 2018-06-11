/****************************************************************************
 **
 **				qapp.h
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Subclassing for QApplication, contains the X11 event
 **  filter and some static functions that are common to all
 **  classes
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/
        
#ifndef QAPP_H
#define QAPP_H

#include "toolbar.h"
#include "pager.h"
#include "winlist.h"
#include "menu.h"
#include "procbar.h"
#include "apbar.h"
#include "winfo.h"
#include "rubber.h"
#include "xwindow.h"
#include "desktp.h"

extern QList <xwindow*> clients;       // client list 


class qapp : public QApplication
{
  Q_OBJECT
protected:
  virtual bool x11EventFilter(XEvent *);


public:
  //  static Atoms *atoms;
  static Toolbar *tb;                   // Toolbar
  static desktp *Desktop;
  static QPixmap *minmaxpix;            // minmax button pixmap
  static QPixmap *uminmaxpix;           // untitled minmax button pixmap
  static QPixmap *closepix;             // close button pixmap
  static QPixmap *uclosepix;            // untitled close button pixmap
  static QPixmap *minbtnpix;            // minimize button pixmap
  static QPixmap *uminbtnpix;           // untitled minimize button pixmap
  static QPixmap *maxbtnpix;            // maximize button pixmap
  static QPixmap *umaxbtnpix;           // untitled maximize button pixmap
  static QPixmap *helpbtnpix;           // help button pixmap
  static QPixmap *uhelpbtnpix;          // untitled help button pixmap
  static QPixmap *restorebtnpix;        // restore button pixmap
  static QPixmap *urestorebtnpix;       // untitled restore button pixmap
  static QPixmap *defaultpix;           // default window pixmap

  static QImage *border_tlimage;
  static QImage *border_trimage;
  static QImage *topborderimage;
  static QImage *border_leftimage;
  static QImage *border_rightimage;
  static QImage *border_blimage;
  static QImage *border_brimage;
  static QImage *bottomborderimage;
  static QImage *uborder_tlimage;
  static QImage *uborder_trimage;
  static QImage *utopborderimage;
  static QImage *uborder_leftimage;
  static QImage *uborder_rightimage;
  static QImage *uborder_blimage;
  static QImage *uborder_brimage;
  static QImage *ubottomborderimage;

  static QImage *titlepix;             // titlebar pixmap
  static QImage *titlerightpix;        // titlebar right pixmap
  static QImage *titleleftpix;         // titlebar left pixmap
  static QImage *untitlepix;           // unactive titlebar pixmap
  static QImage *untitlerightpix;      // unactive titlebar righ pixmap
  static QImage *untitleleftpix;       // unactive titlebar left pixmap


  static QHash <Window, xwindow*> cwindows;   // child window lookup table
  static QHash <Window, xwindow*> pwindows;   // parent window lookup table
  static int next_x;                    // autoplacement counter
  static int next_y;                    // autoplacement counter
  static int adesk;                     // current desktop
  static Atom wm_protocols;             // WM_PROTOCOLS
  static Atom wm_delete;                // WM_DELETE property
  static Atom wm_change_state;          // message from client
  static Atom wm_state;                 // message to client 
  static Atom wm_take_focus;            // WM_TAKE_FOCUS property
  static Atom wm_resource_manager;      // Resource changed
  static Atom wm_colormaps;             // WM_COLORMAP_WINDOWS property
  static Atom kde_net_wm_system_tray_window_for;
  static Atom net_wm_name;
  static Atom net_wm_icon_name;
  static Atom XA_MOTIF_WM_HINTS;

  static Atom net_wm_context_help;
  static Atom net_system_tray;
  static Atom net_system_tray_opcode;
  static Atom net_system_tray_message_data;

  static bool smode;                    // screen mode
  static QPalette *ipal;                // window inactive palette
  static QPalette *upal;                // window urgent palette
  static bool mrb;                      // move/resize active
  static xwindow *focusclient;          // currently active client
  static xwindow *tmaxclient;
  static bool tdesks[];                 // desks in tiled state
  static winfo *winf;                   // window info 
  static bool menu_open;                // toolbar menu popped up
  static QMap <QString, int> cprops;    // Property flags
  static QMap <QString, int> apclients; // Toolbar clients, position number
  static QDateTime lmtime;              // last defaults modification time
  static bool sighup;                   // SIGHUP received
  static int servershapes;              // server supports nonrectangular windows
  static Window grabbedWin;

#define logmsg QTextStream(stderr)
  enum clflags { WindowListSkip = 0x01, Sticky = 0x02, SmallFrame = 0x04,
		 NoResize = 0x08, NoTile = 0x10, NoKey = 0x20, 
		 NoScreen = 0x40, ClassOnly = 0x80 };

		
  qapp(int &argc, char **argv);
  void setinactive(xwindow *);
  static void manageTray();
  static void focus_window(xwindow *client);
  static void stopautofocus(void);
  static void run_client(Window);
  static void install_colormap(Colormap);
  static bool is_curdesk(xwindow *);
  static bool is_tileddesk(void) { return(tdesks[adesk]); }
  static void tile_order(xwindow *);
  static void tile_maximize(xwindow *);
  static void toggle_tiled(void);
  static void wm_restart();
  static void read_cprops(void);
  static QString get_cfile(const char *);
  static void send_configurenotify(xwindow *);
  static void free_grabbedmouse();
  static void grabmouse(Window win);
  static void setUpdateRect(QRect rect, xwindow *me);
};
#endif
