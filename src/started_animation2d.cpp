#include "started_animation2d.hpp"

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

const unsigned int StartedAnimation2d::getPassedFrames() const
{
	return _passedFrames;
}

const unsigned int StartedAnimation2d::getRowIndex() const
{
	return _rowIndex;
}

const unsigned int StartedAnimation2d::getColumnIndex() const
{
	return _columnIndex;
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

void StartedAnimation2d::setPassedFrames(unsigned int value)
{
	_passedFrames = value;
}