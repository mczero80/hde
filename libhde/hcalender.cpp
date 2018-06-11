/****************************************************************************
**
**	hcalender.cpp
**
****************************************************************************/
#include "hcalender.h"
#include <qmessagebox.h> 
//Added by qt3to4:
#include <QHBoxLayout>
#include <QFrame>
#include <QVBoxLayout>
#include <QHeaderView>

//bool isHijri;


HCalender::HCalender( QWidget* parent,  const char* name, bool hijri )
  : QWidget( parent )
{
  // We have a fixed size
  setFixedSize( 285, 180 ); 
  showLines = true;

  isHijri = hijri;

  // Append the names of the months to the monthNames list
  if(isHijri){
    monthNames.append(Qhijri::longMonthName ( 1 ));
    for(int i = 2; i <= 12; i++)
      monthNames += Qhijri::longMonthName ( i );
  }else{
    monthNames.append(QDate::longMonthName ( 1 ));
    for(int i = 2; i <= 12; i++)
      monthNames += QDate::longMonthName ( i );
  }
   
  // Create the layouts
  cLayout = new QVBoxLayout( this ); 
  cLayout->setMargin(0);
  cLayout->setSpacing(6);
    
  dateLayout = new QHBoxLayout( 0 ); 
  dateLayout->setMargin(0);
  dateLayout->setSpacing(6);
    
  monthCombo = new QComboBox(  this );
  monthCombo->setEditable(FALSE); 
  monthCombo->insertItems( 0, monthNames );
  dateLayout->addWidget( monthCombo );
    
  yearSpin = new QSpinBox( this );
  yearSpin->setMaximum( 40000 );
  dateLayout->addWidget( yearSpin );
  cLayout->addLayout( dateLayout );
  
  Cal = new calFrame( this, "Cal",  QDate::currentDate(), isHijri);
    
  //Cal->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
  Cal->setFrameShape( QFrame::StyledPanel );
  Cal->setFrameShadow( QFrame::Sunken );
  cLayout->addWidget( Cal );
    
    
  reset();
       
  connect( monthCombo, SIGNAL( activated( int ) ), this, SLOT( changed() ) );
  connect( yearSpin, SIGNAL( valueChanged( int ) ), this, 
	   SLOT( changed() ) );
  
  connect( Cal, SIGNAL( currentCellChanged( int, int, int, int ) ), this, 
	   SLOT( calChanged( int, int, int, int ) ) );
    
}

/***********************************************************
 *
 * Reset the time and date to the current date and time.
 *
 ***********************************************************/
void HCalender::reset(void){
  dt = QDateTime::currentDateTime();
  hd = Qhijri::currentDate();
    
  if(isHijri){
    yearSpin->setValue( hd.year() );
    monthCombo->setCurrentIndex(hd.month()-1);
    
    QDate da = hd.getDate();
    Cal->setDate( da );
  }else{
    yearSpin->setValue( dt.date().year() );
    monthCombo->setCurrentIndex(dt.date().month()-1);
    Cal->setDate(dt.date());
  }
}

/***************************************************************
 *
 * Something has changed?? update our calender
 *
 ***************************************************************/
void HCalender::changed()
{
  if(isHijri)
  {
    hd.setYMD( yearSpin->value(), monthCombo->currentIndex()+1, 
	       hd.day() );
    QDate da = hd.getDate();
    dt.setDate ( da );
  }
  else
  {
    dt.setDate ( QDate(yearSpin->value(), monthCombo->currentIndex()+1, 
		     dt.date().day() ) );
  }
    Cal->setDate(dt.date());

    emit dateChanged(dt.date());
}

/**************************************************************
 *
 * Date selection has been changed
 *
 **************************************************************/
void HCalender::calChanged(int r, int c, int, int)
{
  if(isHijri){
    if(Cal->item(r, c)->text() != "")
      hd.setYMD(yearSpin->value(), monthCombo->currentIndex()+1, 
		Cal->item(r, c)->text ().toInt() );
    else
      hd.setYMD( yearSpin->value(), monthCombo->currentIndex()+1, 
		       hd.day() );

    QDate da = hd.getDate();
    dt.setDate ( da );

  }else{
    if(Cal->item(r, c)->text() != "")
      dt.setDate ( QDate(yearSpin->value(), monthCombo->currentIndex()+1, 
			 Cal->item(r, c)->text().toInt() ) );
    else
      dt.setDate ( QDate(yearSpin->value(), monthCombo->currentIndex()+1, 
			 dt.date().day() ) );
  }
    Cal->setDate(dt.date());
    
    emit dateChanged(dt.date());
}



/**************************************************************************
 * 
 *	Calender Grid
 *
 **************************************************************************/


calFrame::calFrame( QWidget* parent,  const char* name, QDate date, 
		    bool hijri )
    : QTableWidget( 6, 7, parent )
{

  isHijri = hijri;
  
    setSortingEnabled ( false );
    setShowGrid( false );
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setSelectionMode( QTableWidget::SingleSelection );
    
  
    horizontalHeader()->setResizeMode( QHeaderView::Fixed );
    horizontalHeader()->setClickable( false );

    QPalette palette;
    palette.setBrush(horizontalHeader()->backgroundRole(), QColor("darkBlue"));
    horizontalHeader()->setPalette(palette);

    palette.setColor(horizontalHeader()->foregroundRole(),  QColor("white"));
    horizontalHeader()->setPalette(palette);
    //horizontalHeader()->setBackgroundRole( QPalette::HighlightedText );
    //    horizontalHeader()->setFrameShadow( QFrame::Plain );
    //    horizontalHeader()->setFrameShape (QFrame::NoFrame );

    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    hd = Qhijri::currentDate();
    hd.setYMD( dt.year(), dt.month(), dt.day() );
 
    QStringList strl;
    
    for(int i = 1; i <= 7; ++i){
      if(isHijri){
	Qhijri hdd;
	//horizontalHeader()->setLabel( i-1, hdd.shortDayName ( i ) );
	strl << hdd.shortDayName ( i );
      }else{
	strl << QDate::shortDayName ( i );
	//	horizontalHeader()->setLabel( i-1, QDate::shortDayName ( i ) );
      }
      //      horizontalHeader()-> resizeSection( i-1, 40 );
      horizontalHeader()->resizeSection( i-1, 40  );

    }
    //setLeftMargin(1);
    setHorizontalHeaderLabels(strl);
    for(int i = 1; i <= 7; ++i){
      horizontalHeaderItem(i-1)->setBackground(QColor("darkBlue"));
      horizontalHeaderItem(i-1)->setForeground(QColor("white"));

    }
    for(int i = 1; i <= 6; ++i){
      verticalHeader()-> resizeSection( i-1, 20 );
    }
    verticalHeader()->hide() ;
    
    refresh();
}

calFrame::~calFrame()
{
    // no need to delete child widgets, Qt does it all for us
}

/*************************************************************
 *
 * Here we draw our calender.
 *
 ************************************************************/
void calFrame::refresh()
{
  
  int i = 0;
  // Reset all the items in our calender and center them.
  for(i= 0; i < rowCount(); i++ )
    for(int j= 0; j < columnCount(); j++ ){
      QTableWidgetItem *itm = new QTableWidgetItem( "" );
      itm->setTextAlignment(Qt::AlignCenter);
      setItem(i,j, itm );
    }
  
  Qhijri hd2( hd.year(), hd.month(), 1 );

  //hd.setYMD( dt.year(), dt.month(), 1 );
  
  QDate tempDate(dt.year(), dt.month(), 1  );
  int firstDay = -1;
  
  int j = 0;
  
  if( isHijri ){
    
    firstDay = hd2.dayOfWeek() -1;

    if(firstDay < 0)
      firstDay = firstDay + 7;
    
    // We have 5 Columns to set the days on the weeks.
    for(i= firstDay; i <= rowCount(); i++ ){
      item( 0, i )->setText( QString::number(++j) );
    }

    for(i = 0; i < 7; i++)
      item( 1, i )->setText( QString::number(++j) );

    for(i = 0; i < 7; i++)
      item( 2, i )-> setText ( QString::number(++j) );

    for(i = 0; i < 7; i++)
      item( 3, i )->setText (QString::number(++j) );

    for(i = 0; (i < 7) && (j < hd.daysInMonth()) ; i++)
      item( 4, i )->setText(QString::number(++j) );
     
    
    for(i = 0; (i < 7) && (j < hd.daysInMonth() ); i++)
      item( 5, i )->setText( QString::number(++j) );

      
    for(i= 0; i < rowCount(); i++ )
      for( j= 0; j < columnCount(); j++ )
	
	if(item(i, j)->text() == QString::number(hd.day()) ){
	  setCurrentCell ( i, j );
	  break;
	}
    
  }else{
    
    firstDay = tempDate.dayOfWeek() -1;
      
    for(i= firstDay; i <= rowCount(); i++ )
      item( 0, i )->setText( QString::number(++j) );
    
    for(i = 0; i < 7; i++)
      item( 1, i )->setText( QString::number(i+8-firstDay) );
      
    for(i = 0; i < 7; i++)
      item( 2, i )->setText( QString::number(i+15-firstDay) );
      
    for(i = 0; i < 7; i++)
      item( 3, i )->setText( QString::number(i+22-firstDay) );


    for(i = 0; (i < 7) && (i+29-firstDay <= tempDate.daysInMonth() ); i++)
      item( 4, i )->setText( QString::number(i+29-firstDay) );

    if(36-firstDay < tempDate.daysInMonth())
      for(i = 0; (i < 7) && (i+36-firstDay <= tempDate.daysInMonth() ); i++)
	item( 5, i )->setText( QString::number(i+36-firstDay) );
     
    
    for(i= 0; i < rowCount(); i++ )
      for( j= 0; j < columnCount(); j++ )
	  
	if(item(i, j)->text() == QString::number(dt.day()) ){
	  setCurrentCell ( i, j );
	  break;
	}
   
    }
  
}

void calFrame::paintCell( QPainter * p, int row, int col, const QRect & cr,
			     bool selected )
{
  
  p->fillRect( visualItemRect(item(row, col)),  QColor("white"));
  p->drawText ( visualItemRect(item(row, col)), 
		Qt::AlignHCenter|Qt::AlignVCenter, item(row, col)->text() );
  
  //refresh();
}

void calFrame::paintFocus ( QPainter * p, const QRect & cr )
{
  p->fillRect( visualItemRect(item(currentRow(),currentColumn() )), 
	       QColor("darkBlue"));
  p->setPen( QColor("white") ); 
  p->drawText ( visualItemRect(item(currentRow(),currentColumn() )), 
		Qt::AlignHCenter|Qt::AlignVCenter , 
		item(currentRow(), currentColumn())->text() );
} 

void calFrame::setDate(QDate date)
{
  
  dt = date; 
  hd.GregorianToHijri( dt.year(), dt.month(), dt.day());
  refresh();
  
};
