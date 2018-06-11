#include "deskitem.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <defaults.h>
#include <libhde.h>




deskitem::deskitem(QWidget *parent)
  :QDialog(parent)
{
  ui.setupUi(this);
  ui.iconBtn->setIconSize ( QSize(64,64) );
  connect( ui.okBtn, SIGNAL( clicked() ), this, SLOT( ok_clicked() ) );
}

bool deskitem::setFile(QString filename)
{
  //filename = QFile::decodeName ( QCString(filename) );
  if(!QFileInfo::QFileInfo(filename).exists()){
    QMessageBox::critical( this, "Application name",
			   "File: \"" +filename +
			   "\" does not exists\n" );
    return false;
  }
  
  hdeItem ditem = defaults::readItem(filename);
 
  
  if(!ditem.isDesktop)
    cout << "is not a Desktop file\n\n";
  
  QString iname(ditem.name);
  
  iname = iname.replace( QRegExp("%2f"), "/" );
  ui.nameEdit->setText(iname);
  
  /*
  if (svar == "" || ! QFile( svar ).exists())
    ui.iconBtn->setIcon(QIcon(defaults::get_cfile("images/default-48.png")));
  else
    ui.iconBtn->setIcon(QIcon(svar));
  */



  QString svar = ditem.icon;
  svar = getIconFile(svar, "large");

  if (svar == "" || ! QFile( svar ).exists())
    svar = defaults::get_cfile("images/default-48.png");

  QImage pimg(svar);
  QPixmap pix;

  if(! pimg.isNull())
    pix = QPixmap::fromImage(pimg.scaled(48, 48));
  else{
    pix.load(defaults::get_cfile("images/default-48.png"));
    pix = pix.scaled(48, 48);
  }

  ui.iconBtn->setIcon(QIcon(pix));

  //svar = path + "/" + fname;
    
  //icn->setPath(svar);
  //icn->setFilename( fname );
  



 
  return true;
}

void deskitem::ok_clicked()
{
}
