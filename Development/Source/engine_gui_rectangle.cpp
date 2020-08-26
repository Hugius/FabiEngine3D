#include "engine_gui_rectangle.hpp"

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, bool centered) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(color)
{
	_fe3d.guiEntity_add(_entityID, color, position, 0.0f, size, centered);
}

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, const string& textureName, bool centered) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(vec3(1.0f))
{
	_fe3d.guiEntity_add(_entityID, "Engine\\Textures\\" + textureName, position, 0.0f, size, centered);
}

EngineGuiRectangle::~EngineGuiRectangle()
{
	_fe3d.guiEntity_delete(_entityID);
}

void EngineGuiRectangle::show()
{
	_fe3d.guiEntity_show(_entityID);
}

void EngineGuiRectangle::hide()
{
	_fe3d.guiEntity_hide(_entityID);
}

vec2 EngineGuiRectangle::getOriginalPosition()
{
	return _originalPosition;
}

vec2 EngineGuiRectangle::getOriginalSize()
{
	return _originalSize;
}

vec3 EngineGuiRectangle::getOriginalColor()
{
	return _originalColor;
}

const string& EngineGuiRectangle::getID()
{
	return _ID;
}

const string& EngineGuiRectangle::getEntityID()
{
	return _entityID;
}

const string& EngineGuiRectangle::getParentID()
{
	return _parentID;
}