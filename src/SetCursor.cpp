#include "SetCursor.hpp"
#include "Player.hpp"
#include <algorithm>
#include <functional>

void SetCursor::addCursor(PlayerMember type, const Cursor& cursor, const mat_data_t& color)
{
	mapCursor_t::iterator it = this->_cursors.find(type);

	if(it != this->_cursors.end())
		this->_cursors.erase(type);

	this->_cursors[type] = coloredCursor_t(cursor, color);
}

void SetCursor::updateCursor(PlayerMember type, const Cursor& cursor)
{
	this->_cursors[type].first = cursor;
}
void SetCursor::updateColor(PlayerMember type, const mat_data_t& color)
{
	this->_cursors[type].second = color;
}

const Cursor& SetCursor::getCursor(PlayerMember type) const
{
	return this->_cursors.at(type).first;
}

Cursor& SetCursor::getCursor(PlayerMember type)
{
	return this->_cursors[type].first;
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
	std::for_each(this->_cursors.begin(), this->_cursors.end(),	[&frame] (mapCursor_t::value_type& val) {
		val.second.first.draw(frame, val.second.second);
	});
}

void SetCursor::update(const Player& player)
{
	for(int p = 0; p < PlayerMember::NB_PLAYER_MEMBER; ++p)
		updateCursor(static_cast<PlayerMember>(p), player.getPositionOf(static_cast<PlayerMember>(p)));

}