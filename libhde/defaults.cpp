/****************************************************************************
 **
 **				defaults.cpp
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


#include <qstylefactory.h>
#include <qtranslator.h>
#include <qdir.h>
#include <QTextIStream>
#include <QLocale>
#include <QTextCodec>

#include "defs.h"
#include "lhdeconf.h"
#include "defaults.h"
#include "hinifile.h"
#include "libhde.h"

QDateTime lmtime; 
int defaults::tb_height = 24;	   		// toolbar height
//int defaults::windowbuttonsize = 16;		// upper window border
int defaults::titlebarHeight = 16;    	        // upper window border
int defaults::lowerborderwidth = 22;            // lower window border
int defaults::lowerborderheight = 6;            // lower window border
int defaults::pager_height = 18;                // pager height
QFont defaults::borderfont;                     // window border font
QFont defaults::toolbarfont;                    // toolbar font
QFont defaults::startbtnfont;			// The Start Button Font

bool defaults::toolbar_top = FALSE;             // toolbar on top
bool defaults::sideBorders = TRUE;
bool defaults::topBorder = TRUE;
//bool defaults::windowsBtns = FALSE;
bool defaults::clickToFocus = FALSE;
int defaults::vdesks = 3;                       // virtual desktops
bool defaults::show_menu = TRUE;                // show menu on toolbar
int defaults::autofocustime = 600;              // autofocus time/ms or 0 = off

int defaults::tc_height = 20;                   // toolbar contents height
QColor defaults::inactive_bg = Qt::darkGray;    // window inactive color
QColor defaults::active_bg = Qt::lightGray;  	// window active color
QColor defaults::inactive_bg2 = QColor("#c5c5c5");// window inactive color
QColor defaults::active_bg2 = QColor("#c5c5c5");// window active color
QColor defaults::inactive_fg = Qt::white;    	// text inactive color
QColor defaults::active_fg = Qt::white;  	// text active color
QColor defaults::urgent_bg = Qt::red;           // window urgent color
QColor defaults::root_bg = Qt::black;           // root window background

int defaults::bordersTransparency = 127;        //BordersTransparency 0 -> 255

QString defaults::root_pix;                     // root window background pixmap
bool defaults::starturgent = TRUE;              // new windows with urgent colors
QStack <QString> defaults::initexec;            // Loaded with Exec option
bool defaults::showclientmachines = FALSE;      // show client machine names on winlist
bool defaults::show_winlist = TRUE;             // show winlist on toolbar
bool defaults::start_restart = FALSE;           // restart running
char **defaults::argv;                          // copy for restart
int defaults::argc;                             // copy for restart
float defaults::tleftspace = 0.65;              // left frame in tiled desk
int defaults::maxontab = 600;                   // maximize with tab key in tiled mode
int defaults::wminframe = 3;                    // minimize right frame in tiling mode
bool defaults::sttiled[10];                     // deskops to be tiled after start
QString defaults::cfdir = NULL;                 // config directory
int defaults::tmx1=-1,defaults::tmx2,defaults::tmy1,defaults::tmy2; 
int defaults::smx1=-1,defaults::smx2,defaults::smy1,defaults::smy2;
QColor defaults::pager_active = Qt::darkGray;   // active background color
QColor defaults::pager_window = Qt::blue;       // window background color
QColor defaults::pager_visible = Qt::darkRed;   // visible window background color
int defaults::menuwidth = 65;
QString defaults::styleName = "";
QString defaults::titleStyle = "hde";
QString defaults::taskStyle = "hde";
QString defaults::apbarStyle = "hde";
QString defaults::lng = "";
QString defaults::coding = "";
QString defaults::bgdir = "";
QString defaults::bgDisplay = "Stretch";

QString defaults::min_icon = "images/minbtn.xpm";
QString defaults::minmo_icon = "";
QString defaults::mindown_icon = "";
QString defaults::umin_icon = "images/minbtn.xpm";
QString defaults::uminmo_icon = "";
QString defaults::umindown_icon = "";

QString defaults::max_icon = "images/maxbtn.xpm";
QString defaults::maxmo_icon = "";
QString defaults::maxdown_icon = "";
QString defaults::umax_icon = "images/maxbtn.xpm";
QString defaults::umaxmo_icon = "";
QString defaults::umaxdown_icon = "";

QString defaults::rest_icon = "images/restorebtn.xpm";
QString defaults::restmo_icon = "";
QString defaults::restdown_icon = "";
QString defaults::urest_icon = "images/restorebtn.xpm";
QString defaults::urestmo_icon = "";
QString defaults::urestdown_icon = "";

QString defaults::close_icon = "images/button_right.xpm";
QString defaults::closemo_icon = "";
QString defaults::closedown_icon = "";
QString defaults::uclose_icon = "images/button_right.xpm";
QString defaults::uclosemo_icon = "";
QString defaults::uclosedown_icon = "";

QString defaults::help_icon = "images/helpbtn.xpm";
QString defaults::helpmo_icon = "";
QString defaults::helpdown_icon = "";
QString defaults::uhelp_icon = "images/helpbtn.xpm";
QString defaults::uhelpmo_icon = "";
QString defaults::uhelpdown_icon = "";

QString defaults::left_icon = "images/button_left.xpm";
QString defaults::leftmo_icon = "";
QString defaults::leftdown_icon = "";
QString defaults::uleft_icon = "images/button_left.xpm";
QString defaults::uleftmo_icon = "";
QString defaults::uleftdown_icon = "";

QString defaults::deficon = "images/default.png";
//QString defaults::starticon = "images/xpmenu.xpm";
QString defaults::starticon = "";
QString defaults::startdown = "";
QString defaults::starticonmo = "";
QString defaults::starticonplace = "MIDDLE";
int defaults::startheight = -1;
int defaults::startwidth = -1;


QString defaults::defaultBrowser = "firefox";
QString defaults::defaultFM = "hfm";

QStringList defaults::imagesDirs;

QString defaults::titleimage = "";
QString defaults::titlerimage = "";
QString defaults::titlelimage = "";
QString defaults::untitleimage = "";
QString defaults::untitlerimage = "";
QString defaults::untitlelimage = "";

QString defaults::topborderimage = "";	// Top Border Image
QString defaults::border_tlimage = "";	// Top Left Border Image
QString defaults::border_trimage = "";	// Top Right Border Image
QString defaults::border_leftimage= "";	// Left Border Image
QString defaults::border_rightimage="";	// Right Border Image
QString defaults::bottomborderimage="";	// Bottom Border Image
QString defaults::border_blimage = "";	// Bottom Left Border Image
QString defaults::border_brimage = "";	// Bottom Right Border Image

QString defaults::utopborderimage = "";	// Unactive Top Border Image
QString defaults::uborder_tlimage = "";	// Unactive Top Left Border Image
QString defaults::uborder_trimage = "";	// Unactive Top Right Border Image
QString defaults::uborder_leftimage= "";// Unactive Left Border Image
QString defaults::uborder_rightimage="";// Unactive Right Border Image
QString defaults::ubottomborderimage="";// Unactive Bottom Border Image
QString defaults::uborder_blimage = "";	// Unactive Bottom Left Border Image
QString defaults::uborder_brimage = "";	// Unactive Bottom Right Border Image

QString defaults::minglow_icon = "";	// Minimize Glow Icon
QString defaults::maxglow_icon = "";	// Maximize Glow Icon
QString defaults::restglow_icon = "";	// Restore Glow Icon
QString defaults::closeglow_icon = "";	// Close Glow Icon
QString defaults::helpglow_icon = "";	// Help Glow Icon
QString defaults::minmaxglow_icon = "";	// MinMax Glow Icon
int defaults::glowThickness = 0;	// Thickness of the glow.


int defaults::iconsize = 12;            // Icons Size
int defaults::windowButtonSize = 12;    // Window Buttons Size
QString defaults::windowButtonPos="";	// Window Buttons Position
int defaults::closeButtonWidth=-1;	// Close Button Width

bool defaults::flaticons = false;

QString defaults::toolbar_bg = "";

QString defaults::tbButton_bg = "";
QString defaults::tbButtondown_bg = "";
QString defaults::tbButtonmo_bg = "";
int defaults::tbButtonHeight = -1;
QColor defaults::tbButton_fg = Qt::black;
QColor defaults::startButton_fg = Qt::black;
QColor defaults::apbar_fg = Qt::black;

QString defaults::wininfo_bg = "";
QString defaults::wininfodown_bg = "";
QString defaults::wininfomo_bg = "";
int defaults::wininfoHeight = -1;

QString defaults::appbar_bg = "";

//bool defaults::withxpmenu = false;
bool defaults::hijriDate = false;

startMenu *defaults::smenu;
QString defaults::menuStyle = "normal";

QString defaults::defaultIconsDir="";

QStringList defaults::titleOrder;

QStyle *defstyle;

bool defaults::startBtnShadow = true;	// Enable Text Shadow on start button
bool defaults::titlebarShadow = true;	// Enable Text Shadow on titlebar
bool defaults::toolbuttonsShadow = true;// Enable Text Shadow on Tool Buttons


/*************************************************************************
 *
 * Read theme
 *
 ************************************************************************/
void defaults::readTheme(QString fname){
    QString sval;
    int ival;


    HIniFile theme(fname);
    //    theme.read();
    
    sval = theme.readString("Style","");

    defstyle = QStyleFactory::create(sval);
    styleName = sval;


    sval = theme.readString("Theme","");

    if(sval.toLower() == "motif"){
	//	styleName = "motifStyle";
    }else if(sval.toLower() == "windows"){
	//	styleName = "win98Style";
	titleStyle = "win";
	taskStyle  = "win";
	apbarStyle = "win";
	//windowsBtns = true;
	titleOrder.clear();
	titleOrder << "Menu" << "Title" << "Minimize" << "Maximize" << "Close";
	clickToFocus = true;

    }else if(sval.toLower() == "winxp"){
	titleStyle = "hde";
	taskStyle = "hde";
	apbarStyle = "hde";
	//	windowsBtns = true;
	titleOrder.clear();
	titleOrder << "Menu" << "Title" << "Minimize" << "Maximize" << "Close";
	clickToFocus = true;

	
    }else if(sval.toLower() == "hdestyle"){
	//	styleName = "hdeStyle";
	titleStyle = "hde";
	taskStyle = "hde";
	apbarStyle = "hde";
	titleOrder.clear();
	titleOrder << "Menu" << "Title" << "MinMax" << "Close";
	clickToFocus = true;
    }
    else{	
      //	cerr << "Unknown Style: " << sval << '\n';
	titleOrder.clear();
	titleOrder << "Menu" << "Title" << "Minimize" << "Maximize" << "Close";
	styleName = "hdeStyle";
    }


    min_icon = theme.readString("minicon", min_icon);
    minmo_icon = theme.readString("minmoicon", minmo_icon);
    mindown_icon = theme.readString("mindownicon", mindown_icon);
    umin_icon = theme.readString("uminicon", umin_icon);
    uminmo_icon = theme.readString("uminmoicon", uminmo_icon);
    umindown_icon = theme.readString("umindownicon", umindown_icon);

    max_icon = theme.readString("maxicon", max_icon);
    maxmo_icon = theme.readString("maxmoicon", maxmo_icon);
    maxdown_icon = theme.readString("maxdownicon", maxdown_icon);
    umax_icon = theme.readString("umaxicon", umax_icon);
    umaxmo_icon = theme.readString("umaxmoicon", umaxmo_icon);
    umaxdown_icon = theme.readString("umaxdownicon", umaxdown_icon);

    rest_icon = theme.readString("resticon", rest_icon);
    restmo_icon = theme.readString("restmoicon", restmo_icon);
    restdown_icon = theme.readString("restdownicon", restdown_icon);
    urest_icon = theme.readString("uresticon", urest_icon);
    urestmo_icon = theme.readString("urestmoicon", urestmo_icon);
    urestdown_icon = theme.readString("urestdownicon", urestdown_icon);

    close_icon = theme.readString("closeicon", close_icon);
    closemo_icon = theme.readString("closemoicon", closemo_icon);
    closedown_icon = theme.readString("closedownicon", closedown_icon);
    uclose_icon = theme.readString("ucloseicon", uclose_icon);
    uclosemo_icon = theme.readString("uclosemoicon", uclosemo_icon);
    uclosedown_icon = theme.readString("uclosedownicon", uclosedown_icon);

    help_icon = theme.readString("helpicon", help_icon);
    helpmo_icon = theme.readString("helpmoicon", helpmo_icon);
    helpdown_icon = theme.readString("helpdownicon", helpdown_icon);
    uhelp_icon = theme.readString("uhelpicon", uhelp_icon);
    uhelpmo_icon = theme.readString("uhelpmoicon", uhelpmo_icon);
    uhelpdown_icon = theme.readString("uhelpdownicon", uhelpdown_icon);

    left_icon = theme.readString("lefticon", left_icon);
    leftmo_icon = theme.readString("leftmoicon", leftmo_icon);
    leftdown_icon = theme.readString("leftdownicon", leftdown_icon);
    uleft_icon = theme.readString("ulefticon", uleft_icon);
    uleftmo_icon = theme.readString("uleftmoicon", uleftmo_icon);
    uleftdown_icon = theme.readString("uleftdownicon", uleftdown_icon);

    minglow_icon = theme.readString("minglowicon", minglow_icon);
    maxglow_icon = theme.readString("maxglowicon", maxglow_icon);
    restglow_icon = theme.readString("restglowicon", restglow_icon);
    closeglow_icon = theme.readString("closeglowicon", closeglow_icon);
    helpglow_icon = theme.readString("helpglowicon", helpglow_icon);
    minmaxglow_icon = theme.readString("minmaxlowicon", minmaxglow_icon);

    glowThickness = theme.readInt("glowThickness", glowThickness);


    deficon = theme.readString("deficon", deficon);

    starticon = theme.readString("starticon", starticon);
    startdown = theme.readString("startdown", startdown);
    starticonmo = theme.readString("starticonmo", starticonmo);

    starticonplace = theme.readString("StartIconPlace", starticonplace);

    startheight  =  theme.readInt("StartIconHeight", startheight);


    startwidth  =  theme.readInt("StartIconWidth", startheight);



    sval = theme.readString("WindowFontName","arial");
    borderfont.fromString(sval);
    ival  =  theme.readInt("WindowFontHeight", 12);
    if(ival < 4 || ival > 500)
      cerr << "WindowFontHeight: Value out of range\n";
    else
      borderfont.setPixelSize(ival);


    sval = theme.readString("StartButtonFont","arial");
    startbtnfont.fromString(sval);


    sval = theme.readString("IconFontName","arial");
    toolbarfont.fromString(sval);

    ival  =  theme.readInt("IconFontHeight", 12);
    if(ival < 4 || ival > 500)
      cerr << "IconFontHeight: Value out of range\n";
    else
      toolbarfont.setPixelSize(ival);



    tbButton_bg = theme.readString("tbButton_bg", tbButton_bg);
    tbButtondown_bg = theme.readString("tbButtondown_bg", tbButtondown_bg);
    tbButtonmo_bg = theme.readString("tbButtonmo_bg", tbButtonmo_bg);


    wininfo_bg = theme.readString("wininfo_bg", wininfo_bg);
    wininfodown_bg = theme.readString("wininfodown_bg", wininfodown_bg);
    wininfomo_bg = theme.readString("wininfomo_bg", wininfomo_bg);

    wininfoHeight  =  theme.readInt("WinInfoHeight", wininfoHeight);

    appbar_bg = theme.readString("TryBackGround", appbar_bg);



    tbButtonHeight  =  theme.readInt("ToolButtonHeight", tbButtonHeight);


    clickToFocus = theme.readBool("clickToFocus", clickToFocus);


    menuStyle = theme.readString("menuStyle", menuStyle);

    titleimage = theme.readString("TitleImage", titleimage);
    titlerimage = theme.readString("TitleRightImage", titlerimage);
    titlelimage = theme.readString("TitleLeftImage", titlelimage);

    untitleimage = theme.readString("UnactiveTitleImage", untitleimage);
    untitlerimage = theme.readString("UnactiveTitleRightImage", titlerimage);
    untitlelimage = theme.readString("UnactiveTitleLeftImage", titlelimage);

    // Borders Images
    topborderimage = theme.readString("BorderTopImage", topborderimage);
    border_tlimage = theme.readString("BorderTopLeftImage", border_tlimage);
    border_trimage = theme.readString("BorderTopRightImage", border_trimage);

    border_leftimage = theme.readString("BorderLeftImage", border_leftimage);
    border_rightimage = theme.readString("BorderRightImage",
					 border_rightimage);

    bottomborderimage = theme.readString("BorderBottomImage",
					 bottomborderimage);

    border_blimage = theme.readString("BorderBottomLeftImage", border_blimage);
    border_brimage = theme.readString("BorderBottomRightImage",
				      border_brimage);

    // Unactive Borders Images
    utopborderimage = theme.readString("UBorderTopImage", utopborderimage);
    uborder_tlimage = theme.readString("UBorderTopLeftImage", uborder_tlimage);
    uborder_trimage = theme.readString("UBorderTopRightImage",
				       uborder_trimage);

    uborder_leftimage = theme.readString("UBorderLeftImage", 
					 uborder_leftimage);
    uborder_rightimage = theme.readString("UBorderRightImage",
					 uborder_rightimage);

    ubottomborderimage = theme.readString("UBorderBottomImage",
					 ubottomborderimage);

    uborder_blimage = theme.readString("UBorderBottomLeftImage",
				       uborder_blimage);
    uborder_brimage = theme.readString("UBorderBottomRightImage",
				      uborder_brimage);

    flaticons = theme.readBool("flaticons", flaticons);

    sideBorders = theme.readBool("SideBorders",sideBorders);
    topBorder = theme.readBool("topBorder",sideBorders);

    //    windowsBtns = theme.readBool("windowsBtns", windowsBtns);

    clickToFocus = theme.readBool("clickToFocus", clickToFocus);


    toolbar_bg = theme.readString("ToolbarBackGround", toolbar_bg);

    sval = theme.readString("tbButtonForeground", tbButton_fg.name());
    if (sval != "" )
	tbButton_fg.setNamedColor(sval);


    sval = theme.readString("startForeground", startButton_fg.name());
    if(sval == "Qt::transparent")
      startButton_fg = Qt::transparent;
    else if (sval != "" )
	startButton_fg.setNamedColor(sval);


    sval = theme.readString("apbarForeground", apbar_fg.name());
    if (sval != "" )
	apbar_fg.setNamedColor(sval);



    ival  =  theme.readInt("ToolbarHeight", tb_height);
    if(ival < 10 || ival > 500)
      cerr << "ToolbarHeight: Value out of range\n";
    else
      tb_height = ival;
						

    ival  =  theme.readInt("TitlebarHeight", titlebarHeight);
    if(ival < 6 || ival > 500)
      cerr << "TitlebarHeight: Value out of range\n";
    else
    {
      titlebarHeight = ival;
      iconsize = titlebarHeight -4;
      windowButtonSize = iconsize;
    }

    windowButtonPos = theme.readString("WindowButtonPos",windowButtonPos);

    closeButtonWidth  =  theme.readInt("closewidth", closeButtonWidth);


    ival  =  theme.readInt("IconSize", iconsize);
    if(ival < 3 || ival > titlebarHeight)
      cerr << "IconSize: Value out of range\n";
    else
      iconsize = ival;

    ival  =  theme.readInt("WindowButtonSize", windowButtonSize);
    if(ival < 3 || ival > titlebarHeight)
      cerr << "WindowButtonSize: Value out of range\n";
    else
      windowButtonSize = ival;

    if(closeButtonWidth < 0)
      closeButtonWidth = windowButtonSize;

    ival  =  theme.readInt("LowerBorderHeight", lowerborderheight);
    if(ival < 1 || ival > 500)
      cerr << "LowerBorderHeight: Value out of range\n";
    else
      lowerborderheight = ival;
    
    
    ival  =  theme.readInt("LowerBorderWidth", lowerborderwidth);
    if(ival < 1 || ival > 500)
      cerr << "LowerBorderWidth: Value out of range\n";
    else
      lowerborderwidth = ival;
    

    
    ival  =  theme.readInt("PagerHeight", pager_height);
    if(ival < 4 && ival > 500)
      cerr << "PagerHeight: Value out of range\n";
    else
      pager_height = ival;
    
    startBtnShadow = theme.readBool("startBtnShadow", startBtnShadow);
    titlebarShadow = theme.readBool( "titlebarShadow", titlebarShadow);
    toolbuttonsShadow = theme.readBool( "toolbuttonsShadow", 
					toolbuttonsShadow);
    
    
    // Colors & Backgrounds
    theme.setGroup("Color_Background");
    sval = theme.readString("InactiveWindowColor","");
    if (sval != "" )
      inactive_bg.setNamedColor(sval);
    
    sval = theme.readString("activeWindowColor","");
    if (sval != "" )
      active_bg.setNamedColor(sval);
    
    sval = theme.readString("InactiveWindowColor2","");
    if (sval != "" )
	    inactive_bg2.setNamedColor(sval);
    
    sval = theme.readString("activeWindowColor2","");
    if (sval != "" )
      active_bg2.setNamedColor(sval);
    
    
    sval = theme.readString("InactiveTextColor","");
    if (sval != "" )
      inactive_fg.setNamedColor(sval);
    
    sval = theme.readString("activeTextColor","");
    if (sval != "" )
      active_fg.setNamedColor(sval);

	
    sval = theme.readString("UrgentWindowColor","");
    if (sval != "" )
      urgent_bg.setNamedColor(sval);


    ival = theme.readInt("BordersTransparency",	bordersTransparency);
    if(ival < 0 || ival > 256)
      cerr << "BordersTransparency: Value out of range\n";
    else
      bordersTransparency = ival;



    // Titlebar Order
    theme.setGroup("TitlebarOrder");
    titleOrder.clear();
    for(int i = 0; i < 6; i++)
    {
      sval = theme.readString(QString("TitlebarItem[%1]").arg(i), "");
      if (sval != "" )
	titleOrder << sval;
    }

    if(titleOrder.empty())
    {
      titleOrder << "Menu" << "Title" << "MinMax" << "Close";
    }

}

/***********************************************************************
 *
 * Read Config
 *
 **********************************************************************/
void defaults::read_config(void){
    int ival;

    borderfont.setPixelSize(windowButtonSize-5);
    //    initexec.setAutoDelete(TRUE);
    /*
    static char *par[] = {
      "Exec",                   // 0
      "Maximize1",              // 1
      "Maximize2",              // 2
      "TileStart",              // 3
      NULL };
    */
    QString fname,cline,sval, p1,p2;
    
    fname = get_cfile("defaults");

    QFileInfo fi(fname);
    
    if(fi.lastModified() == lmtime)
	return;
    
    lmtime == fi.lastModified();


    //QFile istr(fname);

    HIniFile defaults(fname);

    ival  =  defaults.readInt("ToolbarHeight", 24);
    if(ival < 10 || ival > 500)
      cerr << "ToolbarHeight: Value out of range\n";
    else
      tb_height = ival;
						

	ival  =  defaults.readInt("TitlebarHeight", 16);
	if(ival < 6 || ival > 500)
	    cerr << "TitlebarHeight: Value out of range\n";
	else
	{
	  titlebarHeight = ival;
	  iconsize = titlebarHeight -4;
	  windowButtonSize = iconsize;
	}

	ival  =  defaults.readInt("IconSize", iconsize);
	if(ival < 3 || ival > titlebarHeight)
	    cerr << "IconSize: Value out of range\n";
	else
	    iconsize = ival;

	ival  =  defaults.readInt("WindowButtonSize", iconsize);
	if(ival < 3 || ival > titlebarHeight)
	    cerr << "WindowButtonSize: Value out of range\n";
	else
	    windowButtonSize = ival;

	ival  =  defaults.readInt("LowerBorderHeight", 6);
	if(ival < 1 || ival > 500)
	    cerr << "LowerBorderHeight: Value out of range\n";
	else
	    lowerborderheight = ival;
	

	sideBorders = defaults.readBool("SideBorders",true);
	

	ival  =  defaults.readInt("LowerBorderWidth", 22);
	if(ival < 1 || ival > 500)
	    cerr << "LowerBorderWidth: Value out of range\n";
	else
	    lowerborderwidth = ival;



	ival  =  defaults.readInt("PagerHeight", 18);
	if(ival < 4 && ival > 500)
	    cerr << "PagerHeight: Value out of range\n";
	else
	    pager_height = ival;


	//	menutxt = defaults.readString("MenuText","Start");
	coding = defaults.readString("Encoding","");


	sval = defaults.readString("WindowFontName","arial");
	//	borderfont.setFamily(sval);
	borderfont.fromString(sval);
	ival  =  defaults.readInt("WindowFontHeight", 11);
	if(ival < 4 || ival > 500)
	    cerr << "WindowFontHeight: Value out of range\n";
	else
	    borderfont.setPixelSize(ival);


	sval = defaults.readString("StartButtonFont","arial");
	startbtnfont.fromString(sval);


	sval = defaults.readString("IconFontName","arial");
	//toolbarfont.setFamily(sval);
	toolbarfont.fromString(sval);

	ival  =  defaults.readInt("IconFontHeight", 11);
	if(ival < 4 || ival > 500)
	    cerr << "IconFontHeight: Value out of range\n";
	else
	    toolbarfont.setPixelSize(ival);



	toolbar_top = defaults.readBool("ToolbarOnTop",false);





	show_menu = defaults.readBool("ShowMenus",true);;



	ival  =  defaults.readInt("AutoRaiseTime", 600);
	if(ival < 0 || ival > 100000)
	    cerr << "AutoRaiseTime: Value out of range\n";
	else
	    autofocustime = ival;







	starturgent = defaults.readBool("StartClientsUrgent",false);








	showclientmachines = defaults.readBool("ShowClientMachines",false);

	show_winlist = defaults.readBool("ShowWinlist",true);



	defaultBrowser = defaults.readString("defaultBrowser",defaultBrowser);
	defaultFM = defaults.readString("defaultFileManager",defaultFM);



	lng = defaults.readString("Language","default");

	if(lng == "default"){
	  /*
	  QLocale locale = QLocale::system();
	  QString lngTmp(QLocale::languageToString(locale.language()));
	    if (int indx = lngTmp.indexOf('_') != -1)
		lng = lngTmp.left(indx+1);
	    else
		lng = lngTmp;
	  */
	  lng = QLocale::system().name();

	}

	ival = defaults.readInt("TileSplit", 65);
	if(ival < 1 || ival > 99)
	    cerr << "TileSplit: Value out of range\n";
	else
	    tleftspace = ival/100;


	ival  =  defaults.readInt("TileMaxWithTab", 600);
		if(ival < 0 || ival > 10000)
		    cerr << "TileMaxOnTab: Value out of range\n";
		else
		    maxontab = ival;


	ival  =  defaults.readInt("TileMinframe", 600);
	if(ival < 0 || ival > 10000)
	    cerr << "TileMinframe: Value out of range\n";
	else
	    wminframe = ival;

	//	windowsBtns = defaults.readBool("windowsBtns", windowsBtns);
	clickToFocus = defaults.readBool("clickToFocus", clickToFocus);


	// Pager
	defaults.setGroup("Pager");

	sval = defaults.readString("PagerActiveColor","");
	if (sval != "" )
	    pager_active.setNamedColor(sval);


	sval = defaults.readString("PagerVisibleColor","");
	if (sval != "" )
	    pager_visible.setNamedColor(sval);


	sval = defaults.readString("PagerInvisibleColor","");
	if (sval != "" )
	    pager_window.setNamedColor(sval);

	ival  =  defaults.readInt("VirtualDesktops", 3);
	if(ival < 1 || ival > MAXDESKS){
	    cerr << "VirtualDesktops: Value out of range\n";
	    vdesks = 3;
	}else
	    vdesks = ival;



	// Colors & Backgrounds
	defaults.setGroup("Color_Background");
	sval = defaults.readString("InactiveWindowColor","");
	if (sval != "" )
	    inactive_bg.setNamedColor(sval);

	sval = defaults.readString("activeWindowColor","");
	if (sval != "" )
	    active_bg.setNamedColor(sval);

	sval = defaults.readString("InactiveWindowColor2","");
	if (sval != "" )
	    inactive_bg2.setNamedColor(sval);

	sval = defaults.readString("activeWindowColor2","");
	if (sval != "" )
	    active_bg2.setNamedColor(sval);


	sval = defaults.readString("InactiveTextColor","");
	if (sval != "" )
	    inactive_fg.setNamedColor(sval);

	sval = defaults.readString("activeTextColor","");
	if (sval != "" )
	    active_fg.setNamedColor(sval);


	sval = defaults.readString("UrgentWindowColor","");
	if (sval != "" )
	    urgent_bg.setNamedColor(sval);


	ival = defaults.readInt("BordersTransparency",	bordersTransparency);
	if(ival < 0 || ival > 256)
	  cerr << "BordersTransparency: Value out of range\n";
	else
	  bordersTransparency = ival;



	bgdir = getenv("HOME");
	bgdir = defaults.readString("BGDIR", bgdir);

	sval = defaults.readString("RootBackgroundColor","");
	if (sval != "" )
	    root_bg.setNamedColor(sval);

#ifdef Q_WS_X11 

	sval = defaults.readString("RootBackgroundPicture","");
	if((access((const char *)sval.toAscii().data(), R_OK) == -1)
	   || sval == "")
	  perror((const char *)sval.toAscii().data());
	else	
	    root_pix = sval;

	bgDisplay = defaults.readString("bgDisplay", bgDisplay);
#endif

	//QStringList defaults::imagesDirs;
	//QStringList drs;
	sval = defaults.readString("ImagesDirs","");
	imagesDirs.clear();
	imagesDirs.append(sval);
	
	defaultIconsDir = defaults.readString("DefaultIconsDir", 
					      defaultIconsDir);
	if(defaultIconsDir != "")
	    imagesDirs.append(defaultIconsDir);

	if(QFile(QString(getenv("HOME")) + "/.config/hde2").exists())
		imagesDirs.append( QString(getenv("HOME")) + "/.config/hde2");
        if(QFile().exists(QString(CONFDIR) ))
	    imagesDirs.append( QString(CONFDIR));
	   

//        if(QFile().exists(QStringList::split(";", sval)))
 //		imagesDirs += QStringList::split(";", sval);
        if(QFile().exists("/usr/share/pixmaps"))
	    imagesDirs.append( "/usr/share/pixmaps" );
       if(QFile().exists("/usr/share/icons/crystalsvg"))
	 imagesDirs.append("/usr/share/icons/crystalsvg");

        if(QFile().exists("/usr/share/icons"))
	  imagesDirs.append("/usr/share/icons");
	if(QFile().exists("/usr/share/icons/hicolor"))
	  imagesDirs.append("/usr/share/icons/hicolor");
//        if(QFile().exists("/usr/share/icons/Crystal"))
//	    imagesDirs += "/usr/share/icons/Crystal";
	
	// Date & Time
	defaults.setGroup("DateTime");
	hijriDate = defaults.readBool("hijriDate", hijriDate);

	// Style & Themes

	defaults.setGroup("Style");
	sval = defaults.readString("Style","platinum");

	defstyle = QStyleFactory::create(sval);
	//qApp->setStyle(sval);
	styleName = sval;

	if(sval.toLower() == "motif"){
	    //	    defstyle = QStyleFactory::create("Motif");
	    //    styleName = "motifStyle";
	}else if(sval.toLower() == "windows"){
	  //defstyle = QStyleFactory::create("Windows");
	  //styleName = "win98Style";
	  titleStyle = "win";
	  taskStyle = "win";
	  apbarStyle = "win";
	  //	    windowsBtns = true;
	  titleOrder.clear();
	  titleOrder << "Menu" << "Title" << "Minimize" << "Maximize"
		     << "Close";
	  clickToFocus = true;
	    /*
	}else if(sval.toLower() == "platinum"){
	    //defstyle = QStyleFactory::create("Platinum");
	    styleName = "platinumStyle";
	}else if(sval.toLower() == "motifplus"){
	    //defstyle = QStyleFactory::create("MotifPlus");
	    styleName = "motifPlusStyle";
	}else if(sval.toLower() == "cde"){
	    //defstyle = QStyleFactory::create("CDE");
	    styleName = "cdeStyle";


	}else if(sval.toLower() == "sgi"){
	    //defstyle = QStyleFactory::create("SGI");
	    styleName = "SGIStyle";
	    */

	}else if(sval.toLower() == "winxp"){
	    //    defstyle = new hdeStyle;
	    //defstyle = QStyleFactory::create("hdeStyle");
	    //  styleName = "WinXPStyle";
	    titleStyle = "hde";
	    taskStyle = "hde";
	    apbarStyle = "hde";
	    //	    windowsBtns = true;
	    titleOrder.clear();
	    titleOrder << "Menu" << "Title" << "Minimize" << "Maximize" 
		       << "Close";
	    clickToFocus = true;
	
	}else if(sval.toLower() == "hdestyle"){
	    //defstyle = new hdeStyle;
	    //defstyle = QStyleFactory::create("hdeStyle");
	    //styleName = "hdeStyle";
	    titleStyle = "hde";
	    taskStyle = "hde";
	    apbarStyle = "hde";
	    clickToFocus = true;
	}
	else{	
	  //cerr << "Unknown Style: " << sval << '\n';
	    styleName = "hdeStyle";
	}
	sval = "";

	//	if(defstyle)
	//qApp->setStyle(defstyle);
	menuStyle = defaults.readString("menuStyle", menuStyle);


	sval = defaults.readString("Theme","");
	if(sval != "")
	    readTheme(sval);

	if(defstyle)
	  qApp->setStyle(defstyle);

	// Execute at Startup
	if(start_restart == FALSE){
	  defaults.setGroup("Execute");
	  ival  =  defaults.readInt("Exec_Number", 0);

	  if (ival > 0){
	    for(int i = 0; i < ival; i++){
	      sval = defaults.readString(QString("Exec[%1]").arg(i+1), 
					 "");
	      if(sval != ""){
		initexec.push( sval );
	      }
	    }
	  }
	}




    /*	
    QFontInfo info(borderfont);
    if(info.family() != borderfont.family())
	cerr << "WM: no match for font " << borderfont.family() << ", using " << info.family() << " instead\n";
    

    QFontInfo tinfo(toolbarfont);
    if(tinfo.family() != toolbarfont.family())
	cerr << "WM: no match for font " << toolbarfont.family() << ", using " << tinfo.family() << " instead\n";
    */	

    tc_height = tb_height-4;

    if(pager_height > tb_height)
	pager_height = tb_height;
	
    if(borderfont.pixelSize() > windowButtonSize-3){
	iconsize = borderfont.pixelSize()+3;
	//cerr << "WM: windowborder too small for font, set to " << windowbuttonsize << '\n';
    }

    if(toolbarfont.pixelSize() > tc_height-4){
	tc_height = toolbarfont.pixelSize()+4;
	tb_height = tc_height+4;
	//cerr << "WM: toolbar contents too small for font, set to " << tc_height << '\n';
    }


    QTranslator libtranslator( 0 );
    libtranslator.load( "libhde_" + defaults::lng , get_cfile("lng") );

    qApp->installTranslator( &libtranslator );


}

/**************************************************************************
 *
 * Read small config, for programs others than hde, which need the full
 * configuration reading above.
 *
 *************************************************************************/
void defaults::read_cfg(void){
    int ival;

    QString fname,cline,sval, p1,p2;
    
    fname = get_cfile("defaults");

    QFileInfo fi(fname);
    
    if(fi.lastModified() == lmtime)
      return;
    
    lmtime == fi.lastModified();
    
    HIniFile defaults(fname);
    //defaults.read();


    if(fname.isNull() ){
      if(! fname.isNull())
	perror("cannot open defaults file");
    }else{
      
      ival  =  defaults.readInt("ToolbarHeight", 24);
      if(ival < 10 || ival > 500)
	;//cerr << "ToolbarHeight: Value out of range\n";
      else
	tb_height = ival;
						
      
      ival  =  defaults.readInt("TitlebarHeight", titlebarHeight);
      if(ival < 6 || ival > 500)
	;//cerr << "WindowButtonSize: Value out of range\n";
      else
	titlebarHeight = ival;
      
      
      ival  =  defaults.readInt("LowerBorderHeight", 6);
      if(ival < 1 || ival > 500)
	;//cerr << "LowerBorderHeight: Value out of range\n";
      else
	lowerborderheight = ival;
      
      
      sideBorders = defaults.readBool("SideBorders",true);
	
      
      ival  =  defaults.readInt("LowerBorderWidth", 22);
      if(ival < 1 || ival > 500)
	;//cerr << "LowerBorderWidth: Value out of range\n";
      else
	lowerborderwidth = ival;


	coding = defaults.readString("Encoding","");

	lng = defaults.readString("Language","default");

	if(lng == "default"){
	  QLocale locale = QLocale::system();
	  QString lngTmp(QLocale::languageToString(locale.language()));
	  //	  QString lngTmp(QTextCodec::locale());
	  if (int indx = lngTmp.indexOf('_') != -1)
	    lng = lngTmp.left(indx+1);
	  else
	    lng = lngTmp;
	}


	//	bgdir = getenv("HOME");
	//	bgdir = defaults.readString("BGDIR", bgdir);
	//	bgDisplay = defaults.readString("bgDisplay", bgDisplay);


	
	// Style & Themes
	defaults.setGroup("Style");

	sval = defaults.readString("Style","platinum");
	
	
	qApp->setStyle(sval);
	styleName = sval;



	defaults.setGroup("Color_Background");
	sval = defaults.readString("ImagesDirs","");
	imagesDirs.clear();
	imagesDirs.append(sval);
	
	defaultIconsDir = defaults.readString("DefaultIconsDir", 
					      defaultIconsDir);
	if(defaultIconsDir != "")
	    imagesDirs.append(defaultIconsDir);

	if(QFile(QString(getenv("HOME")) + "/.config/hde2").exists())
		imagesDirs.append( QString(getenv("HOME")) + "/.config/hde2");
        if(QFile().exists(QString(CONFDIR) ))
	    imagesDirs.append( QString(CONFDIR));
	   

//        if(QFile().exists(QStringList::split(";", sval)))
 //		imagesDirs += QStringList::split(";", sval);
        if(QFile().exists("/usr/share/pixmaps"))
	    imagesDirs.append( "/usr/share/pixmaps" );
       if(QFile().exists("/usr/share/icons/crystalsvg"))
	 imagesDirs.append("/usr/share/icons/crystalsvg");

        if(QFile().exists("/usr/share/icons"))
	  imagesDirs.append("/usr/share/icons");
	if(QFile().exists("/usr/share/icons/hicolor"))
	  imagesDirs.append("/usr/share/icons/hicolor");

   }



    sval = "";
    sval = defaults.readString("Theme","");
    if(sval != "")
      readTheme(sval);
    
    QTranslator libtranslator( 0 );
    libtranslator.load( "libhde_" + defaults::lng , get_cfile("lng") );
    
    qApp->installTranslator( &libtranslator );
}


/************************************************************************
 *
 * Returns the path of the config file.
 *
 ***********************************************************************/
QString defaults::get_cfile(char *name){
  QString fname;
  
  if(cfdir.isNull()){
    QString fname(getenv("HOME"));
    
    if(! fname.isNull())
      cfdir = fname + "/.config/hde2";
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
  
  perror((const char *)fname.toAscii().data());
  fname = QString();
  return(fname);
}

/*********************************************************************
 *
 * Get the standard menu path from the categories.
 *
 ********************************************************************/
QString getRightCategory(QString cat){
  QString category = cat;
  /*
  if(category == "Qt"){
    category = "";
  }else if(category == "KDE"){
    category = "";
  }else if(category == "GNOME"){
    category = "";
  }else if(category == "GTK"){
    category = "";
  }else if(category == "Motif"){
    category = "";
  }else if(category == "Java"){
    category = "";
  }else if(category == "X-Haydar"){
    category = "";
  }else if(category == "X-Haydar-Extra"){
    category = "";
  }else if(category == "X-Haydar-Base"){
    category = "";
  }else if(category == "X-Red-Hat-Base"){
    category = "";
  }else if(category == "X-Red-Hat-Extra"){
    category = "";
  }else if(category == "Application"){
    category = "";
  }else if(category == "X-Ximian-Main"){
    category = "";
  }else if(category == "X-Ximian-Toplevel"){
    category = "";
  }else if(category == "X-KDE-settings-sound"){
    category = "KDE/Settings/Sound";
  }else if(category == "X-KDE-settings-looknfeel"){
    category = "KDE/Settings/LookNFeel";
  }else if(category == "X-KDE-settings-system"){
    category = "KDE/Settings/System";
  }else if(category == "X-KDE-settings-webbrowsing"){
    category = "KDE/Settings/WebBrowsing";
  }else if(category == "X-KDE-settings-components"){
    category = "KDE/Settings/Components";
  }else if(category == "X-KDE-settings-security"){
    category = "KDE/Settings/Security";
  }else if(category == "X-KDE-settings-desktop"){
    category = "KDE/Settings/Desktop";
  }else if(category == "X-KDE-settings-hardware"){
    category = "KDE/Settings/Hardware";
  }else if(category == "X-KDE-settings-network"){
    category = "KDE/Settings/Nework";
  }else if(category == "X-KDE-settings-accessibility"){
    category = "KDE/Settings/Accessibility";
  }else if(category == "X-KDE-information"){
    category = "KDE/Information";
  }
*/

  return category;
}

QString stripCategories(QString cat){

  return cat;
  /*
  QString categories= "";
  int indx, oldIndx;
  oldIndx = 0;
  indx = cat.indexOf(';');

  while(indx >= 0){
    QString subCat = "";
    if(oldIndx == 0)
      subCat = cat.mid(oldIndx, indx-oldIndx);
    else
      subCat = cat.mid(oldIndx+1, indx-oldIndx-1);
    
    subCat = getRightCategory(subCat);

    if(!subCat.isEmpty())
    {
      if(categories.isEmpty())
      {
	categories.append(subCat);
      }else{
	categories.append("/");
	categories.append(subCat);
      }
    }

    //    cout << categories << endl;
    oldIndx= indx;
    indx = cat.indexOf(';', indx +1);
  }

  return categories;
  */
}

/********************************************************************
 *
 * Read desktop Item
 *
 *******************************************************************/
hdeItem defaults::readItem(QString path){
  hdeItem item;
  QString svar = QFileInfo(path).fileName();
  
  QString prg, exec= "";


  if( QFileInfo(path).isExecutable() )
  {
    QFileInfo *fi = new QFileInfo(path);
    item.name = fi->fileName();
    item.icon = "";//prg;
    item.exec = path;
    item.path = path;
    delete fi;
    return item;
  }

  QFile file( path );
  if ( file.exists()){
    if ( file.open( QIODevice::ReadOnly ) ) {
      //      QTextStream stream( &file );
      QString line;
      //      line = stream.readLine();
      line = file.readLine().simplified();
      while(line.at(0) == '#')
	line = file.readLine().simplified();
      if(line.contains("[Desktop" ) > 0){
	item.isDesktop = true;
	//break;
      }else if(line.contains("[KDE Desktop Entry]" ) > 0){
	item.isKdeDesktop = true;
	//break;
      }else
      {
	QFileInfo *fi = new QFileInfo(path);
	if(fi->suffix() == "exe")
	{
	  item.name = fi->baseName();
	  item.icon = "exec_wine";//prg;
	  item.exec = "wine " + path;
	}else{
	  item.name = fi->fileName();
	  item.icon = "";//prg;
	  item.exec = path;
	}
	item.path = path;
	delete fi;
	return item;
      }
      file.close();
    }
    
    if(!item.isDesktop){
      item.name = svar;
      
      if(item.isKdeDesktop){
	
	HIniFile lnkIni(path);
	//lnkIni.read();
	lnkIni.setGroup("KDE Desktop Entry");
	QString enc = lnkIni.readString("Encoding", "NOENC");

	bool isHidden = lnkIni.readBool("Hidden", false);
	if(isHidden)
	{
	  item.error = path + ": is Hidden Item";	
	  return item;
	}

	svar = lnkIni.readString("Name", svar);
	if(lng != "default"){
	  svar = lnkIni.readString("Name["+ lng + "]" , 
				   lnkIni.readString("Name["+ lng.left(2) + 
						     "]", svar));

	  QString charset = hde_langinfo(lng);
	  
	  if (enc != "NOENC"){
	    if(enc == "UTF-8") 
	      svar = QString::fromUtf8( (char *)svar.toAscii().data() );
	    else
	    {
	      QTextCodec *codec = 
		QTextCodec::codecForName(enc.toAscii().data());
	      if(codec->canEncode ( svar ) )
	      svar = codec->toUnicode((char *)svar.toAscii().data());
	    }
	  }else{
	      QTextCodec *codec = QTextCodec::codecForName(charset.toAscii().data());
	    svar = codec->toUnicode((char *)svar.toAscii().data());
	  }
	}else{
	  svar = lnkIni.readString("Name",svar);
	}
	
	prg = lnkIni.readString("Icon", "");
	
	QString type = lnkIni.readString("Type", "");
	/* Values are: Application, Link, FSDevice, MimeType, Directory, 
	   Service, ServiceType */ 

	if(type == "Link" || type == "Directory" ){
	  exec = lnkIni.readString("URL", "");
	  if(defaults::lng != "default")
	    exec = 
	      lnkIni.readString( "URL["+ lng + "]" ,
				 lnkIni.readString("URL["+ lng.left(2)+ "]", 
						   lnkIni.readString("URL", 
								     exec)));


	}else{
	  exec = lnkIni.readString("Exec", "");
	  if(defaults::lng != "default")
	    exec = 
	      lnkIni.readString("Exec["+ lng + "]",
				lnkIni.readString("Exec[" + lng.left(2)
						  + "]", 
						  lnkIni.readString("Exec",
								    exec)));
	}

	if(type == "Link"){
	  if( QDir(exec).exists() ){
	    type = "Directory";
	  }else if((exec == "system:/") || (exec == "trash:/")
		   || (exec == "media:/") || (exec == "remote:/")
		   || (exec == "applications:/") || (exec == "settings:/") ){
	    type = "Directory";
	  }
	}
	
	if(type == "Link" )
	  exec = defaultBrowser+ " " + exec;
	else if(type == "Directory")
	  exec = defaultFM + " " + exec;
	
	item.name = svar;
	item.icon = prg;
	item.exec = exec;
	item.path = path;
	
      }
    }else{
      HIniFile lnkIni(path);
      lnkIni.setGroup("Desktop Entry");
      
      bool isHidden = lnkIni.readBool("Hidden", false);
      if(isHidden)
      {
	item.error = path + ": is Hidden Item";	
	return item;
      }

      QString enc = lnkIni.readString("Encoding", "NOENC");
      svar = lnkIni.readString("Name", svar);
      if(lng != "default"){
	svar = lnkIni.readString("Name["+ lng + "]" , 
				 lnkIni.readString("Name["+ lng.left(2) + "]", 
						   svar));
	
	QString charset = hde_langinfo(lng);
	if ((enc != "NOENC") && (enc != "Legacy-Mixed")){
	  if(enc == "UTF-8") 
	    svar = QString::fromUtf8( (char *)svar.toAscii().data() );
	  else
	  {
	    QTextCodec *codec = 
	      QTextCodec::codecForName(enc.toAscii().data());
	    //if(codec->canEncode ( svar ) )
	    svar = codec->toUnicode(svar.toAscii());
	  }
	}else{
	  QTextCodec *codec = 
	   QTextCodec::codecForName(charset.toAscii().data());
	  svar = codec->toUnicode(svar.toAscii());
	}
      }else{
	svar = lnkIni.readString("Name",svar);
      }
     
      prg = lnkIni.readString("Icon", "");
      
      QString type = lnkIni.readString("Type", "");
      /* Values are: Application, Link, FSDevice, MimeType, Directory, 
	 Service, ServiceType */ 
      
      if(type == "Link" || type == "Directory" ){
	exec = lnkIni.readString("URL", "");
	if(defaults::lng != "default")
	  exec =  lnkIni.readString("URL["+ lng + "]" , 
				    lnkIni.readString("URL["+ lng.left(2)
				    + "]", lnkIni.readString("URL",  exec)));

      }else{
	exec = lnkIni.readString("Exec", "");
	if(defaults::lng != "default")
	  exec = lnkIni.readString("Exec["+ lng + "]" ,
				   lnkIni.readString("Exec["+ lng.left(2)
				+ "]", lnkIni.readString("Exec", exec)));
      }
      
      if(type == "Link"){
	if( QDir(exec).exists() ){
	  type = "Directory";
	}else if((exec == "system:/") || (exec == "trash:/")
		 || (exec == "media:/") || (exec == "remote:/")
		 || (exec == "applications:/") || (exec == "settings:/") ){
	  type = "Directory";
	}
      }
      
      if(type == "Link" )
	exec = defaultBrowser + " " + exec;
      else if(type == "Directory")
	exec = defaultFM + " " + exec;
      

      //QString categories = lnkIni.readString("Categories", "Application");
      
      /********************************************************************
       *
       * Work arround ';' issue in QSetting
       *
       *******************************************************************/
      QString categories;
      if (file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
	QTextStream stream(&file);
	while (!stream.atEnd()) {
	  QString line = stream.readLine().simplified();
	  if(line.left(11) == "Categories=")
	  {
	    categories = line.right(line.length()-11).simplified();
	  }else	if(line.left(12) == "Categories =")
	  {
	    categories = line.right(line.length()-12).simplified();
	  }
	}
      }


      /*
      if(categories != "")
	{
	  // Get rid of latst category
	  	  
	  int indx = categories.findRev(';');
	  categories = categories.left(indx);
	  indx = categories.findRev(';');
	  categories = categories.left(indx+1);
	  //categories = categories.replace(';', '/');
	  
	  //categories = stripCategories(categories);//.left(indx);
	 
	}
      */

      item.categories = categories;
      item.name = svar;
      item.icon = prg;
      item.exec = exec;
      item.path = path;
      }
    }else{
	item.error = path + ": file not found";	
    }
    return item;
}

void defaults::addToRecentPrograms(QString path)
{
    if(defaults::cfdir.isNull()){
	QString fname(getenv("HOME"));

	if(! fname.isNull())
	    defaults::cfdir = fname + "/.config/hde2";
    }
    QString cmp( defaults::cfdir + "/recentPrograms" );

    QFile file( cmp );
    if(!file.exists()){
      if ( file.open( QIODevice::WriteOnly ) ) {
	QTextStream stream( &file );
	stream << path << endl;
	file.close();
      }
    }else{
      QStringList list;
      if ( file.open( QIODevice::ReadOnly ) ) {
	QTextStream stream( &file );
	while (!stream.atEnd()) {
	  QString line = stream.readLine();
	  list << line;
	}
	file.close();
      }
      if ( file.open( QIODevice::WriteOnly ) ) {
	if( list.contains(path) )
	{
	  list.move(list.indexOf(path),0);
	  QTextStream stream( &file );
	  for (int i = 0; i < list.size(); ++i)
	    stream << list.at(i) << endl;
	  file.close();

	}else{
	  QTextStream stream( &file );
	  stream << path << endl;
	  for (int i = 0; i < list.size(); ++i)
	    stream << list.at(i) << endl;
	  file.close();
	}
      }

    }

    smenu->readRecents();
}

/*****************************************************************
 *
 * Get username.
 *
 ****************************************************************/
QString defaults::get_fullname()
{
    QString fullname, cline;

    QString fname(getenv("USER"));

    QFile istr("/etc/passwd");

    if(fname.isNull() || ! istr.open(QIODevice::ReadOnly)){
	if(! fname.isNull())
	    return fname;
    }else{
	while(! istr.atEnd()){
	  cline = istr.readLine();
	    
	  int indx =0;
	  indx = cline.indexOf(":", indx);
	  if(fname == cline.left(indx)){
	    for(int i=0; i < 3; i++)
	      indx = cline.indexOf(":", indx+1);
	    
	    QString tmpname = cline.mid(indx+1, 
					cline.indexOf(":", indx+1) - indx -1);
		
	    if(! tmpname.isNull())
	      fullname = tmpname;
	  }
	}

	istr.close();
    }


    return fullname;
}
