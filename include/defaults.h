/****************************************************************************
 **
 **				defaults.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  reads the defaults file and makes information statically
 **  accessible
 **
 ****************************************************************************/

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <startmenu.h>
#include "defs.h"

/***************************************************************************
 *
 * Desktop / Menu item structure.
 *
 **************************************************************************/
struct hdeItem {
  QString name;		// Item Name
  QString icon;		// Item Icon
  QString exec;		// Executable file
  QString path;		// it's path
  QString categories;	// Menu place
  bool isDesktop;	// is it a Dektop item?
  bool isKdeDesktop;	// is it a Kde Dektop item?
  QString error;	//
};

class defaults
{
 public:
  static int tb_height;			// Toolbar Height
  static int tc_height;			// Toolbar contents height
  static bool toolbar_top;		// Toolbar on Top
  static bool sideBorders;		// Has Side Borders		 
  static bool topBorder;		// Has Top Borders
  static int vdesks;			// 
  static bool clickToFocus;		// Focus on click
  static int lowerborderwidth;		// side borders with
  static int lowerborderheight;		// Borders Size
  static int titlebarHeight;		// upper window border
  static QFont borderfont;		//
  static QFont toolbarfont;		//
  static QFont startbtnfont;		// The Start Button Font
  static QColor inactive_bg;		//
  static QColor active_bg;		//
  static QColor inactive_bg2;		//
  static QColor active_bg2;		//
  static QColor inactive_fg;		//
  static QColor active_fg;		//
  static QColor urgent_bg;		//
  static QColor root_bg;		//
  static int bordersTransparency;	// BordersTransparency 0 -> 255
  static QString root_pix;		//
  static bool starturgent;		//
  static QStack <QString> initexec;	//
  static bool show_menu;		//
  static bool show_winlist;		//
  static bool showclientmachines;	//
  static int autofocustime;		//
  static bool start_restart;		//
  static char **argv;			//
  static int argc;			//
  static float tleftspace;		//
  static int maxontab;			//
  static int wminframe;			//
  static bool sttiled[10];		//
  static QString cfdir;			//
  static QString bgdir;			//
  static int tmx1,tmx2,tmy1,tmy2;	//
  static int smx1,smx2,smy1,smy2;	//
  static int pager_height;		//
  static QColor pager_active;		//
  static QColor pager_window;		//
  static QColor pager_visible;		//
  static int menuwidth;			//
  //static QString menutxt;		//
  static QString coding;		//
  static QString styleName;		//
  static QString titleStyle;		//
  static QString taskStyle;		//
  static QString apbarStyle;		//
  static QString lng;			//
  static QString bgDisplay;		//

  static QString min_icon;		// Minimize Icon
  static QString minmo_icon;		// Minimize Mouseover Icon
  static QString mindown_icon;		// Minimize Down Icon
  static QString umin_icon;		// Minimize Unactive Icon
  static QString uminmo_icon;		// Minimize Unactive Mouseover Icon
  static QString umindown_icon;		// Minimize Unactive Down Icon

  static QString max_icon;		// Maximize Icon
  static QString maxmo_icon;		// Maximize Mouseover Icon
  static QString maxdown_icon;		// Maximize Down Icon
  static QString umax_icon;		// Maximize Unactive Icon
  static QString umaxmo_icon;		// Maximize Unactive Mouseover Icon
  static QString umaxdown_icon;		// Maximize Unactive Down Icon

  static QString rest_icon;		// Restore Icon
  static QString restmo_icon;		// Restore Mouseover Icon
  static QString restdown_icon;		// Restore Down Icon
  static QString urest_icon;		// Restore Unactive Icon
  static QString urestmo_icon;		// Restore Unactive Mouseover Icon
  static QString urestdown_icon;	// Restore Unactive Down Icon

  static QString close_icon;		// Close Icon
  static QString closemo_icon;		// Close Mouseover Icon
  static QString closedown_icon;	// Close Down Icon
  static QString uclose_icon;		// Close Unactive Icon
  static QString uclosemo_icon;		// Close Unactive Mouseover Icon
  static QString uclosedown_icon;	// Close Unactive Down Icon

  static QString help_icon;		// Help Icon
  static QString helpmo_icon;		// Help Mouseover Icon
  static QString helpdown_icon;		// Help Down Icon
  static QString uhelp_icon;		// Help Unactive Icon
  static QString uhelpmo_icon;		// Help Unactive Mouseover Icon
  static QString uhelpdown_icon;	// Help Unactive Down Icon

  static QString left_icon;		// MinMax Icon
  static QString leftmo_icon;		// MinMax Mouseover Icon
  static QString leftdown_icon;		// MinMax Down Icon
  static QString uleft_icon;		// MinMax Unactive Icon
  static QString uleftmo_icon;		// MinMax Unactive Mouseover Icon
  static QString uleftdown_icon;	// MinMax Unactive Down Icon

  static QString minglow_icon;		// Minimize Glow Icon
  static QString maxglow_icon;		// Maximize Glow Icon
  static QString restglow_icon;		// Restore Glow Icon
  static QString closeglow_icon;	// Close Glow Icon
  static QString helpglow_icon;		// Help Glow Icon
  static QString minmaxglow_icon;		// MinMax Glow Icon
  static int glowThickness;		// Thickness of the glow.

  static QString deficon;		//
  static QString starticon;		//
  static QString startdown;		//
  static QString starticonmo;		//
  static QString starticonplace;	//
  static int startheight;		//
  static int startwidth;		//
  
  static QString toolbar_bg;		//  
  static QString tbButton_bg;		//
  static QString tbButtondown_bg;	//
  static QString tbButtonmo_bg;		//
  static int tbButtonHeight;		//

  static QColor startButton_fg;		//
  static QColor apbar_fg;		//
  static QColor tbButton_fg;		//
  
  static QString wininfo_bg;		//
  static QString wininfodown_bg;	//
  static QString wininfomo_bg;		//
  static int wininfoHeight;		//

  static QString appbar_bg;		//

  static QString titleimage;		//
  static QString titlerimage;		//
  static QString titlelimage;		//
  static QString untitleimage;		//
  static QString untitlerimage;		//
  static QString untitlelimage;		//

  static QString topborderimage;	// Top Border Image
  static QString border_tlimage;	// Top Left Border Image
  static QString border_trimage;	// Top Right Border Image
  static QString border_leftimage;	// Left Border Image
  static QString border_rightimage;	// Right Border Image
  static QString bottomborderimage;	// Bottom Border Image
  static QString border_blimage;	// Bottom Left Border Image
  static QString border_brimage;	// Bottom Right Border Image

  static QString utopborderimage;	// Unactive Top Border Image
  static QString uborder_tlimage;	// Unactive Top Left Border Image
  static QString uborder_trimage;	// Unactive Top Right Border Image
  static QString uborder_leftimage;	// Unactive Left Border Image
  static QString uborder_rightimage;	// Unactive Right Border Image
  static QString ubottomborderimage;	// Unactive Bottom Border Image
  static QString uborder_blimage;	// Unactive Bottom Left Border Image
  static QString uborder_brimage;	// Unactive Bottom Right Border Image

  static QStringList imagesDirs;	//
  static QString defaultIconsDir;	//
  static QString defaultBrowser;
  static QString defaultFM;
  static int iconsize;			// Icons Size
  static int windowButtonSize;		// Window Buttons Size
  static QString windowButtonPos;	// Window Buttons Position
  static int closeButtonWidth;		// Close Button Width
  //static int defaultButtonWidth;	// Default Button Width
  static bool flaticons;		// Down't draw buttons borders
  //  static bool withxpmenu;		//
  static startMenu *smenu;		//
  static QString menuStyle;
  static bool hijriDate;		//
  static QStringList titleOrder;	//
  static bool startBtnShadow;		// Enable Text Shadow on start button
  static bool titlebarShadow;		// Enable Text Shadow on titlebar
  static bool toolbuttonsShadow;	// Enable Text Shadow on Tool Buttons

  static void readTheme(QString theme);	//
  static void read_config(void);	// 
  static void read_cfg(void);		//
  static QString get_cfile(char *name);	//
  static QString get_cfile(QString &name){ 
    return get_cfile(name.toAscii().data());
  };	//
  static int get_tb_height(void){return tb_height;};	//
  static hdeItem readItem(QString path);		//
  
  static void addToRecentPrograms(QString path);	//
  static QString get_fullname();			//
};
#endif
