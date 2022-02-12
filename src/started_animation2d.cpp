#include "started_animation2d.hpp"

using std::max;

StartedAnimation2d::StartedAnimation2d(const string& animationId, const string& quadId)
	:
	_animationId(animationId),
	_quadId(quadId)
{

}

const string& StartedAnimation2d::getAnimationId() const
{
	return _animationId;
}

const string& StartedAnimation2d::getQuadId() const
{
	return _quadId;
}

const int StartedAnimation2d::getPlayCount() const
{
	return _playCount;
}

const unsigned int StartedAnimation2d::getUpdateCount() const
{
	return _updateCount;
}

const unsigned int StartedAnimation2d::getRowIndex() const
{
	return _rowIndex;
}

const unsigned int StartedAnimation2d::getColumnIndex() const
{
	return _columnIndex;
}

const unsigned int StartedAnimation2d::getIntervalMultiplier() const
{
	return _intervalMultiplier;
}

const unsigned int StartedAnimation2d::getIntervalDivider() const
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

void StartedAnimation2d::setRowIndex(unsigned int value)
{
	_rowIndex = value;
}

void StartedAnimation2d::setColumnIndex(unsigned int value)
{
	_columnIndex = value;
}

void StartedAnimation2d::setUpdateCount(unsigned int value)
{
	_updateCount = value;
}

void StartedAnimation2d::setIntervalMultiplier(unsigned int value)
{
	_intervalMultiplier = max(unsigned int(1), value);
}

void StartedAnimation2d::setIntervalDivider(unsigned int value)
{
	_intervalDivider = max(unsigned int(1), value);
}