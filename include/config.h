/* config.h */

#ifndef CONFIG_H
#define CONFIG_H

#include "defaults.h"
#include "defs.h"

class config
{

 private:
    static QString grouptmp, rest, fname;
    static int groupnum, linenr;
    static QList<QString> lns;
    static bool checkForGroup(QString group, bool items);
    static bool nextGroup(QString name);
    static void loadmenulist(void);
    static void savelist(void);
    static void checkForItem(QString name, QString shortcut, QString icon);
    static void deleteMenuItem(QString name, QString shortcut, QString icon);
    static void addMenuShorcut2(QString name, QString shortcut, QString icon);

 public:
    static void addMenuShorcut(QString name, QString shortcut, QString Iocn);
    static void delMenuShorcut(QString name, QString shortcut, QString Iocn);

};
#endif
