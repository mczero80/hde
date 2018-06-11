/****************************************************************************
 **
 **				hdestyle.h
 **			=========================
 **
 **  begin                : Wed Jan 01 2003
 **  copyright            : (C) 2003 -2006 by Haydar Alkaduhimi
 **  email                : haydar@haydarnet.nl
 **
 **  The primary style for libhde.
 **
 ****************************************************************************/


#include "hdestyle.h"
#include <QtGui>


/*
// from windows style
static const int windowsItemFrame        =  2; // menu item frame width
static const int windowsSepHeight        =  6; // separator item height
static const int windowsItemHMargin      =  3; // menu item hor text margin
static const int windowsItemVMargin      =  8; // menu item ver text margin
static const int windowsArrowHMargin     =  6; // arrow horizontal margin
static const int windowsTabSpacing       = 12; // space between text and tab
static const int windowsCheckMarkHMargin =  2; // horiz. margins of check mark
static const int windowsRightBorder      = 15; // right border on windows
static const int windowsCheckMarkWidth   = 12; // checkmarks width on windows
*/
enum Direction {
    TopDown,
    FromLeft,
    BottomUp,
    FromRight
};


static const char * const qt_scrollbar_button_arrow_left[] = {
    "4 7 2 1",
    "   c None",
    "*  c #000000",
    "   *",
    "  **",
    " ***",
    "****",
    " ***",
    "  **",
    "   *"};

static const char * const qt_scrollbar_button_arrow_right[] = {
    "4 7 2 1",
    "   c None",
    "*  c #000000",
    "*   ",
    "**  ",
    "*** ",
    "****",
    "*** ",
    "**  ",
    "*   "};

static const char * const qt_scrollbar_button_arrow_up[] = {
    "7 4 2 1",
    "   c None",
    "*  c #000000",
    "   *   ",
    "  ***  ",
    " ***** ",
    "*******"};

static const char * const qt_scrollbar_button_arrow_down[] = {
    "7 4 2 1",
    "   c None",
    "*  c #000000",
    "*******",
    " ***** ",
    "  ***  ",
    "   *   "};




class hdeStylePlugin : public QStylePlugin
{
public:
  QStringList keys() const {
    return QStringList() << "hde";
  }
  
  QStyle *create(const QString &key) {
    if (key == "hde")
      return new hdeStyle;
    return 0;
  }
};

Q_EXPORT_PLUGIN(hdeStylePlugin);

hdeStyle::hdeStyle(void) : QCommonStyle()
{ 
  winstyle = QStyleFactory::create("Windows");
  
  if(!winstyle) {
    // We don't have the Windows style, neither builtin nor as a plugin.
    // Use any style rather than crashing.
    winstyle = QStyleFactory::create(*(QStyleFactory::keys().begin()));
  }
  hdestyle = QPixmap::defaultDepth() > 8;
}


hdeStyle::~hdeStyle()
{
}

void hdeStyle::polish(QWidget* widget)
{
    if (qobject_cast<QAbstractButton*>(widget)
#ifndef QT_NO_COMBOBOX
        || qobject_cast<QComboBox *>(widget)
#endif
#ifndef QT_NO_PROGRESSBAR
        || qobject_cast<QProgressBar *>(widget)
#endif
#ifndef QT_NO_SCROLLBAR
        //|| qobject_cast<QScrollBar *>(widget)
#endif
#ifndef QT_NO_SPLITTER
        || qobject_cast<QSplitterHandle *>(widget)
#endif
        || qobject_cast<QAbstractSlider *>(widget)
#ifndef QT_NO_SPINBOX
        || qobject_cast<QAbstractSpinBox *>(widget)
#endif
        || (widget->inherits("QWorkspaceChild"))
        || (widget->inherits("QDockSeparator"))
        || (widget->inherits("QDockWidgetSeparator"))
        ) {
        widget->setAttribute(Qt::WA_Hover, true);
    }
}

void hdeStyle::polish ( QApplication * app )
{
  winstyle->polish(app);     
}

void hdeStyle::polish ( QPalette & pal )
{
  winstyle->polish(pal);
}

void hdeStyle::unpolish(QWidget* widget)
{
    if (qobject_cast<QAbstractButton*>(widget)
#ifndef QT_NO_COMBOBOX
        || qobject_cast<QComboBox *>(widget)
#endif
#ifndef QT_NO_PROGRESSBAR
        || qobject_cast<QProgressBar *>(widget)
#endif
#ifndef QT_NO_SCROLLBAR
        //|| qobject_cast<QScrollBar *>(widget)
#endif
#ifndef QT_NO_SPLITTER
        || qobject_cast<QSplitterHandle *>(widget)
#endif
        || qobject_cast<QAbstractSlider *>(widget)
#ifndef QT_NO_SPINBOX
        || qobject_cast<QAbstractSpinBox *>(widget)
#endif
        || (widget->inherits("QWorkspaceChild"))
        || (widget->inherits("QDockSeparator"))
        || (widget->inherits("QDockWidgetSeparator"))
        ) {
        widget->setAttribute(Qt::WA_Hover, false);
    }
}

void hdeStyle::unpolish ( QApplication * app ) 
{
//  app->removeEventFilter(this);
  winstyle->unpolish(app);
     
}


static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50)
{
    const int maxFactor = 100;
    QColor tmp = colorA;
    tmp.setRed((tmp.red() * factor) / maxFactor + (colorB.red() * (maxFactor - factor)) / maxFactor);
    tmp.setGreen((tmp.green() * factor) / maxFactor + (colorB.green() * (maxFactor - factor)) / maxFactor);
    tmp.setBlue((tmp.blue() * factor) / maxFactor + (colorB.blue() * (maxFactor - factor)) / maxFactor);
    return tmp;
}


static void hdeStyle_draw_gradient(QPainter *painter, const QRect &rect, const QColor &gradientStart,
                                        const QColor &gradientStop, Direction direction = TopDown, QBrush bgBrush = QBrush())
{
        int x = rect.center().x();
        int y = rect.center().y();
        QLinearGradient *gradient;
        switch(direction) {
            case FromLeft:
                gradient = new QLinearGradient(rect.left(), y, rect.right(), y);
                break;
            case FromRight:
                gradient = new QLinearGradient(rect.right(), y, rect.left(), y);
                break;
            case BottomUp:
                gradient = new QLinearGradient(x, rect.bottom(), x, rect.top());
            case TopDown:
            default:
                gradient = new QLinearGradient(x, rect.top(), x, rect.bottom());
                break;
        }
        if (bgBrush.gradient())
            gradient->setStops(bgBrush.gradient()->stops());
        else {
            gradient->setColorAt(0, gradientStart);
            gradient->setColorAt(1, gradientStop);
        }
        painter->fillRect(rect, *gradient);
        delete gradient;
}

static QString uniqueName(const QString &key, const QStyleOption *option, const QSize &size)
{
    QString tmp;
    const QStyleOptionComplex *complexOption = qstyleoption_cast<const QStyleOptionComplex *>(option);
    tmp.sprintf("%s-%d-%d-%d-%dx%d", key.toLatin1().constData(), uint(option->state),
                complexOption ? uint(complexOption->activeSubControls) : uint(0),
                option->palette.serialNumber(), size.width(), size.height());
#ifndef QT_NO_SPINBOX
    if (const QStyleOptionSpinBox *spinBox = qstyleoption_cast<const QStyleOptionSpinBox *>(option)) {
        tmp.append(QLatin1Char('-'));
        tmp.append(QString::number(spinBox->buttonSymbols));
        tmp.append(QLatin1Char('-'));
        tmp.append(QString::number(spinBox->stepEnabled));
        tmp.append(QLatin1Char('-'));
        tmp.append(QLatin1Char(spinBox->frame ? '1' : '0'));
    }
#endif // QT_NO_SPINBOX
    return tmp;
}


void hdeStyle::drawComplexControl( ComplexControl control, 
				   const QStyleOptionComplex * option,
				   QPainter * painter,
				   const QWidget * widget ) const
{
    QColor button = option->palette.button().color();
    QColor dark;
    QColor grooveColor;
    QColor darkOutline;
    dark.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*1.9)),
                qMin(255, (int)(button.value()*0.7)));
    grooveColor.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*2.6)),
                qMin(255, (int)(button.value()*0.9)));
    darkOutline.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*3.0)),
                qMin(255, (int)(button.value()*0.6)));

    QColor alphaCornerColor;
    if (widget) {
        // ### backgroundrole/foregroundrole should be part of the style option
        alphaCornerColor = mergedColors(option->palette.color(widget->backgroundRole()), darkOutline);
    } else {
        alphaCornerColor = mergedColors(option->palette.background().color(), darkOutline);
    }
    QColor gripShadow = grooveColor.dark(110);
    QColor buttonShadow = option->palette.button().color().dark(110);

    QColor gradientStartColor = option->palette.button().color().light(108);
    QColor gradientStopColor = mergedColors(option->palette.button().color().dark(108), dark.light(150), 70);

    QColor highlightedGradientStartColor = option->palette.button().color();
    QColor highlightedGradientStopColor = mergedColors(option->palette.button().color(), option->palette.highlight().color(), 85);

    QColor highlightedDarkInnerBorderColor = mergedColors(option->palette.button().color(), option->palette.highlight().color(), 35);
    QColor highlightedLightInnerBorderColor = mergedColors(option->palette.button().color(), option->palette.highlight().color(), 58);

    QColor buttonShadowAlpha = option->palette.background().color().dark(105);

    QPalette palette = option->palette;

    switch (control) {
#ifndef QT_NO_SCROLLBAR
    case CC_ScrollBar:
        painter->save();
        if (const QStyleOptionSlider *scrollBar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            bool isEnabled = scrollBar->state & State_Enabled;
            bool reverse = scrollBar->direction == Qt::RightToLeft;
            bool horizontal = scrollBar->orientation == Qt::Horizontal;
            bool sunken = scrollBar->state & State_Sunken;

            painter->fillRect(option->rect, option->palette.background());

            painter->setPen(darkOutline);
            QRect rect = scrollBar->rect;
            painter->drawRect( rect.adjusted(0,0,-1,-1) );
            //painter->drawLine(rect.topLeft() , rect.bottomLeft());
            
            QRect scrollBarSubLine = subControlRect(control, scrollBar, SC_ScrollBarSubLine, widget);
            QRect scrollBarAddLine = subControlRect(control, scrollBar, SC_ScrollBarAddLine, widget);
            QRect scrollBarSlider = subControlRect(control, scrollBar, SC_ScrollBarSlider, widget);
            QRect grooveRect = subControlRect(control, scrollBar, SC_ScrollBarGroove, widget);

            // paint groove
            if (scrollBar->subControls & SC_ScrollBarGroove) {
                painter->setBrush(grooveColor);
                painter->setPen(Qt::NoPen);
                if (horizontal) {
                    painter->drawRect(grooveRect);
                    painter->setPen(darkOutline);
                    painter->drawLine(grooveRect.topLeft(), grooveRect.topRight());
                    painter->drawLine(grooveRect.bottomLeft(), grooveRect.bottomRight());
                } else {
                    painter->drawRect(grooveRect);
                    painter->setPen(darkOutline);
                    painter->drawLine(grooveRect.topLeft(), grooveRect.bottomLeft());
                    painter->drawLine(grooveRect.topRight(), grooveRect.bottomRight());
                }
            }
            //paint slider
            if (scrollBar->subControls & SC_ScrollBarSlider) {
                QRect pixmapRect = scrollBarSlider;
                if (horizontal)
                    pixmapRect.adjust(-1, 0, 0, -1);
                else
                    pixmapRect.adjust(0, -1, -1, 0);

                if (isEnabled) {
                    QLinearGradient gradient(pixmapRect.center().x(), pixmapRect.top(),
                                             pixmapRect.center().x(), pixmapRect.bottom());
                    if (!horizontal)
                        gradient = QLinearGradient(pixmapRect.left(), pixmapRect.center().y(),
                                                   pixmapRect.right(), pixmapRect.center().y());

                    if (option->palette.button().gradient()) {
                        gradient.setStops(option->palette.button().gradient()->stops());
                    } else {
                        if (sunken || (option->state & State_MouseOver &&
                            (scrollBar->activeSubControls & SC_ScrollBarSlider))) {
                            gradient.setColorAt(0, gradientStartColor.light(110));
                            gradient.setColorAt(1, gradientStopColor.light(110));
                        } else {
                            gradient.setColorAt(0, gradientStartColor);
                            gradient.setColorAt(1, gradientStopColor);
                        }
                    }
                    painter->setPen(QPen(darkOutline, 0));
                    painter->setBrush(gradient);
                    painter->drawRect(pixmapRect);


                    //calculate offsets used by highlight and shadow
                    int yoffset, xoffset;
                    if (option->state & State_Horizontal) {
                        xoffset = 0;
                        yoffset = 1;
                    } else {
                        xoffset = 1;
                        yoffset = 0;
                    }
                    //draw slider highlights
                    painter->setPen(QPen(gradientStopColor, 0));
                    painter->drawLine(scrollBarSlider.left() + xoffset,
                                      scrollBarSlider.bottom() - yoffset,
                                      scrollBarSlider.right() - xoffset,
                                      scrollBarSlider.bottom() - yoffset);
                    painter->drawLine(scrollBarSlider.right() - xoffset,
                                      scrollBarSlider.top() + yoffset,
                                      scrollBarSlider.right() - xoffset,
                                      scrollBarSlider.bottom() - yoffset);

                    //draw slider shadow
                    painter->setPen(QPen(gradientStartColor, 0));
                    painter->drawLine(scrollBarSlider.left() + xoffset,
                                      scrollBarSlider.top() + yoffset,
                                      scrollBarSlider.right() - xoffset,
                                      scrollBarSlider.top() + yoffset);
                    painter->drawLine(scrollBarSlider.left() + xoffset,
                                      scrollBarSlider.top() + yoffset,
                                      scrollBarSlider.left() + xoffset,
                                      scrollBarSlider.bottom() - yoffset);
                } else {
                    QLinearGradient gradient(pixmapRect.center().x(), pixmapRect.top(),
                                             pixmapRect.center().x(), pixmapRect.bottom());
                    if (!horizontal) {
                        gradient = QLinearGradient(pixmapRect.left(), pixmapRect.center().y(),
                                                   pixmapRect.right(), pixmapRect.center().y());
                    }
                    if (sunken) {
                        gradient.setColorAt(0, gradientStartColor.light(110));
                        gradient.setColorAt(1, gradientStopColor.light(110));
                    } else {
                        gradient.setColorAt(0, gradientStartColor);
                        gradient.setColorAt(1, gradientStopColor);
                    }
                    painter->setPen(darkOutline);
                    painter->setBrush(gradient);
                    painter->drawRect(pixmapRect);
                }
                int gripMargin = 4;
                //draw grips
                if (horizontal) {
                    for (int i = -3; i< 6 ; i += 3) {
                        painter->setPen(QPen(gripShadow, 1));
                        painter->drawLine(
                            QPoint(scrollBarSlider.center().x() + i ,
                                   scrollBarSlider.top() + gripMargin),
                            QPoint(scrollBarSlider.center().x() + i,
                                   scrollBarSlider.bottom() - gripMargin));
                        painter->setPen(QPen(palette.light(), 1));
                        painter->drawLine(
                            QPoint(scrollBarSlider.center().x() + i + 1,
                                   scrollBarSlider.top() + gripMargin  ),
                            QPoint(scrollBarSlider.center().x() + i + 1,
                                   scrollBarSlider.bottom() - gripMargin));
                    }
                } else {
                    for (int i = -3; i < 6 ; i += 3) {
                        painter->setPen(QPen(gripShadow, 1));
                        painter->drawLine(
                            QPoint(scrollBarSlider.left() + gripMargin ,
                                   scrollBarSlider.center().y()+ i),
                            QPoint(scrollBarSlider.right() - gripMargin,
                                   scrollBarSlider.center().y()+ i));
                        painter->setPen(QPen(palette.light(), 1));
                        painter->drawLine(
                            QPoint(scrollBarSlider.left() + gripMargin,
                                   scrollBarSlider.center().y() + 1 + i),
                            QPoint(scrollBarSlider.right() - gripMargin,
                                   scrollBarSlider.center().y() + 1 + i));
                    }
                }
                
            }

            // The SubLine (down/right) button            
            if (scrollBar->subControls & SC_ScrollBarAddLine) {
                //QRect pixmapRect = scrollBarAddLine;
                if (isEnabled ) {
                    int x1 = scrollBarAddLine.x()+1;
                    int y1 = scrollBarAddLine.y();
                    int x2 = scrollBarAddLine.x()+scrollBarAddLine.width()-2;
                    int y2 = scrollBarAddLine.y()+scrollBarAddLine.height()-2;
                    if (horizontal){
                       x1 = scrollBarAddLine.x();             
                    }

                    if (horizontal){
                       x1 = x1+1;
                       x2 = x2+1;
                       y1 = y1+1;
                       y2 = y2+1;             
                    }
                    QRect fillRect = scrollBarAddLine.adjusted(1, 0, -1, -1);
                    if(horizontal)
                        fillRect = scrollBarAddLine.adjusted(1, 1, -1, -1);

                    // Gradients
                    if ((scrollBar->activeSubControls & SC_ScrollBarAddLine) && sunken) {
                        hdeStyle_draw_gradient(painter,
                                                    fillRect,
                                                    gradientStopColor.dark(105),
                                                    gradientStartColor.dark(105),
                                                    TopDown, option->palette.button());
                        
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y1, x2,  y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    } else {
                        hdeStyle_draw_gradient(painter,
                                                    fillRect,
                                                    gradientStartColor,
                                                    gradientStopColor,
                                                    TopDown, option->palette.button());
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y1, x2, y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    }
                }
                //
                    if (horizontal){
                       QRect pixRect = scrollBarAddLine.adjusted(6,5,0,0);
                       pixRect.setWidth(4);
                       pixRect.setHeight(7);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_right) );
                    }else{
                       QRect pixRect = scrollBarAddLine.adjusted(4,6,0,0);
                       pixRect.setWidth(7);
                       pixRect.setHeight(4);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_down) );
                    }                    
                
            }
            
            // The SubLine (up/left) buttons
            if (scrollBar->subControls & SC_ScrollBarSubLine) {
                //int scrollBarExtent = pixelMetric(PM_ScrollBarExtent, option, widget);
                QRect firstRect = scrollBarSubLine;
                if (horizontal)
                  firstRect.setWidth(16);
                else
                  firstRect.setHeight(16);
                QRect secondRect = scrollBarSubLine;
                if (horizontal)
                  secondRect.setX(scrollBarSubLine.width() - 16);
                else
                  secondRect.setY(scrollBarSubLine.height() - 15);

                if (isEnabled ) {
                    // First Buttom
                    int x1 = firstRect.x()+1;
                    int y1 = firstRect.y()+1;
                    int x2 = firstRect.x()+firstRect.width()-2;
                    int y2 = firstRect.y()+firstRect.height()-1;

                  //QRect fillRect = pixmapRect.adjusted(1, 1, -1, -1);
                    // Gradients
                    if ((scrollBar->activeSubControls & SC_ScrollBarSubLine) && sunken) {
                        hdeStyle_draw_gradient(painter,
                                                    firstRect.adjusted(1,1,-1,0),
                                                    gradientStopColor.dark(105),
                                                    gradientStartColor.dark(105),
                                                    TopDown, option->palette.button());
                        
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y1, x2, y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    } else {
                        hdeStyle_draw_gradient(painter,
                                                    firstRect.adjusted(1,1,-1,0),
                                                    gradientStartColor,
                                                    gradientStopColor,
                                                    TopDown, option->palette.button());
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y1, x2,  y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    }

                    if (horizontal){
                       QRect pixRect = firstRect.adjusted(6,5,0,0);
                       pixRect.setWidth(4);
                       pixRect.setHeight(7);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_left) );
                    }else{
                       QRect pixRect = firstRect.adjusted(4,6,0,0);
                       pixRect.setWidth(7);
                       pixRect.setHeight(4);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_up) );
                    }                    
                    // Second Buttom
                    x1 = secondRect.x()+1;
                    y1 = secondRect.y();
                    x2 = secondRect.x()+secondRect.width()-2;
                    y2 = secondRect.y()+secondRect.height()-1;
                  //QRect fillRect = pixmapRect.adjusted(1, 1, -1, -1);
                    if (horizontal){
                       //x1 = x1+1;
                       x2 = x2+1;
                       y1 = y1+1;
                       //y2 = y2+1;             
                    }
                    QRect fillRect = secondRect.adjusted(1, 0, -1, 0);
                    if(horizontal)
                        fillRect = secondRect.adjusted(1, 1, -1, -1);

                    // Gradients
                    if ((scrollBar->activeSubControls & SC_ScrollBarSubLine) && sunken) {
                        hdeStyle_draw_gradient(painter,
                                                    fillRect,
                                                    gradientStopColor.dark(105),
                                                    gradientStartColor.dark(105),
                                                    TopDown, option->palette.button());
                        
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y1, x2,  y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    } else {
                        hdeStyle_draw_gradient(painter,
                                                    fillRect,
                                                    gradientStartColor,
                                                    gradientStopColor,
                                                    TopDown, option->palette.button());
                        painter->setPen(option->palette.light().color());
                        painter->drawLine(x1, y1, x2, y1);
                        painter->drawLine(x1, y1, x1, y2);
                        painter->setPen(option->palette.dark().color());
                        painter->drawLine(x1, y2, x2, y2);
                        painter->drawLine(x2, y1, x2, y2);
                    }
                    
                    if (horizontal){
                       QRect pixRect = secondRect.adjusted(6,5,0,0);
                       pixRect.setWidth(4);
                       pixRect.setHeight(7);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_left) );
                    }else{
                       QRect pixRect = secondRect.adjusted(4,6,0,0);
                       pixRect.setWidth(7);
                       pixRect.setHeight(4);
                       painter->drawPixmap(pixRect , QPixmap(qt_scrollbar_button_arrow_up) );
                    }                    
                }
            }
        }
        painter->restore();
        break;;
#endif // QT_NO_SCROLLBAR
        default:
            winstyle->drawComplexControl(control, option, painter, widget);
        break;
    }
}

void hdeStyle::drawControl ( ControlElement element, 
			     const QStyleOption * option, QPainter * painter, 
			     const QWidget * widget) const
{
    QColor button = option->palette.button().color();
    QColor dark;
    dark.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*1.9)),
                qMin(255, (int)(button.value()*0.7)));
    QColor darkOutline;
    darkOutline.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*2.0)),
                qMin(255, (int)(button.value()*0.6)));
    QRect rect = option->rect;
    QColor shadow = mergedColors(option->palette.background().color().dark(120),
                                 dark.light(130), 60);
    //QColor tabFrameColor = mergedColors(option->palette.background().color(),
      //                                          dark.light(135), 60);

    QColor highlight = option->palette.highlight().color();
    QColor highlightText = option->palette.highlightedText().color();

    switch(element) {
    case CE_MenuBarItem:
        painter->save();
        if (const QStyleOptionMenuItem *mbi = qstyleoption_cast<const QStyleOptionMenuItem *>(option))
        {
            QStyleOptionMenuItem item = *mbi;
            item.rect = mbi->rect.adjusted(0, 3, 0, -1);
            QColor highlightOutline = highlight.dark(125);
/*
            QColor highlightOutline = highlight.dark(125);
            QLinearGradient gradient(rect.topLeft(), QPoint(rect.bottomLeft().x(), rect.bottomLeft().y()*2));

            if (option->palette.button().gradient()) {
                gradient.setStops(option->palette.button().gradient()->stops());
            } else {
                gradient.setColorAt(0, option->palette.button().color());
                gradient.setColorAt(1, option->palette.button().color().dark(110));
            }
            painter->fillRect(rect, gradient);
*/
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
                QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
                QColor gradientStartColor = option->palette.button().color().light(108);

                QColor buttonColor = option->palette.button().color();
                QColor gradientStopColor;
                gradientStopColor.setHsv(buttonColor.hue(),
                                     qMin(255, (int)(buttonColor.saturation()*1.9)),
                                     qMin(255, (int)(buttonColor.value()*0.94)));

                int x2 = r.x()+r.width();//-1;
	            int y2 = r.y()+r.height();//-1;
                  hdeStyle_draw_gradient(painter, rect/*.adjusted(1, 1, -1, -1)*/,                                          
                                            highlightedGradientStartColor,
                                            highlightedGradientStopColor, TopDown,
                                            option->palette.button());

            QCommonStyle::drawControl(element, &item, painter, widget);

            bool act = mbi->state & State_Selected && mbi->state & State_Sunken;
            //bool act = mbi->state & State_Active;
            bool mover = mbi->state & State_MouseOver;
            bool dis = !(mbi->state & State_Enabled);

            //QRect r = option->rect;
            if (act || mover) {
                hdeStyle_draw_gradient(painter, r.adjusted(1, 1, -1, -1),
                                            highlight,
                                            highlightOutline, TopDown,
                                            option->palette.highlight());

                painter->setPen(QPen(highlightOutline, 0));
                painter->drawLine(QPoint(r.left(), r.top() + 1), QPoint(r.left(), r.bottom()));
                painter->drawLine(QPoint(r.right(), r.top() + 1), QPoint(r.right(), r.bottom()));
                painter->drawLine(QPoint(r.left() + 1, r.bottom()), QPoint(r.right() - 1, r.bottom()));
                painter->drawLine(QPoint(r.left() + 1, r.top()), QPoint(r.right() - 1, r.top()));

                //draw text
                QPalette::ColorRole textRole = dis ? QPalette::Text : QPalette::HighlightedText;
                uint alignment = Qt::AlignCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
                if (!styleHint(SH_UnderlineShortcut, mbi, widget))
                    alignment |= Qt::TextHideMnemonic;
                drawItemText(painter, item.rect, alignment, mbi->palette, mbi->state & State_Enabled, mbi->text, textRole);
            }

        }
        painter->restore();
        break;
/*        
    case CE_MenuItem:
        painter->save();
        // Draws one item in a popup menu.
        if (const QStyleOptionMenuItem *menuItem = qstyleoption_cast<const QStyleOptionMenuItem *>(option)) {
            QColor highlightOutline = highlight.dark(125);
            QColor menuBackground = option->palette.background().color().light(104);
            QColor borderColor = option->palette.background().color().dark(160);
            QColor alphaCornerColor;

            if (widget) {
                // ### backgroundrole/foregroundrole should be part of the style option
                alphaCornerColor = mergedColors(option->palette.color(widget->backgroundRole()), borderColor);
            } else {
                alphaCornerColor = mergedColors(option->palette.background().color(), borderColor);
            }
            QColor alphaTextColor = mergedColors(option->palette.background().color(), option->palette.text().color());
            if (menuItem->menuItemType == QStyleOptionMenuItem::Separator) {
                painter->fillRect(menuItem->rect, menuBackground);
                int w = 0;
                if (!menuItem->text.isEmpty()) {
                    painter->setFont(menuItem->font);
                    drawItemText(painter, menuItem->rect.adjusted(5, 0, -5, 0), Qt::AlignLeft | Qt::AlignVCenter,
                                 menuItem->palette, menuItem->state & State_Enabled, menuItem->text,
                                 QPalette::Text);
                    w = menuItem->fontMetrics.width(menuItem->text) + 5;
                }
                painter->setPen(shadow.light(106));
                bool reverse = menuItem->direction == Qt::RightToLeft;
                painter->drawLine(menuItem->rect.left() + 5 + (reverse ? 0 : w), menuItem->rect.center().y(),
                                  menuItem->rect.right() - 5 - (reverse ? w : 0), menuItem->rect.center().y());
                painter->restore();
                break;
            }
            bool selected = menuItem->state & State_Selected && menuItem->state & State_Enabled;
            if (selected) {
                QRect r = option->rect.adjusted(1, 0, -2, -1);
                hdeStyle_draw_gradient(painter, r, highlight,
                                            highlightOutline, TopDown,
                                            highlight);
                r = r.adjusted(-1, 0, 1, 0);
                painter->setPen(QPen(highlightOutline, 0));
                painter->drawLine(QPoint(r.left(), r.top() + 1), QPoint(r.left(), r.bottom() - 1));
                painter->drawLine(QPoint(r.right(), r.top() + 1), QPoint(r.right(), r.bottom() - 1));
                painter->drawLine(QPoint(r.left() + 1, r.bottom()), QPoint(r.right() - 1, r.bottom()));
                painter->drawLine(QPoint(r.left() + 1, r.top()), QPoint(r.right() - 1, r.top()));
            } else {
                painter->fillRect(option->rect, menuBackground);
            }

            bool checkable = menuItem->checkType != QStyleOptionMenuItem::NotCheckable;
            bool checked = menuItem->checked;
            bool sunken = menuItem->state & State_Sunken;
            bool enabled = menuItem->state & State_Enabled;

            bool ignoreCheckMark = false;
            int checkcol = qMax(menuItem->maxIconWidth, 20);

#ifndef QT_NO_COMBOBOX
            if (qobject_cast<const QComboBox*>(widget))
                ignoreCheckMark = true; //ignore the checkmarks provided by the QComboMenuDelegate
#endif

            if (!ignoreCheckMark) {
                // Check
                QRect checkRect(option->rect.left() + 7, option->rect.center().y() - 6, 13, 13);
                checkRect = visualRect(menuItem->direction, menuItem->rect, checkRect);
                if (checkable) {
                    if (menuItem->checkType & QStyleOptionMenuItem::Exclusive) {
                        // Radio button
                        if (checked || sunken) {
                            painter->setRenderHint(QPainter::Antialiasing);
                            painter->setPen(Qt::NoPen);

                            QPalette::ColorRole textRole = !enabled ? QPalette::Text:
                                                        selected ? QPalette::HighlightedText : QPalette::ButtonText;
                            painter->setBrush(option->palette.brush( option->palette.currentColorGroup(), textRole));
                            painter->drawEllipse(checkRect.adjusted(4, 4, -4, -4));
                        }
                    } else {
                        // Check box
                        if (menuItem->icon.isNull()) {
                                if (checked || sunken) {
                                QImage image(hdeStyle_menuitem_checkbox_checked);
                                if (menuItem->state & State_Selected) {
                                    image.setColor(1, 0x55ffffff);
                                    image.setColor(2, 0xAAffffff);
                                    image.setColor(3, 0xBBffffff);
                                    image.setColor(4, 0xFFffffff);
                                    image.setColor(5, 0x33ffffff);
                                } else {
                                    image.setColor(1, 0x55000000);
                                    image.setColor(2, 0xAA000000);
                                    image.setColor(3, 0xBB000000);
                                    image.setColor(4, 0xFF000000);
                                    image.setColor(5, 0x33000000);
                                }
                                painter->drawImage(QPoint(checkRect.center().x() - image.width() / 2,
                                                        checkRect.center().y() - image.height() / 2), image);
                            }
                            
                        } else if (checked) {
                            int iconSize = qMax(menuItem->maxIconWidth, 20);
                            QRect sunkenRect(option->rect.left() + 2,
                                            option->rect.top() + (option->rect.height() - iconSize) / 2,
                                            iconSize, iconSize);
                            sunkenRect = visualRect(menuItem->direction, menuItem->rect, sunkenRect);

                            QStyleOption opt = *option;
                            opt.state |= State_Sunken;
                            opt.rect = sunkenRect;
                        }
                    }
                }
            } else { //ignore checkmark
                if (menuItem->icon.isNull())
                    checkcol = 0;
                else
                    checkcol = menuItem->maxIconWidth;
            }

            // Text and icon, ripped from windows style
            bool dis = !(menuItem->state & State_Enabled);
            bool act = menuItem->state & State_Selected;
            const QStyleOption *opt = option;
            const QStyleOptionMenuItem *menuitem = menuItem;

            QPainter *p = painter;
            QRect vCheckRect = visualRect(opt->direction, menuitem->rect,
                                          QRect(menuitem->rect.x(), menuitem->rect.y(),
                                                checkcol, menuitem->rect.height()));
            if (!menuItem->icon.isNull()) {
                QIcon::Mode mode = dis ? QIcon::Disabled : QIcon::Normal;
                if (act && !dis)
                    mode = QIcon::Active;
                QPixmap pixmap;
                if (checked)
                    pixmap = menuItem->icon.pixmap(pixelMetric(PM_SmallIconSize), mode, QIcon::On);
                else
                    pixmap = menuItem->icon.pixmap(pixelMetric(PM_SmallIconSize), mode);
                int pixw = pixmap.width();
                int pixh = pixmap.height();

                QRect pmr(0, 0, pixw, pixh);
                pmr.moveCenter(vCheckRect.center());
                painter->setPen(menuItem->palette.text().color());
                if (checkable && checked)
                    painter->drawPixmap(QPoint(pmr.left() + 1, pmr.top() + 1), pixmap);
                else
                    painter->drawPixmap(pmr.topLeft(), pixmap);
            }
            if (selected) {
                painter->setPen(menuItem->palette.highlightedText().color());
            } else {
                painter->setPen(menuItem->palette.text().color());
            }
            int x, y, w, h;
            menuitem->rect.getRect(&x, &y, &w, &h);
            int tab = menuitem->tabWidth;
            QColor discol;
            if (dis) {
                discol = menuitem->palette.text().color();
                p->setPen(discol);
            }
            int xm = windowsItemFrame + checkcol + windowsItemHMargin;
            int xpos = menuitem->rect.x() + xm;

            QRect textRect(xpos, y + windowsItemVMargin, w - xm - windowsRightBorder - tab + 1, h - 2 * windowsItemVMargin);
            QRect vTextRect = visualRect(opt->direction, menuitem->rect, textRect);
            QString s = menuitem->text;
            if (!s.isEmpty()) {                     // draw text
                p->save();
                int t = s.indexOf(QLatin1Char('\t'));
                int text_flags = Qt::AlignVCenter | Qt::TextShowMnemonic | Qt::TextDontClip | Qt::TextSingleLine;
                if (!styleHint(SH_UnderlineShortcut, menuitem, widget))
                    text_flags |= Qt::TextHideMnemonic;
                text_flags |= Qt::AlignLeft;
                if (t >= 0) {
                    QRect vShortcutRect = visualRect(opt->direction, menuitem->rect,
                                                     QRect(textRect.topRight(), QPoint(menuitem->rect.right(), textRect.bottom())));
                    if (dis && !act) {
                        p->setPen(menuitem->palette.light().color());
                        p->drawText(vShortcutRect.adjusted(1, 1, 1, 1), text_flags, s.mid(t + 1));
                        p->setPen(discol);
                    }
                    p->drawText(vShortcutRect, text_flags, s.mid(t + 1));
                    s = s.left(t);
                }
                QFont font = menuitem->font;

                if (menuitem->menuItemType == QStyleOptionMenuItem::DefaultItem)
                    font.setBold(true);

                p->setFont(font);
                if (dis && !act) {
                    p->setPen(menuitem->palette.light().color());
                    p->drawText(vTextRect.adjusted(1, 1, 1, 1), text_flags, s.left(t));
                    p->setPen(discol);
                }
                p->drawText(vTextRect, text_flags, s.left(t));
                p->restore();
            }

            // Arrow
            if (menuItem->menuItemType == QStyleOptionMenuItem::SubMenu) {// draw sub menu arrow
                int dim = (menuItem->rect.height() - 4) / 2;
                PrimitiveElement arrow;
                arrow = QApplication::isRightToLeft() ? PE_IndicatorArrowLeft : PE_IndicatorArrowRight;
                int xpos = menuItem->rect.left() + menuItem->rect.width() - 1 - dim;
                QRect  vSubMenuRect = visualRect(option->direction, menuItem->rect,
                                                 QRect(xpos, menuItem->rect.top() + menuItem->rect.height() / 2 - dim / 2, dim, dim));
                QStyleOptionMenuItem newMI = *menuItem;
                newMI.rect = vSubMenuRect;
                newMI.state = !enabled ? State_None : State_Enabled;
                if (selected)
                    newMI.palette.setColor(QPalette::ButtonText,
                                           newMI.palette.highlightedText().color());
                drawPrimitive(arrow, &newMI, painter, widget);
            }
        }
        painter->restore();
        break;
        
        
    case CE_MenuHMargin:
    case CE_MenuVMargin:
        break;
    case CE_MenuEmptyArea:
        break;
        */
    case CE_MenuBarEmptyArea:
        painter->save();
        {
/*
            QColor shadow = mergedColors(option->palette.background().color().dark(120),
                                 dark.light(140), 60);

            QLinearGradient gradient(rect.topLeft(), QPoint(rect.bottomLeft().x(), rect.bottomLeft().y()*2));
            gradient.setColorAt(0, option->palette.button().color());
            gradient.setColorAt(1, option->palette.button().color().dark(110));
            painter->fillRect(rect, gradient);
*/
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
                QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
                QColor gradientStartColor = option->palette.button().color().light(108);

                QColor buttonColor = option->palette.button().color();
                QColor gradientStopColor;
                gradientStopColor.setHsv(buttonColor.hue(),
                                     qMin(255, (int)(buttonColor.saturation()*1.9)),
                                     qMin(255, (int)(buttonColor.value()*0.94)));

                int x2 = r.x()+r.width()-1;
	            int y2 = r.y()+r.height()-1;
                  hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                                            highlightedGradientStartColor,
                                            highlightedGradientStopColor, TopDown,
                                            option->palette.button());

#ifndef QT_NO_MAINWINDOW
            if (widget && qobject_cast<const QMainWindow *>(widget->parentWidget())) {
                QPen oldPen = painter->pen();
                painter->setPen(QPen(shadow));
                painter->drawLine(option->rect.bottomLeft(), option->rect.bottomRight());
            }
#endif // QT_NO_MAINWINDOW
        }
        painter->restore();
        break;


        /***************************************************************************
        *
        * Toolbar
        *
        **************************************************************************/
#ifndef QT_NO_TOOLBAR
    case CE_ToolBar:
       {
           painter->save();
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
           QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
           QColor gradientStartColor = option->palette.button().color().light(108);

           QColor buttonColor = option->palette.button().color();
           QColor gradientStopColor;
           gradientStopColor.setHsv(buttonColor.hue(),
                    qMin(255, (int)(buttonColor.saturation()*1.9)),
                    qMin(255, (int)(buttonColor.value()*0.94)));

           int x2 = r.x()+r.width()-1;
	       int y2 = r.y()+r.height()-1;
	       if((r.width() < r.height()))
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, FromLeft,
                        option->palette.button());
           else
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, TopDown,
                        option->palette.button());

                                            
           painter->setPen(option->palette.light().color());
	       painter->drawLine(r.x(), r.y(), x2-1,  r.y());
	       painter->drawLine(r.x(), r.y(), r.x(), y2-1);
	       painter->setPen(option->palette.dark().color());
	       painter->drawLine(r.x(), y2, x2, y2);
	       painter->drawLine(x2, r.y(), x2, y2);
	

           painter->restore();
        }
        break;
#endif // QT_NO_TOOLBAR

#ifdef QT3_SUPPORT
    case CE_Q3DockWindowEmptyArea:
       {
           painter->save();
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
           QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
           QColor gradientStartColor = option->palette.button().color().light(108);

           QColor buttonColor = option->palette.button().color();
           QColor gradientStopColor;
           gradientStopColor.setHsv(buttonColor.hue(),
                    qMin(255, (int)(buttonColor.saturation()*1.9)),
                    qMin(255, (int)(buttonColor.value()*0.94)));

           int x2 = r.x()+r.width()-1;
	       int y2 = r.y()+r.height()-1;
	       if((r.width() < r.height()))
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, FromLeft,
                        option->palette.button());
           else
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, TopDown,
                        option->palette.button());

                                            
           painter->setPen(option->palette.light().color());
	       painter->drawLine(r.x(), r.y(), x2-1,  r.y());
	       painter->drawLine(r.x(), r.y(), r.x(), y2-1);
	       painter->setPen(option->palette.dark().color());
	       painter->drawLine(r.x(), y2, x2, y2);
	       painter->drawLine(x2, r.y(), x2, y2);
	

           painter->restore();
       }
       break;
#endif

    case CE_PushButton:
       {
           painter->save();
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
           QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
           QColor gradientStartColor = option->palette.button().color().light(108);

           QColor buttonColor = option->palette.button().color();
           QColor gradientStopColor;

           bool sunken = false;
           bool flat = false;
           bool hover = false;
           bool defaultButton = false;
           if (const QStyleOptionButton *button = qstyleoption_cast<const QStyleOptionButton *>(option)) {
              sunken = (button->state & State_Sunken) || (button->state & State_On);
              if ((button->features & QStyleOptionButton::Flat) && !sunken)
                  flat = true;

              defaultButton = (button->features & (QStyleOptionButton::DefaultButton
                                                      | QStyleOptionButton::AutoDefaultButton));

            
              //QPen oldPen = p->pen();
              hover = (button->state & State_Enabled) && (button->state & State_MouseOver);
           }
           
           if(flat){
              winstyle->drawControl ( CE_PushButtonLabel, option, painter, widget);  
              break;
           }
           gradientStopColor.setHsv(buttonColor.hue(),
                    qMin(255, (int)(buttonColor.saturation()*1.9)),
                    qMin(255, (int)(buttonColor.value()*0.94)));

           int x2 = r.x()+r.width()-1;
	       int y2 = r.y()+r.height()-1;
	       
	       if(sunken)
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                     highlightedGradientStartColor.dark(115),
                     highlightedGradientStopColor.dark(115), TopDown,
                     option->palette.button());
           else if(hover)
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                     highlightedGradientStartColor.light(105),
                     highlightedGradientStopColor.light(105), TopDown,
                     option->palette.button());
           else
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                     highlightedGradientStartColor,
                     highlightedGradientStopColor, TopDown,
                     option->palette.button());
                                            
	       if(sunken){
              painter->setPen(option->palette.dark().color());
	          painter->drawLine(r.x()+1, r.y(), x2-2,  r.y());
	          painter->drawLine(r.x(), r.y()+1, r.x(), y2-2);
	          painter->setPen(option->palette.light().color());
	          painter->drawLine(r.x()+1, y2, x2-1, y2);
	          painter->drawLine(x2, r.y()+1, x2, y2-1);
           }else if(defaultButton){
              painter->setPen(option->palette.light().color().light());
	          painter->drawLine(r.x()+1, r.y(), x2-2,  r.y());
	          painter->drawLine(r.x(), r.y()+1, r.x(), y2-2);
	          painter->setPen(option->palette.dark().color().dark());
	          painter->drawLine(r.x()+1, y2, x2-1, y2);
	          painter->drawLine(x2, r.y()+1, x2, y2-1);           
           }else{
              painter->setPen(option->palette.light().color());
	          painter->drawLine(r.x()+1, r.y(), x2-2,  r.y());
	          painter->drawLine(r.x(), r.y()+1, r.x(), y2-2);
	          painter->setPen(option->palette.dark().color());
	          painter->drawLine(r.x()+1, y2, x2-1, y2);
	          painter->drawLine(x2, r.y()+1, x2, y2-1);
           }
           option->rect.adjusted(1, 1, -1, -1);
           winstyle->drawControl ( CE_PushButtonLabel, option, painter, widget);  
           painter->restore();
       }
       break;

    default:
       winstyle->drawControl ( element, option, painter, widget);  
       break;
    }
}

void hdeStyle::drawItemPixmap ( QPainter * painter, const QRect & rect,
				int alignment, 
				const QPixmap & pixmap ) const
{
  winstyle->drawItemPixmap ( painter, rect, alignment, pixmap );      
}
 
void hdeStyle::drawItemText ( QPainter * painter, const QRect & rect, 
			      int alignment, const QPalette & pal, 
			      bool enabled, const QString & text,
			      QPalette::ColorRole textRole) const
{
  winstyle->drawItemText ( painter, rect, alignment, pal, enabled, text, 
			   textRole);  
}



void hdeStyle::drawPrimitive(PrimitiveElement element, 
			     const QStyleOption *option,
			     QPainter *painter, const QWidget *widget) const
{
         
    Q_ASSERT(option);
    QRect rect = option->rect;
    int state = option->state;
    QColor button = option->palette.button().color();
    QColor buttonShadow = option->palette.button().color().dark(110);
    QColor buttonShadowAlpha = buttonShadow;
    buttonShadowAlpha.setAlpha(128);
    QColor darkOutline;
    QColor dark;
    darkOutline.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*3.0)),
                qMin(255, (int)(button.value()*0.6)));
    dark.setHsv(button.hue(),
                qMin(255, (int)(button.saturation()*1.9)),
                qMin(255, (int)(button.value()*0.7)));
    //QColor tabFrameColor = mergedColors(option->palette.background().color(),
      //                                          dark.light(135), 60);

    switch(element) {

     case PE_FrameMenu:
        painter->save();
        {
            painter->setPen(QPen(darkOutline, 1));
            painter->drawRect(option->rect.adjusted(0, 0, -1, -1));
            QColor frameLight = option->palette.background().color().light(160);
            QColor frameShadow = option->palette.background().color().dark(110);

            //paint beveleffect
            QRect frame = option->rect.adjusted(1, 1, -1, -1);
            painter->setPen(frameLight);
            painter->drawLine(frame.topLeft(), frame.bottomLeft());
            painter->drawLine(frame.topLeft(), frame.topRight());

            painter->setPen(frameShadow);
            painter->drawLine(frame.topRight(), frame.bottomRight());
            painter->drawLine(frame.bottomLeft(), frame.bottomRight());
        }
        painter->restore();
        break;

    case PE_FrameDockWidget:
       {
           painter->save();
           QRect r = option->rect;
           QColor ligt = option->palette.light().color();
           QColor highlightedGradientStartColor = option->palette.button().color().light(107);
           QColor highlightedGradientStopColor = option->palette.button().color().dark(110).light(107);
           QColor gradientStartColor = option->palette.button().color().light(108);

           QColor buttonColor = option->palette.button().color();
           QColor gradientStopColor;
           gradientStopColor.setHsv(buttonColor.hue(),
                    qMin(255, (int)(buttonColor.saturation()*1.9)),
                    qMin(255, (int)(buttonColor.value()*0.94)));

           int x2 = r.x()+r.width()-1;
	       int y2 = r.y()+r.height()-1;
	       if((r.width() < r.height()))
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, FromLeft,
                        option->palette.button());
           else
              hdeStyle_draw_gradient(painter, rect.adjusted(1, 1, -1, -1),                                          
                        highlightedGradientStartColor,
                        highlightedGradientStopColor, TopDown,
                        option->palette.button());

                                            
           painter->setPen(option->palette.light().color());
	       painter->drawLine(r.x(), r.y(), x2-1,  r.y());
	       painter->drawLine(r.x(), r.y(), r.x(), y2-1);
	       painter->setPen(option->palette.dark().color());
	       painter->drawLine(r.x(), y2, x2, y2);
	       painter->drawLine(x2, r.y(), x2, y2);
	

           painter->restore();
       }
       break;
/*
    case PE_FrameDockWidget:

        painter->save();
        {
            QColor softshadow = option->palette.background().color().dark(120);

            QRect rect= option->rect;
            painter->setPen(softshadow);
            painter->drawRect(option->rect.adjusted(0, 0, -1, -1));
            painter->setPen(QPen(option->palette.light(), 0));
            painter->drawLine(QPoint(rect.left() + 1, rect.top() + 1), QPoint(rect.left() + 1, rect.bottom() - 1));
            painter->setPen(QPen(option->palette.background().color().dark(120), 0));
            painter->drawLine(QPoint(rect.left() + 1, rect.bottom() - 1), QPoint(rect.right() - 2, rect.bottom() - 1));
            painter->drawLine(QPoint(rect.right() - 1, rect.top() + 1), QPoint(rect.right() - 1, rect.bottom() - 1));

        }
        painter->restore();
        break;
        */
        
       default:
            winstyle->drawPrimitive(element, option, painter, widget);
        break;
    }
}

QSize hdeStyle::sizeFromContents ( ContentsType type, 
				   const QStyleOption * option, 
				   const QSize & size, 
				   const QWidget * widget ) const
{

    QSize newSize = winstyle->sizeFromContents(type, option, size, widget);

    switch (type) {
#ifndef QT_NO_SCROLLBAR

    case CT_ScrollBar:
        if (const QStyleOptionSlider *scrollBar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            int scrollBarExtent = pixelMetric(PM_ScrollBarExtent, option, widget);
            int scrollBarSliderMinimum = pixelMetric(PM_ScrollBarSliderMin, option, widget);
            if (scrollBar->orientation == Qt::Horizontal) {
                newSize = QSize(16 * 3 + scrollBarSliderMinimum, scrollBarExtent);
            } else {
                newSize = QSize(scrollBarExtent, 16 * 3 + scrollBarSliderMinimum);
            }
        }
        break;

#endif // QT_NO_SCROLLBAR
    default:
        break;
    }

    return newSize;

//  return winstyle->sizeFromContents ( type, option, contentsSize, widget );
}

QIcon hdeStyle::standardIcon( StandardPixmap standardIcon, 
			      const QStyleOption * option, 
			      const QWidget * widget ) const
{
  return winstyle->standardIcon( standardIcon, option, widget ); 
}
/*
QPalette hdeStyle::standardPalette () const
{
  return winstyle->standardPalette();         
} 
*/
QPixmap hdeStyle::standardPixmap ( StandardPixmap standardPixmap, 
				   const QStyleOption * option, 
				   const QWidget * widget ) const
{
  return winstyle->standardPixmap ( standardPixmap, option, widget );
}


int hdeStyle::styleHint ( StyleHint hint, const QStyleOption * option, 
			  const QWidget * widget, 
			  QStyleHintReturn * returnData ) const
{
    int ret = 0;
    switch (hint) {
 
    case SH_EtchDisabledText:
        ret = 1;
        break;
    case SH_MainWindow_SpaceBelowMenuBar:
        ret = 0;
        break;
    case SH_MenuBar_MouseTracking:
        ret = 1;
        break;
    case SH_TitleBar_AutoRaise:
        ret = 1;
        break;
    case SH_TitleBar_NoBorder:
        ret = 1;
        break;
    case SH_ItemView_ShowDecorationSelected:
        ret = true;
        break;
    case SH_Table_GridLineColor:
        if (option) {
            ret = option->palette.background().color().dark(120).rgb();
            break;
        }
    case SH_ComboBox_Popup:
        if (const QStyleOptionComboBox *cmb = qstyleoption_cast<const QStyleOptionComboBox *>(option))
            ret = !cmb->editable;
        else
            ret = 0;
        break;
    case SH_WindowFrame_Mask:
        ret = 1;
        if (QStyleHintReturnMask *mask = qstyleoption_cast<QStyleHintReturnMask *>(returnData)) {
            //left rounded corner
            mask->region = option->rect;
            mask->region -= QRect(option->rect.left(), option->rect.top(), 5, 1);
            mask->region -= QRect(option->rect.left(), option->rect.top() + 1, 3, 1);
            mask->region -= QRect(option->rect.left(), option->rect.top() + 2, 2, 1);
            mask->region -= QRect(option->rect.left(), option->rect.top() + 3, 1, 2);

            //right rounded corner
            mask->region -= QRect(option->rect.right() - 4, option->rect.top(), 5, 1);
            mask->region -= QRect(option->rect.right() - 2, option->rect.top() + 1, 3, 1);
            mask->region -= QRect(option->rect.right() - 1, option->rect.top() + 2, 2, 1);
            mask->region -= QRect(option->rect.right() , option->rect.top() + 3, 1, 2);
        }
        break;
    case SH_DialogButtonLayout:
        ret = QDialogButtonBox::GnomeLayout;
        break;
    case SH_MessageBox_TextInteractionFlags:
        ret = Qt::TextBrowserInteraction;
        break;
    case SH_DialogButtonBox_ButtonsHaveIcons:
        ret = true;
        break;
	/*
    case SH_MessageBox_CenterButtons:
        ret = false;
        break;
	*/
/*    case SH_ScrollBar_MiddleClickAbsolutePosition:
        ret = true;
        break;*/
    default:
        ret = winstyle->styleHint ( hint, option, widget, returnData );   
        break;
    }
    
    return ret;
   
   //     return winstyle->styleHint ( hint, option, widget, returnData );   
}


int hdeStyle::pixelMetric( PixelMetric metric, const QStyleOption * option, 
			   const QWidget * widget ) const
{
    int ret = -1;
    switch (metric) {
    case PM_ScrollBarExtent:
        ret = 16;
        break;
    case PM_ScrollBarSliderMin:
        ret = 26;
        break;

    default:
        break;
    }

    return ret != -1 ? ret : winstyle->pixelMetric(metric, option, widget);

//  return winstyle->pixelMetric( metric, option, widget );    
}

QRect hdeStyle::subControlRect ( ComplexControl control, 
				 const QStyleOptionComplex * option, 
				 SubControl subControl, 
				 const QWidget * widget ) const
{
    QRect rect = winstyle->subControlRect(control, option, subControl, widget);

    switch (control) {
#ifndef QT_NO_SCROLLBAR
	// 3 BUTTON SCROLLBAR
	// -------------------------------------------------------------------
/*
    case CC_ScrollBar: {
	const QScrollBar *sb = (const QScrollBar*)widget;
	
	QRect  addline, subline, subline2, addpage, subpage, slider, first, 
	    last;
	bool   maxedOut   = (sb->minimum()    == sb->maximum());
	bool   horizontal = (sb->orientation() == Qt::Horizontal);
//	SFlags sflags     = ((horizontal ? Style_Horizontal : Style_Default) |
//			     (maxedOut   ? Style_Default : Style_Enabled));

 

	subline = subControlRect ( control, option, SC_ScrollBarSubLine, widget);
	addline = subControlRect ( control, option, SC_ScrollBarAddLine, widget);
	subpage = subControlRect ( control, option, SC_ScrollBarSubPage, widget);
	addpage = subControlRect ( control, option, SC_ScrollBarAddPage, widget);
	slider  = subControlRect ( control, option, SC_ScrollBarSlider,  widget);
	first   = subControlRect ( control, option, SC_ScrollBarFirst,   widget);
	last    = subControlRect ( control, option, SC_ScrollBarLast, widget);
	subline2 = addline;

	if (horizontal)
	    subline2.translate(-addline.width(), 0);
	else
	    subline2.translate(0, -addline.height());

	// Draw the up/left button set
	
	if ((sub & SC_ScrollBarSubLine) && subline.isValid()) {
	    drawPrimitive(PE_ScrollBarSubLine, p, subline, cg,
			  sflags | (subActive == SC_ScrollBarSubLine ?
				    Style_Down : Style_Default));

	    if (subline2.isValid())
		drawPrimitive(PE_ScrollBarSubLine, p, subline2, cg,
                              sflags | (subActive == SC_ScrollBarSubLine ?
					Style_Down : Style_Default));
	}
	
	if ((sub & SC_ScrollBarAddLine) && addline.isValid())
	    drawPrimitive(PE_ScrollBarAddLine, p, addline, cg,
			  sflags | ((subActive == SC_ScrollBarAddLine) ?
				    Style_Down : Style_Default));

	if ((sub & SC_ScrollBarSubPage) && subpage.isValid())
	    drawPrimitive(PE_ScrollBarSubPage, p, subpage, cg,
			  sflags | ((subActive == SC_ScrollBarSubPage) ?
				    Style_Down : Style_Default));

	if ((sub & SC_ScrollBarAddPage) && addpage.isValid())
	    drawPrimitive(PE_ScrollBarAddPage, p, addpage, cg,
			  sflags | ((subActive == SC_ScrollBarAddPage) ?
				    Style_Down : Style_Default));

	if ((sub & SC_ScrollBarFirst) && first.isValid())
	    drawPrimitive(PE_ScrollBarFirst, p, first, cg,
			  sflags | ((subActive == SC_ScrollBarFirst) ?
				    Style_Down : Style_Default));

	if ((sub & SC_ScrollBarLast) && last.isValid())
	    drawPrimitive(PE_ScrollBarLast, p, last, cg,
			  sflags | ((subActive == SC_ScrollBarLast) ?
				    Style_Down : Style_Default));

	if ((sub & SC_ScrollBarSlider) && slider.isValid()) {
	    drawPrimitive(PE_ScrollBarSlider, p, slider, cg,
			  sflags | ((subActive == SC_ScrollBarSlider) ?
				    Style_Down : Style_Default));
				// Draw focus rect
	    if (sb->hasFocus()) {
		QRect fr(slider.x() + 2, slider.y() + 2,
			 slider.width() - 5, slider.height() - 5);
		drawPrimitive(PE_FocusRect, p, fr, cg, Style_Default);
	    }
	} 

	break;
    }
*/

    case CC_ScrollBar:
        if (const QStyleOptionSlider *scrollBar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            int scrollBarExtent = pixelMetric(PM_ScrollBarExtent, scrollBar, widget);
            int sliderMaxLength = ((scrollBar->orientation == Qt::Horizontal) ?
                                   scrollBar->rect.width() : scrollBar->rect.height()) - (16 * 3);
            int sliderMinLength = pixelMetric(PM_ScrollBarSliderMin, scrollBar, widget);
            int sliderLength;

            // calculate slider length
            if (scrollBar->maximum != scrollBar->minimum) {
                uint valueRange = scrollBar->maximum - scrollBar->minimum;
                sliderLength = (scrollBar->pageStep * sliderMaxLength) / (valueRange + scrollBar->pageStep);

                if (sliderLength < sliderMinLength || valueRange > INT_MAX / 2)
                    sliderLength = sliderMinLength;
                if (sliderLength > sliderMaxLength)
                    sliderLength = sliderMaxLength;
            } else {
                sliderLength = sliderMaxLength;
            }

            int sliderStart = 16 + sliderPositionFromValue(scrollBar->minimum,
                                                           scrollBar->maximum,
                                                           scrollBar->sliderPosition,
                                                           sliderMaxLength - sliderLength,
                                                           scrollBar->upsideDown);

            QRect scrollBarRect = scrollBar->rect;

            switch (subControl) {
            case SC_ScrollBarSubLine: // top/left button
                if (scrollBar->orientation == Qt::Horizontal) {
                    rect.setRect(scrollBarRect.left(), scrollBarRect.top(), scrollBarRect.width() - 16, scrollBarExtent);
                } else {
                    rect.setRect(scrollBarRect.left(), scrollBarRect.top(), scrollBarExtent, scrollBarRect.height() - 16);
                }
                break;
            case SC_ScrollBarAddLine: // bottom/right button
                if (scrollBar->orientation == Qt::Horizontal) {
                    rect.setRect(scrollBarRect.right() - 15, scrollBarRect.top(), 16, scrollBarExtent);
                } else {
                    rect.setRect(scrollBarRect.left(), scrollBarRect.bottom() - 15, scrollBarExtent, 16);
                }
                break;
            case SC_ScrollBarSubPage:
                if (scrollBar->orientation == Qt::Horizontal) {
                    rect.setRect(scrollBarRect.left() + 16, scrollBarRect.top(),
                                 sliderStart - (scrollBarRect.left() + 16), scrollBarExtent);
                } else {
                    rect.setRect(scrollBarRect.left(), scrollBarRect.top() + 16,
                                 scrollBarExtent, sliderStart - (scrollBarRect.left() + 16));
                }
                break;
            case SC_ScrollBarAddPage:
                if (scrollBar->orientation == Qt::Horizontal)
                    rect.setRect(sliderStart + sliderLength, 0,
                                 sliderMaxLength - sliderStart - sliderLength + 16, scrollBarExtent);
                else
                    rect.setRect(0, sliderStart + sliderLength,
                                 scrollBarExtent, sliderMaxLength - sliderStart - sliderLength + 16);
                break;
            case SC_ScrollBarGroove:
                if (scrollBar->orientation == Qt::Horizontal) {
                    rect = scrollBarRect.adjusted(16, 0, -32, 0);
                } else {
                    rect = scrollBarRect.adjusted(0, 16, 0, -32);
                }
                break;
            case SC_ScrollBarSlider:
                if (scrollBar->orientation == Qt::Horizontal) {
                    rect.setRect(sliderStart, 0, sliderLength, scrollBarExtent);
                } else {
                    rect.setRect(0, sliderStart, scrollBarExtent, sliderLength);
                }
                break;
            default:
                break;
            }
            rect = visualRect(scrollBar->direction, scrollBarRect, rect);
        }
        break;        
#endif // QT_NO_SCROLLBAR
#ifndef QT_NO_SLIDER
    case CC_Slider:
        if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            int tickSize = pixelMetric(PM_SliderTickmarkOffset, option, widget);

            switch (subControl) {
            case SC_SliderHandle:
                if (slider->orientation == Qt::Horizontal) {
                    rect.setWidth(11);
                    rect.setHeight(15);
                    int centerY = slider->rect.center().y() - rect.height() / 2;
                    if (slider->tickPosition & QSlider::TicksAbove)
                        centerY += tickSize;
                    if (slider->tickPosition & QSlider::TicksBelow)
                        centerY -= tickSize;
                    rect.moveTop(centerY);
                } else {
                    rect.setWidth(15);
                    rect.setHeight(11);
                    int centerX = slider->rect.center().x() - rect.width() / 2;
                    if (slider->tickPosition & QSlider::TicksAbove)
                        centerX += tickSize;
                    if (slider->tickPosition & QSlider::TicksBelow)
                        centerX -= tickSize;
                    rect.moveLeft(centerX);
                }
                break;
            case SC_SliderGroove: {
                QPoint grooveCenter = slider->rect.center();
                if (slider->orientation == Qt::Horizontal) {
                    rect.setHeight(14);
                    --grooveCenter.ry();
                    if (slider->tickPosition & QSlider::TicksAbove)
                        grooveCenter.ry() += tickSize;
                    if (slider->tickPosition & QSlider::TicksBelow)
                        grooveCenter.ry() -= tickSize;
                } else {
                    rect.setWidth(14);
                    --grooveCenter.rx();
                    if (slider->tickPosition & QSlider::TicksAbove)
                        grooveCenter.rx() += tickSize;
                    if (slider->tickPosition & QSlider::TicksBelow)
                        grooveCenter.rx() -= tickSize;
                }
                rect.moveCenter(grooveCenter);
                break;
            }
            default:
                break;
            }
        }
        break;
#endif // QT_NO_SLIDER


    default:
        break;
    }

    return rect;


//  return winstyle->subControlRect ( control, option, subControl, widget );
} 

QRect hdeStyle::subElementRect ( SubElement element, 
				 const QStyleOption * option, 
				 const QWidget * widget) const
{
  return winstyle->subElementRect ( element, option, widget);      
} 

QPalette hdeStyle::standardPalette () const
{
    QPalette palette = winstyle->standardPalette();
    palette.setBrush(QPalette::Active, QPalette::Highlight, QColor(98, 140, 178));
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, QColor(145, 141, 126));
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, QColor(145, 141, 126));

    QColor backGround(239, 235, 231);

    QColor light = backGround.light(150);
    QColor base = Qt::white;
    QColor dark = QColor(170, 156, 143).dark(110);
    dark = backGround.dark(150);
    QColor darkDisabled = QColor(209, 200, 191).dark(110);

    //### Find the correct disabled text color
    palette.setBrush(QPalette::Disabled, QPalette::Text, QColor(190, 190, 190));

    palette.setBrush(QPalette::Window, backGround);
    palette.setBrush(QPalette::Mid, backGround.dark(130));
    palette.setBrush(QPalette::Light, light);

    palette.setBrush(QPalette::Active, QPalette::Base, base);
    palette.setBrush(QPalette::Inactive, QPalette::Base, base);
    palette.setBrush(QPalette::Disabled, QPalette::Base, backGround);

    palette.setBrush(QPalette::Midlight, palette.mid().color().light(110));

    palette.setBrush(QPalette::All, QPalette::Dark, dark);
    palette.setBrush(QPalette::Disabled, QPalette::Dark, darkDisabled);

    QColor button = backGround;

    palette.setBrush(QPalette::Button, button);

    QColor shadow = dark.dark(135);
    palette.setBrush(QPalette::Shadow, shadow);
    palette.setBrush(QPalette::Disabled, QPalette::Shadow, shadow.light(150));
    palette.setBrush(QPalette::HighlightedText, QColor(QRgb(0xffffffff)));
    return palette;
}

QStyle::SubControl hdeStyle::hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                                                          const QPoint &pos, const QWidget *widget) const
{
    SubControl ret = SC_None;
    switch (control) {
#ifndef QT_NO_SCROLLBAR

    case CC_ScrollBar:
        if (const QStyleOptionSlider *scrollBar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            QRect slider = subControlRect(control, scrollBar, SC_ScrollBarSlider, widget);
            if (slider.contains(pos)) {
                ret = SC_ScrollBarSlider;
                break;
            }

            QRect scrollBarAddLine = subControlRect(control, scrollBar, SC_ScrollBarAddLine, widget);
            if (scrollBarAddLine.contains(pos)) {
                ret = SC_ScrollBarAddLine;
                break;
            }

            QRect scrollBarSubPage = subControlRect(control, scrollBar, SC_ScrollBarSubPage, widget);
            if (scrollBarSubPage.contains(pos)) {
                ret = SC_ScrollBarSubPage;
                break;
            }

            QRect scrollBarAddPage = subControlRect(control, scrollBar, SC_ScrollBarAddPage, widget);
            if (scrollBarAddPage.contains(pos)) {
                ret = SC_ScrollBarAddPage;
                break;
            }

            QRect scrollBarSubLine = subControlRect(control, scrollBar, SC_ScrollBarSubLine, widget);
            if (scrollBarSubLine.contains(pos)) {
                ret = SC_ScrollBarSubLine;
                break;
            }
        }
        break;

#endif // QT_NO_SCROLLBAR
    default:
        break;
    }

    return ret != SC_None ? ret : winstyle->hitTestComplexControl(control, option, pos, widget);
}

