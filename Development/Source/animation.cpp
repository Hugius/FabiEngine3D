#include "animation.hpp"

using std::make_pair;
using std::max;

Animation::Animation(const string& ID)
	:
	_ID(ID)
{

}

void Animation::setFrames(const vector<AnimationFrame>& value)
{
	_frames = value;
}

void Animation::setFrame(unsigned int index, const AnimationFrame& value)
{
	_frames[index] = value;
}

void Animation::addFrame(const AnimationFrame& value)
{
	_frames.push_back(value);
}

void Animation::setPartIDs(const vector<string>& value)
{
	_partIDs = value;
}

void Animation::setPartID(unsigned int index, const string& value)
{
	_partIDs[index] = value;
}

void Animation::addPartID(const string& value)
{
	_partIDs.push_back(value);
}

void Animation::setTotalMovement(const string& partID, Vec3 value)
{
	_totalMovements[partID] = value;
}

void Animation::addTotalMovement(const string& partID, Vec3 value)
{
	_totalMovements.insert(make_pair(partID, value));
}

void Animation::setTotalRotations(const map<string, Vec3>& value)
{
	_totalRotations = value;
}

void Animation::setTotalRotation(const string& partID, Vec3 value)
{
	_totalRotations[partID] = Vec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void Animation::addTotalRotation(const string& partID, Vec3 value)
{
	_totalRotations.insert(make_pair(partID, value));
}

void Animation::setTotalScalings(const map<string, Vec3>& value)
{
	_totalScalings = value;
}

void Animation::setTotalScaling(const string& partID, Vec3 value)
{
	_totalScalings[partID] = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Animation::addTotalScaling(const string& partID, Vec3 value)
{
	_totalScalings.insert(make_pair(partID, value));
}

void Animation::setPreviewModelID(const string& value)
{
	_previewModelID = value;
}

void Animation::setOldPreviewModelID(const string& value)
{
	_oldPreviewModelID = value;
}

void Animation::setAnimatedModelID(const string& value)
{
	_animatedModelID = value;
}

void Animation::setTotalMovements(const map<string, Vec3>& value)
{
	_totalMovements = value;
}

void Animation::setInitialSize(Vec3 value)
{
	_initialSize = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Animation::setSpeedMultiplier(float value)
{
	_speedMultiplier = max(0.0f, value);
}

void Animation::setTimesToPlay(int value)
{
	_timesToPlay = value;
}

void Animation::setFadeFramestep(int value)
{
	_fadeFramestep = value;
}

void Animation::setFadeFrameIndex(int value)
{
	_fadeFrameIndex = value;
}

void Animation::setFrameIndex(unsigned int value)
{
	_frameIndex = value;
}

void Animation::setPaused(bool value)
{
	_isPaused = value;
}

void Animation::setAutoPaused(bool value)
{
	_isAutoPaused = value;
}

const vector<AnimationFrame>& Animation::getFrames() const
{
	return _frames;
}

const string& Animation::getID() const
{
	return _ID;
}

const map<string, Vec3>& Animation::getTotalMovements() const
{
	return _totalMovements;
}

const map<string, Vec3>& Animation::getTotalRotations() const
{
	return _totalRotations;
}

const map<string, Vec3>& Animation::getTotalScalings() const
{
	return _totalScalings;
}

const vector<string>& Animation::getPartIDs() const
{
	return _partIDs;
}

const string& Animation::getPreviewModelID() const
{
	return _previewModelID;
}

const string& Animation::getOldPreviewModelID() const
{
	return _oldPreviewModelID;
}

const string& Animation::getAnimatedModelID() const
{
	return _animatedModelID;
}

const Vec3 Animation::getInitialSize() const
{
	return _initialSize;
}

const float Animation::getSpeedMultiplier() const
{
	return _speedMultiplier;
}

const int Animation::getTimesToPlay() const
{
	return _timesToPlay;
}

const int Animation::getFadeFramestep() const
{
	return _fadeFramestep;
}

const int Animation::getFadeFrameIndex() const
{
	return _fadeFrameIndex;
}

const unsigned int Animation::getFrameIndex() const
{
	return _frameIndex;
}

const bool Animation::isPaused() const
{
	return _isPaused;
}

const bool Animation::isAutoPaused() const
{
	return _isAutoPaused;
}