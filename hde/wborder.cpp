/****************************************************************************
 **
 **				wborder.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Creates the window borders
 **
 **  Special Thanks to Alexander Linden <alinden@gmx.de>
 **
 ****************************************************************************/


#include "defs.h"
#include "defaults.h"
#include "libhde.h"
#include "qapp.h"

#include <QStyle>

wframe::wframe(QWidget *parent, QString name)
  : QLabel(parent), frameName(name)
{
  //  setFrameStyle(QFrame::Panel|QFrame::Raised);
  //  setLineWidth(1);
  mousedown = false;
  mouseover = false;
  maxed = false;
  activepal = false;
  setMinimumWidth(1);
  setWordWrap(FALSE);
  //setMouseTracking( true );
}

void wframe::set_text(QString btxt, bool center)
{
  setAlignment(center?Qt::AlignCenter:Qt::AlignLeft|Qt::AlignVCenter);
  setText(btxt);
}


static void draw_gradient(QPainter *painter, const QRect &rect, 
				   const QColor &gradientStart,
				   const QColor &gradientStop)
{
  int x = rect.center().x();
  //  int y = rect.center().y();
  QLinearGradient *gradient;
  gradient = new QLinearGradient(x, rect.top(), x, rect.bottom());

    gradient->setColorAt(0, gradientStart);
    gradient->setColorAt(1, gradientStop);
  painter->fillRect(rect, *gradient);
  delete gradient;
}

static void draw_button(QPainter *p, const QRect &r, bool sunken = false,
			bool hover = false)
{

  QColor light = Qt::lightGray;
  QColor buttonColor = Qt::gray;
  buttonColor.setAlpha(150);

  QColor highlightedGradientStartColor = light.light(107);
  QColor highlightedGradientStopColor = buttonColor.dark(110).light(107);
  QColor gradientStartColor = buttonColor.light(108);
  
  QColor gradientStopColor;
  
  QPalette palette(buttonColor);
  
  
  gradientStopColor.setHsv(buttonColor.hue(),
			   qMin(255, (int)(buttonColor.saturation()*1.9)),
			   qMin(255, (int)(buttonColor.value()*0.94)));
    
  int x2 = r.x()+r.width()-1;
  int y2 = r.y()+r.height()-1;
	       
  if(sunken)
    draw_gradient(p, r.adjusted(1, 1, -1, -1),
		  highlightedGradientStartColor.dark(115),
		  highlightedGradientStopColor.dark(115));
  else if(hover)
    draw_gradient(p, r.adjusted(1, 1, -1, -1),
		  highlightedGradientStartColor.light(105),
		  highlightedGradientStopColor.light(105));
  else
    draw_gradient(p, r.adjusted(1, 1, -1, -1),
		  highlightedGradientStartColor,
		  highlightedGradientStopColor);
  
  if(sunken){
    p->setPen(palette.dark().color());
    p->drawLine(r.x()+1, r.y(), x2-2,  r.y());
    p->drawLine(r.x(), r.y()+1, r.x(), y2-2);
    p->setPen(palette.light().color());
    p->drawLine(r.x()+1, y2, x2-1, y2);
    p->drawLine(x2, r.y()+1, x2, y2-1);
  }else{
    p->setPen(palette.light().color());
    p->drawLine(r.x()+1, r.y(), x2-2,  r.y());
    p->drawLine(r.x(), r.y()+1, r.x(), y2-2);
    p->setPen(palette.dark().color());
    p->drawLine(r.x()+1, y2, x2-1, y2);
    p->drawLine(x2, r.y()+1, x2, y2-1);
  }
} 
static QPixmap mirror(const QPixmap &pix, bool hor)
{
  QPixmap mpix;// = pix;
  QImage img = pix.toImage();
  mpix = QPixmap::fromImage(img.mirrored(hor, !hor));
  return mpix;
}

void wframe::paintEvent( QPaintEvent *e )
{
  QPainter p(this);
  
  QRect r = e->rect();
  p.setClipRect(r);

  if(frameName == "Title")
  {
    QColor textColor = palette().color(QPalette::Normal, 
				       QPalette::WindowText);
    QRect cr(5, 0, width()-10, height());
    QRect cr0(6, 1, width()-10, height());

    if(defaults::titlebarShadow)
    {
      QColor shadowColor = getOppositeColor(textColor);
      p.setPen(shadowColor);
      p.setBrush(shadowColor);
      p.drawText( cr0, Qt::AlignLeft|Qt::AlignVCenter, text().simplified());
    }
    p.setPen(textColor);
    p.setBrush(defaults::tbButton_fg);
    p.drawText( cr, Qt::AlignLeft|Qt::AlignVCenter, text().simplified());
    
    //QLabel::paintEvent(e);
  }else if(frameName == "upperFrame")
  {
    uborder *uper = (uborder *)this;
    if(!defaults::closeglow_icon.isEmpty())
    {
      if(uper->closeframe->mouseover)
      {
	QWidget *close = uper->closeframe;
	int gw = close->x() - defaults::glowThickness;
	int gh = close->y() - defaults::glowThickness;
	p.drawImage(gw, gh, 
		    QImage(defaults::get_cfile(defaults::closeglow_icon)));

      }
    }
    /*
    QString glowBtn = ((uborder *)this)->glowBtn;
    if(glowBtn == "")
    {
      //logmsg << glowBtn << endl;
	//QLabel::paintEvent(e);
    }else{
      if(glowBtn == "Close")
      {
	if(!defaults::closeglow_icon.isEmpty())
	{
	  QWidget *close = ((uborder *)this)->closeframe;
	  int gw = close->x() -
	    defaults::glowThickness;
	  int gh = close->y() - 
	    defaults::glowThickness;
	  p.drawImage(gw, gh,
		     QImage(defaults::get_cfile(defaults::closeglow_icon)));
	}
      }else
	logmsg << glowBtn << endl;
    
    }
    */
  }else if(frameName == "MinMax")
  {
    if(!defaults::flaticons)
      draw_button(&p, r, mousedown, mouseover);
    else
    {
      //if(defaults::windowButtonPos == "Top")
      {
	QPixmap pix;
	if(activepal)
	{
	  pix = *qapp::minmaxpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::leftdown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::leftmo_icon));

	}else{
	  pix = *qapp::uminmaxpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::uleftdown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::uleftmo_icon));

	}
	if(pix.isNull())
	  QLabel::paintEvent(e);
	else
	{
	  if(QApplication::isRightToLeft())
	    pix =  mirror(pix, true);
	  p.drawPixmap(0,0, pix);
	  if(mouseover)
	    ((uborder *)parent())->update();
	}
      }/*else{
	QLabel::paintEvent(e);
	}*/
    }
    //    QLabel::paintEvent(e);
  }else if(frameName == "Minimize")
  {
    if(!defaults::flaticons)
      draw_button(&p, r, mousedown, mouseover);
    else
    {
      //if(defaults::windowButtonPos == "Top")
      {
	QPixmap pix;
	if(activepal)
	{
	  pix = *qapp::minbtnpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::mindown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::minmo_icon));

	}else{
	  pix = *qapp::uminbtnpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::umindown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::uminmo_icon));

	}
	if(pix.isNull())
	  QLabel::paintEvent(e);
	else
	{
	  if(QApplication::isRightToLeft())
	    pix =  mirror(pix, true);
	  p.drawPixmap(0,0, pix);
	  if(mouseover)
	    ((uborder *)parent())->update();
	}
      }/*else{
	QLabel::paintEvent(e);
	}*/
    }
    // QLabel::paintEvent(e);
  }else if(frameName == "Maximize")
  {
    if(!defaults::flaticons)
      draw_button(&p, r, mousedown, mouseover);
    else
    {
      //if(defaults::windowButtonPos == "Top")
      {
	QPixmap pix;
	if(activepal)
	{
	  if(maxed)
	  {
	    pix = *qapp::restorebtnpix;
	  
	    if(mousedown)
	      pix = QPixmap(defaults::get_cfile(defaults::restdown_icon));
	    else if(mouseover)
	      pix =  QPixmap(defaults::get_cfile(defaults::restmo_icon));
	  }else{
	    pix = *qapp::maxbtnpix;
	  
	    if(mousedown)
	      pix = QPixmap(defaults::get_cfile(defaults::maxdown_icon));
	    else if(mouseover)
	      pix =  QPixmap(defaults::get_cfile(defaults::maxmo_icon));
	  }
	}else{
	  if(maxed)
	  {
	    pix = *qapp::urestorebtnpix;
	    
	    if(mousedown)
	      pix = QPixmap(defaults::get_cfile(defaults::urestdown_icon));
	    else if(mouseover)
	      pix =  QPixmap(defaults::get_cfile(defaults::urestmo_icon));
	  }else{
	    pix = *qapp::umaxbtnpix;
	    
	    if(mousedown)
	      pix = QPixmap(defaults::get_cfile(defaults::umaxdown_icon));
	    else if(mouseover)
	      pix =  QPixmap(defaults::get_cfile(defaults::umaxmo_icon));
	  }
	}
	if(pix.isNull())
	  QLabel::paintEvent(e);
	else
	{
	  if(QApplication::isRightToLeft())
	    pix =  mirror(pix, true);
	  p.drawPixmap(0,0, pix);
	  if(mouseover)
	    ((uborder *)parent())->update();
	}
      }/*else{
	QLabel::paintEvent(e);
	}*/
    }
    // QLabel::paintEvent(e);
  }else if(frameName == "Close")
  {
    if(!defaults::flaticons)
      draw_button(&p, r, mousedown, mouseover);
    else
    {
      //      if(defaults::windowButtonPos == "Top")
      {
	QPixmap pix;
	if(activepal)
	{
	  pix = *qapp::closepix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::closedown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::closemo_icon));

	}else{
	  pix = *qapp::uclosepix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::uclosedown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::uclosemo_icon));

	}
	if(pix.isNull())
	  QLabel::paintEvent(e);
	else
	{
	  if(QApplication::isRightToLeft())
	    pix =  mirror(pix, true);
	  p.drawPixmap(0,0, pix);
	  if(mouseover)
	    ((uborder *)parent())->update();
	}
      }//else{
      //	QLabel::paintEvent(e);
      //}
    }
  }else if(frameName == "Help")
  {
    if(!defaults::flaticons)
      draw_button(&p, r, mousedown, mouseover);
    else
    {
      //if(defaults::windowButtonPos == "Top")
      {
	QPixmap pix;
	if(activepal)
	{
	  pix = *qapp::helpbtnpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::helpdown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::helpmo_icon));

	}else{
	  pix = *qapp::uhelpbtnpix;
	  
	  if(mousedown)
	    pix = QPixmap(defaults::get_cfile(defaults::uhelpdown_icon));
	  else if(mouseover)
	    pix =  QPixmap(defaults::get_cfile(defaults::uhelpmo_icon));

	}
	if(pix.isNull())
	  QLabel::paintEvent(e);
	else
	{
	  if(QApplication::isRightToLeft())
	    pix =  mirror(pix, true);
	  p.drawPixmap(0,0, pix);
	  if(mouseover)
	    ((uborder *)parent())->update();
	}
      }/*else{
	QLabel::paintEvent(e);
	}*/
    }
    // QLabel::paintEvent(e);
  }else if(frameName == "Menu")
  {
    QLabel::paintEvent(e);
  }
  /*******************************
   * Upper Border
   ******************************/
  else if(frameName == "topLeft")
  {
    if(defaults::border_tlimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0,0 , width(), 0); 
      p.drawLine(0, 0, 0, height()); 
    }
    /*
    p.setPen(Qt::darkGray);
    p.drawLine( 0, height()-1 , width(), height()-1); 
    p.drawLine(width()-1, 0, width()-1, height()-1);
    */
  }else if(frameName == "top")
  {
    if(defaults::topborderimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0,0 , width(), 0);
    }
  }else if(frameName == "topRight")
  {
    if(defaults::border_trimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0,0 , width(), 0); 
      //p.drawLine(0, 0, 0, height()); 
    
    
      p.setPen(Qt::darkGray);
      //    p.drawLine( 0, height()-1 , width(), height()-1); 
      p.drawLine(width()-1, 0, width()-1, height()-1);
    }
  }else if(frameName == "upperLeft")
  {
    if(defaults::border_tlimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0, 0, 0, height());
    } 
  }else if(frameName == "upperRight")
  {
    if(defaults::border_trimage.isEmpty())
    {
      p.setPen(Qt::darkGray);
      p.drawLine(width()-1, 0, width()-1, height());
    }
  }
  /*******************************
   * Left Border
   ******************************/
  else if(frameName == "left")
  {
    if(defaults::border_leftimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0, 0, 0, height());
    } 
  }else if(frameName == "leftLower")
  {
    if(defaults::border_blimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0, 0, 0, height());
    }
  }
  /*******************************
   * Right Border
   ******************************/
  else if(frameName == "right")
  {
    if(defaults::border_leftimage.isEmpty())
    {
      p.setPen(Qt::darkGray);
      p.drawLine(width()-1, 0, width()-1, height()-1);
    }
  }else if(frameName == "rightLower")
  {
    if(defaults::border_brimage.isEmpty())
    {
      p.setPen(Qt::darkGray);
      p.drawLine(width()-1, 0, width()-1, height()-1);
    }
  }
  /*******************************
   * Lower Border
   ******************************/
  else if(frameName == "lowerLeft")
  {
    if(defaults::border_blimage.isEmpty())
    {
      p.setPen(Qt::white);
      p.drawLine(0, 0, 0, height()); 
      p.setPen(Qt::darkGray);
      p.drawLine( 0, height()-1 , width(), height()-1);
    }
  }else if(frameName == "lower")
  {
    if(defaults::bottomborderimage.isEmpty())
    {
      p.setPen(Qt::darkGray);
      p.drawLine( 0, height()-1 , width(), height()-1);
    } 
  }else if(frameName == "lowerRight")
  {
    if(defaults::border_brimage.isEmpty())
    {
      p.setPen(Qt::darkGray);
      p.drawLine( 0, height()-1 , width(), height()-1); 
      p.drawLine(width()-1, 0, width()-1, height()-1);
    }
  }else
    QLabel::paintEvent(e);

  p.end();
}

void wframe::resizeEvent(QResizeEvent *)
{
  repaint();
}

void wframe::mousePressEvent(QMouseEvent *event)
{
  QFrame::mousePressEvent(event);
  mousedown = true;
  emit press(event);
  emit press();

  if(event->button() == Qt::RightButton)
  {
    emit right_press();
  }	
  else if(event->button() == Qt::LeftButton)
  {
    emit left_press(event);
    emit left_press();
  }
  else if(event->button() == Qt::MidButton)
  {
    emit mid_press();
  }
  repaint();
}

void wframe::mouseReleaseEvent(QMouseEvent *event)
{
  QFrame::mouseReleaseEvent(event);

  mousedown = false;
  emit release(event);
  
  if(event->button() == Qt::RightButton)
  {
    emit right_release();
    if(underMouse())
      emit right_clicked();
  }
  else if(event->button() == Qt::LeftButton)
  {
    emit left_release(event);
    emit left_release();
    if(underMouse())
      emit left_clicked();
  }
  else if(event->button() == Qt::MidButton)
  {
    emit mid_release();
    if(underMouse())
      emit mid_clicked();
  }
  repaint();
}

void wframe::mouseMoveEvent(QMouseEvent *event)
{
  QFrame::mouseMoveEvent(event);
  emit mouse_move(event);
  //  repaint();
}

void wframe::enterEvent ( QEvent *event )
{
  QFrame::enterEvent(event);
  mouseover = true;
  repaint();
}
void wframe::leaveEvent ( QEvent *event )
{
  QFrame::leaveEvent(event);
  mouseover = false;
  repaint();
}

lborder::lborder(QWidget *parent) : QWidget(parent)
{
  layout = new QHBoxLayout(this);
  Q_CHECK_PTR(layout);
  leftframe = new wframe(this, "lowerLeft");
  Q_CHECK_PTR(leftframe);
  midframe = new wframe(this, "lower");
  Q_CHECK_PTR(midframe);
  rightframe = new wframe(this, "lowerRight");
  Q_CHECK_PTR(rightframe);
	
  leftframe->setMaximumWidth(defaults::lowerborderwidth);
  rightframe->setMaximumWidth(defaults::lowerborderwidth);
  setFixedHeight(defaults::lowerborderheight);
  
  leftframe->setCursor(QCursor(Qt::SizeBDiagCursor));
  midframe->setCursor(QCursor(Qt::SizeVerCursor));
  rightframe->setCursor(QCursor(Qt::SizeFDiagCursor));
  
  if(QApplication::isRightToLeft())
    layout->addWidget(rightframe);
  else
    layout->addWidget(leftframe);
  layout->addWidget(midframe);

  if(QApplication::isRightToLeft())
    layout->addWidget(leftframe);
  else
    layout->addWidget(rightframe);
  layout->setMargin(0);
  layout->setSpacing(0);
  setLayout(layout);
}

void uborder::setActivePal(bool act)
{
  foreach (QString str, titleOrder) {
    if (str == "MinMax")
    {
      minmaxframe->setActivePal(act);
    }else if (str == "Menu")
    {
    }else if (str == "Minimize")
    {
      minframe->setActivePal(act);
    }else if (str == "Maximize")
    {
      maxframe->setActivePal(act);
    }else if(str == "Close")
    {
      closeframe->setActivePal(act);
    }else if(str == "Help")
    {
      helpframe->setActivePal(act);
    }
  }
}

void uborder::set_small(void)
{
  setFixedHeight(defaults::lowerborderheight);
  foreach (QString str, titleOrder) {
    if (str == "MinMax")
    {
      minmaxframe->setMaximumWidth(defaults::lowerborderwidth);
      minmaxframe->setPixmap(QPixmap());
    }else if (str == "Menu")
    {
    }else if (str == "Minimize")
    {
    }else if (str == "Maximize")
    {
    }else if(str == "Close")
    {
      closeframe->setMaximumWidth(defaults::lowerborderwidth);
      closeframe->setPixmap(QPixmap());
    }else if(str == "Help")
    {
    }
  }
  midframe->setText("");
}

void uborder::set_normal(void)
{
  setFixedHeight(defaults::titlebarHeight+defaults::lowerborderwidth);
  foreach (QString str, titleOrder) {
    if (str == "MinMax")
    {
      minmaxframe->setPixmap(*qapp::minmaxpix);
      minmaxframe->setMaximumWidth(defaults::windowButtonSize);
    }else if (str == "Menu")
    {
    }else if (str == "Minimize")
    {
    }else if (str == "Maximize")
    {
    }else if(str == "Close")
    {
      if(defaults::closeButtonWidth > 0)
	closeframe->setMaximumWidth(defaults::closeButtonWidth);
      else
	closeframe->setMaximumWidth(defaults::windowButtonSize);
      closeframe->setPixmap(*qapp::closepix);
    }else if(str == "Help")
    {
    }
  }
}

void uborder::set_max(bool max)
{
  maxed = max;
  if(maxframe != NULL)
    maxframe->set_max( maxed );
 
  /*
   * set top borders width to 0, shrink height
   * redraw without top border, top left or topright.
   */
  if(maxed)
  {
    if(defaults::topBorder)
    {
      topleftframe->setFixedHeight(0);   
      topframe->setFixedHeight(0);
      toprightframe->setFixedHeight(0);
      upperleftframe->setFixedWidth(0);

      setFixedHeight(defaults::titlebarHeight);

      upperrightframe->setFixedWidth(0);
    }
  }else{
    if(defaults::topBorder)
    {
      topleftframe->setFixedHeight(defaults::lowerborderheight);
      topframe->setFixedHeight(defaults::lowerborderheight);
      toprightframe->setFixedHeight(defaults::lowerborderheight);
      upperleftframe->setFixedWidth(defaults::lowerborderheight);
 
      setFixedHeight(defaults::titlebarHeight+defaults::lowerborderheight);
   
      upperrightframe->setFixedWidth(defaults::lowerborderheight);
    }
  }
}


//uborder::uborder(bool showleft, QWidget *parent) : QWidget(parent)
uborder::uborder(QWidget *parent, QStringList to) 
  : wframe(parent, "upperFrame")
{
  titleOrder = to;
  if(titleOrder.empty())
    titleOrder << "MinMax" << "Title" << "Close";

  maxframe = NULL;
  setFont(defaults::borderfont);

  if(defaults::topBorder)
  {
    layout = new QHBoxLayout;
    Q_CHECK_PTR(layout);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout0 = new QVBoxLayout(this);
    Q_CHECK_PTR(layout0);
    layout0->setMargin(0);
    layout0->setSpacing(0);

    QHBoxLayout *layout1 = new QHBoxLayout;
    Q_CHECK_PTR(layout1);
    layout1->setMargin(0);
    layout1->setSpacing(0);

    /*********************************************************
     *
     * Adding the very top borders.
     *
     ********************************************************/
    topleftframe = new wframe(this, "topLeft");
    Q_CHECK_PTR(topleftframe);
    topleftframe->setMaximumWidth(defaults::lowerborderwidth);
    topleftframe->setFixedHeight(defaults::lowerborderheight);   


    topframe = new wframe(this, "top");
    Q_CHECK_PTR(topframe);
    topframe->setFixedHeight(defaults::lowerborderheight);

    toprightframe = new wframe(this, "topRight");
    Q_CHECK_PTR(toprightframe);
    toprightframe->setMaximumWidth(defaults::lowerborderwidth);
    toprightframe->setFixedHeight(defaults::lowerborderheight);

    topleftframe->setCursor(QCursor(Qt::SizeFDiagCursor));
    topframe->setCursor(QCursor(Qt::SizeVerCursor));
    toprightframe->setCursor(QCursor(Qt::SizeBDiagCursor));

    if(QApplication::isRightToLeft())
    {
      layout1->addWidget(toprightframe);
      layout1->addWidget(topframe);
      layout1->addWidget(topleftframe);
    }else{
      layout1->addWidget(topleftframe);
      layout1->addWidget(topframe);
      layout1->addWidget(toprightframe);
    }


    layout0->addLayout(layout1);

    /*********************************************************
     *
     * Adding the top left border.
     *
     ********************************************************/
    if(QApplication::isRightToLeft())
    {
      upperrightframe = new wframe(this, "upperRight");
      Q_CHECK_PTR(upperrightframe);
      upperrightframe->setMaximumHeight(defaults::lowerborderwidth);
      upperrightframe->setFixedWidth(defaults::lowerborderheight);
      upperrightframe->setFixedHeight(defaults::titlebarHeight);
      layout->addWidget(upperrightframe);

    }else{
      upperleftframe = new wframe(this, "upperLeft");
      Q_CHECK_PTR(upperleftframe);
      upperleftframe->setMaximumHeight(defaults::lowerborderwidth);
      upperleftframe->setFixedWidth(defaults::lowerborderheight);
      upperleftframe->setFixedHeight(defaults::titlebarHeight);
      layout->addWidget(upperleftframe);
    }
    setFixedHeight(defaults::titlebarHeight+defaults::lowerborderheight);

  }else{
    layout = new QHBoxLayout(this);
    Q_CHECK_PTR(layout);
    setFixedHeight(defaults::titlebarHeight);
    layout->setMargin(0);
    layout->setSpacing(0);
  }


  foreach (QString str, titleOrder) {
    if (str == "MinMax")
    {

      minmaxframe = new wframe(this, "MinMax");
      Q_CHECK_PTR(minmaxframe);
      minmaxframe->setMaximumWidth(defaults::windowButtonSize);
      minmaxframe->setMaximumHeight(defaults::windowButtonSize);
      minmaxframe->setAlignment(Qt::AlignCenter);
      minmaxframe->setPixmap(*qapp::minmaxpix);
      layout->addWidget(minmaxframe);

    }else if (str == "Menu")
    {

      menuframe = new wframe(this, "Menu");
      Q_CHECK_PTR(menuframe);
      menuframe->setMaximumWidth(defaults::windowButtonSize);
      menuframe->setMaximumHeight(defaults::windowButtonSize);
      menuframe->setAlignment(Qt::AlignCenter);
      menuframe->setPixmap(*qapp::defaultpix);
      layout->addWidget(menuframe);

    }else if (str == "Minimize")
    {

      minframe = new wframe(this, "Minimize");
      Q_CHECK_PTR(minframe);
      minframe->setMaximumWidth(defaults::windowButtonSize);
      minframe->setMaximumHeight(defaults::windowButtonSize);
      minframe->setAlignment(Qt::AlignCenter);
      minframe->setPixmap(*qapp::minbtnpix);
      layout->addWidget(minframe);

    }else if (str == "Maximize")
    {

      maxframe = new wframe(this, "Maximize");
      Q_CHECK_PTR(maxframe);
      maxframe->setMaximumWidth(defaults::windowButtonSize);
      maxframe->setMaximumHeight(defaults::windowButtonSize);
      maxframe->setAlignment(Qt::AlignCenter);
      maxframe->setPixmap(*qapp::maxbtnpix);
      layout->addWidget(maxframe);

    }else if (str == "Help")
    {

      helpframe = new wframe(this, "Help");
      Q_CHECK_PTR(helpframe);
      helpframe->setMaximumWidth(defaults::windowButtonSize);
      helpframe->setMaximumHeight(defaults::windowButtonSize);
      helpframe->setAlignment(Qt::AlignCenter);
      helpframe->setPixmap(*qapp::helpbtnpix); 
      layout->addWidget(helpframe);

    }else if(str == "Title")
    {
      midframe = new wframe(this, "Title");
      Q_CHECK_PTR(midframe);
      layout->addWidget(midframe);
      midframe->setFixedHeight(defaults::titlebarHeight);
      midframe->setFont(defaults::borderfont);

    }else if(str == "Close")
    {

      closeframe = new wframe(this, "Close");
      Q_CHECK_PTR(closeframe);
      if(defaults::closeButtonWidth > 0)
	closeframe->setMaximumWidth(defaults::closeButtonWidth);
      else
	closeframe->setMaximumWidth(defaults::windowButtonSize);
      closeframe->setMaximumHeight(defaults::windowButtonSize);
      closeframe->setAlignment(Qt::AlignCenter);
      closeframe->setPixmap(*qapp::closepix);
      layout->addWidget(closeframe);

    }
  }

  if(defaults::topBorder)
  {
    /*********************************************************
     *
     * Adding the top left border.
     *
     ********************************************************/
    if(QApplication::isRightToLeft())
    {
      upperleftframe = new wframe(this, "upperLeft");
      Q_CHECK_PTR(upperleftframe);
      upperleftframe->setMaximumHeight(defaults::lowerborderwidth);
      upperleftframe->setFixedWidth(defaults::lowerborderheight);
      upperleftframe->setFixedHeight(defaults::titlebarHeight);
      layout->addWidget(upperleftframe);
    }else{
      upperrightframe = new wframe(this, "upperRight");
      Q_CHECK_PTR(upperrightframe);
      upperrightframe->setMaximumHeight(defaults::lowerborderwidth);
      upperrightframe->setFixedWidth(defaults::lowerborderheight);
      upperrightframe->setFixedHeight(defaults::titlebarHeight);
      layout->addWidget(upperrightframe);
    }
    layout0->addLayout(layout);
    upperleftframe->setCursor(QCursor(Qt::SizeFDiagCursor));
    upperrightframe->setCursor(QCursor(Qt::SizeBDiagCursor));

    setLayout(layout0);
  }else{
    setLayout(layout);
  }
  /*

  bool showleft = titleOrder.contains("MinMax");

  layout = new QHBoxLayout(this);
  Q_CHECK_PTR(layout);
  setFixedHeight(defaults::windowbuttonsize);
  
  if(showleft)
  {
    minmaxframe = new wframe(this);
    Q_CHECK_PTR(leftframe);
    minmaxframe->setMaximumWidth(defaults::windowbuttonsize);
    minmaxframe->setAlignment(Qt::AlignCenter);
    minmaxframe->setPixmap(*qapp::leftwinpix);
    
    layout->addWidget(minmaxframe);
  }
	
  midframe = new wframe(this);
  Q_CHECK_PTR(midframe);
  closeframe = new wframe(this);
  Q_CHECK_PTR(rightframe);
  closeframe->setMaximumWidth(defaults::windowbuttonsize);
  closeframe->setAlignment(Qt::AlignCenter);
  closeframe->setPixmap(*qapp::rightwinpix);
  
  layout->addWidget(midframe);
  layout->addWidget(closeframe);
  layout->setMargin(0);
  layout->setSpacing(0);
  setLayout(layout);
  */
}

slborder::slborder( QWidget *parent): QWidget(parent)
{
  layout = new QVBoxLayout(this);
  Q_CHECK_PTR(layout);
  layout->setMargin(0);

  midframe = new wframe(this, "left");
  Q_CHECK_PTR(midframe);
  midframe->setMinimumHeight(2);

  lowerframe = new wframe(this, "leftLower");
  Q_CHECK_PTR(lowerframe);
	
  lowerframe->setMaximumHeight(defaults::lowerborderwidth);
  lowerframe->setMinimumHeight(2);
  setFixedWidth(defaults::lowerborderheight);
  
  midframe->setCursor(QCursor(Qt::SizeHorCursor));
  lowerframe->setCursor(QCursor(Qt::SizeBDiagCursor));
  
  layout->addWidget(midframe);
  layout->addWidget(lowerframe);
  layout->setMargin(0);
  layout->setSpacing(0);
  setLayout(layout);
}

slborder::~slborder(void)
{
  delete midframe;
  delete lowerframe;
}


srborder::srborder( QWidget *parent): QWidget(parent)
{
  layout = new QVBoxLayout(this);
  Q_CHECK_PTR(layout);
  layout->setMargin(0);

  midframe = new wframe(this, "right");
  Q_CHECK_PTR(midframe);
  midframe->setMinimumHeight(2);

  lowerframe = new wframe(this, "rightLower");
  Q_CHECK_PTR(lowerframe);
	
  lowerframe->setMaximumHeight(defaults::lowerborderwidth);
  lowerframe->setMinimumHeight(2);
  setFixedWidth(defaults::lowerborderheight);
  
  midframe->setCursor(QCursor(Qt::SizeHorCursor));
  lowerframe->setCursor(QCursor(Qt::SizeFDiagCursor));
  
  layout->addWidget(midframe);
  layout->addWidget(lowerframe);
  layout->setMargin(0);
  layout->setSpacing(0);
  setLayout(layout);

}

srborder::~srborder(void)
{
  delete midframe;
  delete lowerframe;
}

