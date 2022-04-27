#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::animation2d_create(const string & id)
{
	_core->getAnimation2dManager()->createAnimation(id);
}

void EngineInterface::animation2d_delete(const string & id)
{
	for(const auto & [animationId, quad3dId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimationIds())
	{
		if(id == animationId)
		{
			quad3d_stopAnimation(quad3dId, animationId);
		}
	}

	for(const auto & [animationId, quad2dId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimationIds())
	{
		if(id == animationId)
		{
			quad2d_stopAnimation(quad2dId, animationId);
		}
	}

	_core->getAnimation2dManager()->deleteAnimation(id);
}

void EngineInterface::animation2d_setRowCount(const string & id, int value)
{
	_core->getAnimation2dManager()->getAnimation(id)->setRowCount(value);
}

void EngineInterface::animation2d_setColumnCount(const string & id, int value)
{
	_core->getAnimation2dManager()->getAnimation(id)->setColumnCount(value);
}

void EngineInterface::animation2d_setInterval(const string & id, int value)
{
	_core->getAnimation2dManager()->getAnimation(id)->setInterval(value);
}

const vector<string> EngineInterface::animation2d_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getAnimation2dManager()->getAnimations())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const int EngineInterface::animation2d_getInterval(const string & id) const
{
	return _core->getAnimation2dManager()->getAnimation(id)->getInterval();
}

const bool EngineInterface::animation2d_isExisting(const string & id) const
{
	return _core->getAnimation2dManager()->isAnimationExisting(id);
}

const int EngineInterface::animation2d_getRowCount(const string & id) const
{
	return _core->getAnimation2dManager()->getAnimation(id)->getRowCount();
}

const int EngineInterface::animation2d_getColumnCount(const string & id) const
{
	return _core->getAnimation2dManager()->getAnimation(id)->getColumnCount();
}