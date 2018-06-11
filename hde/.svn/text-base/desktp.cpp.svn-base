/****************************************************************************
 **
 **				desktp.cpp
 **			=========================
 **
 **  begin                : 2001 based on qlwm
 **  copyright            : (C) 2001 - 2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **  License              : GPL
 **
 **  Our Desktop Class.
 **
 ****************************************************************************/


#include <QDir>
#include "desktp.h"
#include <defaults.h>
#include <QDesktopWidget>
#include <QItemDelegate>

#include <libhde.h>

QString curItem;


class  MyDelegate : public QItemDelegate
{
 public:
  MyDelegate( QObject * parent = 0 )
  {
    setClipping(true);
  };
   ~MyDelegate(){};

   virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, 
	      const QModelIndex &index) const
   {

     painter->save();
     QColor selColor = Qt::blue;
     selColor.setAlpha(50);
     QColor whiteColor = Qt::white;
     whiteColor.setAlpha(50);

     if( option.state & QStyle::State_Selected )
     {
       QRectF r = option.rect;
       QLinearGradient linearGrad(QPointF(r.x(), r.y()), 
				  QPointF(r.x()+r.width(), r.y()+r.height()));
       linearGrad.setColorAt(0, selColor);
       linearGrad.setColorAt(0.5, whiteColor);
       linearGrad.setColorAt(1, selColor);
       painter->setBrush(linearGrad);
       painter->setPen(whiteColor);
       painter->drawRoundRect( option.rect.adjusted(0,0,-1,-1) );
     }
     
     if(( option.state & QStyle::State_MouseOver ) || 
	( option.state & QStyle::State_Off ))
       painter->fillRect( option.rect, Qt::red);
     painter->restore();
     

     QItemDelegate::paint(painter, option, index);
   };

 protected:
  virtual void drawFocus ( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect ) const
  {
    painter->save();
     QColor selColor = Qt::blue;
     selColor.setAlpha(50);
     QColor whiteColor = Qt::white;
     whiteColor.setAlpha(50);
     if( option.state & QStyle::State_HasFocus ) 
     {
       QRectF r = option.rect;
       QLinearGradient linearGrad(QPointF(r.x(), r.y()), 
				  QPointF(r.x()+r.width(), r.y()+r.height()));
       linearGrad.setColorAt(0, selColor);
       linearGrad.setColorAt(0.5, whiteColor);
       linearGrad.setColorAt(1, selColor);
       painter->setBrush(linearGrad);
       painter->setPen(whiteColor);
       painter->drawRoundRect( option.rect.adjusted(0,0,-1,-1) );
     }
    painter->restore();
     
  };

  QSize sizeHint(const QStyleOptionViewItem& option,
		 const QModelIndex& index) const
  {
    const QVariant& size = index.data(Qt::SizeHintRole);
    if (size.isValid())
      return qvariant_cast<QSize>(size);
    
    const QVariant& data = index.data();

    const QString& result =  data.toString();
    if (!result.isNull())
    {
      //const int margin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
      QSize size = option.fontMetrics.size(Qt::TextWrapAnywhere, result);
      size.rwidth() += 10;
      size.rheight() += 58;
      /*
      while(size.width() < 58)
	size.rwidth() += 10;
      */
      if(size.width() > size.height())
	size.rheight() = size.width();
      else
	size.rwidth() = size.height();

      return size;
    }

    // else flow through
    return QItemDelegate::sizeHint(option, index);
  };

  virtual void drawDisplay ( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text ) const
  {
    //    painter->save();
    QRectF r(rect.x()+1, rect.y()+1, rect.width(), rect.height());
    QRectF re(rect.x()+0.0, rect.y()+0.0, rect.width()+0.0, rect.height()+0.0);

    QTextOption textoption = QTextOption(Qt::AlignCenter);
    textoption.setWrapMode( QTextOption::WrapAnywhere );

    painter->setPen( Qt::black);
    painter->drawText(r, text, textoption);

    painter->setPen( Qt::white);
    painter->drawText(re, text, textoption);

    //    painter->restore();
  };
};
MyDelegate * idel;

desktp::desktp(QWidget *parent)
  : QListWidget(parent)

{
  setGeometry(0, 0, QApplication::desktop()->width(), 
	      QApplication::desktop()->height());
  curItem = QString();

  setWordWrap( true );
  //setUniformItemSizes ( true );

  idel = new MyDelegate;
  setItemDelegate(idel);

  init();


  connect( this, SIGNAL( itemClicked ( QListWidgetItem *) ), 
	   SLOT( iconClicked( QListWidgetItem* ) ));

  connect( this, SIGNAL( itemDoubleClicked ( QListWidgetItem *) ),
	   this, SLOT( iconDblClicked( QListWidgetItem * ) ) );

  rightmnu = new QMenu;
  rightmnu->addAction(tr("New"), this, SLOT(newItem()));
  //QMenu *ai = new QMenu;

  rightmnu->addSeparator();
  
  QMenu *ai = rightmnu->addMenu(tr("&Arrange icons"));
  rightmnu->addAction(tr("&Refresh"), this, SLOT( refreshDesktop() ) );

  rightmnu->addSeparator();

  rightmnu->addAction(tr("Properties"), this, SLOT( prop() ));




  show();
}

void desktp::init()
{
  setFrameStyle(NoFrame);
  setViewMode(QListView::IconMode);
  setFlow ( QListView::TopToBottom );
  setIconSize(QSize(48,48));	
  setGridSize ( QSize(104,104) );
  setSpacing(10);

  setBackground();

  refreshIV();
}

void desktp::setBackground(void)
{
  
  QPixmap bg = QPixmap(QApplication::desktop()->size());
  QPainter p(&bg);
  p.setBackground(defaults::root_bg);
  p.fillRect(0, 0, QApplication::desktop()->width(),
	     QApplication::desktop()->height(), defaults::root_bg);

  if(!defaults::root_pix.isNull())
  {
    if(defaults::bgDisplay == "Center"){   
      p.fillRect(0, 0, QApplication::desktop()->width(), 
		 QApplication::desktop()->height(), 
		 QBrush(defaults::root_bg));

      QPixmap tst(defaults::root_pix);
      int xi = (QApplication::desktop()->width()/2) - (tst.width()/2);
      int yi = (QApplication::desktop()->height()/2) - (tst.height()/2);
      
      p.drawPixmap( xi, yi, defaults::root_pix);
    }else if(defaults::bgDisplay == "Tile"){
      p.drawTiledPixmap( 0, 0, QApplication::desktop()->width(), 
			 QApplication::desktop()->height(), 
			 defaults::root_pix);
    }else if(defaults::bgDisplay == "Stretch"){
      /* 
      rootpix->convertFromImage(rootimg.smoothScale(QApplication::
				    desktop()->width(), 
				    QApplication::desktop()->height()));
      */
      QPixmap pix = QPixmap(defaults::root_pix
			    ).scaled(QApplication::desktop()->width(),
				     QApplication::desktop()->height());
      p.drawPixmap(0, 0, pix);

    }else{// "Tile"
      p.drawTiledPixmap( 0, 0, QApplication::desktop()->width(), 
			 QApplication::desktop()->height(), 
			 defaults::root_pix);
    }
  }

  p.end();

  QPalette br;
  br.setBrush(QPalette::Window, QBrush(bg));
  br.setBrush(QPalette::AlternateBase, QBrush(bg));
  br.setBrush(QPalette::Base, QBrush(bg));

  QApplication::desktop()->setPalette(br);
  setPalette(br);
  setAutoFillBackground(true);
  desktopBG = bg.toImage();
  rootBG = bg.toImage();
  drawBG();
  //desktopBG = QPixmap::grabWindow(winId()).toImage();
}


void desktp::refreshDesktop(void)
{
  init();
}

void desktp::createIcon(QString path, QString fname)
{
  if(!QFileInfo::QFileInfo(path + "/" + fname).exists())
    return;

  if ( (path.right(7) == "Desktop") ||( path.right(6) == "kdelnk")){
    QString svar;

    desktopItem *icn = new desktopItem( (QListWidget *) this );

    //	setFocusPolicy(QWidget::ClickFocus);
    hdeItem ditem = defaults::readItem(path + "/" + fname);

    QString iname(ditem.name);
    
    iname = iname.replace( QRegExp("%2f"), "/" );
    icn->setText(iname);

    svar = ditem.icon;
    svar = getIconFile(svar, "large");

    if (svar == "" || ! QFile( svar ).exists())
      svar = defaults::get_cfile("images/default-48.png");

    QImage pimg(svar);
    QPixmap pix;

    if(! pimg.isNull())
      pix = QPixmap::fromImage(pimg.scaled(48, 48));
    else{
      pix.load(defaults::get_cfile("images/default-48.png"));
      //      pix = pix.scaled(48, 48);
    }

    icn->setIcon(QIcon(pix));
    svar = path + "/" + fname;
    
    icn->setPath(svar);
    icn->setFilename( fname );
  }

}

void desktp::refreshIV(void)
{
  clear();

  QString dirname = defaults::get_cfile("Desktop");
  QDir d(dirname);
  d.setFilter( QDir::Files );

  const QFileInfoList list = d.entryInfoList();

  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fi = list.at(i);
    createIcon(d.path(), fi.fileName());
  }

  setAcceptDrops( TRUE );

  drawBG();
}

void desktp::drawBG()
{
  desktopBG = rootBG;
  QPainter p(&desktopBG);
  QListWidgetItem *deskitem;
  for( int i = 0; i < count(); i++)
  {
    deskitem = item( i );

    QModelIndex index = indexFromItem(deskitem);
    QStyleOptionViewItem option = viewOptions();

    QRect r = visualItemRect(deskitem);
    option.rect = QRect(0,0, r.width(), r.height());
    QSize size = r.size();//deskitem->sizeHint();
    QPixmap pix(size);
    //pix->fill(Qt::transparent);
    QPainter painter(&pix);
    painter.fillRect(0, 0, size.width(), size.height(), rootBG.copy(r));

    idel->paint(&painter, option, index);
    painter.end();

    p.drawPixmap( r , pix);



  }
  //    desktopBG = QPixmap::grabWidget(this).toImage();
  p.end();
}

void desktp::iconClicked( QListWidgetItem *item )
{
    if(!item){
      curItem = QString();
      return;
    }
    //    QString cmd(*exelist.find(item->index())); 
    desktopItem *ico = (desktopItem *)item;
    QString cmd(ico->getPath());
    //curItem = cmd;
    //    if(cmd.isNull())
    //return;


    if(cmd.isNull())
	curItem = QString();
    else
	curItem = cmd;
}

void desktp::iconDblClicked( QListWidgetItem *item )
{
  desktopItem *ico = (desktopItem *)item;
  QString cmd(ico->getPath());
  if(cmd.isNull())
    return;

  execCmd(cmd);
}

void desktp::iconReturnPressed( QListWidgetItem * )
{

}

void desktp::rightClicked( QListWidgetItem* item, const QPoint& pos )
{

  if(item){
    desktopItem *ico = (desktopItem *)item;
    QString cmd(ico->getPath());
    if(cmd.isNull())
      rightmnu->exec(pos);
    else{
      curItem = cmd;
      
      QMenu *itemMenu = new QMenu;
      itemMenu->addAction(tr("&Open"), this, SLOT( openItem() ) );
      itemMenu->addSeparator();
      itemMenu->addAction(tr("&Rename"), this, SLOT( renameItem() ) );
      itemMenu->addAction(tr("&Delete"), this, SLOT( deleteItem() ) );
      itemMenu->addSeparator();
      itemMenu->addAction(tr("&Properties"), this, SLOT( itemProp() ) );
      
      
      itemMenu->exec(pos);
    }
  }else
     rightmnu->exec(pos);
  

}

void desktp::openItem()
{
  QListWidgetItem *item = currentItem();
  if(item != NULL)
    iconDblClicked(item);
}


void desktp::prop( void )
{
  execCmd( "hDisplay2" );
}

void desktp::newItem( void )
{
  execCmd( "hadditem" );
}

void desktp::deleteItem()
{

}

void desktp::renameItem()
{

}

void desktp::itemProp( void )
{
  QString cmd = "deskitem \"" + QFile::encodeName( curItem )+ "\"";
  execCmd( cmd );
}

void desktp::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::RightButton)
  {
    const QPoint& pos = event->pos();
    QListWidgetItem* item =  itemAt(pos);
    
    rightClicked( item, pos );
  }

  QListWidget::mouseReleaseEvent(event);
}

void desktp::keyPressEvent( QKeyEvent * event )
{
  if(event->key() == Qt::Key_Return)
  {
    QListWidgetItem *item = currentItem();
    if(item != NULL)
      iconDblClicked(item);

  }
  QListWidget::keyPressEvent( event );
}
