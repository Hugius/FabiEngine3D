#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::billboard_create(const string& ID, bool isCentered)
{
	_core->getQuad3dEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::billboard_deleteAll()
{
	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		billboard_delete(entity->getID());
	}
}

void EngineInterface::billboard_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::BILLBOARD))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbID);
	}

	_core->getQuad3dEntityManager()->deleteEntity(ID);
}

void EngineInterface::billboard_deleteGroup(const string& ID)
{
	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		if(entity->getID().size() >= ID.size())
		{
			auto subString = entity->getID().substr(0, ID.size());

			if(subString == ID)
			{
				billboard_delete(entity->getID());
			}
		}
	}
}

void EngineInterface::billboard_setVisible(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::billboard_move(const string& ID, fvec3 change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::billboard_rotate(const string& ID, fvec3 change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->rotate(change);
}

void EngineInterface::billboard_scale(const string& ID, fvec2 change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->scale(change);
}

void EngineInterface::billboard_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::billboard_rotateTo(const string& ID, fvec3 target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::billboard_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::billboard_setPosition(const string& ID, fvec3 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::billboard_setRotation(const string& ID, fvec3 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::billboard_setSize(const string& ID, fvec2 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::billboard_setColor(const string& ID, fvec3 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::billboard_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::billboard_setUvMultiplier(const string& ID, fvec2 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::billboard_setUvOffset(const string& ID, fvec2 value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::billboard_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMap(texture);
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::billboard_setEmissionMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMap(texture);
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMapPath(value);
	}
}

void EngineInterface::billboard_setWireframed(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::billboard_setFrozen(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFrozen(value);
}

void EngineInterface::billboard_setFacingCameraX(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFacingCameraX(value);
}

void EngineInterface::billboard_setFacingCameraY(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFacingCameraY(value);
}

void EngineInterface::billboard_setDepthMapIncluded(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setDepthMapIncluded(value);
}

void EngineInterface::billboard_setShadowed(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setShadowed(value);
}

void EngineInterface::billboard_setReflected(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setReflected(value);
}

void EngineInterface::billboard_setBright(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setBright(value);
}

void EngineInterface::billboard_setMinHeight(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setMinHeight(value);
}

void EngineInterface::billboard_setMaxHeight(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setMaxHeight(value);
}

void EngineInterface::billboard_setLightness(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::billboard_setTransparency(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setTransparency(value);
}

void EngineInterface::billboard_setTextureRepeat(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setTextureRepeat(value);
}

void EngineInterface::billboard_setEmissionIntensity(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionIntensity(value);
}