#include "hrun.h"
#include <QFileDialog>
#include <defaults.h>
#include <libhde.h>


static const char* const image0_data[] = { 
"32 32 13 1",
". c None",
"a c #000000",
"c c #000080",
"g c #0000ff",
"h c #008000",
"j c #00ff00",
"i c #00ffff",
"# c #303030",
"e c #800000",
"k c #800080",
"b c #808080",
"f c #ff0000",
"d c #ffffff",
"................................",
"................................",
"................................",
"................................",
"................................",
"........#aaaaaaaaaaaaaaaaaa#....",
"........abbbbbbbbbbbbbbbbbba....",
"........ab.................a....",
"........ab.cccccccccdadada.a....",
"........ab.cccccccccaaaaaa.a....",
"........ab.................a....",
"....aaaaab.ddddddddddddddd.a....",
"...aeeeeeeeeeadddddddddddd.a....",
"...aef..fffffaddgdddddhddd.a....",
"....aaaaaaaaadddiggdddhhdd.a....",
"....abdd...badddgg.ddhjgdd.a....",
"....abdd...baddk.kkddhhhdd.a....",
"....ab.b.a.baddddddddddddd.a....",
".....ab.a.baddddbbbddbbbdd.a....",
"......abdbaddddddddddddddd.a....",
"......abdbaddddddddddddddd.a....",
".....ab.b.ba...............a....",
"....ab.d...baaaaaaaaaaaaaaa#....",
"....abdda..ba...................",
"....abda.a.ba...................",
"....aaaaaaaaa...................",
"...aef..fffffa..................",
"....aaaaaaaaa...................",
"................................",
"................................",
"................................",
"................................"};




hrun::hrun(QWidget *parent)
  :QDialog(parent)
{
  setWindowIcon( QPixmap(( const char** ) image0_data));
  ui.setupUi(this);
  connect( ui.okBtn, SIGNAL( clicked() ), this, SLOT( ok_clicked() ) );
  connect( ui.browseBtn, SIGNAL( clicked() ), this, SLOT( browse_clicked()) );

  /*
  if(defaults::cfdir.isNull()){
    QString fname(getenv("HOME"));
    
    if(! fname.isNull())
      defaults::cfdir = fname + "/.hde";
  }
  */
  QString cmp( defaults::cfdir + "/hrunfiles" );
  QFile file( cmp);
  if ( file.open( QIODevice::ReadOnly ) ) {
    QTextStream in( &file );
    QString line = in.readLine();
    int i = 0;
    while (!line.isNull()) {
      ui.openCombo->insertItem( i++, line );
      line = in.readLine();
    }
    file.close();
  }
  ui.openCombo->setCurrentIndex( 0 );


}

void hrun::ok_clicked()
{
  if(ui.openCombo->currentText().isEmpty())
    accept();

  QStringList args;
  
  QProcess *proc = new QProcess( this );

  if(ui.xtermBox->isChecked()){
    args << "-e";
    args << ui.openCombo->currentText();
  }

  connect( proc, SIGNAL( error( QProcess::ProcessError ) ),
	   this, SLOT( runError( QProcess::ProcessError ) ) );
  connect( proc, SIGNAL( started () ),
	   this, SLOT( runStarted() ) );


  if(ui.xtermBox->isChecked())
    proc->start( "xterm", args );
  else
    proc->start( ui.openCombo->currentText() );
  
  hide();
}

void hrun::browse_clicked()
{
  QString s = QFileDialog::getOpenFileName( this, tr("Browse") );
  ui.openCombo->insertItem( 0, s );
  ui.openCombo->setCurrentIndex( 0 );
}

void hrun::runError( QProcess::ProcessError )
{
  accept();
}

//void hrun::runFinished( int, QProcess::ExitStatus )
void hrun::runStarted()
{
  saveChanges();
  accept();
}

void hrun::saveChanges()
{
  if(!QFileInfo( defaults::cfdir ).exists() )
    execCmd( "mkdir -p " + defaults::cfdir );
	

  int index = ui.openCombo->currentIndex();
  QString txt = ui.openCombo->itemText(index);
  ui.openCombo->removeItem( index );
  ui.openCombo->insertItem( 0, txt );

  QString cmp( defaults::cfdir + "/hrunfiles" );
  QFile file( cmp);
  if ( file.open( QIODevice::WriteOnly ) ) {
    QTextStream stream( &file );
    for ( int ival = 0; ival < ui.openCombo->count(); ival++)
      stream << ui.openCombo->itemText(ival) << "\n";
    
    file.close();
  }
}

