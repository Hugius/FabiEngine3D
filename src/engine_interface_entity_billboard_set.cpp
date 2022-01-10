#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::billboard_create(const string& ID, bool isCentered)
{
	_core->getBillboardEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::billboard_deleteAll()
{
	for(const auto& [key, entity] : _core->getBillboardEntityManager()->getEntities())
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

	_core->getBillboardEntityManager()->deleteEntity(ID);
}

void EngineInterface::billboard_deleteGroup(const string& ID)
{
	for(const auto& [key, entity] : _core->getBillboardEntityManager()->getEntities())
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
	_core->getBillboardEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::billboard_move(const string& ID, fvec3 change)
{
	_core->getBillboardEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::billboard_rotate(const string& ID, fvec3 change)
{
	_core->getBillboardEntityManager()->getEntity(ID)->rotate(change);
}

void EngineInterface::billboard_scale(const string& ID, fvec2 change)
{
	_core->getBillboardEntityManager()->getEntity(ID)->scale(change);
}

void EngineInterface::billboard_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getBillboardEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::billboard_rotateTo(const string& ID, fvec3 target, float speed)
{
	_core->getBillboardEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::billboard_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getBillboardEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::billboard_setPosition(const string& ID, fvec3 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::billboard_setRotation(const string& ID, fvec3 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::billboard_setSize(const string& ID, fvec2 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::billboard_setColor(const string& ID, fvec3 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::billboard_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::billboard_setUvMultiplier(const string& ID, fvec2 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::billboard_setUvOffset(const string& ID, fvec2 value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::billboard_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getBillboardEntityManager()->getEntity(ID)->setDiffuseMap(nullptr, false);
		_core->getBillboardEntityManager()->getEntity(ID)->setDiffuseMapPath("");
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

		_core->getBillboardEntityManager()->getEntity(ID)->setDiffuseMap(texture, false);
		_core->getBillboardEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::billboard_setEmissionMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getBillboardEntityManager()->getEntity(ID)->setEmissionMap(0);
		_core->getBillboardEntityManager()->getEntity(ID)->setEmissionMapPath("");
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

		_core->getBillboardEntityManager()->getEntity(ID)->setEmissionMap(texture);
		_core->getBillboardEntityManager()->getEntity(ID)->setEmissionMapPath(value);
	}
}

void EngineInterface::billboard_setWireframed(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::billboard_setFrozen(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setFrozen(value);
}

void EngineInterface::billboard_setFacingCameraX(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setFacingCameraX(value);
}

void EngineInterface::billboard_setFacingCameraY(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setFacingCameraY(value);
}

void EngineInterface::billboard_setDepthMapIncluded(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setDepthMapIncluded(value);
}

void EngineInterface::billboard_setShadowed(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setShadowed(value);
}

void EngineInterface::billboard_setReflected(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setReflected(value);
}

void EngineInterface::billboard_setBright(const string& ID, bool value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setBright(value);
}

void EngineInterface::billboard_setMinHeight(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setMinHeight(value);
}

void EngineInterface::billboard_setMaxHeight(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setMaxHeight(value);
}

void EngineInterface::billboard_setLightness(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::billboard_setTransparency(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setTransparency(value);
}

void EngineInterface::billboard_setTextureRepeat(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setTextureRepeat(value);
}

void EngineInterface::billboard_setEmissionIntensity(const string& ID, float value)
{
	_core->getBillboardEntityManager()->getEntity(ID)->setEmissionIntensity(value);
}

void EngineInterface::billboard_setFont(const string& ID, const string& value)
{
	auto entity = _core->getBillboardEntityManager()->getEntity(ID);

	entity->setFontPath(value);

	auto textContent = entity->getTextContent();
	if(!textContent.empty())
	{
		//entity->setDiffuseMap(_core->getImageLoader()->load2dTexture(textContent, value), true);
	}
}

void EngineInterface::billboard_setTextContent(const string& ID, const string& value)
{
	auto entity = _core->getBillboardEntityManager()->getEntity(ID);

	auto fontPath = entity->getFontPath();
	if(fontPath.empty())
	{
		Logger::throwWarning("Tried to set text content of billboard with ID \"" + ID + "\": no font loaded!");
		return;
	}

	if(entity->getTextContent() != value)
	{
		entity->setTextContent(value);

		//entity->setDiffuseMap(_core->getImageLoader()->load2dTexture(value, fontPath), true);
	}
}