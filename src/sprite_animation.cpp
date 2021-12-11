#include "sprite_animation.hpp"
#include "logger.hpp"

SpriteAnimation::SpriteAnimation(const string& ID)
	:
	_ID(ID)
{

}

const string& SpriteAnimation::getID() const
{
	return _ID;
}

const int SpriteAnimation::getMaxLoops() const
{
	return _maxLoops;
}

const unsigned int SpriteAnimation::getPassedFrames() const
{
	return _passedFrames;
}

const unsigned int SpriteAnimation::getFramestep() const
{
	return _framestep;
}

const unsigned int SpriteAnimation::getRowCount() const
{
	return _rowCount;
}

const unsigned int SpriteAnimation::getColumnCount() const
{
	return _columnCount;
}

const unsigned int SpriteAnimation::getRowIndex() const
{
	return _rowIndex;
}

const unsigned int SpriteAnimation::getColumnIndex() const
{
	return _columnIndex;
}

const unsigned int SpriteAnimation::getLoops() const
{
	return _passedLoops;
}

const bool SpriteAnimation::isStarted() const
{
	return _isStarted;
}

const bool SpriteAnimation::isPaused() const
{
	return _isPaused;
}

void SpriteAnimation::start(int maxLoops)
{
	if(_isStarted)
	{
		Logger::throwWarning("SpriteAnimation::start::1");
	}
	if(maxLoops < -1)
	{
		Logger::throwWarning("SpriteAnimation::start::2");
	}

	_isStarted = true;
	_passedFrames = 0;
	_passedLoops = 0;
	_maxLoops = maxLoops;
}

void SpriteAnimation::pause()
{
	if(!_isStarted)
	{
		Logger::throwWarning("SpriteAnimation::pause::1");
	}
	else if(_isPaused)
	{
		Logger::throwWarning("SpriteAnimation::pause::2");
	}

	_isPaused = true;
}

void SpriteAnimation::resume()
{
	if(!_isPaused)
	{
		Logger::throwWarning("SpriteAnimation::resume");
	}

	_isPaused = false;
}

void SpriteAnimation::stop()
{
	if(!_isStarted)
	{
		Logger::throwWarning("SpriteAnimation::stop");
	}

	_maxLoops = 0;
	_framestep = 0;
	_passedFrames = 0;
	_rowCount = 0;
	_columnCount = 0;
	_rowIndex = 0;
	_columnIndex = 0;
	_passedLoops = 0;
	_isStarted = false;
	_isPaused = false;
}

void SpriteAnimation::setRowIndex(unsigned int value)
{
	_rowIndex = value;
}

void SpriteAnimation::setColumnIndex(unsigned int value)
{
	_columnIndex = value;
}

void SpriteAnimation::setRowCount(unsigned int value)
{
	_rowCount = value;
}

void SpriteAnimation::setColumnCount(unsigned int value)
{
	_columnCount = value;
}

void SpriteAnimation::setFramestep(unsigned int value)
{
	_framestep = value;
}

void SpriteAnimation::setPassedFrames(unsigned int value)
{
	_passedFrames = value;
}

void SpriteAnimation::setLoops(unsigned int value)
{
	_passedLoops = value;
}