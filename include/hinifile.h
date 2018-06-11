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
 
#ifndef HINIFILE_H 
#define HINIFILE_H 
   

#include <qstringlist.h>  
class QSettings;
   
class HIniFile { 
 public: 
    HIniFile(); 
    HIniFile(const QString& filename); 
    ~HIniFile(); 
   
    
    // file 
    void setName(const QString& filename); 
    QString name(){ return fname; } 
   
    // current group 
    void setGroup(const QString& group); 
    QString group(); 
    
    // write entries 
    void writeEntry(const QString& key, const QString& value); 
    void writeString(const QString& key, const QString& value); 
    void writeInt(const QString& key, int value); 
    void writeDouble(const QString& key, double value); 
    void writeBool(const QString& key, bool value); 
    void writeStringlist(const QString& key, QStringList value); 
    
    // read entries 
    QString readString(const QString& key,const QString& default_value);
    int readInt(const QString& key, int default_value); 
    double readDouble(const QString& key, double default_value);
    bool readBool(const QString& key, bool default_value); 
    QStringList readStringlist(const QString& key, 
			       QStringList default_value);

 private:    
    QString fname;
    QSettings *settings;
};	 
   
#endif // HINIFILE_H
