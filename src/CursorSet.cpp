#include "CursorSet.hpp"
#include "Player.hpp"
#include "logs.hpp"
#include <algorithm>
#include <functional>

SetCursor::SetCursor()
{}

SetCursor::~SetCursor()
{}

void SetCursor::init(const Player& player, const mat_data_t& color)
{
	if(!player.isVisible())
		return;

	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
		addCursor(static_cast<PlayerMember>(p), ColoredCursor(player.getCameraPositionOf(static_cast<PlayerMember>(p)), color));
}

void SetCursor::addCursor(PlayerMember type, const ColoredCursor& cursor)
{
    mapCursor_t::iterator it = this->_cursors.find(type);

    if(it != this->_cursors.end())
        this->_cursors.erase(type);

    this->_cursors[type] = coloredCursor_t(cursor);
    this->_cursors[type].radius(4u);
}

void SetCursor::updateCursor(PlayerMember type, const ColoredCursor& cursor)
{
    this->_cursors[type].x(cursor.x());
    this->_cursors[type].y(cursor.y());
}

void SetCursor::updateColor(PlayerMember type, const mat_data_t& color)
{
    this->_cursors[type] = color;
}

const Cursor& SetCursor::getCursor(PlayerMember type) const
{
    return this->_cursors.at(type);
}

Cursor& SetCursor::getCursor(PlayerMember type)
{
    return this->_cursors[type];
}

mapCursor_t::const_iterator SetCursor::begin() const
{
    return this->_cursors.begin();
}

mapCursor_t::iterator SetCursor::begin()
{
    return this->_cursors.begin();
}

mapCursor_t::const_iterator SetCursor::end() const
{
    return this->_cursors.end();
}

mapCursor_t::iterator SetCursor::end()
{
    return this->_cursors.end();
}

void SetCursor::draw(cv::Mat& frame)
{
    std::for_each(this->_cursors.begin(), this->_cursors.end(),    [&frame] (mapCursor_t::value_type& val) {
        if (val.second.x() > 0 || val.second.y() > 0)
            mtl::log::info((int)val.first, val.second.x(), val.second.y());
        val.second.draw(frame);
    });
}

void SetCursor::update(const Player& player)
{
	if(!player.isVisible())
		return;
	
	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
	{
//		updateCursor(static_cast<PlayerMember>(p), ColoredCursor(player.getPositionOf(static_cast<PlayerMember>(p))));
        updateCursor(static_cast<PlayerMember>(p), ColoredCursor(player.getCameraPositionOf(static_cast<PlayerMember>(p))));
	}
}
