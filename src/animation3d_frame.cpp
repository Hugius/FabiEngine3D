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

void Animation3dFrame::addPart(const string& partID, const fvec3& targetTransformation, const fvec3& rotationOrigin, const fvec3& speed, Animation3dSpeedType animationSpeedType, TransformationType transformationType)
{
	_targetTransformations.insert(make_pair(partID, targetTransformation));
	_rotationOrigins.insert(make_pair(partID, rotationOrigin));
	_speeds.insert(make_pair(partID, speed));
	_speedTypes.insert(make_pair(partID, animationSpeedType));
	_transformationTypes.insert(make_pair(partID, transformationType));
}

void Animation3dFrame::setTargetTransformation(const string& partID, const fvec3& value)
{
	_targetTransformations.at(partID) = value;
}

void Animation3dFrame::setRotationOrigin(const string& partID, const fvec3& value)
{
	_rotationOrigins.at(partID) = value;
}

void Animation3dFrame::setSpeed(const string& partID, const fvec3& value)
{
	_speeds.at(partID) = value;
}

void Animation3dFrame::setSpeedType(const string& partID, Animation3dSpeedType value)
{
	_speedTypes.at(partID) = value;
}

void Animation3dFrame::setTransformationType(const string& partID, TransformationType value)
{
	_transformationTypes.at(partID) = value;
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