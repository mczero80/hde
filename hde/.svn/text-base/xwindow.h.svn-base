/****************************************************************************
 **
 **				xwindow.h
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi, 
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  This is constructed for every normal window
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/

#include "wborder.h"
#include "rubber.h"

#ifndef XWINDOW_H
#define XWINDOW_H

#include "defs.h"

class xwindow : public QWidget
{
  Q_OBJECT

    QDesktopWidget *dt;         // root window
  WId clientid;               // client window
  int icx, icy, icw, ich;     // normal geometry in maximize state
  int scx, scy, scw, sch;     // normal geometry in screenmode
  int tcx, tcy, tcw, tch;     // normal geometry in tilemode
  char maxstate;              // maximized state 1=toolbar,2=screen
  QPoint mousepos;            // mouse position at button press
  rubber *mrb;                // move/resize rubberband
  bool actpal;                // set to active colors
  bool urgpal;                // set to urgent colors
  QColor curColor;

  bool hasTitle;
  bool hasMenu;
  bool hasMinBtn;
  bool hasMaxBtn;
  bool hasHelpBtn;
  bool decorated;
  bool startMax;
  QStringList titleOrder;

  QTimer *focustimer;         // autofocus timer
  QTimer *tfocustimer;        // focus timer in tiled mode
  int borderh;                // diff between parent and client height
  int borderw;                // diff between parent and client width
  int uborderh;               // upper border height;
  int borderSize;
  bool prot_delete;           // client has delete WM protocol
  bool prot_takefocus;        // client has take focus WM protocol
  int pos_x, pos_y;                       // XWMNormalHints 
  int base_w, base_h, inc_w, inc_h;       // XWMNormalHints
  int max_w, max_h, min_w, min_h;         // XWMNormalHints
  int wingrav;                            // XWMNormalhints
  long wmnflags;                          // XWMNormalHints
  uint init_w, init_h;        // window initial size
  bool withdrawnstate;
  bool unmapped;              // unmap called
  bool inputfield;            // WMHints
  bool map_iconic;            // WMHints
  bool urgent;                // WMHints
  Colormap cmap;              // colormap
  Window *cmapwins;           // array of subwindows with colormaps
  int ncmaps;                 // number of entries in cmaps
  bool shaped;                // nonrectangular window
  bool whidden;               // window in hidden state
  QString wmname;             // WM_NAME property or res_name
  QString icname;             // WM_ICON property or wmname
  QString res_name;           // ClassHint
  QString res_class;          // ClassHint
  QString clientmachine;      // WM_CLIENT_MACHINE
  QString clientfqdn;         // WM_CLIENT_MACHINE
  QString command;            // WM_COMMAND invoke line
  QString clientname;         // res_class or WM_COMMAND basename
  bool sstate;                // screen mode
  bool tstate;                // tile mode
  bool trsize;                // restore size after iconified in tiled mode
  Window transfor;            // TransientForHint or None
  int tnumber;                // numbering for window title
  QPixmap wicon;              // icon
  int pflags;                 // Flags from Property command
  wframe *midmove;            // upper border mid frame for move
  uborder *ubdr;              // upper window border
  lborder *lbdr;              // lower window border
  slborder *slbdr;            // side left window border
  srborder *srbdr;            // side right window border
  QVBoxLayout *layout;
  QHBoxLayout *hlayout;
  QMenu *iconmenu;
  QAction *restAct;
  QAction *maxAct;

  void getsize(int *, int *);            // adjust for possible size
  void send_wmprotocol(long, long);      // send WM_PROTOCOL to child window
  bool query_shape(void);                // nonrectangular window
  void create_wborder(void);             // create window border
  int  get_clientstate(void);            // WM_STATE
  void get_servericon(Pixmap, Pixmap);   // set wicon to server icon pixmap
  void getwmprotocols(void);             // get wm protocols
  void enable_disable_menu(void);


public slots:
  void showhelp(void);        // Show help cursor for contenxt help
  void state(bool);           // map/unmap window
  void wdestroy(void);        // destroy client
  void focus_mouse_wlist(void);  // map from window list
  void map(void);             // map/raise with check for map_iconic 
  void map_normal(void);      // map/raise without check for map_iconic
  void raise(void);           // raise only
  void show_info(void);       // show info on mid mouse button
  void unmap(void);
  void iconify(void);

  // window frame connects
  
  void t_maximize(void);      // toggle maximize to toolbar
  void s_maximize(void);      // toggle maximize to screen size
  void toggle_tiled();        // toggle tiled mode
  void tile_maximize();       // maximize in tiled mode
  void press_move(QMouseEvent *);          // start move on mouse button
  void release_move(QMouseEvent *);        // set new window position on mouse button release
  void press_leftresize(QMouseEvent *);    // start resize left
  void release_leftresize(QMouseEvent *);  // set new window size on mouse button release
  void press_rightresize(QMouseEvent *);   // start resize right
  void release_rightresize(QMouseEvent *); // set new window size on mouse button release
  void press_midresize(QMouseEvent *);
  void release_midresize(QMouseEvent *);
  void move_move(QMouseEvent *);           // mouse move for move
  void move_leftresize(QMouseEvent *);     // mouse move for left resize
  void move_rightresize(QMouseEvent *);
  void move_midresize(QMouseEvent *);

  void press_leftborder(QMouseEvent *);    // start resize left
  void release_leftborder(QMouseEvent *);  // set new window size on mouse but
  void move_leftborder(QMouseEvent *);     // mouse move for left resize

  void press_rightborder(QMouseEvent *);   // start resize right
  void release_rightborder(QMouseEvent *); // set new window size on mouse but
  void move_rightborder(QMouseEvent *);    // mouse move for right resize

  void press_topleft(QMouseEvent *);   // start resize topleft
  void release_topleft(QMouseEvent *); // set new window size on mouse but
  void move_topleft(QMouseEvent *);    // mouse move for topleft resize

  void press_topright(QMouseEvent *);  // start resize topright
  void release_topright(QMouseEvent *);// set new window size on mouse but
  void move_topright(QMouseEvent *);   // mouse move for topright resize

  void press_topborder(QMouseEvent *);  // start resize top
  void release_topborder(QMouseEvent *);// set new window size on mouse but
  void move_topborder(QMouseEvent *);   // mouse move for top resize


  void menuexec(void);
  void menuexec2(void){iconmenu->popup( QCursor::pos() );}
  void ContextMenuRequested(const QPoint &){menuexec2();};
  void repaintBG();
  void maximizeFrame(bool);
  void updateScreenShot();
  /*
protected:
  virtual void enterEvent ( QEvent *);
  virtual void leaveEvent ( QEvent *);
  virtual void wheelEvent ( QWheelEvent * );
  virtual void mousePressEvent ( QMouseEvent * );
  */
protected:
  //virtual void paintEvent ( QPaintEvent *);
  virtual void resizeEvent ( QResizeEvent * );
  virtual void moveEvent ( QMoveEvent *);
  //  QImage *bg;
  bool checkDecoration(void);

public:
  xwindow(Window w, QWidget *parent=0);
  QTimer *screenshotTimer;        // screentshot Timer
  QTimer *bgTimer;                // Rpaint Background Timer
  void get_wmname(void);          // get WM_NAME, set caption and title
  void set_title(void);           // set title on window frame
  void get_wmnormalhints(void);   // get WMNormalHints
  void get_wmhints(void);         // get WMHints
  void get_classhint(void);       // WMClassHint
  WId client_id(void)             { return(clientid); }
  int get_pflags(void)            { return(pflags); }
  QString getmachine(void)        { return(clientmachine); }
  void setinactive(void);         // set inactive colors
  void setactive(void);           // set active colors
  void seturgent(void);           // set urgent colors 
  void withdraw(void);            // transition to withdrawn state
  bool iswithdrawn(void)          { return(withdrawnstate); }
  int get_tnumber(void)           { return(tnumber); }
  QString get_clientname(void)    { return(clientname); }
  bool hidden_win(void)           { return(whidden); }
  void whide(void);               // hide window
  bool is_unmapped(void)          { return(unmapped); }
  bool is_tileable(void);         // client can be tiled
  bool is_tiled(void)             { return(tstate); }
  void minimize_frame(bool);      // minimize frame in tiling mode
  void focus_mouse(bool wlist=FALSE);    // map/raise and set mouse into window
  int  set_tile(int, int, int, int); // change to tiled desk
  void unset_tile(void);             // change to overlapped desk
  void reshape(void);             // reshape window
  void startautofocus(void);      // start autofocus
  void stopautofocus(void);       // stop autofocus timer
  void resize_client(int, int, int, int);   // resize with child window
  void resize_request(int, int, int, int);  // client resize request
  void unscreen(void);            // unset screenmode
  void set_clientstate(int);      // WM_STATE
  bool isshaped(void)             { return(shaped); }
  bool isstate(void)              { return(sstate); }
  void setchildfocus(long);       // set focus to child window
  void setcmapfocus(void);        // set colormap focus
  void setcmap(Colormap cm)       { cmap = cm; }
  void get_colormaps(void);       // get subwindow colormaps
  int get_clientflags(void);      // get client flags
  void set_pflags(int tflags=-1);     // change pflags
  int get_clienty(void)           { return(y()+uborderh); }
  int get_clientx(void)           { return(x()+(borderw/2)); }
  WId gettransfor(void)           { return(transfor); }
  int getcheight(void)            { return(height()-borderh); } 
  int getcwidth(void)             { return(width()-borderw); } 
  QString ccaption(void)          { return(wmname); }
  QString icaption(void)          { return(icname); }
  QPixmap *icon(void)             { return(&wicon); }
  //  QImage *screenShot;
  QByteArray screenBytes;
  //QString screenData;
  ~xwindow(void);
  void trayUpdateScreenShot();
  void trayRepaintBG();
};
#endif
