#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text3d_create(const string& ID, bool isCentered)
{
	_core->getText3dEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::text3d_deleteAll()
{
	for(const auto& [key, entity] : _core->getText3dEntityManager()->getEntities())
	{
		text3d_delete(entity->getID());
	}
}

void EngineInterface::text3d_setFontMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getText3dEntityManager()->getEntity(ID)->setFontMap(nullptr);
		_core->getText3dEntityManager()->getEntity(ID)->setFontMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getText3dEntityManager()->getEntity(ID)->setFontMap(_core->getTextureBufferCache()->get2dBuffer(value));
		_core->getText3dEntityManager()->getEntity(ID)->setFontMapPath(value);
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