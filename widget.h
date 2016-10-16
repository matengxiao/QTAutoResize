#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "AutoResize.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    AutoResize *m_autoResizeHandler;
    void resizeEvent(QResizeEvent * event);
};

#endif // WIDGET_H
