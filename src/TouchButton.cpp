/**
 * @file TouchButton.cpp
 */
#include <utility>

#include "TouchButton.hpp"
#include "Sprite.hpp"


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

TouchButton::TouchButton(Sprite* image) : Widget(), sprite(image)
{
    
}

void TouchButton::init(Sprite* image, int x, int y, double seconde)
{
	this->sprite = image;
	this->x() = x;
	this->y() = y;
	this->setActivationTime(seconde);
}

bool TouchButton::isUnderCursor(UNUSED(const Cursor& cursor))
{
    return this->changeFirstActivation(cursor.x() >= x() && cursor.x() <= (x() + sprite->cols) && cursor.y() >= y() && cursor.y() <= (y() + sprite->rows));
}

void TouchButton::action()
{
    // à implémenter pour les classes supérieures
    mtl::log::info("Action réalisée pour le TouchButton");
}

void TouchButton::draw(UNUSED(Sprite& frame))
{
    blit(frame, *(this->sprite), this->x(), this->y());
}



