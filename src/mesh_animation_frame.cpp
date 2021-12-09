#include "mesh_animation_frame.hpp"

using std::max;

void MeshAnimationFrame::clearParts()
{
	_targetTransformations.clear();
	_rotationOrigins.clear();
	_speeds.clear();
	_speedTypes.clear();
	_transformationTypes.clear();
}

void MeshAnimationFrame::addPart(const string& partID, fvec3 targetTransformation, fvec3 rotationOrigin, fvec3 speed, MeshAnimationSpeedType animationSpeedType, TransformationType transformationType)
{
	_targetTransformations.insert(make_pair(partID, targetTransformation));
	_rotationOrigins.insert(make_pair(partID, rotationOrigin));
	_speeds.insert(make_pair(partID, speed));
	_speedTypes.insert(make_pair(partID, animationSpeedType));
	_transformationTypes.insert(make_pair(partID, transformationType));
}

void MeshAnimationFrame::setTargetTransformation(const string& partID, fvec3 value)
{
	_targetTransformations.at(partID) = value;
}

void MeshAnimationFrame::setRotationOrigin(const string& partID, fvec3 value)
{
	_rotationOrigins.at(partID) = value;
}

void MeshAnimationFrame::setSpeed(const string& partID, fvec3 value)
{
	_speeds.at(partID) = value;
}

void MeshAnimationFrame::setSpeedType(const string& partID, MeshAnimationSpeedType value)
{
	_speedTypes.at(partID) = value;
}

void MeshAnimationFrame::setTransformationType(const string& partID, TransformationType value)
{
	_transformationTypes.at(partID) = value;
}

const map<string, fvec3>& MeshAnimationFrame::getTargetTransformations() const
{
	return _targetTransformations;
}

const map<string, fvec3>& MeshAnimationFrame::getRotationOrigins() const
{
	return _rotationOrigins;
}

const map<string, fvec3>& MeshAnimationFrame::getSpeeds() const
{
	return _speeds;
}

const map<string, MeshAnimationSpeedType>& MeshAnimationFrame::getSpeedTypes() const
{
	return _speedTypes;
}

const map<string, TransformationType>& MeshAnimationFrame::getTransformationTypes() const
{
	return _transformationTypes;
}