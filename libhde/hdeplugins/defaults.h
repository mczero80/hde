/* defaults.h */

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "defs.h"

struct hdeItem {
  QString name;
  QString icon;
  QString exec;
  QString path;
  bool isDesktop;
  bool isKdeDesktop;
  QString error;
};

class defaults
{

public:
	static QString cfdir; 
	static QString get_cfile(char *name); 
	static QStringList imagesDirs;
	static QString coding;
	static hdeItem readItem(QString path);
	static void addToRecentPrograms(QString path);
};
#endif
