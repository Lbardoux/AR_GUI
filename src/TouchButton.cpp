/**
 * @file TouchButton.cpp
 */
#include <utility>

#include "TouchButton.hpp"


TouchButton::TouchButton(void) : Widget(), sprite(nullptr)
{
    
}

TouchButton::TouchButton(const TouchButton& other) : TouchButton()
{
    this->sprite = other.sprite;
    
}

TouchButton::TouchButton(TouchButton&& other) : TouchButton(other)
{
    std::swap(this->sprite, other.sprite);
    
}

TouchButton::TouchButton(const cv::Mat* image) : Widget(), sprite(image)
{
    
}

bool TouchButton::isUnderCursor(UNUSED(const Cursor& cursor)) const
{
    
}

bool TouchButton::isActivated() const
{
    // A refaire éventuellement
    return true;
}

void TouchButton::action()
{
    // à implémenter pour les classes supérieures
}

void TouchButton::draw(UNUSED(cv::Mat& frame))
{
    
}



