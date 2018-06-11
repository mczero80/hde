
#include "hdisplay.h"
#include <QDir>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QColorDialog>
#include <libhde.h>
#include <defaults.h>
#include <hinifile.h>

QString bgDisplay;
QString bgdir;
QString root_pix;
QColor root_bg;
QLabel *bgImage;

hDisplay::hDisplay(QWidget *parent)
  :QDialog(parent)
{
  ui.setupUi(this);

    ui.displayBox->addItem( trUtf8( "Center" ) );
    ui.displayBox->addItem( trUtf8( "Tile" ) );
    ui.displayBox->addItem( trUtf8( "Stretch" ) );
    ui.displayBox->setCurrentIndex( 2 );

  defaults::read_config();
  if(defaults::bgDisplay == "Center" )
    bgDisplay = trUtf8("Center" );
  else if(defaults::bgDisplay ==  "Tile" )
    bgDisplay = trUtf8( "Tile" );
  if(defaults::bgDisplay == "Stretch" )
    bgDisplay = trUtf8("Stretch");

  ui.displayBox->setCurrentIndex( ui.displayBox->findText(bgDisplay) );

  bgdir = defaults::bgdir;
  if(!defaults::bgdir.endsWith('/'))
    bgdir.append('/');
  root_pix = defaults::root_pix;

  root_bg = defaults::root_bg;
  drawBgBtn();

  bgImage = new QLabel(ui.bgLabel);
  bgImage->setGeometry(13,17,ui.bgLabel->width() -30, 
		       ui.bgLabel->height()-54);
  //bgImage->setPixmap(QPixmap(root_pix));

  readCurentDir();
  selCurentImg();
  drawImage();

  ui.applyBtn->setEnabled(false);


  connect( ui.displayBox, SIGNAL( activated(const QString&) ), this, 
	   SLOT( displayChanged(const QString&) ) ); 
  connect( ui.browseBtn, SIGNAL( clicked() ), this, SLOT(browse_clicked()));


  connect( ui.imagesList, SIGNAL( itemActivated( QListWidgetItem * )), this,
	   SLOT( imageSelected(QListWidgetItem *)));

  connect( ui.imagesList, SIGNAL( currentItemChanged ( QListWidgetItem *,
						       QListWidgetItem *)),
	   this,  SLOT( imageSelected(QListWidgetItem *)));

  //connect( ui.okBtn, SIGNAL( clicked() ), this, SLOT( ok_clicked() ) );
  connect( ui.applyBtn, SIGNAL( clicked() ), this, SLOT( apply_clicked()));
  connect( ui.bgBtn, SIGNAL( clicked() ), this, SLOT( bg_clicked()));

  /*
     ui.colorDepthCombo->addItem(tr("2 colors (1 bit per pixel)"));
     ui.colorDepthCombo->addItem(tr("4 colors (2 bits per pixel)"));
     ui.colorDepthCombo->addItem(tr("16 colors (4 bits per pixel)"));
     ui.colorDepthCombo->addItem(tr("256 colors (8 bits per pixel)"));
     ui.colorDepthCombo->addItem(tr("65536 colors (16 bits per pixel)"));
     ui.colorDepthCombo->addItem(tr("16 million colors (24 bits per pixel)"));

     connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
     connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  */
}

void hDisplay::drawImage()
{
  int dw = QApplication::desktop()->width();     // returns desktop width
  int dh = QApplication::desktop()->height();    // returns desktop height
  int bgw = bgImage->width();
  int bgh = bgImage->height();

  if(root_pix == "")
  {
    QPixmap rootPix = QPixmap(bgw,bgh);
    rootPix.fill(root_bg);
    bgImage->setPixmap(rootPix);
    return;
  }


  QPixmap rootPix = QPixmap(root_pix);
  int imw = rootPix.width();
  int imh = rootPix.height();


  if(bgDisplay == trUtf8( "Center" ))
  {
    QPixmap *rootpix = new QPixmap(bgw, bgh);
    QPainter p(rootpix);
    p.fillRect(0, 0, bgImage->width(), bgImage->height(), 
	       QBrush(root_bg));

    int xi = 0;
    int yi = 0;

    if(bgw > rootpix->width())
      xi = ((imw *bgw / dw)/2) - (rootpix->width()/2);
    else
      xi = (rootpix->width()/2) - ((imw * bgw / dw)/2);
    
    if(bgh > rootpix->height())
      yi = ( (imh * bgh / dh ) /2 ) - 
	(bgh/2);
    else
      yi = (bgh/2) -
	( (imh * bgh / dh ) /2 );
    rootPix = rootPix.scaled(imw * bgw / dw, imh * bgh / dh );

    p.drawPixmap( xi, yi, rootPix);
    p.end();
    
    bgImage->setPixmap(*rootpix);
    delete rootpix;
  }else if(bgDisplay == trUtf8( "Tile" ))
  {
    QPixmap *rootpix = new QPixmap(bgw, bgh);

    rootPix = rootPix.scaled(imw * bgw / dw, imh * bgh / dh );
    
    QPainter p(rootpix);
    p.fillRect(0, 0, bgw, bgh, QBrush(root_bg));
    p.drawTiledPixmap( 0, 0, bgw, bgh, rootPix);
    p.end();

    bgImage->setPixmap(*rootpix);
    delete rootpix;
  }else if(bgDisplay == trUtf8( "Stretch" ))
  {
    QPixmap *rootpix = new QPixmap(bgw, bgh);

    rootPix = rootPix.scaled( bgw, bgh );

    QPainter p(rootpix);
    p.fillRect(0, 0, bgw, bgh, QBrush(root_bg));
    p.fillRect( 0, 0, bgw, bgh, rootPix);
    p.end();

    bgImage->setPixmap(*rootpix);
    delete rootpix;

  }
}

void hDisplay::bg_clicked()
{
  QColor clr;
  clr = QColorDialog::getColor ( root_bg );
  if(clr.isValid())
    root_bg = clr;

  drawBgBtn();
  drawImage();
  ui.applyBtn->setEnabled(true);
}

void hDisplay::drawBgBtn()
{
  int bw = ui.bgBtn->width()-10;
  int bh = ui.bgBtn->height()-10;

  QPixmap *bgPix = new QPixmap(bw,bh);
  bgPix->fill(root_bg);
  ui.bgBtn->setIcon(QIcon(*bgPix));
  ui.bgBtn->setIconSize(QSize(bw,bh)); 
  delete bgPix;
}

void hDisplay::browse_clicked()
{
  QString s = 
    QFileDialog::getExistingDirectory(this, 
				      tr("BrowseOpen Directory"),
				      bgdir,
				      QFileDialog::ShowDirsOnly
				      | QFileDialog::DontResolveSymlinks);
  if( !s.isNull() ){
    bgdir = s;
    readCurentDir();
    ui.applyBtn->setEnabled(true);
  }
}

void hDisplay::apply_clicked()
{
  applyDisplay();
  applyApearance();

  ui.applyBtn->setEnabled(false);
    
  pid_t pid;
  if((pid = fork()) == -1)
  {
    perror("fork()");
    return;
  }	
  if(pid)
    return;
  
  execCmd("killall -HUP hde");
  return;
}


void hDisplay::applyDisplay()
{
  QString fname;
  fname = defaults::get_cfile("defaults");
 
  HIniFile def(fname);
  def.setGroup("Color_Background"); 
  
  if(bgDisplay == trUtf8( "Center" ))
    def.writeString("bgDisplay", "Center");
  if(bgDisplay == trUtf8( "Tile" ))
    def.writeString("bgDisplay", "Tile");
  if(bgDisplay == trUtf8( "Stretch" ))
    def.writeString("bgDisplay", "Stretch");
  
  def.writeString("BGDIR", bgdir);
  def.writeString("RootBackgroundPicture", root_pix);
  def.writeString("RootBackgroundColor", root_bg.name() );

  ui.applyBtn->setEnabled(false);

}

void hDisplay::applyApearance()
{

}

void hDisplay::readCurentDir()
{
  ui.imagesList->clear();
  ui.imagesList->addItem( trUtf8( "No Background" ) );

  QDir dir(bgdir);
  if(!dir.exists())
    return;

  dir.setFilter(QDir::Files | QDir::Hidden );
  dir.setSorting(QDir::Name);

  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    if(fileInfo.suffix() == "jpg" ||
       fileInfo.suffix() == "jpeg" ||
       fileInfo.suffix() == "gif" ||
       fileInfo.suffix() == "bmp" ||
       fileInfo.suffix() == "png" ||
       fileInfo.suffix() == "xpm")
      ui.imagesList->addItem( fileInfo.fileName() );
  }
}

void hDisplay::selCurentImg()
{
  QString im;
  im = root_pix.right( root_pix.length() - bgdir.length() );
  if(im.isNull()){
    ui.imagesList->setCurrentRow(0);
    //    std::cout << "im.isNull()" << std::endl;
    root_pix = "";
    drawImage();
    return;
  }

  std::cout << im.toAscii().data() << std::endl;
  std::cout << root_pix.toAscii().data() << std::endl;

  for(int i = 0; i < ui.imagesList->count(); ++i)
  {
    if(ui.imagesList->item(i)->text() == im)
    {
      ui.imagesList->setCurrentRow(i);
    }
  } 
}


void hDisplay::displayChanged(const QString& disp)
{
  bgDisplay = disp;
  drawImage();
  ui.applyBtn->setEnabled(true);
}

void hDisplay::imageSelected(QListWidgetItem *item )
{
  if(item == NULL)
  {
    ui.imagesList->setCurrentRow(0);
    return;
  }

  QString im = item->text();
  if(im != trUtf8( "No Background" )){
    root_pix = bgdir + im;
    //	bgImage->setPixmap(root_pix);
    //cout << root_pix << endl;
    drawImage();

  }else{
    root_pix = "";
    drawImage();
    //bgImage->setBackgroundPixmap(root_pix);
    
  }
  //    QMessageBox::information( this, "Application name", im );

  ui.applyBtn->setEnabled(true);
	

}
