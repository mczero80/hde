
#ifndef QHIJRI_H
#define QHIJRI_H

#include <qstring.h> 
#include <qdatetime.h>

static const char * const qt_H_shortMonthNames[]={"MHM","SFR","R0I","RII","J0I","JII","RJB","SBN","RMD","SWL","DQD","DHJ"};

class Qhijri
{
 public:
  double jd;

  Qhijri(){jd=0;}               //set null date
  Qhijri(int y,int m,int d);    //set date
  
  bool isNull()                            const { return jd==0; }
  bool isValid(int y,int m,int d)         const;
  bool leapYear(int y);

  int year()                 const;
  int month()                const;  //1..12
  int day()                  const;  //1..30
  int dayOfWeek()            ;//const;  //1..7
  int dayOfYear();//            const;  //1..365
  int daysInYear()           ;//const;  //29..30
  int daysInMonth()        ;//const;  //365 or 366


  QDate getDate();


  QString monthName(int i, bool shortName) const;
  QString formatDate();

  
  bool setYMD(int y,int m,int d);

  Qhijri addDays(int ndays)     const;
  Qhijri addMonths(int nmonths) const;
  Qhijri addYears(int nyears)   const;
  double daysTo(const Qhijri &d)const; 
  
  Qhijri fromString( const QString& s, Qt::DateFormat f );
  
  QString shortDayName(int weekday)const;
  static QString longMonthName(int month);//const;
  QString longDayName(int weekday)const;
  QString shortMonthName( int month )const;
  
  static Qhijri currentDate();

  void GregorianToHijri(int yg,int mg, int dg);
  static double HijriToJulian(int yh,int mh,int dh);
  static void JulianToHijri(double JD,int *y,int *m,int *d);
  
  bool operator==(const Qhijri &d) const {return jd ==d.jd;}
  bool operator!=(const Qhijri &d) const {return jd !=d.jd;}
  bool operator<(const Qhijri &d) const {return jd <d.jd;}
  bool operator<=(const Qhijri &d) const {return jd <=d.jd;}
  bool operator>(const Qhijri &d) const {return jd >d.jd;}
  bool operator>=(const Qhijri &d) const {return jd >=d.jd;}

 private:
  int  BH2GA(int yh,int mh,int *yg,int *mg, int *dg,int *dayweek);
  int  G2HA(int yg,int mg, int dg,int *yh,int *mh,int *dh,int *dayweek);
  int  H2GA(int *yh,int *mh,int *dh,int *yg,int *mg, int *dg,int *dayweek);
  void S2G(int ys,int ms,int ds,int *yg,int *mg,int *dg);
  void G2S(int yg,int mg,int dg,int *ys,int *ms,int *ds);


  double GCalendarToJD(int yg,int mg, double dg );
  double JDToGCalendar(double JD, int *yy,int *mm, int *dd);
  int GLeapYear(int year);

  void GDateAjust(int *yg,int *mg,int *dg);
  int DayWeek(long JulianD);

  static void JDToHCalendar(double JD,int *yh,int *mh,int *dh);
  static void JDToHACalendar(double JD,int *yh,int *mh,int *dh);
  static double HCalendarToJD(int yh,int mh,int dh);
  static double HCalendarToJDA(int yh,int mh,int dh);
  static int HMonthLength(int yh,int mh);

  double ip(double x);
  static int mod(double x, double y);

  int DayinYear(int yh,int mh,int dh);
  int HYearLength(int yh);
  bool isValid(int y,int m,int d);
  int IsValid(int yh, int mh, int dh);


};


#endif 

 
