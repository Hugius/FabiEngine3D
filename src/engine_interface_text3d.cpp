#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text3d_create(const string & text3dId, const string & fontMapPath, bool isCentered)
{
	_core->getText3dManager()->createText3d(text3dId, fontMapPath, isCentered);
}

void EngineInterface::text3d_setContent(const string & text3dId, const string & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setContent(value);
}

void EngineInterface::text3d_delete(const string & text3dId)
{
	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(text3dId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::TEXT3D)
				{
					aabb_delete(aabbId);
				}
			}
		}
	}

	_core->getText3dManager()->deleteText3d(text3dId);
}

void EngineInterface::text3d_setVisible(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setVisible(value);
}

void EngineInterface::text3d_move(const string & text3dId, const fvec3 & change)
{
	_core->getText3dManager()->getText3d(text3dId)->move(change);
}

void EngineInterface::text3d_rotate(const string & text3dId, const fvec3 & change)
{
	_core->getText3dManager()->getText3d(text3dId)->rotate(change);
}

void EngineInterface::text3d_scale(const string & text3dId, const fvec2 & change)
{
	_core->getText3dManager()->getText3d(text3dId)->scale(change);
}

void EngineInterface::text3d_moveTo(const string & text3dId, const fvec3 & target, float speed)
{
	_core->getText3dManager()->getText3d(text3dId)->moveTo(target, speed);
}

void EngineInterface::text3d_rotateTo(const string & text3dId, const fvec3 & target, float speed)
{
	_core->getText3dManager()->getText3d(text3dId)->rotateTo(target, speed);
}

void EngineInterface::text3d_scaleTo(const string & text3dId, const fvec2 & target, float speed)
{
	_core->getText3dManager()->getText3d(text3dId)->scaleTo(target, speed);
}

void EngineInterface::text3d_setPosition(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setPosition(value);
}

void EngineInterface::text3d_setRotation(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setRotation(value);
}

void EngineInterface::text3d_setSize(const string & text3dId, const fvec2 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setSize(value);
}

void EngineInterface::text3d_setColor(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setColor(value);
}

void EngineInterface::text3d_setWireframeColor(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setWireframeColor(value);
}

void EngineInterface::text3d_setMinClipPosition(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setMinClipPosition(value);
}

void EngineInterface::text3d_setMaxClipPosition(const string & text3dId, const fvec3 & value)
{
	_core->getText3dManager()->getText3d(text3dId)->setMaxClipPosition(value);
}

void EngineInterface::text3d_setWireframed(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setWireframed(value);
}

void EngineInterface::text3d_setFrozen(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setFrozen(value);
}

void EngineInterface::text3d_setHorizontallyFlipped(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setHorizontallyFlipped(value);
}

void EngineInterface::text3d_setVerticallyFlipped(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setVerticallyFlipped(value);
}

void EngineInterface::text3d_setRotationOrder(const string & text3dId, DirectionOrderType value)
{
	_core->getText3dManager()->getText3d(text3dId)->setRotationOrder(value);
}

void EngineInterface::text3d_setFacingCameraHorizontally(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setFacingCameraHorizontally(value);
}

void EngineInterface::text3d_setFacingCameraVertically(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setFacingCameraVertically(value);
}

void EngineInterface::text3d_setShadowed(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setShadowed(value);
}

void EngineInterface::text3d_setReflected(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setReflected(value);
}

void EngineInterface::text3d_setRefracted(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setRefracted(value);
}

void EngineInterface::text3d_setBright(const string & text3dId, bool value)
{
	_core->getText3dManager()->getText3d(text3dId)->setBright(value);
}

void EngineInterface::text3d_setLightness(const string & text3dId, float value)
{
	_core->getText3dManager()->getText3d(text3dId)->setLightness(value);
}

void EngineInterface::text3d_setOpacity(const string & text3dId, float value)
{
	_core->getText3dManager()->getText3d(text3dId)->setOpacity(value);
}

void EngineInterface::text3d_setMinTextureAlpha(const string & text3dId, float value)
{
	_core->getText3dManager()->getText3d(text3dId)->setMinTextureAlpha(value);
}

const float EngineInterface::text3d_getLightness(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getLightness();
}

const float EngineInterface::text3d_getOpacity(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getOpacity();
}

const float EngineInterface::text3d_getMinTextureAlpha(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getMinTextureAlpha();
}

const bool EngineInterface::text3d_isExisting(const string & text3dId) const
{
	return _core->getText3dManager()->isText3dExisting(text3dId);
}

const bool EngineInterface::text3d_isVisible(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isVisible();
}

const fvec3 & EngineInterface::text3d_getPosition(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getPosition();
}

const fvec3 & EngineInterface::text3d_getRotation(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getRotation();
}

const fvec2 & EngineInterface::text3d_getSize(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getSize();
}

const fvec3 & EngineInterface::text3d_getColor(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getColor();
}

const fvec3 & EngineInterface::text3d_getWireframeColor(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getWireframeColor();
}

const fvec3 & EngineInterface::text3d_getMinClipPosition(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getMinClipPosition();
}

const fvec3 & EngineInterface::text3d_getMaxClipPosition(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getMaxClipPosition();
}

const vector<string> EngineInterface::text3d_getIds() const
{
	vector<string> result;

	for(const auto & [text3dId, text3d] : _core->getText3dManager()->getText3ds())
	{
		result.push_back(text3d->getId());
	}

	return result;
}

const vector<string> EngineInterface::text3d_getChildAabbIds(const string & text3dId) const
{
	vector<string> result;

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(text3dId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::TEXT3D)
				{
					result.push_back(aabb->getId());
				}
			}
		}
	}

	return result;
}

const string & EngineInterface::text3d_getFontMapPath(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getFontMapPath();
}

const string & EngineInterface::text3d_getContent(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getContent();
}

const bool EngineInterface::text3d_isFacingCameraHorizontally(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isFacingCameraHorizontally();
}

const bool EngineInterface::text3d_isFacingCameraVertically(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isFacingCameraVertically();
}

const bool EngineInterface::text3d_isShadowed(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isShadowed();
}

const bool EngineInterface::text3d_isReflected(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isReflected();
}

const bool EngineInterface::text3d_isRefracted(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isRefracted();
}

const bool EngineInterface::text3d_isBright(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isBright();
}

const bool EngineInterface::text3d_isFrozen(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isFrozen();
}

const bool EngineInterface::text3d_isHorizontallyFlipped(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isHorizontallyFlipped();
}

const bool EngineInterface::text3d_isVerticallyFlipped(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isVerticallyFlipped();
}

const DirectionOrderType EngineInterface::text3d_getRotationOrder(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->getRotationOrder();
}

const bool EngineInterface::text3d_isWireframed(const string & text3dId) const
{
	return _core->getText3dManager()->getText3d(text3dId)->isWireframed();
}