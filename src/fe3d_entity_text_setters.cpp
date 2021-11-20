#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::textEntity_deleteAll()
{
	_core->_textEntityManager.deleteAllEntities();
}

void FabiEngine3D::textEntity_create(const string& ID, bool isCentered, bool isDynamic)
{
	_core->_textEntityManager.createEntity(ID, isCentered, isDynamic);
}

void FabiEngine3D::textEntity_delete(const string& ID)
{
	// Check if text if dynamic
	if(_core->_textEntityManager.isExisting(ID) && _core->_textEntityManager.getEntity(ID)->isDynamic())
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

void FabiEngine3D::textEntity_setFont(const string& ID, const string& fontPath)
{
	// Temporary values
	auto entity = _core->_textEntityManager.getEntity(ID);

	// Set font
	entity->setFontPath(fontPath);

	// Load text
	auto textContent = entity->getTextContent();
	if(!textContent.empty())
	{
		if(entity->isDynamic())
		{
			_core->_textEntityManager.loadCharacters(ID);
		}
		else
		{
			entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(textContent, fontPath));
		}
	}
}

void FabiEngine3D::textEntity_setTextContent(const string& ID, const string& textContent, float charWidth, float charHeight)
{
	// Temporary values
	auto entity = _core->_textEntityManager.getEntity(ID);

	// Font must be loaded
	auto fontPath = entity->getFontPath();
	if(fontPath.empty())
	{
		Logger::throwWarning("Tried to set text content of text with ID \"" + ID + "\": no font loaded!");
		return;
	}

	// Set new text
	entity->setTextContent(textContent);

	// Calculate new size
	Vec2 newSize = entity->getSize();
	if(charWidth >= 0.0f)
	{
		newSize.x = (charWidth * static_cast<float>(textContent.size()));
	}
	if(charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}
	entity->setSize(newSize);

	// Reload text
	if(entity->isDynamic())
	{
		_core->_textEntityManager.loadCharacters(ID);
	}
	else
	{
		entity->setDiffuseMap(_core->_textureLoader.loadTexture2D(textContent, entity->getFontPath()));
	}
}

void FabiEngine3D::textEntity_setColor(const string& ID, Vec3 color)
{
	_core->_textEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::textEntity_setTransparency(const string& ID, float transparency)
{
	_core->_textEntityManager.getEntity(ID)->setTransparency(transparency);
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

void FabiEngine3D::textEntity_moveTo(const string& ID, Vec2 target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::textEntity_rotateTo(const string& ID, float target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::textEntity_scaleTo(const string& ID, Vec2 target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::textEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_textEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::textEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_textEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}