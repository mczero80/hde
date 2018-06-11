/****************************************************************************
 **
 **				hinifile.cpp
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi, GPL
 **  email                : haydar@haydarnet.nl
 **
 **  Reads from ini files and write to them
 **
 ****************************************************************************/

#include <QSettings>
#include <hinifile.h>
#include "defs.h"

/***************************************************************
 *
 * Create a new QSetting with a file name for the inifile
 * and set the default group.
 *
 **************************************************************/
HIniFile::HIniFile(const QString& filename) { 
  settings = NULL;
  setName(filename);
  
  // create default group 
  setGroup("Default"); 
} 

/***************************************************************
 *
 * Create a new setting on changing the file name.
 *
 **************************************************************/
void HIniFile::setName(const QString& filename)
{
  if(settings != NULL)
    delete settings;
  fname = filename;
  settings = new QSettings( filename, QSettings::IniFormat );
} 


HIniFile::~HIniFile(){
  delete settings;
}

/****************************************************************
 *
 * Changing group, end the old one so we don't go inside the old
 * group
 *
 ***************************************************************/
void HIniFile::setGroup(const QString& group)
{
  if(! settings->group().isNull())
    settings->endGroup();
  settings->beginGroup(group);
}

QString HIniFile::group()
{
  return settings->group();
}
 

/*****************************************************************
 *
 * write entries 
 *
 ****************************************************************/
void HIniFile::writeEntry(const QString& key, const QString& value)
{
  settings->setValue( key, value);
}

void HIniFile::writeString(const QString& key, const QString& value) 
{
  settings->setValue( key, value);
}

void HIniFile::writeInt(const QString& key, int value)
{
  settings->setValue( key, value);
}

void HIniFile::writeDouble(const QString& key, double value) 
{
  settings->setValue( key, value);
}

void HIniFile::writeBool(const QString& key, bool value)
{
  if(value)
    settings->setValue( key, "TRUE");
  else
    settings->setValue( key, "FALSE");
}


void HIniFile::writeStringlist(const QString& key, QStringList value)
{
  settings->setValue( key, value);
} 


/*****************************************************************
 *
 * Read entries 
 *
 ****************************************************************/
QString HIniFile::readString(const QString& key, 
				    const QString& default_value)
{
  return settings->value(key, default_value).toString();
}

int HIniFile::readInt(const QString& key, int default_value)
{
  return settings->value(key, default_value).toInt();
}

double HIniFile::readDouble(const QString& key, double default_value)
{
  return settings->value(key, default_value).toDouble();
}

bool HIniFile::readBool(const QString& key, bool default_value)
{
  return settings->value(key, default_value).toBool();
  /*
  QString val;
  if(default_value)
    val = "TRUE";
  else
    val = "FALSE";

  val = settings->value(key, val).toString();
  cout << "Key = " << key.toAscii().data() << endl;
  cout << "Value = " << val.toAscii().data() << endl;
  if( val.toUpper() == "FALSE" )
    return false;
  
  return true;
  */
}

QStringList HIniFile::readStringlist(const QString& key, 
				     QStringList default_value)
{
  /*
  QStringList strings;
  QList<QVariant> list = settings->value(key, default_value).toList();
  for (int i = 0; i < list.size(); ++i) {
    strings << list.at(i).toString();
  }
  return strings;
  */
  return settings->value(key, default_value).toStringList();
}
