#include "started_animation3d.hpp"

using std::max;

StartedAnimation3d::StartedAnimation3d(const string& animationId, const string& modelId)
	:
	_animationId(animationId),
	_modelId(modelId)
{

}

const string& StartedAnimation3d::getAnimationId() const
{
	return _animationId;
}

const string& StartedAnimation3d::getModelId() const
{
	return _modelId;
}

const int StartedAnimation3d::getPlayCount() const
{
	return _playCount;
}

const float StartedAnimation3d::getSpeedMultiplier() const
{
	return _speedMultiplier;
}

const unsigned int StartedAnimation3d::getFrameIndex() const
{
	return _frameIndex;
}

const bool StartedAnimation3d::isPaused() const
{
	return _isPaused;
}

const bool StartedAnimation3d::isAutopaused() const
{
	return _isAutopaused;
}

void StartedAnimation3d::setPartIds(const vector<string>& value)
{
	_partIds = value;

	for(const auto& partId : _partIds)
	{
		_totalMovements.insert(make_pair(partId, fvec3(0.0f)));
		_totalRotations.insert(make_pair(partId, fvec3(0.0f)));
		_totalScalings.insert(make_pair(partId, fvec3(0.0f)));
	}
}

void StartedAnimation3d::setPlayCount(int value)
{
	_playCount = value;
}

void StartedAnimation3d::setPaused(bool value)
{
	_isPaused = value;
}

void StartedAnimation3d::setAutopaused(bool value)
{
	_isAutopaused = value;
}

void StartedAnimation3d::setSpeedMultiplier(float value)
{
	_speedMultiplier = max(0.0f, value);
}

void StartedAnimation3d::setFrameIndex(unsigned int value)
{
	_frameIndex = value;
}

void StartedAnimation3d::setTotalMovement(const string& partId, const fvec3& value)
{
	_totalMovements.at(partId) = value;
}

void StartedAnimation3d::setTotalRotation(const string& partId, const fvec3& value)
{
	_totalRotations.at(partId) = value;
}

void StartedAnimation3d::setTotalScaling(const string& partId, const fvec3& value)
{
	_totalScalings.at(partId) = value;
}

void StartedAnimation3d::setTotalSpeed(const string& partId, const fvec3& value)
{
	_totalSpeeds.at(partId) = value;
}

void StartedAnimation3d::setInitialSize(const fvec3& value)
{
	_initialSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

const fvec3& StartedAnimation3d::getTotalMovement(const string& partId) const
{
	return _totalMovements.at(partId);
}

const fvec3& StartedAnimation3d::getTotalRotation(const string& partId) const
{
	return _totalRotations.at(partId);
}

const fvec3& StartedAnimation3d::getTotalScaling(const string& partId) const
{
	return _totalScalings.at(partId);
}

const fvec3& StartedAnimation3d::getTotalSpeed(const string& partId) const
{
	return _totalSpeeds.at(partId);
}

const fvec3& StartedAnimation3d::getInitialSize() const
{
	return _initialSize;
}

const vector<string>& StartedAnimation3d::getPartIds() const
{
	return _partIds;
}