#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::spotlight_create(const string& ID)
{
	if(_core->getSpotlightEntityManager()->getEntities().size() == SpotlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create spotlight entity: maximum reached!");
		return;
	}

	_core->getSpotlightEntityManager()->createEntity(ID);
}

void EngineInterface::spotlight_deleteAll()
{
	_core->getSpotlightEntityManager()->deleteEntities();
}

void EngineInterface::spotlight_delete(const string& ID)
{
	_core->getSpotlightEntityManager()->deleteEntity(ID);
}

void EngineInterface::spotlight_setVisible(const string& ID, bool value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::spotlight_setPosition(const string& ID, fvec3 value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::spotlight_move(const string& ID, fvec3 change)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::spotlight_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::spotlight_setColor(const string& ID, fvec3 value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::spotlight_setYaw(const string& ID, float value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setYaw(value);
}

void EngineInterface::spotlight_setPitch(const string& ID, float value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setPitch(value);
}

void EngineInterface::spotlight_setIntensity(const string& ID, float value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setIntensity(value);
}

void EngineInterface::spotlight_setAngle(const string& ID, float value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setAngle(value);
}

void EngineInterface::spotlight_setDistance(const string& ID, float value)
{
	_core->getSpotlightEntityManager()->getEntity(ID)->setDistance(value);
}