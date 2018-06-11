/* CConfigGroup.h */

#ifndef HINIGROUP_H
#define HINIGROUP_H

// qt include
#include <qstring.h>
#include <qmap.h>
  
// group map type
typedef QMap<QString, QString> GroupMap;
  
class HIniGroup{
    friend class HIniFile;

 public:
    HIniGroup(const QString& groupname);
    HIniGroup();
    
    void setName(const QString& groupname);
    const QString& name() const { return groupname; }
    
    const QString& readEntry(const QString& key, const QString& default_value = QString::null);
    void writeEntry(const QString& key, const QString& value);
 
    bool isEmpty() const { return map.isEmpty(); }
    
 private:
    QString groupname;
    GroupMap map;
};
  
#endif
