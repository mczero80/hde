
#include "deskitem.h"
#include <QApplication>
#include <QTranslator>
#include <defaults.h>


int main(int argc, char *argv[])
{
    bool hasDesktop =false;
    if(argc < 2){
	cout << "Please Specify a Menu/Desktop file\n";
	exit(1);
    }else{
	hasDesktop = true;
    }

  QApplication app(argc, argv);
  
  //  defaults::read_cfg();
  defaults::read_config();
  QTranslator translator( 0 );
  QTranslator qt_translator( 0 );
  QTranslator libtranslator( 0 );
  translator.load( "deskitem_" + defaults::lng,defaults::get_cfile("lng"));
  libtranslator.load( "libhde_" + defaults::lng,defaults::get_cfile("lng"));
  
  QString QTDIR = getenv( "QTDIR" );
  
  qt_translator.load( QString( "qt_%1" ).arg( defaults::lng ), 
		      QTDIR + "/translations" );
  
  app.installTranslator( &qt_translator );
  app.installTranslator( &translator );
  app.installTranslator( &libtranslator );
  
  deskitem *window = new deskitem;
  if(hasDesktop){
    QString filename = argv[1];
    if(! window->setFile(filename)){
      exit(1);
    }
  }

  window->show();
  return app.exec();
 }
