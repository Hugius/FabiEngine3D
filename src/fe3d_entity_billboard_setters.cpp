#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::billboardEntity_create(const string& ID)
{
	_core->_billboardEntityManager.createEntity(ID);
}

void FabiEngine3D::billboardEntity_deleteAll()
{
	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_delete(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for(const auto& aabbID : aabbEntity_getChildIDs(ID, AabbParentType::BILLBOARD_ENTITY))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete billboard entity
	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboardEntity_deleteGroup(const string& ID)
{
	for(const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities()) // Iterate through billboard entities
	{
		if(entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if(subString == ID)
			{
				billboardEntity_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::billboardEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_billboardEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::billboardEntity_move(const string& ID, Vec3 change)
{
	_core->_billboardEntityManager.getEntity(ID)->move(change);
}

void FabiEngine3D::billboardEntity_rotate(const string& ID, Vec3 change)
{
	_core->_billboardEntityManager.getEntity(ID)->rotate(change);
}

void FabiEngine3D::billboardEntity_scale(const string& ID, Vec2 change)
{
	_core->_billboardEntityManager.getEntity(ID)->scale(change);
}

void FabiEngine3D::billboardEntity_moveTo(const string& ID, Vec3 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::billboardEntity_rotateTo(const string& ID, Vec3 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::billboardEntity_scaleTo(const string& ID, Vec2 target, float speed)
{
	_core->_billboardEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::billboardEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_billboardEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::billboardEntity_setRotation(const string& ID, Vec3 rotation)
{
	_core->_billboardEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::billboardEntity_setSize(const string& ID, Vec2 size)
{
	_core->_billboardEntityManager.getEntity(ID)->setSize(size);
}

void FabiEngine3D::billboardEntity_setColor(const string& ID, Vec3 color)
{
	_core->_billboardEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::billboardEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(0, false);
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.loadTexture2D(texturePath, true, true), false);
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
	}
}

void FabiEngine3D::billboardEntity_setEmissionMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMap(0);
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMapPath("");
	}
	else
	{
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMap(_core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_billboardEntityManager.getEntity(ID)->setEmissionMapPath(texturePath);
	}
}

void FabiEngine3D::billboardEntity_setWireframed(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setWireframed(enabled);
}

void FabiEngine3D::billboardEntity_setCameraFacingX(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingX(enabled);
}

void FabiEngine3D::billboardEntity_setCameraFacingY(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setCameraFacingY(enabled);
}

void FabiEngine3D::billboardEntity_setDepthMapIncluded(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setDepthMapIncluded(enabled);
}

void FabiEngine3D::billboardEntity_setShadowed(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::billboardEntity_setReflected(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setReflected(enabled);
}

void FabiEngine3D::billboardEntity_setBright(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setBright(enabled);
}

void FabiEngine3D::billboardEntity_setMinHeight(const string& ID, float height)
{
	_core->_billboardEntityManager.getEntity(ID)->setMinHeight(height);
}

void FabiEngine3D::billboardEntity_setMaxHeight(const string& ID, float height)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxHeight(height);
}

void FabiEngine3D::billboardEntity_setLightness(const string& ID, float lightness)
{
	_core->_billboardEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::billboardEntity_setColorInversion(const string& ID, float colorInversion)
{
	_core->_billboardEntityManager.getEntity(ID)->setColorInversion(colorInversion);
}

void FabiEngine3D::billboardEntity_setTransparency(const string& ID, float transparency)
{
	_core->_billboardEntityManager.getEntity(ID)->setTransparency(transparency);
}

void FabiEngine3D::billboardEntity_setTextureRepeat(const string& ID, float repeat)
{
	_core->_billboardEntityManager.getEntity(ID)->setTextureRepeat(repeat);
}

void FabiEngine3D::billboardEntity_setEmissionIntensity(const string& ID, float intensity)
{
	_core->_billboardEntityManager.getEntity(ID)->setEmissionIntensity(intensity);
}

void FabiEngine3D::billboardEntity_setFont(const string& ID, const string& fontPath)
{
	// Temporary values
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	// Set font path
	entity->setFontPath(fontPath);

	// Load text
	auto textContent = entity->getTextContent();
	if(!textContent.empty())
	{
		entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(textContent, fontPath), true);
	}
}

void FabiEngine3D::billboardEntity_setTextContent(const string& ID, const string& textContent)
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
	if(entity->getTextContent() != textContent)
	{
		// Set text content
		entity->setTextContent(textContent);

		// Load diffuse map
		entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(textContent, fontPath), true);
	}
}

void FabiEngine3D::billboardEntity_startSpriteAnimation(const string& ID, int loops)
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

void FabiEngine3D::billboardEntity_pauseSpriteAnimation(const string& ID)
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

void FabiEngine3D::billboardEntity_resumeSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to resume sprite animation on billboard with ID \"" + ID + "\" animation not paused!");
		return;
	}

	entity->resumeSpriteAnimation();
}

void FabiEngine3D::billboardEntity_stopSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to stop sprite animation on billboard with ID \"" + ID + "\" animation not started!");
		return;
	}

	entity->stopSpriteAnimation();
}

void FabiEngine3D::billboardEntity_setSpriteAnimationRows(const string& ID, unsigned int rows)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationRows(rows);
}

void FabiEngine3D::billboardEntity_setSpriteAnimationColumns(const string& ID, unsigned int columns)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationColumns(columns);
}

void FabiEngine3D::billboardEntity_setSpriteAnimationFramestep(const string& ID, unsigned int framestep)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxSpriteAnimationFramestep(framestep);
}

void FabiEngine3D::billboardEntity_setSpriteAnimationRowIndex(const string& ID, unsigned int index)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(index);
}

void FabiEngine3D::billboardEntity_setSpriteAnimationColumnIndex(const string& ID, unsigned int index)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationColumnIndex(index);
}