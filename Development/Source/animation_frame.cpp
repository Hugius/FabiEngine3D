#include "animation_frame.hpp"

void AnimationFrame::setTargetTransformations(const map<string, Vec3>& value)
{
    _targetTransformations = value;
}

void AnimationFrame::setRotationOrigins(const map<string, Vec3>& value)
{
    _rotationOrigins = value;
}

void AnimationFrame::setSpeeds(const map<string, Vec3>& value)
{
    _speeds = value;
}

void AnimationFrame::setSpeedTypes(const map<string, AnimationSpeedType>& value)
{
    _speedTypes = value;
}

void AnimationFrame::setTransformationTypes(const map<string, TransformationType>& value)
{
    _transformationTypes = value;
}

void AnimationFrame::setTargetTransformation(const string& partID, Vec3 value)
{
    _targetTransformations[partID] = value;
}

void AnimationFrame::addTargetTransformation(const string& partID, Vec3 value)
{
    _targetTransformations.insert(make_pair(partID, value));
}

void AnimationFrame::setRotationOrigin(const string& partID, Vec3 value)
{
    _rotationOrigins[partID] = value;
}

void AnimationFrame::addRotationOrigin(const string& partID, Vec3 value)
{
    _rotationOrigins.insert(make_pair(partID, value));
}

void AnimationFrame::setSpeed(const string& partID, Vec3 value)
{
    _speeds[partID] = value;
}

void AnimationFrame::addSpeed(const string& partID, Vec3 value)
{
    _speeds.insert(make_pair(partID, value));
}

void AnimationFrame::setSpeedType(const string& partID, AnimationSpeedType value)
{
    _speedTypes[partID] = value;
}

void AnimationFrame::addSpeedType(const string& partID, AnimationSpeedType value)
{
    _speedTypes.insert(make_pair(partID, value));
}

void AnimationFrame::setTransformationType(const string& partID, TransformationType value)
{
    _transformationTypes[partID] = value;
}

void AnimationFrame::addTransformationType(const string& partID, TransformationType value)
{
    _transformationTypes.insert(make_pair(partID, value));
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