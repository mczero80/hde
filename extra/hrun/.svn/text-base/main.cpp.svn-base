
#include "hrun.h"
#include <QApplication>
#include <QTranslator>
#include <defaults.h>


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  defaults::read_cfg();
  QTranslator translator( 0 );
  QTranslator qt_translator( 0 );
  QTranslator libtranslator( 0 );
  translator.load( "hrun_" + defaults::lng,defaults::get_cfile("lng"));
  libtranslator.load( "libhde_" + defaults::lng,defaults::get_cfile("lng"));
  
  QString QTDIR = getenv( "QTDIR" );
  
  qt_translator.load( QString( "qt_%1" ).arg( defaults::lng ), 
		      QTDIR + "/translations" );
  
  app.installTranslator( &qt_translator );
  app.installTranslator( &translator );
  app.installTranslator( &libtranslator );
  
  hrun *window = new hrun;

  window->show();
  return app.exec();
 }
