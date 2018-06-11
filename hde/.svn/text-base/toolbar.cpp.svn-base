/**********************************************************************
 **
 **				toolbar.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **  Thanks to            : alinden@gmx.de
 **
 **  Draw the toolbar and place items on it
 **
 *********************************************************************/


#include "defs.h"
#include "qapp.h"
#include "toolbar.h"

menu    *tb_mn;     // menu
pager   *tb_pg;     // pager
winlist *tb_wl;     // winlist
procbar *tb_pb;     // procbar
apbar   *tb_ap;     // apbox

/**********************************************************************
 *
 * Create the toolbar, and add startButton, pager, procbar and apbar
 * to it.
 *
 *********************************************************************/
Toolbar::Toolbar(QWidget *parent) : QFrame(parent)
{
  setFont(defaults::toolbarfont);
  paintBg();
  layout = new QHBoxLayout(0);
  layout->setSpacing(1);
  
  //  setFrameStyle(QFrame::Panel|QFrame::Raised);
  //  setLineWidth(1);
  cout << "numScreens (): " << QApplication::desktop()->numScreens() << endl;
  int toolbar_width = QApplication::desktop()->width();
  toolbar_width = QApplication::desktop()->screenGeometry(1).width();
  cout << "toolbar_width " << toolbar_width << endl;
//  if( QApplication::desktop()->numScreens() > 1)
//	  toolbar_width = QApplication::desktop()->screen(QApplication::desktop()->primaryScreen())->width();
  setGeometry(0, (defaults::toolbar_top)?(0):
	      (QApplication::desktop()->height()-defaults::tb_height),
	      toolbar_width, defaults::tb_height);
  
  //layout->addSpacing(1);
  //  layout->addSpacing(4);

  // menu
  if(defaults::show_menu)
  {
    tb_mn = new menu(this);
    layout->addWidget(tb_mn);
  }	
  else
    tb_mn = new menu(0);
  
  tb_mn->readmenu();

  layout->addSpacing(4);

  // pager
  tb_pg = new pager(this);
  layout->addWidget(tb_pg);
  layout->addSpacing(3);

  // winlist
  if(defaults::show_winlist)
  {
    tb_wl = new winlist(this);
    layout->addWidget(tb_wl);
  }
  else
    tb_wl = new winlist(0);

  if(defaults::show_menu || defaults::show_winlist)
    addsep();

  // procbar
  tb_pb = new procbar(this);
  tb_pb->setFixedHeight(defaults::tb_height);
  layout->addWidget(tb_pb);
  layout->setStretchFactor(tb_pb, 100 );

  addsep();

  tb_ap = new apbar(this);
  layout->addWidget(tb_ap);

  //  layout->addSpacing(2);
  layout->setMargin(0);
  layout->setSpacing(0);
  setLayout(layout);
  show();
}

/********************************************************************
 *
 * Add Seperator, we don't need it in hdeStyle taskbar.
 *
 *******************************************************************/
void Toolbar::addsep(void)
{
  if (defaults::taskStyle != "hde")
  {
    layout->addSpacing(2);
    QFrame *frame = new QFrame(this);
    frame->setLineWidth(1);
    frame->setMidLineWidth(0);
    //frame->setFrameStyle(QFrame::VLine|QFrame::Sunken);
    frame->setFrameStyle(QFrame::Panel|QFrame::Raised);
    frame->setFixedHeight(height()-8);
    frame->setFixedWidth(3);
    //layout->addSpacing(3);
    layout->addWidget(frame);
    layout->addSpacing(2);
  }
  paintBg();
}

void Toolbar::enterEvent( QEvent *e )
{ 
  QFrame::enterEvent( e );
  paintBg();
}

void Toolbar::leaveEvent( QEvent *e )
{
  QFrame::leaveEvent( e );
  paintBg();
}

void Toolbar::paintBg(){
  QImage *bg = new QImage(size(), QImage::Format_RGB32);

  QPainter p(bg);

  {
    xwindow *client;
    
    QRectF target0(0,0, width(), height());
    QRectF source0(geometry().x(), geometry().y(), geometry().width(), 
		   geometry().height());
    p.drawImage(target0, qapp::Desktop->desktopBG, source0);
    
    // foreach(client, clients)
    for (int i = clients.size()-1; i >=0 ; i--)
    {
      client = clients.at(i);
      
      bool curdesk;
      int dwidth = QApplication::desktop()->width();
      //int dheight = QApplication::desktop()->height();
      //    curdesk = qapp::adesk;
      curdesk = client->x() <= dwidth && client->x() >= 0;
      
      if(client->isVisible() && curdesk )
      {
      
	int cx = client->x();
	int cy = client->y();
	int cw = client->width();
	int ch = client->height();
	
	QRect s(cx, cy, cw, ch);
	QRect t(x(), y(), width(), height());
	
	if(t.intersects(s))
	{
	  QRect intrs = t & s;
	  cw = intrs.width();
	  ch = intrs.height();
	  
	  
	  if(x() >= client->x())
	  {
	    cx = 0;
	  }
	  else
	  {
	    cx = client->x() - x();
	  }
	  if(y() >= client->y())
	  {
	    cy = 0;
	  }
	  else
	  {
	    cy = client->y() - y();
	  }
	  
	  int ix = 0;
	  int iy = 0;
	  
	  if(x() > client->x())
	    ix = x() - client->x();
	  if(y() > client->y())
	    iy = y() - client->y();
	  
	  QRect irect(ix, iy, client->width()-ix, client->height()-iy);
	  //QImage img = client->screenShot->copy(irect);
	  QImage img = QImage::fromData(client->screenBytes);
	  img = img.copy(irect);
	  p.drawImage(QRect(cx,cy,irect.width(),irect.height()), img, 
		      QRect(0, 0, irect.width(), irect.height()));
	}
      }
    }
      
    //p.end();

  }

  QString tbbg = defaults::get_cfile(defaults::toolbar_bg);
  if(QFileInfo(tbbg).isFile())
  {
    QImage img(tbbg);
    if(! img.isNull())  // make scaled pixmap
    {
      //      QPainter *p = new QPainter(this);
      img = img.scaled(width(), height());
      //p.drawImage(0,0, *bg); 
      p.drawImage(0,0, img); 
      //p->end();
    }


    /*
  }else if ( defaults::taskStyle == "hde" ){
    int h = (height() - 2)/2; // (height() - 4)/2;
    //QColor firstColor(palette().color(QPalette::Active, 
    //				      QPalette::Background));
    QColor firstColor(Qt::gray);
    //    QPainter painter(this);

    //p.drawImage(0,0, *bg); 
    p.setPen(firstColor.light(100 + (h*2)));

    int i = 0;

    p.setPen(firstColor.dark(100+h*2));
    p.drawLine(0,0 , width(), 0); 
    
    p.setPen(firstColor.light(100+h*2));
    
    for ( i = 1; i < 3; ++i ) {
      p.setPen(firstColor.light(100+(h*2)-i));
      p.drawLine(0,i , width(), i); 
    }

    for ( i = 0; i < h-1; ++i ) {
      p.setPen(firstColor.dark(100 + ((h*2)-3)-(i*2)));
      p.drawLine(0,i+4 , width(), i+4); 
    }


    int j = 0;
    
    for ( i = height()-h; i < height()-1 ; ++i ) {
      j++;
      p.setPen(firstColor.light(100 +(j*2)));
      p.drawLine(0, i , width(), i); 
    }


    p.setPen(firstColor.dark(100+(h*2)));
    
    for ( i = height()-2; i < height(); ++i ) {
      p.drawLine(0,i , width(), i); 
    }
    
    
    p.setPen(firstColor.dark(130));
    p.drawLine(0,0 , 0, height()); 
    
    p.setPen(firstColor.light(130));
    p.drawLine(1,1 , 1, height()); 

    p.setPen(firstColor.light(120));
    p.drawLine(2,2 , 2, height()); 
    
    
    
    p.setPen(firstColor.dark(120));
    p.drawLine(width()-3,2 , width()-3, height()); 
    
    p.setPen(firstColor.dark(130));
    p.drawLine(width()-2,1 , width()-2, height()); 
    
    p.setPen(firstColor.dark(150).dark(120));
    p.drawLine(width()-1,0 , width()-1, height()); 
    
    
    
    if(QApplication::isRightToLeft()){
      for ( i = 0; i < h; ++i ) {
	p.setPen(firstColor.light(100 + (h*3) -(i*3)));
	p.drawLine(0 ,i , 6, i); 
      }

      j = 0;
      for ( i = height()-h-1; i < height() ; ++i ) {
	j++;
	p.setPen(firstColor.dark(100 +(j*3)));
	p.drawLine(0, i , 6, i); 
      }
	
  
     }else{
      
      for ( int i = 0; i < h; ++i ) {
	p.setPen(firstColor.light(100 + (h*3) -(i*3)));
	p.drawLine(width() - 6 ,i , width(), i); 
      }
      
      j = 0;
      for ( int i = height()-h-1; i < height() ; ++i ) {
	j++;
	p.setPen(firstColor.dark(100 +(j*3)));
	p.drawLine(width()-6, i , width(), i); 
      }
      
      

    }
    
    //p.end();
    */
  }else{

    //	QPainter paint( this );
    //p.drawImage(0,0, *bg); 
    //drawFrame( &paint );
    QColor firstColor(QColor(238,234,238));
    p.fillRect(rect(), firstColor);
    //QColor firstColor(palette().color(QPalette::Active, 
    //				      QPalette::Background));
    p.setPen(firstColor.light(130));
    p.drawLine(0 ,0 , width(), 0); 
    p.drawLine(0 ,1 , width(), 1); 
    p.drawLine(0 ,0 , 0, height()); 
    p.drawLine(1 ,0 , 1, height()); 

    //	p.end();	
  }
  p.end();	

  QPalette pal = palette();
  pal.setBrush(QPalette::Background, *bg);
  //  pal.setBrush(QPalette::Button, *bg);
  //  pal.setBrush(QPalette::Window, *bg);
  setPalette(pal);
  delete bg;
}
