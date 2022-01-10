#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::reflection_create(const string& ID)
{
	_core->getReflectionEntityManager()->createEntity(ID);
}

void EngineInterface::reflection_deleteAll()
{
	_core->getReflectionEntityManager()->deleteEntities();
}

void EngineInterface::reflection_delete(const string& ID)
{
	_core->getReflectionEntityManager()->deleteEntity(ID);
}

void EngineInterface::reflection_setVisible(const string& ID, bool value)
{
	_core->getReflectionEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::reflection_setPosition(const string& ID, fvec3 value)
{
	_core->getReflectionEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::reflection_move(const string& ID, fvec3 change)
{
	_core->getReflectionEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::reflection_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getReflectionEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::reflection_capture(const string& ID)
{
	_core->getReflectionEntityManager()->getEntity(ID)->capture();
}