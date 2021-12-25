#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::billboard_create(const string& ID)
{
	_core->_billboardEntityManager.createEntity(ID);
}

void FabiEngine3D::billboard_deleteAll()
{
	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboard_delete(entity->getID());
	}
}

void FabiEngine3D::billboard_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::BILLBOARD))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboard_deleteGroup(const string& ID)
{
	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
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

void FabiEngine3D::billboard_setVisible(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::billboard_move(const string& ID, fvec3 change)
{
	_core->_billboardEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::billboard_rotate(const string& ID, fvec3 change)
{
	_core->_billboardEntityManager.getEntity(ID)->rotate(change);
}

void FabiEngine3D::billboard_scale(const string& ID, fvec2 change)
{
	_core->_billboardEntityManager.getEntity(ID)->scale(change);
}

void FabiEngine3D::billboard_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::billboard_rotateTo(const string& ID, fvec3 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::billboard_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::billboard_setPosition(const string& ID, fvec3 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setPosition(value);
}

void FabiEngine3D::billboard_setRotation(const string& ID, fvec3 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setRotation(value);
}

void FabiEngine3D::billboard_setSize(const string& ID, fvec2 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setSize(value);
}

void FabiEngine3D::billboard_setColor(const string& ID, fvec3 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::billboard_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::billboard_setMultiplierUV(const string& ID, fvec2 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setMultiplierUV(value);
}

void FabiEngine3D::billboard_setAdderUV(const string& ID, fvec2 value)
{
	_core->_billboardEntityManager.getEntity(ID)->setAdderUV(value);
}

void FabiEngine3D::billboard_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(0, false);
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.load2dTexture(value, true, true), false);
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath(value);
	}
}

void FabiEngine3D::billboard_setEmissionMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMap(0);
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMapPath("");
	}
	else
	{
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMap(_core->_textureLoader.load2dTexture(value, true, true));
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMapPath(value);
	}
}

void FabiEngine3D::billboard_setWireframed(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::billboard_setFrozen(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setFrozen(value);
}

void FabiEngine3D::billboard_setFacingCameraX(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setFacingCameraX(value);
}

void FabiEngine3D::billboard_setFacingCameraY(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setFacingCameraY(value);
}

void FabiEngine3D::billboard_setDepthMapIncluded(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setDepthMapIncluded(value);
}

void FabiEngine3D::billboard_setShadowed(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setShadowed(value);
}

void FabiEngine3D::billboard_setReflected(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setReflected(value);
}

void FabiEngine3D::billboard_setBright(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setBright(value);
}

void FabiEngine3D::billboard_setMinHeight(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setMinHeight(value);
}

void FabiEngine3D::billboard_setMaxHeight(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxHeight(value);
}

void FabiEngine3D::billboard_setLightness(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setLightness(value);
}

void FabiEngine3D::billboard_setTransparency(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setTransparency(value);
}

void FabiEngine3D::billboard_setTextureRepeat(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setTextureRepeat(value);
}

void FabiEngine3D::billboard_setEmissionIntensity(const string& ID, float value)
{
	_core->_billboardEntityManager.getEntity(ID)->setEmissionIntensity(value);
}

void FabiEngine3D::billboard_setFont(const string& ID, const string& value)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	entity->setFontPath(value);

	auto textContent = entity->getTextContent();
	if(!textContent.empty())
	{
		entity->setDiffuseMap(_core->_textureLoader.load2dTexture(textContent, value), true);
	}
}

void FabiEngine3D::billboard_setTextContent(const string& ID, const string& value)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	auto fontPath = entity->getFontPath();
	if(fontPath.empty())
	{
		Logger::throwWarning("Tried to set text content of billboard with ID \"" + ID + "\": no font loaded!");
		return;
	}

	if(entity->getTextContent() != value)
	{
		entity->setTextContent(value);

		entity->setDiffuseMap(_core->_textureLoader.load2dTexture(value, fontPath), true);
	}
}