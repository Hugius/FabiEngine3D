#include "EngineGuiRectangle.hpp"

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(color)
{
	_fe3d.guiEntity_add(_entityID, color, position, 0.0f, size, false);
}

EngineGuiRectangle::~EngineGuiRectangle()
{
	_fe3d.guiEntity_delete(_entityID);
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