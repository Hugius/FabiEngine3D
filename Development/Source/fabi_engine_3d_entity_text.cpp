#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::textEntity_deleteAll()
{
	_core->_textEntityManager.deleteAllEntities();
}

void FabiEngine3D::textEntity_add(const string& ID, const string& textContent, const string& fontPath, Vec3 color, Vec2 position,
	float rotation, Vec2 size, bool isCentered, bool isDynamic, bool isVisible)
{
	_core->_textEntityManager.addTextEntity(ID, textContent, fontPath, color, position, rotation, size, false, isCentered, isDynamic);
	_core->_textEntityManager.getEntity(ID)->setVisible(isVisible);
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

void FabiEngine3D::textEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_textEntityManager.getEntity(ID)->setVisible(isVisible);
}

const bool FabiEngine3D::textEntity_isExisting(const string& ID)
{
	return _core->_textEntityManager.isExisting(ID);
}

const bool FabiEngine3D::textEntity_isVisible(const string& ID)
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
	Vec2 newSize = entity->getSize();
	if (charWidth >= 0.0f)
	{
		newSize.x = (charWidth * static_cast<float>(textContent.size()));
	}
	if (charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}
	entity->setSize(newSize);

	// Reload
	if (entity->isDynamic())
	{
		_core->_textEntityManager.reloadCharacters(ID);
	}
	else
	{
		entity->setDiffuseMap(_core->_textureLoader.getText(textContent, entity->getFontPath()));
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

void FabiEngine3D::textEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::textEntity_setRotation(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::textEntity_setSize(const string& ID, Vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->setSize(size);
}

void FabiEngine3D::textEntity_move(const string& ID, Vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->move(position);
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

const Vec2 FabiEngine3D::textEntity_getPosition(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::textEntity_getRotation(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::textEntity_getAlpha(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getAlpha();
}

const Vec2 FabiEngine3D::textEntity_getSize(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getSize();
}

const Vec2 FabiEngine3D::textEntity_getMinPosition(const string& ID)
{
	return  _core->_textEntityManager.getEntity(ID)->getMinPosition();
}

const Vec2 FabiEngine3D::textEntity_getMaxPosition(const string& ID)
{
	return  _core->_textEntityManager.getEntity(ID)->getMaxPosition();
}

const Vec3 FabiEngine3D::textEntity_getColor(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getColor();
}

const string& FabiEngine3D::textEntity_getTextContent(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}

const vector<string> FabiEngine3D::textEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}