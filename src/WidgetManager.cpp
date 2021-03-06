#include "WidgetManager.hpp"
#include "clamp.hpp"

Widget::Widget() : firstActiveTime(0), pourcent(0)
{

}

Widget::~Widget()
{

}

bool Widget::isUnderCursor(UNUSED(const Cursor& cursor))
{
    return changeFirstActivation(false);
}

bool Widget::changeFirstActivation(bool underCursor)
{
    if (underCursor)
    {
        if (this->firstActiveTime == 0)
            time(&this->firstActiveTime);
    }
    else
    {
        this->pourcent = 0.0;
        this->firstActiveTime = 0;
    }

    return underCursor;
}

void Widget::setActivationTime(double seconde)
{
    this->activationTime = seconde;
}

bool Widget::isActivated()
{
    if(this->activationTime <= .0f || this->firstActiveTime == 0)
        return false;

    time_t timer;
    timer = time(NULL);

    this->pourcent = difftime(timer, this->firstActiveTime) / static_cast<double>(this->activationTime - 1.0f);
    clamp(this->pourcent, 0.0, 1.0);

    return (this->pourcent >= 1.0);
}

void Widget::update(void)
{
    
}

void Widget::updateTime(UNUSED(const CursorSet &cursors))
{

}

void Widget::action()
{

}

void Widget::draw(UNUSED(cv::Mat& frame))
{

}

uint32_t Widget::x() const
{
    return _x;
}
uint32_t& Widget::x()
{
    return _x;
}
uint32_t Widget::y() const
{
    return _y;
}
uint32_t& Widget::y()
{
    return _y;
}


/////////////////
WidgetManager::WidgetManager(void) noexcept
{

}

WidgetManager::~WidgetManager(void)
{

}

void WidgetManager::updateWidgets(void)
{
    std::for_each(this->widgets.begin(), this->widgets.end(), [](Widget * w) {
        w->update();
    });
}

void WidgetManager::updateTime(const CursorSet& cursors)
{
    std::for_each(this->widgets.begin(), this->widgets.end(), [&cursors](Widget * w) {
        w->updateTime(cursors);
    });
}

void WidgetManager::draw(cv::Mat& frame)
{
    std::for_each(this->widgets.begin(), this->widgets.end(), [&frame](Widget * w) {
        w->draw(frame);
    });
}

int WidgetManager::size()
{
    return static_cast<int>(this->widgets.size());
}

WidgetManager& WidgetManager::addWidget(Widget* widget)
{
    this->widgets.push_back(widget);
    return *this;
}
