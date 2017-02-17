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
    return cursor.x() >= x() && cursor.x() <= (x() + sprite->cols) && cursor.y() >= y() && cursor.y() <= (y() + sprite->rows);
}

void TouchButton::action()
{
	mtl::log::info("Bouton activé");
}

void TouchButton::draw(UNUSED(Sprite& frame))
{
    blit(frame, *(this->sprite), this->x(), this->y());
}

void TouchButton::update(void)
{
	if(this->isActivated())
	{
		this->action();
	}
}

void TouchButton::updateTime(const CursorSet& cursors)
{
	bool under = false;

	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
	{
		if(this->isUnderCursor(cursors.getCursor((PlayerMember) p)))
			under = true;
	}

	this->changeFirstActivation(under);
}



