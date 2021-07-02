#include "engine_gui_textfield.hpp"

EngineGuiTextfield::EngineGuiTextfield(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, 
	string textContent, Vec3 textColor, bool isCentered, bool isDynamic) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(textColor)
{
	_fe3d.textEntity_add(_entityID, textContent, "engine_assets\\fonts\\font.ttf", textColor, position, 0.0f, size, isCentered, isDynamic);
}

EngineGuiTextfield::~EngineGuiTextfield()
{
	_fe3d.textEntity_delete(_entityID);
}

void EngineGuiTextfield::setVisible(bool isVisible)
{
	_fe3d.textEntity_setVisible(_entityID, isVisible);
}

void EngineGuiTextfield::updateOriginalPosition()
{
	_originalPosition = _fe3d.textEntity_getPosition(_entityID);
}

void EngineGuiTextfield::updateOriginalSize()
{
	_originalSize = _fe3d.textEntity_getSize(_entityID);
}

void EngineGuiTextfield::updateOriginalColor()
{
	_originalColor = _fe3d.textEntity_getColor(_entityID);
}

const Vec2 EngineGuiTextfield::getOriginalPosition()
{
	return _originalPosition;
}

const Vec2 EngineGuiTextfield::getOriginalSize()
{
	return _originalSize;
}

const Vec3 EngineGuiTextfield::getOriginalColor()
{
	return _originalColor;
}

const string& EngineGuiTextfield::getID()
{
	return _ID;
}

const string& EngineGuiTextfield::getEntityID()
{
	return _entityID;
}

const string& EngineGuiTextfield::getParentID()
{
	return _parentID;
}