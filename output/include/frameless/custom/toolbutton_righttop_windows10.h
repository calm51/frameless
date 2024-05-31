#ifndef TOOLBUTTON_RIGHTTOP_WINDOWS10_H
#define TOOLBUTTON_RIGHTTOP_WINDOWS10_H

#include <QToolButton>
#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>

#include "../__frameless_include__.h"

FRAMELESS_BEGIN_NAMESPACE

namespace RIGHTTOP_TYPE {
    enum __type__ {
        Minimize=1,
        Maximize=2,
        Close=3
    };
};

class LIB_EXPORT ToolButton_righttop_windows10 : public QToolButton
{
    Q_OBJECT
public:
    ToolButton_righttop_windows10(QWidget*parent=nullptr);
    ~ToolButton_righttop_windows10();

    RIGHTTOP_TYPE::__type__ type = RIGHTTOP_TYPE::__type__::Minimize;

    QPixmap p;
    bool _is_most_right = false;

    void paintEvent(QPaintEvent *event);
};

FRAMELESS_END_NAMESPACE

#endif // TOOLBUTTON_RIGHTTOP_WINDOWS10_H
