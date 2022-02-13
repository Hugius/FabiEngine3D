#include "animation3d.hpp"

using std::make_pair;
using std::max;
using std::make_unique;

Animation3d::Animation3d(const string& id)
	:
	_id(id)
{

}

void Animation3d::createPart(const string& partId)
{
	_partIds.push_back(partId);

	for(auto& frame : _frames)
	{
		frame->targetTransformations.insert(make_pair(partId, fvec3(0.0f)));
		frame->rotationOrigins.insert(make_pair(partId, fvec3(0.0f)));
		frame->speeds.insert(make_pair(partId, fvec3(0.0f)));
		frame->speedTypes.insert(make_pair(partId, SpeedType::LINEAR));
		frame->transformationTypes.insert(make_pair(partId, TransformationType::MOVEMENT));
	}
}

void Animation3d::deletePart(const string& partId)
{
	_partIds.erase(remove(_partIds.begin(), _partIds.end(), partId), _partIds.end());

	for(auto& frame : _frames)
	{
		frame->targetTransformations.erase(partId);
		frame->rotationOrigins.erase(partId);
		frame->speeds.erase(partId);
		frame->speedTypes.erase(partId);
		frame->transformationTypes.erase(partId);
	}
}

void Animation3d::deleteParts()
{
	_partIds.clear();

	for(auto& frame : _frames)
	{
		frame->targetTransformations.clear();
		frame->rotationOrigins.clear();
		frame->speeds.clear();
		frame->speedTypes.clear();
		frame->transformationTypes.clear();
	}
}

void Animation3d::createFrame(unsigned int index)
{
	_frames.insert((_frames.begin() + index), make_unique<Animation3dFrame>());

	for(auto& partId : _partIds)
	{
		_frames[index]->targetTransformations.insert(make_pair(partId, fvec3(0.0f)));
		_frames[index]->rotationOrigins.insert(make_pair(partId, fvec3(0.0f)));
		_frames[index]->speeds.insert(make_pair(partId, fvec3(0.0f)));
		_frames[index]->speedTypes.insert(make_pair(partId, SpeedType::LINEAR));
		_frames[index]->transformationTypes.insert(make_pair(partId, TransformationType::MOVEMENT));
	}
}

void Animation3d::deleteFrame(unsigned int index)
{
	_frames.erase(_frames.begin() + index);
}

void Animation3d::deleteFrames()
{
	_frames.clear();
}

const string& Animation3d::getId() const
{
	return _id;
}

const vector<string>& Animation3d::getPartIds() const
{
	return _partIds;
}

const unsigned int Animation3d::getFrameCount() const
{
	return static_cast<unsigned int>(_frames.size());
}

void Animation3d::setTargetTransformation(unsigned int frameIndex, const string& partId, const fvec3& value)
{
	_frames[frameIndex]->targetTransformations.at(partId) = value;
}

void Animation3d::setRotationOrigin(unsigned int frameIndex, const string& partId, const fvec3& value)
{
	_frames[frameIndex]->rotationOrigins.at(partId) = value;
}

void Animation3d::setSpeed(unsigned int frameIndex, const string& partId, const fvec3& value)
{
	_frames[frameIndex]->speeds.at(partId) = value;
}

void Animation3d::setSpeedType(unsigned int frameIndex, const string& partId, SpeedType value)
{
	_frames[frameIndex]->speedTypes.at(partId) = value;
}

void Animation3d::setTransformationType(unsigned int frameIndex, const string& partId, TransformationType value)
{
	_frames[frameIndex]->transformationTypes.at(partId) = value;
}

const fvec3& Animation3d::getTargetTransformation(unsigned int frameIndex, const string& partId) const
{
	return _frames[frameIndex]->targetTransformations.at(partId);
}

const fvec3& Animation3d::getRotationOrigin(unsigned int frameIndex, const string& partId) const
{
	return _frames[frameIndex]->rotationOrigins.at(partId);
}

const fvec3& Animation3d::getSpeed(unsigned int frameIndex, const string& partId) const
{
	return _frames[frameIndex]->speeds.at(partId);
}

const SpeedType& Animation3d::getSpeedType(unsigned int frameIndex, const string& partId) const
{
	return _frames[frameIndex]->speedTypes.at(partId);
}

const TransformationType& Animation3d::getTransformationType(unsigned int frameIndex, const string& partId) const
{
	return _frames[frameIndex]->transformationTypes.at(partId);
}