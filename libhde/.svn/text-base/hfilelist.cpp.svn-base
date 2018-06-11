/****************************************************************************
 **
 **				hfilelist.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2007 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  A widget that has a file list and dirlist.
 **
 ****************************************************************************/

#include "hfilelist.h"
#include <QApplication>
#include <QTimer>
#include <QFileIconProvider>
#include <QScrollBar>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDateTime>
#include <QItemDelegate>
#include <QPainter>


static QIcon load_icon( const QString &name )
{
  QIcon icn;
  icn.addFile(":/images/" + name + ".png", QSize(48,48));
  icn.addFile(":/images/" + name + "32.png", QSize(32,32));
  icn.addFile(":/images/" + name + "16.png", QSize(16,16));
  return icn;
}

bool resizing = false;
QTimer *icontimer;



/*****************************************************************************
 *
 * Class MyDelegate
 *
 *****************************************************************************/
class  MyDelegate : public QItemDelegate
{
 public:
   MyDelegate( QObject * parent = 0 ){};
   ~MyDelegate(){};

   virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, 
	      const QModelIndex &index) const
   {
     QStyleOptionViewItem opt( option );
     opt.decorationPosition = QStyleOptionViewItem::Top;
     opt.decorationAlignment = Qt::AlignHCenter;
     opt.displayAlignment = Qt::AlignHCenter;       

     QItemDelegate::paint(painter, opt, index);
   };
};

/*****************************************************************************
 *
 * Class MyDelegate2
 *
 *****************************************************************************/
class  MyDelegate2 : public QItemDelegate
{
 public:
   MyDelegate2( QObject * parent = 0 ){ setClipping(false); };
   ~MyDelegate2(){};
/*
   virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, 
	      const QModelIndex &index) const
   {
     
     QStyleOptionViewItem opt( option );
     opt.decorationPosition = QStyleOptionViewItem::Top;
     opt.decorationAlignment = Qt::AlignHCenter;
     opt.displayAlignment = Qt::AlignHCenter;       
     
     

     QItemDelegate::paint(painter, option, index);
   };
   */
 protected:
   virtual void drawFocus( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect ) const   
   {
     int w = painter->device()->width();
     
     w -=2;
     QRect r( 1, rect.y(), w, rect.height() );
     QItemDelegate::drawFocus( painter, option, r );
   };
   
};


/*****************************************************************************
 *
 * Class HFileList
 *
 *****************************************************************************/

MyDelegate * iconDeligate;
MyDelegate2 * detailedDeligate;
QAbstractItemDelegate *normalDeligate;

HFileList::HFileList( const QString &dir, QWidget* parent)
  :QTableWidget(parent)
{
  longestItem = 0;
  
  extraRow = false;
  extraCol = false;
  setSortingEnabled ( false );
  setShowGrid( false );
  horizontalHeader()->hide();
  verticalHeader()->hide();
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  latsteCordenates = QSize(0,0);
  
  setTabKeyNavigation ( false );
  iconDeligate = new MyDelegate(this);
  detailedDeligate = new MyDelegate2(this);

  normalDeligate = itemDelegate();
  vm = List;
//  vm = Detailed;
//  vm = Icons;
//  vm = Tiles;
  icontimer = new QTimer(this);
  Q_CHECK_PTR(icontimer);
  icontimer->setSingleShot(TRUE);
  connect(icontimer, SIGNAL(timeout()), SLOT(getFileIcon()));


//  setSelectionMode( QAbstractItemView::ContiguousSelection );
//  setSelectionMode( QAbstractItemView::SingleSelection );
  setSelectionMode( QAbstractItemView::NoSelection );
  
  connect(this, SIGNAL( itemActivated( QTableWidgetItem * ) ), 
	  this, SLOT( fileItemActivated( QTableWidgetItem * ) ));

  if(dir == "")
    readDir( QDir(trUtf8( "My Computer" )) );
  else
    readDir( QDir(dir));

  //readDir( QDir("C:/Windows/"));
  //readDir( QDir("/usr/share/icons"));
}


HFileList::~HFileList()
{
//  clear();
  itemsList.clear();
}


void HFileList::showMyComputer(void)
{
//  clearAll();

  viewDir = trUtf8( "My Computer" );
  MyComputer mc;
  //clearAll();

  emit directoryChanged( trUtf8( "My Computer" ) );

  longestItem = 0;
  QFontMetrics fm( font() );
  itemsList.clear();
  for (int i = 0; i < mc.driveList.size(); ++i) {
      HDrive hdr = mc.driveList.at(i);
      itemsList.append(new HFileListItem(hdr.path(), hdr.type(), hdr.icon() ));    

  int itemLengths  = fm.width(hdr.path())+15;
  if( itemLengths > longestItem)
      longestItem = itemLengths;
  }

//  ViewMode oldVm = vm;
//  vm = Tiles;
  setViewMode( vm );
//  vm = oldVm;
  setCurrentCell ( 0, 0 );
}

void HFileList::readDir( const QDir &d )
{

  QDir *dir = new QDir(d);
  // viewDir = dir;
  viewDir = dir->path();

  if( dir->path() == trUtf8( "My Computer" )){
    delete dir;
	emit directoryChanged( trUtf8("My Computer") );
	showMyComputer();
	return;
  }

  if ( !dir->isReadable() )
	return;

  QIcon fileIcon = load_icon("file");
  QIcon dirIcon = load_icon("folder");
  QIcon icon;


  //clearAll();


  emit directoryChanged( dir->path() );

  int itemLengths = 0;
  longestItem = 0;
  setCurrentCell ( 0, 0 );
  
  itemsList.clear();

  if (!dir->isRoot())
     itemsList.append(new HFileListItem(dir->path(), "UP", dirIcon ));

  QFontMetrics fm( font() );


  itemLengths  = fm.width(QString(".."))+15;

  if( itemLengths > longestItem)
      longestItem = itemLengths;
  

  dir->setFilter(QDir::Files | QDir::Hidden | QDir::Dirs);
  dir->setSorting( QDir::DirsFirst | QDir::Size );

  QFileInfoList list = dir->entryInfoList();

  
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);

    if( (fileInfo.fileName() == "." ) || (fileInfo.fileName() == ".." ) )
      continue;

    QString ftype = "File";
    icon = fileIcon;
    if( fileInfo.isFile() )
    {
      ftype = "File";
      icon = fileIcon;
      //icon = iconProvider.icon(fileInfo);

    }
    else if( fileInfo.isDir() )
    {
      ftype = "Dir";
      icon = dirIcon;
      //icon = iconProvider.icon(fileInfo);
    }
    else if( fileInfo.isSymLink())
      ftype = "Link";

    QString path = fileInfo.filePath();

    if( (ftype == "File") || (ftype == "Link") )
        itemLengths  = fm.width(fileInfo.fileName())+10;
    else if(ftype == "Dir")
         itemLengths  = fm.width(QDir(path).dirName())+10;

    if( itemLengths > longestItem)
        longestItem = itemLengths;
    
    itemsList.append(new HFileListItem(path, ftype, icon ));


  }
  
  //setViewMode( vm );

  delete dir;

  //  QTimer::singleShot( 3000, this, SLOT( getFileIcon() ) );
  //  icontimer->start(200);
  getFileIcon();
}

void HFileList::setViewMode( ViewMode mode )
{
  ViewMode oldMode = vm;
  vm = mode;
  // Getting CurItemPosition
  int curIndex = 0;
  int curCol = currentColumn();
  int curRow = currentRow();
    

  if(oldMode == List)
    curIndex = (curCol*getIconsPerColumn( oldMode ))+curRow;
  else if(oldMode == Icons)
    curIndex = (curRow*getIconsPerRow( oldMode ))+curCol;
  else if(oldMode == Tiles)
    curIndex = (curRow*getIconsPerRow( oldMode ))+curCol;
  else if(oldMode == Detailed)
    curIndex = (curRow*getIconsPerRow( oldMode ))+curCol;


  disconnect( this, SIGNAL(currentItemChanged ( QTableWidgetItem *, QTableWidgetItem *) ),
           this, SLOT( currentFileChanged( QTableWidgetItem *, QTableWidgetItem *) ) );

  

  qApp->setOverrideCursor( QCursor(Qt::WaitCursor) );

  clearAll();
//  setRowCount(itemsList.size());
//  setColumnCount(1);
//  setColumnWidth(0, longestItem);

  if(vm == List)
  {
    setShowGrid( false );
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setIconSize(QSize(16,16));
    setItemDelegate(normalDeligate);

    
    int iconPerColumn = getIconsPerColumn(vm);
    int cCount = (itemsList.size()) / iconPerColumn;
    if(extraRow)
      cCount +=1;
      
    if(cCount == 1)
    {
       setRowCount(itemsList.size());
       setColumnCount(1);
    }else{
       setRowCount(iconPerColumn);
       setColumnCount(cCount);
    }
    horizontalHeader()->resizeSections( QHeaderView::Stretch );

/*
--------------------------
|  R:1 C:1  |  R:1 C:2  |
|  R:2 C:1  |  R:2 C:2  |
|  R:3 C:1  |  R:3 C:2  |
------------------------- 
*/

    for(int col = 0; col < columnCount(); col++ )
    {
      setColumnWidth(col, longestItem+20);
      for( int row = 0; row < rowCount(); row++ )
      {
        setRowHeight( row, 20 );

        if( (col*(iconPerColumn)+row) < itemsList.size() )
        {
          HFileListItem *curItem = itemsList.at((col*iconPerColumn)+row);
          if( ((col*iconPerColumn)+row) == curIndex)
          {
            curCol = col;
            curRow = row;
          }
          if(curItem)
          {
            setItem(row, col, new HFileListItem(*curItem));
            latsteCordenates = QSize(row, col);
          }
        } // < itemsList.size()
        else
        { // > itemsList.size()
          QTableWidgetItem *itm = new QTableWidgetItem();
          itm->setFlags( Qt::ItemIsEnabled );
          setItem(row, col, itm);
        }
        
      } // rowCount()
    } // columnCount()
    //verticalHeader()->resizeSections( QHeaderView::Stretch );
  } // List
  else if(vm == Icons)
  {
    setShowGrid( false );
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setIconSize(QSize(32,32));
    setItemDelegate(iconDeligate);

    int iconPerRow = getIconsPerRow(vm);
    int rCount = (itemsList.size()) / iconPerRow;
    
//    if(extraCol)
    if( ((itemsList.size()) % iconPerRow) > 0  )
      rCount +=1;
      
    if(rCount == 1)
    {
       setRowCount(1);
       setColumnCount(itemsList.size());
    }else{
       setRowCount(rCount);
       setColumnCount(iconPerRow);
    }
    horizontalHeader()->resizeSections( QHeaderView::Stretch );
    verticalHeader()->resizeSections( QHeaderView::Stretch );
      
    for(int col = 0; col < columnCount(); col++ )
    {
      setColumnWidth(col, 65);
      for( int row = 0; row < rowCount(); row++ )
      {
        setRowHeight( row, 65 );
        if( (row*(iconPerRow)+col) < itemsList.size() )
        {
          HFileListItem *curItem = itemsList.at((row*iconPerRow)+col);
          if( ((row*iconPerRow)+col) == curIndex)
          {
            curCol = col;
            curRow = row;
          }
          
          if(curItem)
          {
            setItem(row, col, new HFileListItem(*curItem));
            latsteCordenates = QSize(row, col);
          }
        } // < itemsList.size()
        else
        { // > itemsList.size()
          QTableWidgetItem *itm = new QTableWidgetItem();
          itm->setFlags( Qt::ItemIsEnabled );
          setItem(row, col, itm);
        }
        
      } // rowCount()
    } // columnCount()


  }
  else if(vm == Tiles)
  {
    setShowGrid( false );
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setIconSize(QSize(40,40));
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setItemDelegate(normalDeligate);

    int iconPerRow = getIconsPerRow(vm);
    int rCount = (itemsList.size()) / iconPerRow;
    
//    if(extraCol)
    if( ((itemsList.size()) % iconPerRow) > 0  )
      rCount +=1;
      
    if(rCount == 1)
    {
       setRowCount(1);
       setColumnCount(itemsList.size());
    }else{
       setRowCount(rCount);
       setColumnCount(iconPerRow);
    }
    horizontalHeader()->resizeSections( QHeaderView::Stretch );
    verticalHeader()->resizeSections( QHeaderView::Stretch );
      
    for(int col = 0; col < columnCount(); col++ )
    {
      setColumnWidth(col, longestItem+40);
      for( int row = 0; row < rowCount(); row++ )
      {
        setRowHeight( row, 40 );
        if( ((row*iconPerRow)+col) < itemsList.size() )
        {
          HFileListItem *curItem = itemsList.at((row*iconPerRow)+col);
          if( ((row*iconPerRow)+col) == curIndex)
          {
            curCol = col;
            curRow = row;
          }
          
          if(curItem)
          {
            setItem(row, col, new HFileListItem(*curItem));
            latsteCordenates = QSize(row, col);
          }
        } // < itemsList.size()
        else
        { // > itemsList.size()
          QTableWidgetItem *itm = new QTableWidgetItem();
          itm->setFlags( Qt::ItemIsEnabled );
          setItem(row, col, itm);
        }
        
      } // rowCount()
    } // columnCount()

  }
  else if(vm == Detailed)
  {
    /*
    verticalHeader()->show();
    */
    setIconSize(QSize(16,16));
//    setShowGrid( true );
    setShowGrid( false );
    horizontalHeader()->show();
    //setItemDelegate(normalDeligate);
    setItemDelegate(detailedDeligate);
    setRowCount(itemsList.size());
    setColumnCount(5);
    QStringList labels;
    labels << tr("Name") << tr("Ext") << tr("Size") << tr("Date") << tr("Attr");
    setHorizontalHeaderLabels( labels ); 
    //horizontalHeader()->resizeSections( QHeaderView::Stretch );

    for (int i = 0; i < itemsList.size(); ++i) {
      HFileListItem *curItem = itemsList.at(i);
      if( (i) == curIndex)
      {
         curCol = 0;
         curRow = i;
      }
      setItem(i, 0, new HFileListItem(*curItem) );
      
      if( curItem->fileType() != "File" )
      {
        setItem(i, 1, new QTableWidgetItem( "" ));      
        setItem(i, 2, new QTableWidgetItem("<DIR>"));
      }
      else
      {
        setItem(i, 1, new QTableWidgetItem( curItem->fileInfo()->suffix() ));
        setItem(i, 2, new QTableWidgetItem( QString::number(curItem->fileInfo()->size()) ));
      }
      setItem(i, 3, new QTableWidgetItem(  curItem->fileInfo()->lastModified().toString("dd-MM-yyyy hh:mm") ));
      
      setRowHeight( i, 20 );

      /*
        Triplet for u: rwx => 4 + 2 + 1 = 7
        Triplet for g: r-x => 4 + 0 + 1 = 5
        Tripler for o: r-x => 4 + 0 + 1 = 5
        Which makes : 755 
      */
      
      int attr = 0;
      QFile::Permissions perm = curItem->fileInfo()->permissions(); 

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

      setItem(i, 4, new QTableWidgetItem( QString::number(attr) ));
      

    }
    horizontalHeader()->setResizeMode ( 0, QHeaderView::Stretch );
    horizontalHeader()->setResizeMode ( 1, QHeaderView::Fixed );
    horizontalHeader()->resizeSection ( 1, 40 );

//    horizontalHeader()->setResizeMode ( 2, QHeaderView::Interactive );
    horizontalHeader()->setResizeMode ( 2, QHeaderView::ResizeToContents );
    horizontalHeader()->setResizeMode ( 3, QHeaderView::ResizeToContents );
    horizontalHeader()->setResizeMode ( 4, QHeaderView::ResizeToContents );
    setSelectionBehavior(QAbstractItemView::SelectRows);
//    resizeColumnsToContents();
//    resizeRowsToContents(); 
  }
  
  qApp->restoreOverrideCursor();

  setCurrentCell ( curRow, curCol );


  connect( this, SIGNAL(currentItemChanged ( QTableWidgetItem *, QTableWidgetItem *) ),
           this, SLOT( currentFileChanged( QTableWidgetItem *, QTableWidgetItem *) ) );

}

void HFileList::currentFileChanged( QTableWidgetItem * current, QTableWidgetItem * previous )
{
  HFileListItem *itm = NULL;
     if( current->flags() == Qt::ItemIsEnabled )
     {
       if(vm == List) 
       {
         setCurrentItem(item( latsteCordenates.width(), latsteCordenates.height() ) );
         itm = (HFileListItem *)item( latsteCordenates.width(), latsteCordenates.height() );
         return;
       }
       else if( (vm == Tiles) || (vm == Icons) )
       {
         setCurrentItem(previous);
         return;
       }
       else

         ;//setCurrentItem(previous);
     }
     if( (vm == Detailed) && (current->column() != 0 ) )
     {
         setCurrentItem(item( current->row(), 0 ) );
         return;
     }
     
     itm = (HFileListItem *)current;
     if( (itm != (HFileListItem *)previous) && (itm !=NULL) )
     {
       QString dirname;
       if(itm->fileType() == "Dir")
       {
         dirname = itm->fileInfo()->path() + "/" + 
         itm->fileInfo()->fileName();
       }
       else if(itm->fileType() == "UP")
       {
         dirname = itm->fileInfo()->path(); 
       }
       else if( (itm->fileType() == "Hdd") || (itm->fileType() == "LHdd")
         || (itm->fileType() == "WHdd") || (itm->fileType() == "Home")
         || (itm->fileType() == "Fdd") || (itm->fileType() == "CD") )
       {
#ifdef Q_WS_X11
         dirname = itm->fileInfo()->path() + "/" + itm->fileInfo()->fileName();
#else
         dirname = itm->fileInfo()->path(); 
#endif
       }
       else if( itm->fileType() == "File")
       {
         dirname = itm->fileInfo()->path() + "/" + 
                   itm->fileInfo()->fileName();
       }
       emit fileHighlighted( dirname );
     }
     setDirtyRegion( QRegion(rect()) );
}

void HFileList::getFileIcon()
{
#ifdef Q_WS_WIN 
  QFileIconProvider *iconProvider = new QFileIconProvider;
  QFileInfo fileinfo;

  qApp->setOverrideCursor( QCursor(Qt::WaitCursor) );

  for (int i = 0; i < itemsList.size(); ++i) {
    HFileListItem *curItem = itemsList.at(i);       
    if(curItem)
    {
      fileinfo = *curItem->fileInfo();
      QIcon ico = iconProvider->icon(fileinfo);
      curItem->setIcon(ico);
    }
  }
  qApp->restoreOverrideCursor();
  delete iconProvider;
#endif 
  setViewMode( vm );
}


void HFileList::resizeEvent( QResizeEvent * e )
{
  resizing = true;
  setViewMode( vm ); 
  resizing = false;
}

void HFileList::clearAll()
{
  clear();
  if(!resizing)
  {
    setRowCount(0);
    setColumnCount(0);
  }
}

void HFileList::keyPressEvent( QKeyEvent * e ) 
{
  //latsteCordenates = QSize(row, col);
 
  if( vm == List)
  {
    if( (currentColumn()  == (columnCount()-1) ) && ( currentRow() != latsteCordenates.width() )
        && ( e->key() == Qt::Key_Right ) )
    {
         setCurrentItem(item( latsteCordenates.width(), latsteCordenates.height() ) );
    }
    else if( (currentColumn()  == 0 ) && ( currentRow() != 0 ) && ( e->key() == Qt::Key_Left ) )
    {
        setCurrentItem(item( 0, 0 ) );
    }
    else if( (currentColumn()  != (columnCount()-1) ) && ( currentRow() == (rowCount()-1) ) 
    && ( e->key() == Qt::Key_Down ) )
    {
        setCurrentItem(item( 0,  currentColumn()+1) );
    }
    else if( (currentColumn()  != 0 ) && ( currentRow() == 0 ) 
    && ( e->key() == Qt::Key_Up ) )
    {
        setCurrentItem(item( (rowCount()-1),  currentColumn()-1) );
    }
    else if( e->key() == Qt::Key_Insert )
    {
      if( viewDir == trUtf8( "My Computer" ))
        return;
        
      bool sel = ! item( currentRow(), currentColumn() )->isSelected();

      item( currentRow(), currentColumn() )->setSelected( sel );
      QKeyEvent *ke = new QKeyEvent( QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
      keyPressEvent(ke);
      delete ke;

//        setCurrentItem(item( 0,  currentColumn()+1) );
    }
    else
    {
      QTableWidget::keyPressEvent( e );
    }
  }
  else
  {
    if( e->key() == Qt::Key_Insert )
    {
      if( viewDir == trUtf8( "My Computer" ))
        return;
        
      bool sel = ! item( currentRow(), currentColumn() )->isSelected();

      item( currentRow(), currentColumn() )->setSelected( sel );
     // QKeyEvent *ke = new QKeyEvent( QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
      //keyPressEvent(ke);
      //delete ke;

//        setCurrentItem(item( 0,  currentColumn()+1) );
    }
    else  
     QTableWidget::keyPressEvent( e );
  }
  
}

int HFileList::getIconsPerColumn( ViewMode mode )
{
  extraRow = false;
  int number = 10;
  if(mode == List)
  {
    number = (height() / 20);
    
    if((height() % 20) > 0)
      extraRow = true;
  }
  
  if(number > 2)
    number -=1;

  return number;
}

int HFileList::getIconsPerRow( ViewMode mode )
{
  extraCol = false;
  int number = 1;
  if(mode == Tiles)
  {
    int longestWidth = longestItem + 40;
    number = (width() / longestWidth);
    
    if((width() % longestWidth) != 0)
      extraCol = true;
  }
  else if(mode == Icons)
  {
    int longestWidth = 65;
    number = (width() / longestWidth);
    
    if((width() % longestWidth) != 0)
      extraCol = true;
       
  }
//    if(number > 2)
//     number -=1;

  return number;
}


void HFileList::fileItemActivated( QTableWidgetItem * item )
{

  int iconPerColumn = getIconsPerColumn(vm);
  int iconPerRow = getIconsPerRow(vm);
  int irow = row( item );
  int icol = column( item );
  HFileListItem *actItem;
  if( vm == List )
  {
    actItem = itemsList.at(icol*(iconPerColumn)+irow);
  }
  else if( vm == Icons)
  {
    actItem = itemsList.at(irow*(iconPerRow)+icol);
  }
  else if( vm == Tiles)
  {
    actItem = itemsList.at(irow*(iconPerRow)+icol);
  }
  else if( vm == Detailed)
  {
    actItem = itemsList.at(irow);       
  }

  if(!actItem)
  {
    return;
  }

  //  HFileListItem *actItem = (HFileListItem *)itm;
  
  QString dirname;
  if(actItem->fileType() == "Dir")
  {
    dirname = actItem->fileInfo()->path() + "/" + actItem->fileInfo()->fileName();
  } 
  else if(actItem->fileType() == "UP")
  {
    dirname = actItem->fileInfo()->path(); 
  }
  else if( (actItem->fileType() == "Hdd") || (actItem->fileType() == "LHdd")
      || (actItem->fileType() == "WHdd") || (actItem->fileType() == "Home") ||
      (actItem->fileType() == "Fdd") || (actItem->fileType() == "CD") )
  {
#ifdef Q_WS_X11
    dirname = actItem->fileInfo()->path() + "/" + actItem->fileInfo()->fileName();
#else
    dirname = actItem->fileInfo()->path(); 
#endif
    //readDir( QDir(dirname) );
  }
  else if( actItem->fileType() == "File")
  {
    dirname = actItem->fileInfo()->path() + "/" + 
      actItem->fileInfo()->fileName();
    emit fileExecuted( dirname );
    return;
  }
  readDir( QDir(dirname) );
}

void HFileList::focusInEvent ( QFocusEvent * )
{
  emit focusChanged( true );     
}

void HFileList::focusOutEvent ( QFocusEvent * )
{
  emit focusChanged( false );
}

QStringList HFileList::selectedList()
{
  QStringList selList;
  // QList<QTableWidgetItem *> QTableWidget::selectedItems()
  if( selectedItems().empty() )
  {
      HFileListItem *actItem = (HFileListItem *)currentItem();
      QString dirname = "";
      if(actItem->fileType() == "UP")
      {
        return selList;
      }
      else if( (actItem->fileType() == "Hdd") || (actItem->fileType() == "LHdd")
        || (actItem->fileType() == "WHdd") || (actItem->fileType() == "Home") ||
        (actItem->fileType() == "Fdd") || (actItem->fileType() == "CD") )
      {
        return selList;
      }
      else
      {
        dirname = actItem->fileInfo()->path() + "/" + 
                actItem->fileInfo()->fileName();
      }

      selList.append(dirname);
  }
  else
  {
    for (int i = 0; i < selectedItems().size(); ++i)
    {
      HFileListItem *actItem = (HFileListItem *)selectedItems().at(i);
      QString dirname = "";
      if(actItem->fileType() == "UP")
      {
        continue;//dirname = actItem->fileInfo()->path(); 
      }
      else if( (actItem->fileType() == "Hdd") || (actItem->fileType() == "LHdd")
        || (actItem->fileType() == "WHdd") || (actItem->fileType() == "Home") ||
        (actItem->fileType() == "Fdd") || (actItem->fileType() == "CD") )
      {
        continue;//dirname = actItem->fileInfo()->path(); 
      }
      else
      {
        dirname = actItem->fileInfo()->path() + "/" + 
                actItem->fileInfo()->fileName();
      }

      if(actItem->fileType() == "Dir")
        selList.prepend(dirname);
      else
        selList.append(dirname);
    }
  }
  
  
  return selList;
}

void HFileList::refresh()
{
  int curCol = currentColumn();
  int curRow = currentRow();
  disconnect( this, SIGNAL(currentItemChanged ( QTableWidgetItem *, QTableWidgetItem *) ),
           this, SLOT( currentFileChanged( QTableWidgetItem *, QTableWidgetItem *) ) );
  setDir(viewDir);
  
  if( (columnCount()-1) < curCol )
    curCol = columnCount()-1;
    
  if( (rowCount()-1) < curRow )
    curRow = rowCount()-1;

  setCurrentCell ( curRow, curCol );
  
  connect( this, SIGNAL(currentItemChanged ( QTableWidgetItem *, QTableWidgetItem *) ),
           this, SLOT( currentFileChanged( QTableWidgetItem *, QTableWidgetItem *) ) );
}

/*****************************************************************************
 *
 * Class HFileListItem
 *
 *****************************************************************************/

HFileListItem::HFileListItem( QString path, QString ftype, QIcon ico )
  : QTableWidgetItem(Type)
{
  setData(Qt::UserRole, ftype);
  itemPath = path;
 
  itemFileInfo = new QFileInfo(path);
    
  if( (ftype == "File") || (ftype == "Link") )
    setText(itemFileInfo->fileName());
  else if(ftype == "Dir")
    setText(QDir(path).dirName());
  else if(ftype == "UP")
    setText("..");
  else
    setText(path);
    /*
      else if( (ftype == Dir) || (ftype == Dir) || (ftype == Fdd) || (ftype == Hdd)
         || (ftype == LHdd) || (ftype == WHdd) || (ftype == CD) || (ftype == Home) )
    */
    
  setIcon(ico);
  //setSizeHint( QSize(200,20) );
}

HFileListItem::HFileListItem( const HFileListItem& other )
     : QTableWidgetItem(other)
{
  itemPath = other.path();
  itemFileInfo = other.fileInfo();
}

QString HFileListItem::fileType() const
{
  QString typ;
  typ =  data(Qt::UserRole).toString();
  return typ;
}
