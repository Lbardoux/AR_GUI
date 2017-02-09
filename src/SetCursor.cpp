#include "SetCursor.hpp"
#include <algorithm>
#include <functional>

void SetCursor::addCursor(Charles_enum_type type, const Cursor& cursor, const mat_data_t& color)
{
	mapCursor_t::iterator it = this->_cursors.find(type);

	if(it != this->_cursors.end())
		this->_cursors.erase(type);

	this->_cursors[type] = coloredCursor_t(cursor, color);
}

void SetCursor::updateCursor(Charles_enum_type type, const Cursor& cursor)
{
	this->_cursors[type].first = cursor;
}
void SetCursor::updateColor(Charles_enum_type type, const mat_data_t& color)
{
	this->_cursors[type].second = color;
}

const Cursor& SetCursor::getCursor(Charles_enum_type type) const
{
	return this->_cursors.at(type).first;
}

Cursor& SetCursor::getCursor(Charles_enum_type type)
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

void SetCursor::update(cv::Mat& frame)
{
	std::for_each(this->_cursors.begin(), this->_cursors.end(), [&frame] (mapCursor_t::value_type& val) { val.second.first.draw(frame, val.second.second); });
}