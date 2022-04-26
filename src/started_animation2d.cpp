#include "started_animation2d.hpp"

using std::max;

const int StartedAnimation2d::getPlayCount() const
{
	return _playCount;
}

const int StartedAnimation2d::getUpdateCount() const
{
	return _updateCount;
}

const int StartedAnimation2d::getRowIndex() const
{
	return _rowIndex;
}

const int StartedAnimation2d::getColumnIndex() const
{
	return _columnIndex;
}

const int StartedAnimation2d::getIntervalMultiplier() const
{
	return _intervalMultiplier;
}

const int StartedAnimation2d::getIntervalDivider() const
{
	return _intervalDivider;
}

const bool StartedAnimation2d::isPaused() const
{
	return _isPaused;
}

const bool StartedAnimation2d::isAutopaused() const
{
	return _isAutopaused;
}

void StartedAnimation2d::setPlayCount(int value)
{
	_playCount = value;
}

void StartedAnimation2d::setPaused(bool value)
{
	_isPaused = value;
}

void StartedAnimation2d::setAutopaused(bool value)
{
	_isAutopaused = value;
}

void StartedAnimation2d::setRowIndex(int value)
{
	_rowIndex = max(0, value);
}

void StartedAnimation2d::setColumnIndex(int value)
{
	_columnIndex = max(0, value);
}

void StartedAnimation2d::setUpdateCount(int value)
{
	_updateCount = max(0, value);
}

void StartedAnimation2d::setIntervalMultiplier(int value)
{
	_intervalMultiplier = max(1, value);
}

void StartedAnimation2d::setIntervalDivider(int value)
{
	_intervalDivider = max(1, value);
}