#include "mesh_animation.hpp"

using std::make_pair;
using std::max;

MeshAnimation::MeshAnimation(const string& ID)
	:
	_ID(ID)
{

}

void MeshAnimation::setFrames(const vector<MeshAnimationFrame>& value)
{
	_frames = value;
}

void MeshAnimation::setFrame(unsigned int index, const MeshAnimationFrame& value)
{
	_frames[index] = value;
}

void MeshAnimation::addFrame(const MeshAnimationFrame& value)
{
	_frames.push_back(value);
}

void MeshAnimation::addPart(const string& partID, fvec3 totalMovement, fvec3 totalRotation, fvec3 totalScaling)
{
	_partIDs.push_back(partID);
	_totalMovements.insert(make_pair(partID, totalMovement));
	_totalRotations.insert(make_pair(partID, totalRotation));
	_totalScalings.insert(make_pair(partID, totalScaling));
}

void MeshAnimation::setTotalMovement(const string& partID, fvec3 value)
{
	_totalMovements.at(partID) = value;
}

void MeshAnimation::setTotalRotation(const string& partID, fvec3 value)
{
	_totalRotations.at(partID) = value;
}

void MeshAnimation::setTotalScaling(const string& partID, fvec3 value)
{
	_totalScalings.at(partID) = value;
}

void MeshAnimation::setPreviewModelID(const string& value)
{
	_previewModelID = value;
}

void MeshAnimation::setOldPreviewModelID(const string& value)
{
	_oldPreviewModelID = value;
}

void MeshAnimation::setAnimatedModelID(const string& value)
{
	_animatedModelID = value;
}

void MeshAnimation::setInitialSize(fvec3 value)
{
	_initialSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void MeshAnimation::setSpeedMultiplier(float value)
{
	_speedMultiplier = max(0.0f, value);
}

void MeshAnimation::setTimesToPlay(int value)
{
	_timesToPlay = value;
}

void MeshAnimation::setFadeFramestep(int value)
{
	_fadeFramestep = value;
}

void MeshAnimation::setFadeFrameIndex(int value)
{
	_fadeFrameIndex = value;
}

void MeshAnimation::setFrameIndex(unsigned int value)
{
	_frameIndex = value;
}

void MeshAnimation::setPaused(bool value)
{
	_isPaused = value;
}

void MeshAnimation::setAutoPaused(bool value)
{
	_isAutoPaused = value;
}

const vector<MeshAnimationFrame>& MeshAnimation::getFrames() const
{
	return _frames;
}

const string& MeshAnimation::getID() const
{
	return _ID;
}

const map<string, fvec3>& MeshAnimation::getTotalMovements() const
{
	return _totalMovements;
}

const map<string, fvec3>& MeshAnimation::getTotalRotations() const
{
	return _totalRotations;
}

const map<string, fvec3>& MeshAnimation::getTotalScalings() const
{
	return _totalScalings;
}

const vector<string>& MeshAnimation::getPartIDs() const
{
	return _partIDs;
}

const string& MeshAnimation::getPreviewModelID() const
{
	return _previewModelID;
}

const string& MeshAnimation::getOldPreviewModelID() const
{
	return _oldPreviewModelID;
}

const string& MeshAnimation::getAnimatedModelID() const
{
	return _animatedModelID;
}

const fvec3 MeshAnimation::getInitialSize() const
{
	return _initialSize;
}

const float MeshAnimation::getSpeedMultiplier() const
{
	return _speedMultiplier;
}

const int MeshAnimation::getTimesToPlay() const
{
	return _timesToPlay;
}

const int MeshAnimation::getFadeFramestep() const
{
	return _fadeFramestep;
}

const int MeshAnimation::getFadeFrameIndex() const
{
	return _fadeFrameIndex;
}

const unsigned int MeshAnimation::getFrameIndex() const
{
	return _frameIndex;
}

const bool MeshAnimation::isPaused() const
{
	return _isPaused;
}

const bool MeshAnimation::isAutoPaused() const
{
	return _isAutoPaused;
}