#include "CursorSet.hpp"
#include "Player.hpp"
#include "logs.hpp"
#include <algorithm>
#include <functional>

CursorSet::CursorSet()
{}

CursorSet::~CursorSet()
{}

void CursorSet::init(const mat_data_t& color)
{
    Cursor c;

	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
		addCursor(static_cast<PlayerMember>(p), ColoredCursor(c, color));
}

void CursorSet::addCursor(PlayerMember type, const ColoredCursor& cursor)
{
    mapCursor_t::iterator it = this->_cursors.find(type);

    if(it != this->_cursors.end())
        this->_cursors.erase(type);

    this->_cursors[type] = coloredCursor_t(cursor);
    this->_cursors[type].radius(4u);
}

void CursorSet::updateCursor(PlayerMember type, const ColoredCursor& cursor)
{
    this->_cursors[type].x(cursor.x());
    this->_cursors[type].y(cursor.y());
}

void CursorSet::updateColor(PlayerMember type, const mat_data_t& color)
{
    this->_cursors[type] = color;
}

const Cursor& CursorSet::getCursor(PlayerMember type) const
{
    return this->_cursors.at(type);
}

Cursor& CursorSet::getCursor(PlayerMember type)
{
    return this->_cursors[type];
}

mapCursor_t::const_iterator CursorSet::begin() const
{
    return this->_cursors.begin();
}

mapCursor_t::iterator CursorSet::begin()
{
    return this->_cursors.begin();
}

mapCursor_t::const_iterator CursorSet::end() const
{
    return this->_cursors.end();
}

mapCursor_t::iterator CursorSet::end()
{
    return this->_cursors.end();
}

void CursorSet::draw(cv::Mat& frame)
{
    std::for_each(this->_cursors.begin(), this->_cursors.end(), [&frame] (mapCursor_t::value_type& val) {
        val.second.draw(frame);
    });
}

void CursorSet::update(const Player& player)
{
	if(!player.isVisible())
		return;
	
	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
	{
        updateCursor(static_cast<PlayerMember>(p), ColoredCursor(player.getCameraPositionOf(static_cast<PlayerMember>(p))));
	}
}
