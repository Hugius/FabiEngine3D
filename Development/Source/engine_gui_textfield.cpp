#include "engine_gui_textfield.hpp"

EngineGuiTextfield::EngineGuiTextfield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID),
	_originalColor(textColor),
	_originalPosition(position),
	_originalSize(size)
{
	_fe3d.textEntity_add(_entityID, textContent, "Engine\\Fonts\\lucida.ttf", textColor, position, 0.0f, size, true);
}

EngineGuiTextfield::~EngineGuiTextfield()
{
	_fe3d.textEntity_delete(_entityID);
}

void EngineGuiTextfield::show()
{
	_fe3d.textEntity_show(_entityID);
}

void EngineGuiTextfield::hide()
{
	_fe3d.textEntity_hide(_entityID);
}

vec3 EngineGuiTextfield::getOriginalColor()
{
	return _originalColor;
}

vec2 EngineGuiTextfield::getOriginalPosition()
{
	return _originalPosition;
}

vec2 EngineGuiTextfield::getOriginalSize()
{
	return _originalSize;
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