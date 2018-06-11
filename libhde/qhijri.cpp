
/*
  Copyright (C) 2002 Fayez Alhargan.
  King Abdulaziz City for Science and Technology
  Computer and Electronics Research Institute
  Riyadh, Saudi Arabia
  alhargan@kacst.edu.sa
  Tel:4813770 Fax:4813764
  This is a program that computes the Hijary dates for Umm-AlQura calendar
  the official calendar of the Kingdom of Saudi Arabia.

  modified by Mcs. Haydar Alkaduhimi <haydar@haydarnet.nl> on 15-02-2004
  last modified 15-02-2004
  

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser Library General Public License for more details.

*/
 
#include <qhijri.h>
#ifdef Q_WS_WIN
#include <windows.h>
#endif
#include <defs.h>
//#include <qt.h>
#include <stdlib.h>
#include <math.h>

#define HStartYear 1420
#define HEndYear 1450

Qhijri::Qhijri(int y,int m,int d)
{
  jd=0;
  setYMD(y,m,d);

  //cout << "Date is: "<< jd << endl;

}
//*******************************************************
int Qhijri::year() const
{
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );
  return y;
}

int Qhijri::month() const
{
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );
  return m;
}

int Qhijri::day() const
{
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );
  return d;
}


Qhijri Qhijri::addDays(int ndays) const
{
  Qhijri d;
  d.jd = jd + ndays;
  return d;
}

double Qhijri::daysTo( const Qhijri &d ) const
{
  return d.jd - jd;
}

int Qhijri::dayOfYear()  //const
{
  int y ,m ,d ;
  JulianToHijri(jd,&y ,&m ,&d );

  return DayinYear(y ,m ,d );
}

int Qhijri::daysInYear() //const
{
  int y ,m ,d ;
  JulianToHijri(jd,&y ,&m ,&d );
  
  return HYearLength(y);
}




Qhijri Qhijri::addMonths(int nmonths) const
{
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );
  
  
  while ( nmonths != 0 ) {
    if ( nmonths < 0 && nmonths + 12 <= 0 ) {
      y--;
      nmonths+=12;
    } else if ( nmonths < 0 ) {
      m+= nmonths;
      nmonths = 0;
      if ( m <= 0 ) {
	--y;
	m+=12;
      }
    } else if ( nmonths - 12 >= 0 ) {
      y++;
      nmonths-=12;
    } else if ( m == 12 ) {
      y++;
      m = 0;
    } else {
      m+= nmonths;
      nmonths = 0;
      if ( m > 12 ) {
	++y;
	m -= 12;
      }
    }
  }
  
  Qhijri tmp(y,m,1);
  
  if( d > tmp.daysInMonth() )
    d = tmp.daysInMonth();
  
  Qhijri date(y, m, d);
  return date;
  
}

Qhijri Qhijri::addYears(int nyears) const
{
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );
  y +=nyears;
  Qhijri date(y ,m ,d);
  return date;
}

int Qhijri::dayOfWeek() //const
{
  int yg,mg,dg,yh,mh,dh,dayweek;
  //  H2GA(&yh,&mh,&dh,&yg,&mg,&dg,&dayweek);
  JulianToHijri(jd,&yh ,&mh ,&dh );
  JDToGCalendar(jd, &yg, &mg, &dg);
  H2GA(&yh,&mh,&dh,&yg,&mg,&dg,&dayweek);
  return dayweek;
}

int Qhijri::daysInMonth() //const
{
  int leng;//yh,mh;
  int y ,m , d;
  JulianToHijri(jd,&y ,&m ,&d );

  leng=HMonthLength(y,m);
  return leng;
}



QDate Qhijri::getDate()
{
  QDate date;

  int yy, mm, dd;
  JDToGCalendar(jd, &yy, &mm, &dd);
  date.setYMD( yy, mm, dd);
  /*
  cout << "\nThe Year is:" << yy << endl;
  cout << "\nThe Month is:" << mm << endl;
  cout << "\nThe Day is:" << dd << endl;
  */

  return date;
}


QString Qhijri::longMonthName(int month)// const
{
  switch ( month )
    {
    case 1:   return QObject::trUtf8("MUHARRAM");
    case 2:   return QObject::trUtf8("SAFAR");
    case 3:   return QObject::trUtf8("RABI'I");
    case 4:   return QObject::trUtf8("RABI'II");
    case 5:   return QObject::trUtf8("JUMADA'I");
    case 6:   return QObject::trUtf8("JUMADA'II");
    case 7:   return QObject::trUtf8("RAJAB");
    case 8:   return QObject::trUtf8("SHA'BAN");
    case 9:   return QObject::trUtf8("RAMADAN");
    case 10:  return QObject::trUtf8("SHAWWAL");
    case 11:  return QObject::trUtf8("DHU AL-QA'DAH");
    case 12:  return QObject::trUtf8("DHU AL-HIJJAH");
    }
  return QString::null;
}

QString Qhijri::shortDayName(int weekday)const
{
  switch ( weekday )
    {
    case 1:   return ("Mon");
    case 2:   return ("Tue");
    case 3:   return ("Wed");
    case 4:   return ("Thu");
    case 5:   return ("Fri");
    case 6:   return ("Sat");
    case 7:   return ("Sun");
    }
  return QString::null;
}

QString Qhijri::longDayName(int weekday) const
	{
		switch ( weekday )
			{
			case 1:   return ("Monday");
			case 2:   return ("Tuesday");
			case 3:   return ("Wednesday");
			case 4:   return ("Thursday");
			case 5:   return ("Friday");
			case 6:   return ("Saturday");
			case 7:   return ("Sunday");
			}
		return QString::null;
	}

QString Qhijri::monthName(int i, bool shortName) const
	{
		if ( shortName )
			switch ( i )
				{
				case 1:   return (QObject::trUtf8("MUHARRAM"),
						  QObject::trUtf8("MHM"));
				case 2:   return (QObject::trUtf8("SAFAR"),
						  ("SFR"));
				case 3:   return (QObject::trUtf8("RABI'I"),
						  ("R0I"));
				case 4:   return (QObject::trUtf8("RABI'II"),
						  QObject::trUtf8("RII"));
				case 5:   return (QObject::trUtf8("JUMADA'I"),
						  QObject::trUtf8("J0I"));
				case 6:   return (QObject::trUtf8("JUMADA'II"),
						  QObject::trUtf8("JII"));
				case 7:   return (QObject::trUtf8("RAJAB"),
						  QObject::trUtf8("RJB"));
				case 8:   return (QObject::trUtf8("SHA'BAN"),
						  QObject::trUtf8("SBN"));
				case 9:   return (QObject::trUtf8("RAMADAN"),
						  QObject::trUtf8("RMD"));
				case 10:  return (QObject::trUtf8("SHAWWAL"),
						  QObject::trUtf8("SWL"));
				case 11:  return (QObject::trUtf8("DHU AL-QA'DAH"),
						  QObject::trUtf8("DQD"));
				case 12:  return (QObject::trUtf8("DHU AL-HIJJAH"),
						  QObject::trUtf8("DHJ"));
				}
		  else
			 switch (i)
				{
				case 1:   return ("MHM");
				case 2:   return ("SFR");
				case 3:   return ("R0I");
				case 4:   return ("RII");
				case 5:   return ("J0I");
				case 6:   return ("JII");
				case 7:   return ("RJB");
				case 8:   return ("SBN");
				case 9:   return ("RMD");
				case 10:  return ("SWL");
				case 11:  return ("DQD");
				case 12:  return ("DHJ");
				}

		  return QString::null;
	}



bool Qhijri::isValid(int y,int m,int d) // const
	{
		if(IsValid(y,m,d)==0)
		  return FALSE;
		else return TRUE;
	}

bool Qhijri::leapYear ( int y )
	{
		if(GLeapYear(y)==0)
		  return FALSE;
		else
		  return TRUE;
	}
   
QString Qhijri ::formatDate()
	{
	  int y ,m , d;
	  JulianToHijri(jd,&y ,&m ,&d);
	  QString s,temp;
	  temp.setNum(y);
	  s+=temp;
	  s+=" / ";
	  temp.setNum(m);
	  s+=temp;
	  temp.setNum(d);
	  s+=" / " + temp;
	  return s;
	}



Qhijri Qhijri::fromString( const QString& s, Qt::DateFormat f )
{
    if ( ( s.isEmpty() ) || ( f == Qt::LocalDate ) ) {
#if defined(QT_CHECK_RANGE)
	qWarning( "Qhijri::fromString: Parameter out of range." );
#endif
    	return Qhijri();
    }
    switch ( f ) {
    case Qt::ISODate:
	{
	    int year( s.mid( 0, 4 ).toInt() );
	    int month( s.mid( 5, 2 ).toInt() );
	    int day( s.mid( 8, 2 ).toInt() );
	    if ( year && month && day )
		return Qhijri( year, month, day );
	}
	break;
    default:
#ifndef QT_NO_TEXTDATE
    case Qt::TextDate:
	{
	    QString monthName( s.mid( 4, 3 ) );
	    int month = -1;
	    // Assume that Hijri monthnames are the default
	    for ( int i = 0; i < 12; ++i ) {
		if ( monthName == qt_H_shortMonthNames[i] ) {
		    month = i + 1;
		    break;
		}
	    }
	    // If Hijri names can't be found, search the localized ones
	    if ( month == -1 ) {
		for ( int i = 1; i <= 12; ++i ) {
		    if ( monthName == shortMonthName( i ) ) {
			month = i;
			break;
		    }
		}
	    }
#if defined(QT_CHECK_RANGE)
    	    if ( month < 1 || month > 12 ) {
		qWarning( "Qhijri::fromString: Parameter out of range." );
		month = 1;
	    }
#endif
	    int day = s.mid( 8, 2 ).simplified().toInt();
	    int year = s.right( 4 ).toInt();
	    return Qhijri( year, month, day );
	}
#else
	break;
#endif
    }
    return Qhijri();
}




QString Qhijri::shortMonthName( int month )const
{
#if defined(QT_CHECK_RANGE)
    if ( month < 1 || month > 12 ) {
	qWarning( "Qhijri::shortMonthName: Parameter out ouf range." );
	month = 1;
    }
#endif
#ifndef Q_WS_WIN
    char buffer[255];
    tm tt;
    memset( &tt, 0, sizeof( tm ) );
    tt.tm_mon = month - 1;
    if ( strftime( buffer, sizeof( buffer ), "%b", &tt ) )
	return QString::fromLocal8Bit( buffer );
#else
    SYSTEMTIME st;
    memset( &st, 0, sizeof(SYSTEMTIME) );
    st.wYear = 2000;
    st.wMonth = month;
    st.wDay = 1;
#if defined(UNICODE)
    if ( QSysInfo::WindowsVersion & QSysInfo::WV_NT_based ) {
	TCHAR buf[255];
	if ( GetDateFormat( LOCALE_USER_DEFAULT, 0, &st, L"MMM", (TCHAR*)&buf, 255 ) )
	  //	    return qt_winQString( &buf );
	  return QString::fromLocal8Bit( (char *)&buf ) ;
    } else
#endif
    {
	char buf[255];
	if ( GetDateFormatA( LOCALE_USER_DEFAULT, 0, &st, "MMM", (char*)&buf, 255 ) )
	    return QString::fromLocal8Bit( buf );
    }
#endif

    return QString::null;
}




Qhijri Qhijri::currentDate()
{
#if defined(Q_OS_WIN32)

    SYSTEMTIME t;
    memset( &t, 0, sizeof(SYSTEMTIME) );
    GetLocalTime( &t );
    Qhijri d;
    d.GregorianToHijri(t.wYear,t.wMonth,t.wDay);
    d.jd=HijriToJulian(d.year(),d.month(),d.day());
    return d;

#else

    time_t ltime;
    time( &ltime );
    tm *t = localtime( &ltime );
    Qhijri d;
    d.GregorianToHijri( t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
    d.jd=HijriToJulian(d.year(),d.month(),d.day());

    //cout << d.jd;

    return d;

#endif
}


void Qhijri::GregorianToHijri(int yg,int mg, int dg)
{
  int yh,mh,dh,dayweek;
  G2HA(yg,mg,dg,&yh,&mh,&dh,&dayweek);
  jd=HijriToJulian(yh,mh,dh);
}



double Qhijri::HijriToJulian(int yh,int mh,int dh)
{
  double JD;
  JD=HCalendarToJDA(yh,mh,dh);
  return JD;
}


void Qhijri::JulianToHijri(double JD,int *y,int *m,int *d)
{
  JDToHACalendar(JD ,y ,m ,d );
}

//****************************************************
/*

Qhijri::Qhijri()
Construct anull date

*/
//******************************************************
bool Qhijri::setYMD(int y,int m,int d)
{
  if(isValid(y,m,d)!=0)
    {
      jd=HijriToJulian(y,m,d);

      //cout << jd;

      return TRUE;
    }
  else return FALSE;
}
 

int MonthMap[]={19410
	    ,19396,19337,19093,13613,13741,15210,18132,19913,19858,19110
	    ,18774,12974,13677,13162,15189,19114,14669,13469,14685,12986
	    ,13749,17834,15701,19098,14638,12910,13661,15066,18132,18085
	    };
short gmonth[14]={31,31,28,31,30,31,30,31,31,30,31,30,31,31};/* makes it circular m[0]=m[12] & m[13]=m[1] */
short smonth[14]={31,30,30,30,30,30,29,31,31,31,31,31,31,30}; /* makes it circular m[0]=m[12] & m[13]=m[1]  */


/****************************************************************************/
/* Name:    BH2GA                                                            */
/* Type:    Procedure                                                       */
/* Purpose: Finds Gdate(year,month,day) for Hdate(year,month,day=1)  	    */
/* Arguments:                                                               */
/* Input: Hijrah  date: year:yh, month:mh                                   */
/* Output: Gregorian date: year:yg, month:mg, day:dg , day of week:dayweek  */
/*       and returns flag found:1 not found:0                               */
/****************************************************************************/
int Qhijri::BH2GA(int yh,int mh,int *yg,int *mg, int *dg,int *dayweek)
{

  int flag;
  long JD;
  double GJD;
   /* Make sure that the date is within the range of the tables */
  if(mh<1) {mh=12;}
  if(mh>12) {mh=1;}
  if(yh<HStartYear) {yh=HStartYear;}
  if(yh>HEndYear)   {yh=HEndYear;}

   GJD=HCalendarToJDA(yh,mh,1);
   JDToGCalendar(GJD,yg,mg,dg);
   JD=GJD;
   *dayweek=(JD+1)%7;
   flag=1; /* date has been found */


 return flag;

}
/****************************************************************************/
/* Name:    HCalendarToJDA						    */
/* Type:    Function                                                        */
/* Purpose: convert Hdate(year,month,day) to Exact Julian Day     	    */
/* Arguments:                                                               */
/* Input : Hijrah  date: year:yh, month:mh, day:dh                          */
/* Output:  The Exact Julian Day: JD                                        */
/****************************************************************************/
double Qhijri::HCalendarToJDA(int yh,int mh,int dh)
{
  int flag,Dy,m,b;
  long JD;
  double GJD;

   JD=HCalendarToJD(yh,1,1);  /* estimate JD of the begining of the year */
   Dy=MonthMap[yh-HStartYear]/4096;  /* Mask 1111000000000000 */
   GJD=JD-3+Dy;   /* correct the JD value from stored tables  */
   b=MonthMap[yh-HStartYear];
   b=b-Dy*4096;
   for(m=1;m<mh;m++)
   {
    flag=b%2;  /* Mask for the current month */
    if(flag) Dy=30; else Dy=29;
    GJD=GJD+Dy;   /* Add the months lengths before mh */
    b=(b-flag)/2;
   }
   GJD=GJD+dh-1;

   return GJD;
}
/****************************************************************************/
/* Name:    HMonthLength						    */
/* Type:    Function                                                        */
/* Purpose: Obtains the month length            		     	    */
/* Arguments:                                                               */
/* Input : Hijrah  date: year:yh, month:mh                                  */
/* Output:  Month Length                                                    */
/****************************************************************************/
int Qhijri::HMonthLength(int yh,int mh)
{
  int flag,Dy,m,b;

  if(yh<HStartYear || yh>HEndYear)
  {
   flag=0;
   Dy=0;
  }
 else
  {
   Dy=MonthMap[yh-HStartYear]/4096;  /* Mask 1111000000000000 */
   b=MonthMap[yh-HStartYear];
   b=b-Dy*4096;
    for(m=1;m<=mh;m++)
     {
      flag=b%2;  /* Mask for the current month */
      if(flag) Dy=30; else Dy=29;
      b=(b-flag)/2;
     }
   }
   return Dy;
}

/****************************************************************************/
/* Name:    DayInYear							    */
/* Type:    Function                                                        */
/* Purpose: Obtains the day number in the yea          		     	    */
/* Arguments:                                                               */
/* Input : Hijrah  date: year:yh, month:mh  day:dh                          */
/* Output:  Day number in the Year					    */
/****************************************************************************/
int Qhijri::DayinYear(int yh,int mh,int dh)
{
  int flag,Dy,m,b,DL;

  if(yh<HStartYear || yh>HEndYear)
  {
   flag=0;
   DL=0;
  }
 else
  {
   Dy=MonthMap[yh-HStartYear]/4096;  /* Mask 1111000000000000 */
   b=MonthMap[yh-HStartYear];
   b=b-Dy*4096;
   DL=0;
    for(m=1;m<=mh;m++)
     {
      flag=b%2;  /* Mask for the current month */
      if(flag) Dy=30; else Dy=29;
      b=(b-flag)/2;
      DL=DL+Dy;
     }
   DL=DL+dh;
   }

   return DL;
}

/****************************************************************************/
/* Name:    HYearLength						    	    */
/* Type:    Function                                                        */
/* Purpose: Obtains the year length            		     	    	    */
/* Arguments:                                                               */
/* Input : Hijrah  date: year:yh                                  	    */
/* Output:  Year Length                                                     */
/****************************************************************************/
int Qhijri::HYearLength(int yh)
{
  int flag,Dy,m,b,YL;

  if(yh<HStartYear || yh>HEndYear)
  {
   flag=0;
   YL=0;
  }
 else
  {
   Dy=MonthMap[yh-HStartYear]/4096;  /* Mask 1111000000000000 */
   b=MonthMap[yh-HStartYear];
   b=b-Dy*4096;
   flag=b%2;  /* Mask for the current month */
   if(flag) YL=30; else YL=29;
    for(m=2;m<=12;m++)
     {
      flag=b%2;  /* Mask for the current month */
      if(flag) Dy=30; else Dy=29;
      b=(b-flag)/2;
      YL=YL+Dy;
     }
   }

   return YL;
}

/****************************************************************************/
/* Name:    G2HA                                                            */
/* Type:    Procedure                                                       */
/* Purpose: convert Gdate(year,month,day) to Hdate(year,month,day)          */
/* Arguments:                                                               */
/* Input: Gregorian date: year:yg, month:mg, day:dg                         */
/* Output: Hijrah  date: year:yh, month:mh, day:dh, day of week:dayweek     */
/*       and returns flag found:1 not found:0                               */
/****************************************************************************/
int Qhijri::G2HA(int yg,int mg, int dg,int *yh,int *mh,int *dh,int *dayweek)
{
   int  yh1,mh1,dh1;
   int  yh2,mh2;
   int  yg1,mg1,dg1;
   int  df,dw2;
  int flag;
  long J;
  double GJD,HJD;


    GJD=GCalendarToJD(yg,mg,dg+0.5);  /* find JD of Gdate */
    JDToHCalendar(GJD,&yh1,&mh1,&dh1);  /* estimate the Hdate that correspond to the Gdate */
    HJD=HCalendarToJDA(yh1,mh1,dh1);   // get the exact Julian Day
    df=GJD-HJD;
    dh1=dh1+df;
    while(dh1>30)
    {
     dh1=dh1-HMonthLength(yh1,mh1);
     mh1++;
     if(mh1>12) {yh1++;mh1=1;}
    }
   if(dh1==30)
   {
    mh2=mh1+1;
    yh2=yh1;
    if(mh2>12) {mh2=1;yh2++;}
    BH2GA(yh2,mh2,&yg1,&mg1,&dg1,&dw2);
    if(dg==dg1) {yh1=yh2;mh1=mh2;dh1=1;}  /* Make sure that the month is 30days if not make adjustment */
   }
   J=(GCalendarToJD(yg,mg,dg)+2);
   *dayweek=J%7;
   *yh=yh1;
   *mh=mh1;
   *dh=dh1;


  return flag;



}
/****************************************************************************/
/* Name:    H2GA                                                            */
/* Type:    Procedure                                                       */
/* Purpose: convert Hdate(year,month,day) to Gdate(year,month,day)          */
/* Arguments:                                                               */
/* Input/Ouput: Hijrah  date: year:yh, month:mh, day:dh                     */
/* Output: Gregorian date: year:yg, month:mg, day:dg , day of week:dayweek  */
/*       and returns flag found:1 not found:0                               */
/* Note: The function will correct Hdate if day=30 and the month is 29 only */
/****************************************************************************/
int Qhijri::H2GA(int *yh,int *mh,int *dh, int *yg,int *mg, int *dg,int *dayweek)
{
    int found,yh1,mh1,yg1,mg1,dg1,dw1;

    /* make sure values are within the allowed values */
    if(*dh>30) {*dh=1;(*mh)++;}
    if(*dh<1)  {*dh=1;(*mh)--;}
    if(*mh>12) {*mh=1;(*yh)++;}
    if(*mh<1)  {*mh=12;(*yh)--;}

	 /*find the date of the begining of the month*/
    found=BH2GA(*yh,*mh,yg,mg,dg,dayweek);
    *dg=*dg+*dh-1;
    GDateAjust(yg,mg,dg);    /* Make sure that dates are within the correct values */
    *dayweek=*dayweek+*dh-1;
    *dayweek=*dayweek%7;

	 /*find the date of the begining of the next month*/
   if(*dh==30)
   {
    mh1=*mh+1;
    yh1=*yh;
    if(mh1>12) {mh1=mh1-12;yh1++;}
    found=BH2GA(yh1,mh1,&yg1,&mg1,&dg1,&dw1);
    if(*dg==dg1) {*yh=yh1;*mh=mh1;*dh=1;}  /* Make sure that the month is 30days if not make adjustment */
   }

   return found;
}
/****************************************************************************/
/* Name:    JDToGCalendar						    */
/* Type:    Procedure                                                       */
/* Purpose: convert Julian Day  to Gdate(year,month,day)                    */
/* Arguments:                                                               */
/* Input:  The Julian Day: JD                                               */
/* Output: Gregorian date: year:yy, month:mm, day:dd                        */
/****************************************************************************/
double Qhijri::JDToGCalendar(double JD, int *yy,int *mm, int *dd)
{
double A, B, F;
int alpha, C, E;
long D, Z;

  Z = (long)floor (JD + 0.5);
  F = (JD + 0.5) - Z;
  alpha = (int)((Z - 1867216.25) / 36524.25);
  A = Z + 1 + alpha - alpha / 4;
  B = A + 1524;
  C = (int) ((B - 122.1) / 365.25);
  D = (long) (365.25 * C);
  E = (int) ((B - D) / 30.6001);
  *dd = B - D - floor (30.6001 * E) + F;
  if (E < 14)
    *mm = E - 1;
  else
    *mm = E - 13;
  if (*mm > 2)
    *yy = C - 4716;
  else
   *yy = C - 4715;

  F=F*24.0;
  return F;
}
/****************************************************************************/
/* Name:    GCalendarToJD						    */
/* Type:    Function                                                        */
/* Purpose: convert Gdate(year,month,day) to Julian Day            	    */
/* Arguments:                                                               */
/* Input : Gregorian date: year:yy, month:mm, day:dd                        */
/* Output:  The Julian Day: JD                                              */
/****************************************************************************/
double Qhijri::GCalendarToJD(int yy,int mm, double dd)
{        /* it does not take care of 1582correction assumes correct calender from the past  */
int A, B, m, y;
double T1,T2,Tr;
  if (mm > 2) {
    y = yy;
    m = mm;
    }
  else {
    y = yy - 1;
    m = mm + 12;
    }
  A = y / 100;
  B = 2 - A + A / 4;
  T1=ip (365.25 * (y + 4716));
  T2=ip (30.6001 * (m + 1));
  Tr=T1+ T2 + dd + B - 1524.5 ;

  return Tr;
}
/****************************************************************************/
/* Name:    GLeapYear						            */
/* Type:    Function                                                        */
/* Purpose: Determines if  Gdate(year) is leap or not            	    */
/* Arguments:                                                               */
/* Input : Gregorian date: year				                    */
/* Output:  0:year not leap   1:year is leap                                */
/****************************************************************************/
int Qhijri::GLeapYear(int year)
{

  int T;

     T=0;
     if(year%4==0) T=1; /* leap_year=1; */
     if(year%100==0)
       {
	 T=0;        /* years=100,200,300,500,... are not leap years */
	 if(year%400==0) T=1;  /*  years=400,800,1200,1600,2000,2400 are leap years */
       }

  return T;

}
/****************************************************************************/
/* Name:    GDateAjust							    */
/* Type:    Procedure                                                       */
/* Purpose: Adjust the G Dates by making sure that the month lengths        */
/*	    are correct if not so take the extra days to next month or year */
/* Arguments:                                                               */
/* Input: Gregorian date: year:yg, month:mg, day:dg                         */
/* Output: corrected Gregorian date: year:yg, month:mg, day:dg              */
/****************************************************************************/
void Qhijri::GDateAjust(int *yg,int *mg,int *dg)
{
   int dys;

   /* Make sure that dates are within the correct values */
	  /*  Underflow  */
	 if(*mg<1)  /* months underflow */
	  {
	   *mg=12+*mg;  /* plus as the underflow months is negative */
	   *yg=*yg-1;
	  }

	 if(*dg<1)  /* days underflow */
	  {
	   *mg= *mg-1;  /* month becomes the previous month */
	   *dg=gmonth[*mg]+*dg; /* number of days of the month less the underflow days (it is plus as the sign of the day is negative) */
	   if(*mg==2) *dg=*dg+GLeapYear(*yg);
	   if(*mg<1)  /* months underflow */
	    {
	     *mg=12+*mg;  /* plus as the underflow months is negative */
	     *yg=*yg-1;
	    }
	  }

	  /* Overflow  */
	 if(*mg>12)  /* months */
	  {
	   *mg=*mg-12;
	   *yg=*yg+1;
	  }

	 if(*mg==2)
	     dys=gmonth[*mg]+GLeapYear(*yg);  /* number of days in the current month */
	   else
	     dys=gmonth[*mg];
	 if(*dg>dys)  /* days overflow */
	  {
	     *dg=*dg-dys;
	     *mg=*mg+1;
	    if(*mg==2)
	     {
	      dys=gmonth[*mg]+GLeapYear(*yg);  /* number of days in the current month */
	      if(*dg>dys)
	       {
		*dg=*dg-dys;
		*mg=*mg+1;
	       }
	     }
	    if(*mg>12)  /* months */
	    {
	     *mg=*mg-12;
	     *yg=*yg+1;
	    }

	  }


}
/*
  The day of the week is obtained as
  Dy=(Julian+1)%7
  Dy=0 Sunday
  Dy=1 Monday
  ...
  Dy=6 Saturday
*/

int Qhijri::DayWeek(long JulianD)
{
  int Dy;
  Dy=(JulianD+1)%7;

  return Dy;
}

/****************************************************************************/
/* Name:    HCalendarToJD						    */
/* Type:    Function                                                        */
/* Purpose: convert Hdate(year,month,day) to estimated Julian Day     	    */
/* Arguments:                                                               */
/* Input : Hijrah  date: year:yh, month:mh, day:dh                          */
/* Output:  The Estimated Julian Day: JD                                    */
/****************************************************************************/
double Qhijri::HCalendarToJD(int yh,int mh,int dh)
{
 /*
   Estimating The JD for hijrah dates
   this is an approximate JD for the given hijrah date
 */
 double md,yd;
 md=(mh-1.0)*29.530589;
 yd=(yh-1.0)*354.367068+md+dh-1.0;
 yd=yd+1948439.0;  /*  add JD for 18/7/622 first Hijrah date */

 return yd;
}
/****************************************************************************/
/* Name:    JDToHCalendar						    */
/* Type:    Procedure                                                       */
/* Purpose: convert Julian Day to estimated Hdate(year,month,day)	    */
/* Arguments:                                                               */
/* Input:  The Julian Day: JD                                               */
/* Output : Hijrah date: year:yh, month:mh, day:dh                          */
/****************************************************************************/
void Qhijri::JDToHCalendar(double JD,int *yh,int *mh,int *dh)
{
 /*
   Estimating the hijrah date from JD
 */
 double md,yd;

 yd=JD-1948439.0;  /*  subtract JD for 18/7/622 first Hijrah date*/
 md=mod(yd,354.367068);
 *dh=mod(md+0.5,29.530589)+1;
 *mh=(md/29.530589)+1;
 yd=yd-md;
 *yh=yd/354.367068+1;
 if(*dh>30) {*dh=*dh-30;(*mh)++;}
 if(*mh>12) {*mh=*mh-12;(*yh)++;}

}
/****************************************************************************/
/* Name:    JDToHACalendar						    */
/* Type:    Procedure                                                       */
/* Purpose: convert Julian Day to  Hdate(year,month,day)	    	     */
/* Arguments:                                                               */
/* Input:  The Julian Day: JD                                               */
/* Output : Hijrah date: year:yh, month:mh, day:dh                          */
/****************************************************************************/
void Qhijri::JDToHACalendar(double JD,int *yh,int *mh,int *dh)
{
   int  yh1,mh1,dh1;
   //int  yh2,mh2,dh2;
   //int  yg1,mg1,dg1;
   //int  yg2,mg2,dg2;
   int  df;
   //int flag;
   //long J;
  double HJD;


    JDToHCalendar(JD,&yh1,&mh1,&dh1);  /* estimate the Hdate that correspond to the Gdate */
    HJD=HCalendarToJDA(yh1,mh1,dh1);   // get the exact Julian Day
    df=JD+0.5-HJD;
    dh1=dh1+df;
    while(dh1>30)
    {
     dh1=dh1-HMonthLength(yh1,mh1);
     mh1++;
     if(mh1>12) {yh1++;mh1=1;}
    }
   if(dh1==30 && HMonthLength(yh1,mh1)<30)
   {
    dh1=1;mh1++;
   }
   if(mh1>12)
   {
    mh1=1;yh1++;
   }

//   J=JD+2;  *dayweek=J%7;
   *yh=yh1;
   *mh=mh1;
   *dh=dh1;

}

/**************************************************************************/
double Qhijri::ip(double x)
{ /* Purpose: return the integral part of a double value.     */
double  tmp;

   modf(x, &tmp);
  return tmp;
}
/**************************************************************************/
/*
  Name: mod
  Purpose: The mod operation for doubles  x mod y
*/
int Qhijri::mod(double x, double y)
{
  int r;
  double d;

  d=x/y;
  r=d;
  if(r<0) r--;
  d=x-y*r;
  r=d;
 return r;
}

/**************************************************************************/
int Qhijri::IsValid(int yh, int mh, int dh)
{ /* Purpose: returns 0 for incorrect Hijri date and 1 for correct date      */
  int valid;
  valid=1;
  if(yh<HStartYear ||   yh>HEndYear)     valid=0;
  if(mh<1 || mh>12 || dh<1)
      valid=0;
   else
     if(dh>HMonthLength(yh,mh))   valid=0;

  return valid;
}
