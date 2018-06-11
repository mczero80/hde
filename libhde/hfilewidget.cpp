/****************************************************************************
 **
 **					hfilewidget.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/

#include <QLabel>
#include <QComboBox>

#include "hfilewidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QDateTime>

static QIcon load_icon( const QString &name )
{
  //  QString nam = ":/images/" + name;
  QIcon icn;
  icn.addFile(":/images/" + name + ".png", QSize(48,48));
  icn.addFile(":/images/" + name + "32.png", QSize(32,32));
  icn.addFile(":/images/" + name + "16.png", QSize(16,16));
  return icn;
}


/*****************************************************************************
 *
 * Class HFileWidget
 *
 *****************************************************************************/
HFileWidget::HFileWidget( QWidget* parent)
  : QWidget(parent)
{

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSpacing ( 0 );
  layout->setContentsMargins(0,0,0,0);


  QHBoxLayout *drivelayout = new QHBoxLayout;
  drivelayout->setSpacing( 0 );
  drivelayout->setContentsMargins(0,0,0,0);
  
  driveCombo = new HDrivesCombo(this);
  drivelayout->addWidget(driveCombo);
  driveCombo->setFocusPolicy(Qt::NoFocus);
  drivelayout->addStretch();

  layout->addLayout(drivelayout);


  
  dirLabel = new QLabel(this);
  dirLabel->setFixedHeight(20);

  layout->addWidget(dirLabel);
  dirLabel->setText(trUtf8( "My Computer" ));
  listDirectoryChanged(trUtf8( "My Computer" ));
  setDirLabelBackground( false );

  hflist = new HFileList("", this);
  infoLabel = new HInfoLabel(this);

  layout->addWidget(hflist);



  infoLabel->setFixedHeight(20);
//  infoLabel->setFrameStyle(QFrame::Panel|QFrame::Raised);

  layout->addWidget(infoLabel);


  setLayout(layout);

  //hflist->setFocus( Qt::OtherFocusReason );

  connect(hflist, SIGNAL(directoryChanged( const QString & )), this,
                  SLOT(listDirectoryChanged( const QString &)));

  connect(hflist, SIGNAL(fileExecuted( const QString & )), this, 
                  SLOT(listFileExecuted( const QString & )));

  connect(hflist, SIGNAL(fileHighlighted( const QString & )), this, 
                  SLOT(listFileHighlighted( const QString & )));

  connect(hflist, SIGNAL(focusChanged( bool )), this, 
                  SLOT(listFocusChanged( bool )));

  connect( driveCombo, SIGNAL( activated( const QString &) ), this,
           SLOT( driveActivated( const QString& )) );
}

HFileWidget::~HFileWidget()
{                        
}

void HFileWidget::setViewMode( HFileList::ViewMode mode  )
{
  hflist->setViewMode(mode);
}

void HFileWidget::listDirectoryChanged( const QString &dir )
{
  emit directoryChanged( dir );
  dirLabel->setText(dir);
  curDir = dir;
  
  disconnect( driveCombo, SIGNAL( activated( const QString &) ), this,
           SLOT( driveActivated( const QString& )) );
  driveCombo->checkDrive( dir );
  connect( driveCombo, SIGNAL( activated( const QString &) ), this,
           SLOT( driveActivated( const QString& )) );

}

void HFileWidget::listFileExecuted( const QString &file )
{
  emit fileExecuted(file );
}

void HFileWidget::listFileHighlighted( const QString &file )
{
  emit fileHighlighted(file );     
  curFile = file;
//  updateinfoLabel();
  infoLabel->setFilename(file);
}


void HFileWidget::listFocusChanged( bool focus )
{
  if(focus)
    emit hasFocus( this );
  setDirLabelBackground( focus );
}

void HFileWidget::setDirLabelBackground( bool focus )
{
  QPalette palette;
  if(focus)
  {
    palette.setColor(dirLabel->backgroundRole(), Qt::darkGray);
    palette.setColor(dirLabel->foregroundRole(), Qt::white);
  }
  else
  {
    palette.setColor(dirLabel->backgroundRole(), Qt::lightGray);
    palette.setColor(dirLabel->foregroundRole(), Qt::black);
  }
  dirLabel->setPalette(palette);


  dirLabel->setAutoFillBackground ( true );
}

void HFileWidget::driveActivated( const QString&drive )
{
  hflist->setDir(drive);
}

void HFileWidget::showHome(void)
{
  hflist->setDir( QDir::homePath() );
}


/*****************************************************************************
 *
 * Class HInfoLabel
 *
 *****************************************************************************/
void HInfoLabel::paintEvent( QPaintEvent *)
{
  QFileInfo fi(fileName);
  
  QString rest = "";
  
  QString name = fi.completeBaseName();
  if( fi.isDir() )
  {
    name = fi.fileName();
    rest += "<DIR>  ";
  }else{
    rest+= fi.suffix();
    rest+= "  ";

    // Stripping size.
    int siz = fi.size();
    if(siz > 1000000000)
    {
      rest+= QString::number(siz / 1000000000);
      rest += ",";
      siz = siz % 1000000000;      
    }
    if(siz > 1000000)
    {
      rest+= QString::number(siz / 1000000);
      rest += ",";
      siz = siz % 1000000;
    }
    if(siz > 1000)
    {
      rest+= QString::number(siz / 1000);
      rest += ",";
      siz = siz % 1000;
    }
      rest+= QString::number(siz);
    //rest+= QString::number();
    rest+= "  ";
  }

  if(name.isEmpty())
    name = fileName;

  rest += fi.lastModified().toString("dd-MM-yyyy hh:mm");
  rest+= "  ";

  int attr = 0;
  QFile::Permissions perm = fi.permissions(); 

  if(perm & QFile::ReadOwner)
    attr += 400;

  if(perm & QFile::WriteOwner)
    attr += 200;

  if(perm & QFile::ExeOwner)
    attr += 100;

  if(perm & QFile::ReadGroup)
    attr += 40;
        
  if(perm & QFile::WriteGroup)
    attr += 20;

  if(perm & QFile::ExeGroup)
    attr += 10;

  if(perm & QFile::ReadOther)
    attr += 4;

  if(perm & QFile::WriteOther)
    attr += 2;

  if(perm & QFile::ExeOther)
    attr += 1;

  rest+= QString::number(attr);

  rest+= "  ";

  QPainter *painter = new QPainter(this);

  qDrawShadeRect( painter, 0, 0, width(), height(),
                  palette(), true );
  painter->drawText( 3, 3,  width()-6, height()-6, Qt::AlignVCenter, name);
  painter->drawText( 3, 3,  width()-6, height()-6, Qt::AlignVCenter|Qt::AlignRight, rest);
  
  painter->end();
  delete painter;
} 


/*****************************************************************************
 *
 * Class HDriveCombo
 *
 *****************************************************************************/
HDrivesCombo::HDrivesCombo( QWidget* parent)
  : QComboBox(parent)
{
  //addItem( const QIcon & icon, const QString & text, const QVariant & userData = QVariant() ) 
  addItem(load_icon("mc"), trUtf8( "My Computer" ));
  MyComputer mc;
  for (int i = 0; i < mc.driveList.size(); ++i) {
      HDrive hdr = mc.driveList.at(i);
      addItem(hdr.icon(), hdr.path() );    
  }
}

void HDrivesCombo::checkDrive( const QString& path )
{
  int length = 0;
  int index = -1;
  for (int i = 0; i < count(); i++) {
    QString text = itemText(i);
    if(path.contains(text))
    {
      if( length < text.length() )
      {
        length = text.length();
        index = i;
      }
    }
  }
  
  if(index > -1)
  {
    setCurrentIndex ( index );
  }
}
