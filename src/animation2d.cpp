#include "animation2d.hpp"
#include "logger.hpp"

Animation2d::Animation2d(const string& id)
	:
	_id(id)
{

}

const string& Animation2d::getId() const
{
	return _id;
}

const string& Animation2d::getPreviewTexturePath() const
{
	return _previewTexturePath;
}

const int Animation2d::getPlayCount() const
{
	return _playCount;
}

const unsigned int Animation2d::getPassedFrames() const
{
	return _passedFrames;
}

const unsigned int Animation2d::getFramestep() const
{
	return _framestep;
}

const unsigned int Animation2d::getRowCount() const
{
	return _rowCount;
}

const unsigned int Animation2d::getColumnCount() const
{
	return _columnCount;
}

const unsigned int Animation2d::getRowIndex() const
{
	return _rowIndex;
}

const unsigned int Animation2d::getColumnIndex() const
{
	return _columnIndex;
}

const bool Animation2d::isPaused() const
{
	return _isPaused;
}

const bool Animation2d::isAutopaused() const
{
	return _isAutopaused;
}

void Animation2d::setPlayCount(int value)
{
	_playCount = value;
}

void Animation2d::setPaused(bool value)
{
	_isPaused = value;
}

void Animation2d::setAutopaused(bool value)
{
	_isAutopaused = value;
}

void Animation2d::setRowIndex(unsigned int value)
{
	_rowIndex = value;
}

void Animation2d::setColumnIndex(unsigned int value)
{
	_columnIndex = value;
}

void Animation2d::setRowCount(unsigned int value)
{
	_rowCount = value;
}

void Animation2d::setColumnCount(unsigned int value)
{
	_columnCount = value;
}

void Animation2d::setFramestep(unsigned int value)
{
	_framestep = value;
}

void Animation2d::setPassedFrames(unsigned int value)
{
	_passedFrames = value;
}

void Animation2d::setPreviewTexturePath(const string& value)
{
	_previewTexturePath = value;
}