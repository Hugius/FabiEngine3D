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

const string& SpriteAnimation::getPreviewTexturePath() const
{
	return _previewTexturePath;
}

const int SpriteAnimation::getTimesToPlay() const
{
	return _timesToPlay;
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

const bool SpriteAnimation::isPaused() const
{
	return _isPaused;
}

void SpriteAnimation::setTimesToPlay(int value)
{
	_timesToPlay = value;
}

void SpriteAnimation::setPaused(bool value)
{
	_isPaused = value;
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

void SpriteAnimation::setPreviewTexturePath(const string& value)
{
	_previewTexturePath = value;
}