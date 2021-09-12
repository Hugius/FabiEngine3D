#include "animation_frame.hpp"

using std::max;

void AnimationFrame::clearParts()
{
    _targetTransformations.clear();
    _rotationOrigins.clear();
    _speeds.clear();
    _speedTypes.clear();
    _transformationTypes.clear();
}

void AnimationFrame::addPart(const string& partID, Vec3 targetTransformation, Vec3 rotationOrigin, Vec3 speed, AnimationSpeedType animationSpeedType, TransformationType transformationType)
{
    _targetTransformations.insert(make_pair(partID, targetTransformation));
    _rotationOrigins.insert(make_pair(partID, rotationOrigin));
    _speeds.insert(make_pair(partID, speed));
    _speedTypes.insert(make_pair(partID, animationSpeedType));
    _transformationTypes.insert(make_pair(partID, transformationType));
}

void AnimationFrame::setTargetTransformation(const string& partID, Vec3 value)
{
    _targetTransformations.at(partID) = value;
}

void AnimationFrame::setRotationOrigin(const string& partID, Vec3 value)
{
    _rotationOrigins.at(partID) = value;
}

void AnimationFrame::setSpeed(const string& partID, Vec3 value)
{
    _speeds.at(partID) = value;
}

void AnimationFrame::setSpeedType(const string& partID, AnimationSpeedType value)
{
    _speedTypes.at(partID) = value;
}

void AnimationFrame::setTransformationType(const string& partID, TransformationType value)
{
    _transformationTypes.at(partID) = value;
}

const map<string, Vec3>& AnimationFrame::getTargetTransformations() const
{
    return _targetTransformations;
}

const map<string, Vec3>& AnimationFrame::getRotationOrigins() const
{
    return _rotationOrigins;
}

const map<string, Vec3>& AnimationFrame::getSpeeds() const
{
    return _speeds;
}

const map<string, AnimationSpeedType>& AnimationFrame::getSpeedTypes() const
{
    return _speedTypes;
}

const map<string, TransformationType>& AnimationFrame::getTransformationTypes() const
{
    return _transformationTypes;
}