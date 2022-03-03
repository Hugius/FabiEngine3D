#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text3d_create(const string& id, const string& fontMapPath, bool isCentered)
{
	_core->getText3dEntityManager()->createEntity(id, fontMapPath, isCentered);
}

void EngineInterface::text3d_setContent(const string& id, const string& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setContent(value);
}

void EngineInterface::text3d_delete(const string& id)
{
	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::TEXT3D)
				{
					_core->getAabbEntityManager()->deleteEntity(key);
				}
			}
		}
	}

	_core->getText3dEntityManager()->deleteEntity(id);
}

void EngineInterface::text3d_setVisible(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::text3d_move(const string& id, const fvec3& change)
{
	_core->getText3dEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::text3d_rotate(const string& id, const fvec3& change)
{
	_core->getText3dEntityManager()->getEntity(id)->rotate(change);
}

void EngineInterface::text3d_scale(const string& id, const fvec2& change)
{
	_core->getText3dEntityManager()->getEntity(id)->scale(change);
}

void EngineInterface::text3d_moveTo(const string& id, const fvec3& target, float speed)
{
	_core->getText3dEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::text3d_rotateTo(const string& id, const fvec3& target, float speed)
{
	_core->getText3dEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::text3d_scaleTo(const string& id, const fvec2& target, float speed)
{
	_core->getText3dEntityManager()->getEntity(id)->scaleTo(target, speed);
}

void EngineInterface::text3d_setPosition(const string& id, const fvec3& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::text3d_setRotation(const string& id, const fvec3& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setRotation(value);
}

void EngineInterface::text3d_setSize(const string& id, const fvec2& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setSize(value);
}

void EngineInterface::text3d_setColor(const string& id, const fvec3& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::text3d_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getText3dEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::text3d_setWireframed(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::text3d_setFrozen(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setFrozen(value);
}

void EngineInterface::text3d_setFacingCameraHorizontally(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setFacingCameraHorizontally(value);
}

void EngineInterface::text3d_setFacingCameraVertically(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setFacingCameraVertically(value);
}

void EngineInterface::text3d_setShadowed(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setShadowed(value);
}

void EngineInterface::text3d_setReflected(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setReflected(value);
}

void EngineInterface::text3d_setBright(const string& id, bool value)
{
	_core->getText3dEntityManager()->getEntity(id)->setBright(value);
}

void EngineInterface::text3d_setMinHeight(const string& id, float value)
{
	_core->getText3dEntityManager()->getEntity(id)->setMinHeight(value);
}

void EngineInterface::text3d_setMaxHeight(const string& id, float value)
{
	_core->getText3dEntityManager()->getEntity(id)->setMaxHeight(value);
}

void EngineInterface::text3d_setLightness(const string& id, float value)
{
	_core->getText3dEntityManager()->getEntity(id)->setLightness(value);
}

void EngineInterface::text3d_setOpacity(const string& id, float value)
{
	_core->getText3dEntityManager()->getEntity(id)->setOpacity(value);
}

void EngineInterface::text3d_setMinTextureAlpha(const string& id, float value)
{
	_core->getText3dEntityManager()->getEntity(id)->setMinTextureAlpha(value);
}

const float EngineInterface::text3d_getLightness(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getLightness();
}

const float EngineInterface::text3d_getMinHeight(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getMinHeight();
}

const float EngineInterface::text3d_getMaxHeight(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getMaxHeight();
}

const float EngineInterface::text3d_getOpacity(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getOpacity();
}

const float EngineInterface::text3d_getMinTextureAlpha(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getMinTextureAlpha();
}

const bool EngineInterface::text3d_isExisting(const string& id) const
{
	return _core->getText3dEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::text3d_isVisible(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isVisible();
}

const fvec3& EngineInterface::text3d_getPosition(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getPosition();
}

const fvec3& EngineInterface::text3d_getRotation(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getRotation();
}

const fvec2& EngineInterface::text3d_getSize(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getSize();
}

const fvec3& EngineInterface::text3d_getColor(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getColor();
}

const fvec3& EngineInterface::text3d_getWireframeColor(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getWireframeColor();
}

const vector<string> EngineInterface::text3d_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText3dEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const vector<string> EngineInterface::text3d_getChildAabbIds(const string& id) const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::TEXT3D)
				{
					result.push_back(entity->getId());
				}
			}
		}
	}

	return result;
}

const string& EngineInterface::text3d_getFontMapPath(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getFontMapPath();
}

const string& EngineInterface::text3d_getContent(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->getContent();
}

const bool EngineInterface::text3d_isFacingCameraHorizontally(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isFacingCameraHorizontally();
}

const bool EngineInterface::text3d_isFacingCameraVertically(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isFacingCameraVertically();
}

const bool EngineInterface::text3d_isShadowed(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isShadowed();
}

const bool EngineInterface::text3d_isReflected(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isReflected();
}

const bool EngineInterface::text3d_isBright(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isBright();
}

const bool EngineInterface::text3d_isFrozen(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isFrozen();
}

const bool EngineInterface::text3d_hasFontMap(const string& id) const
{
	return (_core->getText3dEntityManager()->getEntity(id)->getFontTextureBuffer() != nullptr);
}

const bool EngineInterface::text3d_isWireframed(const string& id) const
{
	return _core->getText3dEntityManager()->getEntity(id)->isWireframed();
}