#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::animation2d_create(const string & animation2dId)
{
	_core->getAnimation2dManager()->createAnimation2d(animation2dId);
}

void EngineInterface::animation2d_delete(const string & animation2dId)
{
	for(const auto & [animation2dId, quad3dId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimation2dIds())
	{
		if(animation2dId == animation2dId)
		{
			quad3d_stopAnimation(quad3dId, animation2dId);
		}
	}

	for(const auto & [animation2dId, quad2dId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimation2dIds())
	{
		if(animation2dId == animation2dId)
		{
			quad2d_stopAnimation(quad2dId, animation2dId);
		}
	}

	_core->getAnimation2dManager()->deleteAnimation2d(animation2dId);
}

void EngineInterface::animation2d_setRowCount(const string & animation2dId, int value)
{
	_core->getAnimation2dManager()->getAnimation2d(animation2dId)->setRowCount(value);
}

void EngineInterface::animation2d_setColumnCount(const string & animation2dId, int value)
{
	_core->getAnimation2dManager()->getAnimation2d(animation2dId)->setColumnCount(value);
}

void EngineInterface::animation2d_setInterval(const string & animation2dId, int value)
{
	_core->getAnimation2dManager()->getAnimation2d(animation2dId)->setInterval(value);
}

const vector<string> EngineInterface::animation2d_getIds() const
{
	vector<string> result = {};

	for(const auto & [animation2dId, animation2d] : _core->getAnimation2dManager()->getAnimation2ds())
	{
		result.push_back(animation2d->getId());
	}

	return result;
}

const int EngineInterface::animation2d_getInterval(const string & animation2dId) const
{
	return _core->getAnimation2dManager()->getAnimation2d(animation2dId)->getInterval();
}

const bool EngineInterface::animation2d_isExisting(const string & animation2dId) const
{
	return _core->getAnimation2dManager()->isAnimation2dExisting(animation2dId);
}

const int EngineInterface::animation2d_getRowCount(const string & animation2dId) const
{
	return _core->getAnimation2dManager()->getAnimation2d(animation2dId)->getRowCount();
}

const int EngineInterface::animation2d_getColumnCount(const string & animation2dId) const
{
	return _core->getAnimation2dManager()->getAnimation2d(animation2dId)->getColumnCount();
}