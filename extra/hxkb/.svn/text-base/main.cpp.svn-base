#include <qapplication.h>
#include "hxkbwidget.h"



int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    hXkbWidget *wid = new hXkbWidget;
    wid->show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
