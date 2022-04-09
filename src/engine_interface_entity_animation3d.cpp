#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::animation3d_create(const string & id)
{
	_core->getAnimation3dManager()->createAnimation(id);
}

void EngineInterface::animation3d_delete(const string & id)
{
	for(const auto & [animationId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimationIds())
	{
		if(id == animationId)
		{
			model_stopAnimation(modelId, animationId);
		}
	}

	_core->getAnimation3dManager()->deleteAnimation(id);
}

void EngineInterface::animation3d_createFrame(const string & animationId, unsigned int index)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->createFrame(index);
}

void EngineInterface::animation3d_deleteFrame(const string & animationId, unsigned int index)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->deleteFrame(index);
}

void EngineInterface::animation3d_deleteFrames(const string & animationId)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->deleteFrames();
}

void EngineInterface::animation3d_createPart(const string & animationId, const string & partId)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->createPart(partId);
}

void EngineInterface::animation3d_deletePart(const string & animationId, const string & partId)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->deletePart(partId);
}

void EngineInterface::animation3d_deleteParts(const string & animationId)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->deleteParts();
}

void EngineInterface::animation3d_setTargetTransformation(const string & animationId, unsigned int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->setTargetTransformation(frameIndex, partId, value);
}

void EngineInterface::animation3d_setRotationOrigin(const string & animationId, unsigned int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->setRotationOrigin(frameIndex, partId, value);
}

void EngineInterface::animation3d_setSpeed(const string & animationId, unsigned int frameIndex, const string & partId, const fvec3 & value)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->setSpeed(frameIndex, partId, value);
}

void EngineInterface::animation3d_setSpeedType(const string & animationId, unsigned int frameIndex, const string & partId, SpeedType value)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->setSpeedType(frameIndex, partId, value);
}

void EngineInterface::animation3d_setTransformationType(const string & animationId, unsigned int frameIndex, const string & partId, TransformationType value)
{
	_core->getAnimation3dManager()->getAnimation(animationId)->setTransformationType(frameIndex, partId, value);
}

const vector<string> EngineInterface::animation3d_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getAnimation3dManager()->getAnimations())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const vector<string> & EngineInterface::animation3d_getPartIds(const string & animationId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getPartIds();
}

const fvec3 & EngineInterface::animation3d_getTargetTransformation(const string & animationId, unsigned int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getTargetTransformation(frameIndex, partId);
}

const fvec3 & EngineInterface::animation3d_getRotationOrigin(const string & animationId, unsigned int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getRotationOrigin(frameIndex, partId);
}

const fvec3 & EngineInterface::animation3d_getSpeed(const string & animationId, unsigned int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getSpeed(frameIndex, partId);
}

const SpeedType & EngineInterface::animation3d_getSpeedType(const string & animationId, unsigned int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getSpeedType(frameIndex, partId);
}

const TransformationType & EngineInterface::animation3d_getTransformationType(const string & animationId, unsigned int frameIndex, const string & partId) const
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getTransformationType(frameIndex, partId);
}

const unsigned int EngineInterface::animation3d_getFrameCount(const string & animationId)
{
	return _core->getAnimation3dManager()->getAnimation(animationId)->getFrameCount();
}

const bool EngineInterface::animation3d_isExisting(const string & id) const
{
	return _core->getAnimation3dManager()->isAnimationExisting(id);
}