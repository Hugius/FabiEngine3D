#include "engine_gui_text_field.hpp"

EngineGuiTextField::EngineGuiTextField(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 color, bool isCentered, bool isDynamic)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(color)
{
	_fe3d.textEntity_create(_entityID, isCentered, isDynamic);
	_fe3d.textEntity_setPosition(_entityID, position);
	_fe3d.textEntity_setSize(_entityID, size);
	_fe3d.textEntity_setColor(_entityID, color);
	_fe3d.textEntity_setFont(_entityID, "engine_assets\\fonts\\font.ttf");
	_fe3d.textEntity_setTextContent(_entityID, textContent);
}

EngineGuiTextField::~EngineGuiTextField()
{
	_fe3d.textEntity_delete(_entityID);
}

void EngineGuiTextField::setVisible(bool isVisible)
{
	_fe3d.textEntity_setVisible(_entityID, isVisible);
}

void EngineGuiTextField::changeTextContent(const string& content)
{
	// Check if text content changed
	if (content != _fe3d.textEntity_getTextContent(_entityID))
	{
		auto charWidth = (_originalSize.x / static_cast<float>(_fe3d.textEntity_getTextContent(_entityID).size()));
		auto charHeight = _originalSize.y;
		_fe3d.textEntity_setTextContent(_entityID, content, charWidth, charHeight);
		updateOriginalSize();
	}
}

void EngineGuiTextField::updateOriginalPosition()
{
	_originalPosition = _fe3d.textEntity_getPosition(_entityID);
}

void EngineGuiTextField::updateOriginalSize()
{
	_originalSize = _fe3d.textEntity_getSize(_entityID);
}

void EngineGuiTextField::updateOriginalColor()
{
	_originalColor = _fe3d.textEntity_getColor(_entityID);
}

const Vec2 EngineGuiTextField::getOriginalPosition()
{
	return _originalPosition;
}

const Vec2 EngineGuiTextField::getOriginalSize()
{
	return _originalSize;
}

const Vec3 EngineGuiTextField::getOriginalColor()
{
	return _originalColor;
}

const string& EngineGuiTextField::getID()
{
	return _ID;
}

const string& EngineGuiTextField::getEntityID()
{
	return _entityID;
}

const string& EngineGuiTextField::getParentID()
{
	return _parentID;
}