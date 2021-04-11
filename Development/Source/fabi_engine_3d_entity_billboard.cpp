#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::billboardEntity_add(const string& ID, Vec3 color, Vec3 T, Vec3 R, Vec2 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, color, T, R, Vec3(S.x, S.y, 1.0f), facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billboardEntity_add(const string& ID, const string& diffuseMapPath, Vec3 T, Vec3 R, Vec2 S, bool transparent, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, diffuseMapPath, T, R, Vec3(S.x, S.y, 1.0f), transparent, facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billboardEntity_add(const string& ID, const string& text, const string& fontPath, Vec3 color, Vec3 T, Vec3 R, Vec2 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, text, fontPath, color, T, R, Vec3(S.x, S.y, 1.0f), facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::billboardEntity_deleteAll()
{
	for (auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_delete(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for (auto& aabbID : aabbEntity_getBoundIDs(ID, false, true))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete billboard entity
	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboardEntity_deleteGroup(const string& ID)
{
	for (auto& [keyID, entity] : _core->_billboardEntityManager.getEntities()) // Loop over billboard entities
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

void FabiEngine3D::billboardEntity_hideAll()
{
	for (auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_hide(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_showAll()
{
	for (auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		billboardEntity_show(entity->getID());
	}
}

void FabiEngine3D::billboardEntity_hide(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::billboardEntity_show(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setVisible(true);
}

float FabiEngine3D::billboardEntity_getLightness(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::billboardEntity_getMinHeight(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMinHeight();
}

float FabiEngine3D::billboardEntity_getMaxHeight(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxHeight();
}

bool FabiEngine3D::billboardEntity_isExisting(const string& ID)
{
	return _core->_billboardEntityManager.isExisting(ID);
}

bool FabiEngine3D::billboardEntity_isVisible(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isVisible();
}

void FabiEngine3D::billboardEntity_move(const string& ID, Vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->translate(factor);
}

void FabiEngine3D::billboardEntity_rotate(const string& ID, Vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->rotate(factor);
}

void FabiEngine3D::billboardEntity_scale(const string& ID, Vec2 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->scale(Vec3(factor.x, factor.y, 0.0f));
}

void FabiEngine3D::billboardEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_billboardEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::billboardEntity_setRotation(const string& ID, Vec3 rotation)
{
	_core->_billboardEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::billboardEntity_setSize(const string& ID, Vec2 size)
{
	_core->_billboardEntityManager.getEntity(ID)->setScaling(Vec3(size.x, size.y, 1.0f));
}

void FabiEngine3D::billboardEntity_setColor(const string& ID, Vec3 color)
{
	_core->_billboardEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::billboardEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, false, true, false));
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::billboardEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_billboardEntityManager.getEntity(ID)->setTransparent(enabled);
}

Vec3 FabiEngine3D::billboardEntity_getPosition(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTranslation();
}

Vec3 FabiEngine3D::billboardEntity_getRotation(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

Vec2 FabiEngine3D::billboardEntity_getSize(const string& ID)
{
	return Vec2(_core->_billboardEntityManager.getEntity(ID)->getScaling().x, _core->_billboardEntityManager.getEntity(ID)->getScaling().y);
}

Vec3 FabiEngine3D::billboardEntity_getColor(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getColor();
}

vector<string> FabiEngine3D::billboardEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto& [keyID, entity] : _core->_billboardEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

vector<Vec3> FabiEngine3D::billboardEntity_getInstancedOffsets(const string& ID)
{
	if (billboardEntity_isInstanced(ID))
	{
		return _core->_billboardEntityManager.getEntity(ID)->getRenderBuffer(0)->getInstancedOffsets();
	}
	else
	{
		return {};
	}
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

bool FabiEngine3D::billboardEntity_isFacingCameraX(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isCameraFacingX();
}

bool FabiEngine3D::billboardEntity_isFacingCameraY(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isCameraFacingY();
}

bool FabiEngine3D::billboardEntity_isDepthMapIncluded(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isDepthMapIncluded();
}

bool FabiEngine3D::billboardEntity_isInstanced(const string& ID)
{
	if (!_core->_billboardEntityManager.getEntity(ID)->getRenderBuffers().empty())
	{
		return _core->_billboardEntityManager.getEntity(ID)->getRenderBuffer(0)->isInstanced();
	}
	else
	{
		return false;
	}
}

void FabiEngine3D::billboardEntity_setFont(const string& ID, const string& fontPath)
{
	string text = _core->_billboardEntityManager.getEntity(ID)->getTextContent();
	_core->_billboardEntityManager.getEntity(ID)->setFontPath(fontPath);

	// Only update texture if text content is present
	if (text != "")
	{
		_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getText(text, fontPath));
		_core->_billboardEntityManager.getEntity(ID)->setTransparent(true);
	}
}

void FabiEngine3D::billboardEntity_setTextContent(const string& ID, const string& textContent)
{
	// Check if text content is not the same as the current one
	if (_core->_billboardEntityManager.getEntity(ID)->getTextContent() != textContent)
	{
		string fontPath = _core->_billboardEntityManager.getEntity(ID)->getFontPath();
		_core->_billboardEntityManager.getEntity(ID)->setTextContent(textContent);

		// Only update texture if font is loaded
		if (fontPath != "")
		{
			_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getText(textContent, fontPath));
			_core->_billboardEntityManager.getEntity(ID)->setTransparent(true);
		}
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

void FabiEngine3D::billboardEntity_playAnimation(const string& ID, int loops)
{
	_core->_billboardEntityManager.getEntity(ID)->startSpriteAnimation(loops);
}

void FabiEngine3D::billboardEntity_pauseAnimation(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->pauseSpriteAnimation();
}

void FabiEngine3D::billboardEntity_resumeAnimation(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->resumeSpriteAnimation();
}

void FabiEngine3D::billboardEntity_stopAnimation(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->stopSpriteAnimation();
}

void FabiEngine3D::billboardEntity_setAnimationRows(const string& ID, unsigned int rows)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationRows(rows);
}

void FabiEngine3D::billboardEntity_setAnimationColumns(const string& ID, unsigned int columns)
{
	_core->_billboardEntityManager.getEntity(ID)->setTotalSpriteAnimationColumns(columns);
}

void FabiEngine3D::billboardEntity_setAnimationFramestep(const string& ID, unsigned int framestep)
{
	_core->_billboardEntityManager.getEntity(ID)->setMaxSpriteAnimationFramestep(framestep);
}

void FabiEngine3D::billboardEntity_setAnimationRowIndex(const string& ID, unsigned int index)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(index);
}

void FabiEngine3D::billboardEntity_setAnimationColumnIndex(const string& ID, unsigned int index)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimationColumnIndex(index);
}

const string& FabiEngine3D::billboardEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getDiffuseMapPath();
}

bool FabiEngine3D::billboardEntity_isAnimationFinished(const string& ID)
{
	int loops = _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationLoops();
	int maxLoops = _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	return (loops == maxLoops);
}

bool FabiEngine3D::billboardEntity_isAnimationStarted(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationStarted();
}

bool FabiEngine3D::billboardEntity_isAnimationPlaying(const string& ID)
{
	return (billboardEntity_isAnimationStarted(ID) && !billboardEntity_isAnimationPaused(ID));
}

bool FabiEngine3D::billboardEntity_isAnimationPaused(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isSpriteAnimationPaused();
}

bool FabiEngine3D::billboardEntity_isTransparent(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->isTransparent();
}

unsigned int FabiEngine3D::billboardEntity_getAnimationRows(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationRows();
}

unsigned int FabiEngine3D::billboardEntity_getAnimationColumns(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTotalSpriteAnimationColumns();
}

unsigned int FabiEngine3D::billboardEntity_getAnimationFramestep(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationFramestep();
}

unsigned int FabiEngine3D::billboardEntity_getAnimationRowIndex(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationRowIndex();
}

unsigned int FabiEngine3D::billboardEntity_getAnimationColumnIndex(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationColumnIndex();
}

int FabiEngine3D::billboardEntity_getRemainingAnimationLoops(const string& ID)
{
	auto maxLoops = _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
	auto currentLoops = _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationLoops();

	return (maxLoops - currentLoops);
}