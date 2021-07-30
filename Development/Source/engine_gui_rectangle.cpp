#include "engine_gui_rectangle.hpp"

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(color)
{
	_fe3d.imageEntity_create(_entityID, color, position, 0.0f, size, isCentered);
}

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(Vec3(1.0f))
{
	_fe3d.imageEntity_create(_entityID, "engine_assets\\textures\\" + texturePath, position, 0.0f, size, isCentered);
}

EngineGuiRectangle::~EngineGuiRectangle()
{
	_fe3d.imageEntity_delete(_entityID);
}

void EngineGuiRectangle::setVisible(bool isVisible)
{
	_fe3d.imageEntity_setVisible(_entityID, isVisible);
}

void EngineGuiRectangle::updateOriginalPosition()
{
	_originalPosition = _fe3d.imageEntity_getPosition(_entityID);
}

void EngineGuiRectangle::updateOriginalSize()
{
	_originalSize = _fe3d.imageEntity_getSize(_entityID);
}

void EngineGuiRectangle::updateOriginalColor()
{
	_originalColor = _fe3d.imageEntity_getColor(_entityID);
}

const Vec2 EngineGuiRectangle::getOriginalPosition()
{
	return _originalPosition;
}

const Vec2 EngineGuiRectangle::getOriginalSize()
{
	return _originalSize;
}

const Vec3 EngineGuiRectangle::getOriginalColor()
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