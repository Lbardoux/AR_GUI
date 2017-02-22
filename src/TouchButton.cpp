/**
 * @file TouchButton.cpp
 */
#include <utility>

#include "TouchButton.hpp"
#include "Sprite.hpp"


TouchButton::TouchButton(void) : Widget(), sprite(nullptr), membres()
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

TouchButton::~TouchButton()
{
	this->membres.clear();
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

void TouchButton::draw(Sprite& frame)
{
    blit(frame, *(this->sprite), this->x(), this->y());

    if(this->pourcent < 0.05)
    	return;

    int epaisseur = this->sprite->rows / 5;

    int dX = this->x();
    int fX = this->x() + (this->sprite->cols * this->pourcent);
    int y  = this->y() + (this->sprite->rows - (epaisseur / 2));

    cv::line(frame, cv::Point(dX, y), cv::Point(fX, y), cv::Scalar(255,255,255), epaisseur);
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

	for (unsigned int i = 0; i < this->membres.size(); ++i)
	// for (unsigned int i = 0; i < PlayerMember::NB_PLAYER_MEMBER; ++i)
	{
		if(this->isUnderCursor(cursors.getCursor(static_cast<PlayerMember>(this->membres[i]))))
		// if(this->isUnderCursor(cursors.getCursor((PlayerMember) i)))
			under = true;
	}

	this->changeFirstActivation(under);
}

TouchButton& TouchButton::addMembre(int membre)
{
	this->membres.push_back(membre);
	return *this;
}

void TouchButton::setSprite(Sprite* sprite)
{
	this->sprite = sprite;
}