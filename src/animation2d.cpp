#include "animation2d.hpp"

using std::max;

Animation2d::Animation2d(const string& id)
	:
	_id(id)
{

}

const string& Animation2d::getId() const
{
	return _id;
}

const unsigned int Animation2d::getRowCount() const
{
	return _rowCount;
}

const unsigned int Animation2d::getColumnCount() const
{
	return _columnCount;
}

const unsigned int Animation2d::getInterval() const
{
	return _interval;
}

void Animation2d::setRowCount(unsigned int value)
{
	_rowCount = max(unsigned int(1), value);
}

void Animation2d::setColumnCount(unsigned int value)
{
	_columnCount = max(unsigned int(1), value);
}

void Animation2d::setInterval(unsigned int value)
{
	_interval = value;
}