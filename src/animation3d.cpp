#include "animation3d.hpp"

using std::make_pair;
using std::max;

Animation3d::Animation3d(const string& id)
	:
	_ID(id)
{

}

void Animation3d::setFrames(const vector<Animation3dFrame>& value)
{
	_frames = value;
}

void Animation3d::setFrame(unsigned int index, const Animation3dFrame& value)
{
	_frames[index] = value;
}

void Animation3d::addFrame(const Animation3dFrame& value)
{
	_frames.push_back(value);
}

void Animation3d::addPart(const string& partID, const fvec3& totalMovement, const fvec3& totalRotation, const fvec3& totalScaling)
{
	_partIDs.push_back(partID);
	_totalMovements.insert(make_pair(partID, totalMovement));
	_totalRotations.insert(make_pair(partID, totalRotation));
	_totalScalings.insert(make_pair(partID, totalScaling));
}

void Animation3d::setTotalMovement(const string& partID, const fvec3& value)
{
	_totalMovements.at(partID) = value;
}

void Animation3d::setTotalRotation(const string& partID, const fvec3& value)
{
	_totalRotations.at(partID) = value;
}

void Animation3d::setTotalScaling(const string& partID, const fvec3& value)
{
	_totalScalings.at(partID) = value;
}

void Animation3d::setPreviewModelID(const string& value)
{
	_previewModelID = value;
}

void Animation3d::setInitialSize(const fvec3& value)
{
	_initialSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Animation3d::setSpeed(float value)
{
	_speed = max(0.0f, value);
}

void Animation3d::setPlayCount(int value)
{
	_playCount = value;
}

void Animation3d::setFrameIndex(unsigned int value)
{
	_frameIndex = value;
}

void Animation3d::setPaused(bool value)
{
	_isPaused = value;
}

void Animation3d::setAutopaused(bool value)
{
	_isAutopaused = value;
}

const vector<Animation3dFrame>& Animation3d::getFrames() const
{
	return _frames;
}

const string& Animation3d::getId() const
{
	return _ID;
}

const map<string, fvec3>& Animation3d::getTotalMovements() const
{
	return _totalMovements;
}

const map<string, fvec3>& Animation3d::getTotalRotations() const
{
	return _totalRotations;
}

const map<string, fvec3>& Animation3d::getTotalScalings() const
{
	return _totalScalings;
}

const vector<string>& Animation3d::getPartIDs() const
{
	return _partIDs;
}

const string& Animation3d::getPreviewModelID() const
{
	return _previewModelID;
}

const fvec3& Animation3d::getInitialSize() const
{
	return _initialSize;
}

const float Animation3d::getSpeed() const
{
	return _speed;
}

const int Animation3d::getPlayCount() const
{
	return _playCount;
}

const unsigned int Animation3d::getFrameIndex() const
{
	return _frameIndex;
}

const bool Animation3d::isPaused() const
{
	return _isPaused;
}

const bool Animation3d::isAutopaused() const
{
	return _isAutopaused;
}