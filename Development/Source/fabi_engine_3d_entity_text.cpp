#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::textEntity_deleteAll()
{
	_core->_textEntityManager.deleteAllEntities();
}

void FabiEngine3D::textEntity_hideAll()
{
	for (auto& [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		entity->setVisible(false);
	}
}

void FabiEngine3D::textEntity_showAll()
{
	for (auto& [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		entity->setVisible(true);
	}
}

void FabiEngine3D::textEntity_add(const string& ID, const string& textContent, const string& fontPath, Vec3 color, Vec2 position,
	float rotation, Vec2 size, bool isCentered, bool isDynamic)
{
	_core->_textEntityManager.addTextEntity(ID, textContent, fontPath, color, position, rotation, size, false, isCentered, isDynamic);
}

void FabiEngine3D::textEntity_delete(const string& ID)
{
	// Check if text if dynamic
	if (_core->_textEntityManager.isExisting(ID) && _core->_textEntityManager.getEntity(ID)->isDynamic())
	{
		_core->_textEntityManager.deleteDynamicTextEntity(ID);
	}
	else
	{
		_core->_textEntityManager.deleteEntity(ID);
	}
}

bool FabiEngine3D::textEntity_isExisting(const string& ID)
{
	return _core->_textEntityManager.isExisting(ID);
}

bool FabiEngine3D::textEntity_isVisible(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->isVisible();
}

void FabiEngine3D::textEntity_setTextContent(const string& ID, const string& textContent, float charWidth, float charHeight)
{
	// Retrieve entity
	auto entity = _core->_textEntityManager.getEntity(ID);

	// Set new text
	entity->setTextContent(textContent);

	// Calculate new size
	Vec2 newSize = entity->getScaling();
	if (charWidth >= 0.0f)
	{
		newSize.x = charWidth * static_cast<float>(textContent.size());
	}
	if (charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}
	entity->setScaling(newSize);

	// Reload
	if (entity->isDynamic())
	{
		_core->_textEntityManager.reloadCharacters(ID);
	}
	else
	{
		entity->setDiffuseMap(_core->_texLoader.getText(textContent, entity->getFontPath()));
	}
}

void FabiEngine3D::textEntity_setColor(const string& ID, Vec3 color)
{
	_core->_textEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::textEntity_setAlpha(const string& ID, float alpha)
{
	_core->_textEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::textEntity_hide(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::textEntity_show(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::textEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::textEntity_setRotation(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::textEntity_setSize(const string& ID, Vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::textEntity_move(const string& ID, Vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::textEntity_rotate(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::textEntity_scale(const string& ID, Vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::textEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_textEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::textEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_textEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

Vec2 FabiEngine3D::textEntity_getPosition(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::textEntity_getRotation(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

float FabiEngine3D::textEntity_getAlpha(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getAlpha();
}

Vec2 FabiEngine3D::textEntity_getSize(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getScaling();
}

Vec2 FabiEngine3D::textEntity_getMinPosition(const string& ID)
{
	return  _core->_textEntityManager.getEntity(ID)->getMinPosition();
}

Vec2 FabiEngine3D::textEntity_getMaxPosition(const string& ID)
{
	return  _core->_textEntityManager.getEntity(ID)->getMaxPosition();
}

Vec3 FabiEngine3D::textEntity_getColor(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getColor();
}

const string& FabiEngine3D::textEntity_getTextContent(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}

vector<string> FabiEngine3D::textEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

void FabiEngine3D::gfx_setMsaaQuality(int quality)
{
	_core->_renderEngine.loadMsaaFramebuffer(quality);
}

void FabiEngine3D::gfx_setShadowQuality(int quality)
{
	_core->_renderEngine.loadShadowFramebuffer(quality);
}

void FabiEngine3D::gfx_setReflectionQuality(int quality)
{
	_core->_renderEngine.loadReflectionFramebuffer(quality);
}

void FabiEngine3D::gfx_setRefractionQuality(int quality)
{
	_core->_renderEngine.loadRefractionFramebuffer(quality);
}