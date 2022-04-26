#include "animation2d.hpp"

using std::max;

Animation2d::Animation2d(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

const string & Animation2d::getId() const
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

void Animation2d::setRowCount(int value)
{
	_rowCount = max(1, value);
}

void Animation2d::setColumnCount(int value)
{
	_columnCount = max(1, value);
}

void Animation2d::setInterval(int value)
{
	_interval = max(0, value);
}