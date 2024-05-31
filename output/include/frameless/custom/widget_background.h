#ifndef WIDGET_BACKGROUND_H
#define WIDGET_BACKGROUND_H

#include <QObject>
#include <QWidget>

#include "../__frameless_include__.h"

FRAMELESS_BEGIN_NAMESPACE

class LIB_EXPORT Widget_background : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_background(QWidget *parent = nullptr);
    ~Widget_background();
signals:

};

FRAMELESS_END_NAMESPACE

#endif // WIDGET_BACKGROUND_H


