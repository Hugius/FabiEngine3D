#include "engine_gui_text_field.hpp"

EngineGuiTextField::EngineGuiTextField(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 color, bool isCentered, bool isDynamic)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d.text_create(_entityID, isCentered, isDynamic);
	_fe3d.text_setPosition(_entityID, position);
	_fe3d.text_setSize(_entityID, size);
	_fe3d.text_setColor(_entityID, color);
	_fe3d.text_setFont(_entityID, "engine\\assets\\fonts\\font.ttf");
	_fe3d.text_setTextContent(_entityID, textContent);
}

EngineGuiTextField::~EngineGuiTextField()
{
	_fe3d.text_delete(_entityID);
}

void EngineGuiTextField::setVisible(bool isVisible)
{
	_fe3d.text_setVisible(_entityID, isVisible);
}

void EngineGuiTextField::changeTextContent(const string& content)
{
	// Check if text content changed
	if(content != _fe3d.text_getTextContent(_entityID))
	{
		auto charWidth = (_initialSize.x / static_cast<float>(_fe3d.text_getTextContent(_entityID).size()));
		auto charHeight = _initialSize.y;
		_fe3d.text_setTextContent(_entityID, content, charWidth, charHeight);
		updateInitialSize();
	}
}

void EngineGuiTextField::updateInitialPosition()
{
	_initialPosition = _fe3d.text_getPosition(_entityID);
}

void EngineGuiTextField::updateInitialSize()
{
	_initialSize = _fe3d.text_getSize(_entityID);
}

void EngineGuiTextField::updateInitialColor()
{
	_initialColor = _fe3d.text_getColor(_entityID);
}

const Vec2 EngineGuiTextField::getInitialPosition() const
{
	return _initialPosition;
}

const Vec2 EngineGuiTextField::getInitialSize() const
{
	return _initialSize;
}

const Vec3 EngineGuiTextField::getInitialColor() const
{
	return _initialColor;
}

const string& EngineGuiTextField::getID() const
{
	return _ID;
}

const string& EngineGuiTextField::getEntityID() const
{
	return _entityID;
}

const string& EngineGuiTextField::getParentID() const
{
	return _parentID;
}