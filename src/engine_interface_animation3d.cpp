#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::animation3d_create(const string & animation3dId)
{
	_core->getAnimation3dManager()->createAnimation3d(animation3dId);
}

void EngineInterface::animation3d_delete(const string & animation3dId)
{
	for(const auto & [startedAnimation3dId, startedModelId] : _core->getAnimation3dPlayer()->getStartedModelAnimation3dIds())
	{
		if(animation3dId == startedAnimation3dId)
		{
			model_stopAnimation3d(startedModelId, startedAnimation3dId);
		}
	}

	_core->getAnimation3dManager()->deleteAnimation3d(animation3dId);
}

void EngineInterface::animation3d_createFrame(const string & animation3dId, int index)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->createFrame(index);
}

void EngineInterface::animation3d_deleteFrame(const string & animation3dId, int index)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->deleteFrame(index);
}

void EngineInterface::animation3d_deleteFrames(const string & animation3dId)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->deleteFrames();
}

void EngineInterface::animation3d_createPart(const string & animation3dId, const string & partId)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->createPart(partId);
}

void EngineInterface::animation3d_deletePart(const string & animation3dId, const string & partId)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->deletePart(partId);
}

void EngineInterface::animation3d_deleteParts(const string & animation3dId)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->deleteParts();
}

void EngineInterface::animation3d_setTargetTransformation(const string & animation3dId, int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->setTargetTransformation(frameIndex, partId, value);
}

void EngineInterface::animation3d_setRotationOrigin(const string & animation3dId, int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->setRotationOrigin(frameIndex, partId, value);
}

void EngineInterface::animation3d_setSpeed(const string & animation3dId, int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->setSpeed(frameIndex, partId, value);
}

void EngineInterface::animation3d_setSpeedType(const string & animation3dId, int frameIndex, const string & partId, SpeedType value)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->setSpeedType(frameIndex, partId, value);
}

void EngineInterface::animation3d_setTransformationType(const string & animation3dId, int frameIndex, const string & partId, TransformationType value)
{
	_core->getAnimation3dManager()->getAnimation3d(animation3dId)->setTransformationType(frameIndex, partId, value);
}

const vector<string> EngineInterface::animation3d_getIds() const
{
	vector<string> result = {};

	for(const auto & [animation3dId, animation3d] : _core->getAnimation3dManager()->getAnimation3ds())
	{
		result.push_back(animation3d->getId());
	}

	return result;
}

const vector<string> & EngineInterface::animation3d_getPartIds(const string & animation3dId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getPartIds();
}

const fvec3 & EngineInterface::animation3d_getTargetTransformation(const string & animation3dId, int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getTargetTransformation(frameIndex, partId);
}

const fvec3 & EngineInterface::animation3d_getRotationOrigin(const string & animation3dId, int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getRotationOrigin(frameIndex, partId);
}

const fvec3 & EngineInterface::animation3d_getSpeed(const string & animation3dId, int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getSpeed(frameIndex, partId);
}

const SpeedType & EngineInterface::animation3d_getSpeedType(const string & animation3dId, int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getSpeedType(frameIndex, partId);
}

const TransformationType & EngineInterface::animation3d_getTransformationType(const string & animation3dId, int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getTransformationType(frameIndex, partId);
}

const int EngineInterface::animation3d_getFrameCount(const string & animation3dId)
{
	return _core->getAnimation3dManager()->getAnimation3d(animation3dId)->getFrameCount();
}

const bool EngineInterface::animation3d_isExisting(const string & animation3dId) const
{
	return _core->getAnimation3dManager()->isAnimation3dExisting(animation3dId);
}