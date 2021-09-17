#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::billboardEntity_create(const string& ID)
{
	_core->_billboardEntityManager.createEntity(ID);
}

void FabiEngine3D::billboardEntity_deleteAll()
{
	for (const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_delete(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for (const auto& aabbID : aabbEntity_getBoundIDs(ID, AabbParentType::BILLBOARD_ENTITY))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete billboard entity
	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboardEntity_deleteGroup(const string& ID)
{
	for (const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities()) // Iterate through BILLBOARD entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if (subString == ID)
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

const float FabiEngine3D::billboardEntity_getLightness(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::billboardEntity_getInversion(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getInversion();
}

const float FabiEngine3D::billboardEntity_getMinHeight(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::billboardEntity_getMaxHeight(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::billboardEntity_getAlpha(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getAlpha();
}

const float FabiEngine3D::billboardEntity_getUvRepeat(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getUvRepeat();
}

const bool FabiEngine3D::billboardEntity_isExisting(const string& ID)
{
	return _core->_billboardEntityManager.isExisting(ID);
}

const bool FabiEngine3D::billboardEntity_isVisible(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isVisible();
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
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, true, true), false);
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::billboardEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setTransparent(enabled);
}

void FabiEngine3D::billboardEntity_setWireFramed(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setWireFramed(enabled);
}

const Vec3 FabiEngine3D::billboardEntity_getPosition(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::billboardEntity_getRotation(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

const Vec2 FabiEngine3D::billboardEntity_getSize(const string& ID)
{
	return Vec2(_core->_billboardEntityManager.getEntity(ID)->getSize().x, _core->_billboardEntityManager.getEntity(ID)->getSize().y);
}

const Vec3 FabiEngine3D::billboardEntity_getColor(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getColor();
}

const vector<string> FabiEngine3D::billboardEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
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

void FabiEngine3D::billboardEntity_setInversion(const string& ID, float inversion)
{
	_core->_billboardEntityManager.getEntity(ID)->setInversion(inversion);
}

void FabiEngine3D::billboardEntity_setAlpha(const string& ID, float alpha)
{
	_core->_billboardEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::billboardEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_billboardEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

const bool FabiEngine3D::billboardEntity_isFacingCameraX(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraX();
}

const bool FabiEngine3D::billboardEntity_isFacingCameraY(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isFacingCameraY();
}

const bool FabiEngine3D::billboardEntity_isDepthMapIncluded(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::billboardEntity_isShadowed(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::billboardEntity_isReflected(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::billboardEntity_isBright(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isBright();
}

void FabiEngine3D::billboardEntity_setFont(const string& ID, const string& fontPath)
{
	// Temporary values
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	// Set font path
	entity->setFontPath(fontPath);

	// Load text
	auto textContent = entity->getTextContent();
	if (!textContent.empty())
	{
		entity->setDiffuseMap(_core->_textureLoader.getText(textContent, fontPath), true);
		entity->setTransparent(true);
	}
}

void FabiEngine3D::billboardEntity_setTextContent(const string& ID, const string& textContent)
{
	// Temporary values
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	// Font must be loaded
	auto fontPath = entity->getFontPath();
	if (fontPath.empty())
	{
		Logger::throwWarning("Tried to set text content of billboard with ID \"" + ID + "\": no font loaded!");
		return;
	}

	// Check if new text content is not the same as the current one
	if (entity->getTextContent() != textContent)
	{
		// Set text content
		entity->setTextContent(textContent);

		// Load diffuse map
		entity->setDiffuseMap(_core->_textureLoader.getText(textContent, fontPath), true);
		entity->setTransparent(true);
	}
}

const string& FabiEngine3D::billboardEntity_getFontPath(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getFontPath();
}

const string& FabiEngine3D::billboardEntity_getTextContent(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTextContent();
}

void FabiEngine3D::billboardEntity_startSpriteAnimation(const string& ID, int loops)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if (entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to start sprite animation on billboard with ID \"" + ID + "\": animation already started!");
		return;
	}
	if (loops < -1)
	{
		Logger::throwWarning("Tried to start sprite animation on billboard with ID \"" + ID + "\": invalid loops amount!");
		return;
	}

	entity->startSpriteAnimation(loops);
}

void FabiEngine3D::billboardEntity_pauseSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if (!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to pause sprite animation on billboard with ID \"" + ID + "\" animation not started!");
		return;
	}
	else if (entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to pause sprite animation on billboard with ID \"" + ID + "\" animation already paused!");
		return;
	}

	entity->pauseSpriteAnimation();
}

void FabiEngine3D::billboardEntity_resumeSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if (!entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to resume sprite animation on billboard with ID \"" + ID + "\" animation not paused!");
		return;
	}

	entity->resumeSpriteAnimation();
}

void FabiEngine3D::billboardEntity_stopSpriteAnimation(const string& ID)
{
	auto entity = _core->_billboardEntityManager.getEntity(ID);

	if (!entity->isSpriteAnimationStarted())
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

const string& FabiEngine3D::billboardEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationStarted(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationPlaying(const string& ID)
{
	return (billboardEntity_isSpriteAnimationStarted(ID) && !billboardEntity_isSpriteAnimationPaused(ID));
}

const bool FabiEngine3D::billboardEntity_isSpriteAnimationPaused(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

const bool FabiEngine3D::billboardEntity_hasDiffuseMap(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::billboardEntity_isText(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isText();
}

const bool FabiEngine3D::billboardEntity_isTransparent(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isTransparent();
}

const bool FabiEngine3D::billboardEntity_isWireFramed(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isWireFramed();
}

const int FabiEngine3D::billboardEntity_getRemainingSpriteAnimationLoops(const string& ID)
{
	// Temporary values
	auto maxLoops = _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	if (maxLoops == -1) // Infinite
	{
		return -1;
	}
	else // Finite
	{
		return (maxLoops - currentLoops);
	}
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationRows(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationRows();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationColumns(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationColumns();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationFramestep(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationFramestep();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationRowIndex(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

const unsigned int FabiEngine3D::billboardEntity_getSpriteAnimationColumnIndex(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}