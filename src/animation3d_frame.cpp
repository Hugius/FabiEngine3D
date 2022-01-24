#include "animation3d_frame.hpp"

using std::max;

void Animation3dFrame::deleteParts()
{
	_targetTransformations.clear();
	_rotationOrigins.clear();
	_speeds.clear();
	_speedTypes.clear();
	_transformationTypes.clear();
}

void Animation3dFrame::addPart(const string& partId, const fvec3& targetTransformation, const fvec3& rotationOrigin, const fvec3& speed, Animation3dSpeedType animationSpeedType, TransformationType transformationType)
{
	_targetTransformations.insert(make_pair(partId, targetTransformation));
	_rotationOrigins.insert(make_pair(partId, rotationOrigin));
	_speeds.insert(make_pair(partId, speed));
	_speedTypes.insert(make_pair(partId, animationSpeedType));
	_transformationTypes.insert(make_pair(partId, transformationType));
}

void Animation3dFrame::setTargetTransformation(const string& partId, const fvec3& value)
{
	_targetTransformations.at(partId) = value;
}

void Animation3dFrame::setRotationOrigin(const string& partId, const fvec3& value)
{
	_rotationOrigins.at(partId) = value;
}

void Animation3dFrame::setSpeed(const string& partId, const fvec3& value)
{
	_speeds.at(partId) = value;
}

void Animation3dFrame::setSpeedType(const string& partId, Animation3dSpeedType value)
{
	_speedTypes.at(partId) = value;
}

void Animation3dFrame::setTransformationType(const string& partId, TransformationType value)
{
	_transformationTypes.at(partId) = value;
}

const map<string, fvec3>& Animation3dFrame::getTargetTransformations() const
{
	return _targetTransformations;
}

const map<string, fvec3>& Animation3dFrame::getRotationOrigins() const
{
	return _rotationOrigins;
}

const map<string, fvec3>& Animation3dFrame::getSpeeds() const
{
	return _speeds;
}

const map<string, Animation3dSpeedType>& Animation3dFrame::getSpeedTypes() const
{
	return _speedTypes;
}

const map<string, TransformationType>& Animation3dFrame::getTransformationTypes() const
{
	return _transformationTypes;
}