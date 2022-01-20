#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text3d_create(const string& ID, const string& fontMapPath, bool isCentered)
{
	_core->getText3dEntityManager()->createEntity(ID, fontMapPath, isCentered);
}

void EngineInterface::text3d_deleteAll()
{
	for(const auto& [key, entity] : _core->getText3dEntityManager()->getEntities())
	{
		text3d_delete(entity->getID());
	}
}

void EngineInterface::text3d_setContent(const string& ID, const string& value, float charWidth, float charHeight)
{
	auto entity = _core->getText3dEntityManager()->getEntity(ID);

	entity->setContent(value);

	fvec2 newSize = entity->getSize();

	if(charWidth >= 0.0f)
	{
		newSize.x = (charWidth * static_cast<float>(value.size()));
	}
	if(charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}

	entity->setSize(newSize);
}

void EngineInterface::text3d_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::QUAD3D))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbID);
	}

	_core->getText3dEntityManager()->deleteEntity(ID);
}

void EngineInterface::text3d_setVisible(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::text3d_move(const string& ID, fvec3 change)
{
	_core->getText3dEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::text3d_rotate(const string& ID, fvec3 change)
{
	_core->getText3dEntityManager()->getEntity(ID)->rotate(change);
}

void EngineInterface::text3d_scale(const string& ID, fvec2 change)
{
	_core->getText3dEntityManager()->getEntity(ID)->scale(change);
}

void EngineInterface::text3d_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getText3dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::text3d_rotateTo(const string& ID, fvec3 target, float speed)
{
	_core->getText3dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::text3d_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getText3dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::text3d_setPosition(const string& ID, fvec3 value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::text3d_setRotation(const string& ID, fvec3 value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::text3d_setSize(const string& ID, fvec2 value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::text3d_setColor(const string& ID, fvec3 value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::text3d_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::text3d_setWireframed(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::text3d_setFrozen(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setFrozen(value);
}

void EngineInterface::text3d_setFacingCameraX(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setFacingCameraX(value);
}

void EngineInterface::text3d_setFacingCameraY(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setFacingCameraY(value);
}

void EngineInterface::text3d_setDepthMapIncluded(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setDepthMapIncluded(value);
}

void EngineInterface::text3d_setShadowed(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setShadowed(value);
}

void EngineInterface::text3d_setReflected(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setReflected(value);
}

void EngineInterface::text3d_setBright(const string& ID, bool value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setBright(value);
}

void EngineInterface::text3d_setMinHeight(const string& ID, float value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setMinHeight(value);
}

void EngineInterface::text3d_setMaxHeight(const string& ID, float value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setMaxHeight(value);
}

void EngineInterface::text3d_setLightness(const string& ID, float value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::text3d_setTransparency(const string& ID, float value)
{
	_core->getText3dEntityManager()->getEntity(ID)->setTransparency(value);
}

const float EngineInterface::text3d_getLightness(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::text3d_getMinHeight(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::text3d_getMaxHeight(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::text3d_getTransparency(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getTransparency();
}

const bool EngineInterface::text3d_isExisting(const string& ID) const
{
	return _core->getText3dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::text3d_isVisible(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isVisible();
}

const fvec3 EngineInterface::text3d_getPosition(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::text3d_getRotation(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getRotation();
}

const fvec2 EngineInterface::text3d_getSize(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getSize().x;
}

const fvec2 EngineInterface::text3d_getUvMultiplier(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2 EngineInterface::text3d_getUvOffset(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3 EngineInterface::text3d_getColor(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getColor();
}

const fvec3 EngineInterface::text3d_getWireframeColor(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::text3d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText3dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::text3d_getFontMapPath(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getFontMapPath();
}

const string& EngineInterface::text3d_getContent(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->getContent();
}

const bool EngineInterface::text3d_isFacingCameraX(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFacingCameraX();
}

const bool EngineInterface::text3d_isFacingCameraY(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFacingCameraY();
}

const bool EngineInterface::text3d_isDepthMapIncluded(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::text3d_isShadowed(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::text3d_isReflected(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::text3d_isBright(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isBright();
}

const bool EngineInterface::text3d_isFrozen(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::text3d_hasFontMap(const string& ID) const
{
	return (_core->getText3dEntityManager()->getEntity(ID)->getFontMap() != nullptr);
}

const bool EngineInterface::text3d_isWireframed(const string& ID) const
{
	return _core->getText3dEntityManager()->getEntity(ID)->isWireframed();
}