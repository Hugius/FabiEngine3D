#include "fe3d.hpp"
#include "core_engine.hpp"

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
	// Delete all bound AABB entities if existing
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::BILLBOARD))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete billboard entity
	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboard_deleteGroup(const string& ID)
{
	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities()) // Iterate through billboard entities
	{
		if(entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
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

void FabiEngine3D::billboard_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(0, false);
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.loadTexture2D(value, true, true), false);
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
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMap(_core->_textureLoader.loadTexture2D(value, true, true));
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

void FabiEngine3D::billboard_setCameraFacingX(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingX(value);
}

void FabiEngine3D::billboard_setCameraFacingY(const string& ID, bool value)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingY(value);
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
	// Temporary values
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	// Set font path
	entity->setFontPath(value);

	// Load text
	auto textContent = entity->getTextContent();
	if(!textContent.empty())
	{
		entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(textContent, value), true);
	}
}

void FabiEngine3D::billboard_setTextContent(const string& ID, const string& value)
{
	// Temporary values
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	// Font must be loaded
	auto fontPath = entity->getFontPath();
	if(fontPath.empty())
	{
		Logger::throwWarning("Tried to set text content of billboard with ID \"" + ID + "\": no font loaded!");
		return;
	}

	// Check if new text content is not the same as the current one
	if(entity->getTextContent() != value)
	{
		// Set text content
		entity->setTextContent(value);

		// Load diffuse map
		entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(value, fontPath), true);
	}
}

void FabiEngine3D::billboard_startSpriteAnimation(const string& ID, int loops)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to start sprite animation on billboard with ID \"" + ID + "\": animation already started!");
		return;
	}
	if(loops < -1)
	{
		Logger::throwWarning("Tried to start sprite animation on billboard with ID \"" + ID + "\": invalid loops amount!");
		return;
	}

	entity->startSpriteAnimation(loops);
}

void FabiEngine3D::billboard_pauseSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to pause sprite animation on billboard with ID \"" + ID + "\" animation not started!");
		return;
	}
	else if(entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to pause sprite animation on billboard with ID \"" + ID + "\" animation already paused!");
		return;
	}

	entity->pauseSpriteAnimation();
}

void FabiEngine3D::billboard_resumeSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to resume sprite animation on billboard with ID \"" + ID + "\" animation not paused!");
		return;
	}

	entity->resumeSpriteAnimation();
}

void FabiEngine3D::billboard_stopSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to stop sprite animation on billboard with ID \"" + ID + "\" animation not started!");
		return;
	}

	entity->stopSpriteAnimation();
}

void FabiEngine3D::billboard_setSpriteAnimationRowCount(const string& ID, unsigned int value)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationRowCount(value);
}

void FabiEngine3D::billboard_setSpriteAnimationColumnCount(const string& ID, unsigned int value)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationColumnCount(value);
}

void FabiEngine3D::billboard_setSpriteAnimationFramestep(const string& ID, unsigned int value)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationFramestep(value);
}

void FabiEngine3D::billboard_setSpriteAnimationRowIndex(const string& ID, unsigned int value)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(value);
}

void FabiEngine3D::billboard_setSpriteAnimationColumnIndex(const string& ID, unsigned int value)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationColumnIndex(value);
}