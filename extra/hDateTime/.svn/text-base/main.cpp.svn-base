#include <qapplication.h>
#include "configdlg.h"
//#include <hde_tbab.h>
#include <defaults.h>


int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    
    defaults::read_config();
    defaults::read_config();
    QTranslator translator( 0 );
    QTranslator qt_translator( 0 );
    QTranslator libtranslator( 0 );
    translator.load( "hdatetime_" + defaults::lng,defaults::get_cfile("lng"));
    libtranslator.load( "libhde_" + defaults::lng,defaults::get_cfile("lng"));

    QString QTDIR = getenv( "QTDIR" );

    qt_translator.load( QString( "qt_%1" ).arg( defaults::lng ), 
			QTDIR + "/translations" );

    a.installTranslator( &qt_translator );
    a.installTranslator( &translator );
    a.installTranslator( &libtranslator );
    
    configDlg *dc = new configDlg;
    //   a.setMainWidget(dc);
    dc->show();
    return a.exec();
}
