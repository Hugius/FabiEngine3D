#include "engine_gui_rectangle.hpp"

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(color)
{
	_fe3d.imageEntity_create(_entityID, isCentered);
	_fe3d.imageEntity_setPosition(_entityID, position);
	_fe3d.imageEntity_setSize(_entityID, size);
	_fe3d.imageEntity_setColor(_entityID, color);
}

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size),
	_originalColor(Vec3(1.0f))
{
	_fe3d.imageEntity_create(_entityID, isCentered);
	_fe3d.imageEntity_setPosition(_entityID, position);
	_fe3d.imageEntity_setSize(_entityID, size);
	_fe3d.imageEntity_setDiffuseMap(_entityID, ("engine\\textures\\" + texturePath));
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

const Vec2 EngineGuiRectangle::getOriginalPosition() const
{
	return _originalPosition;
}

const Vec2 EngineGuiRectangle::getOriginalSize() const
{
	return _originalSize;
}

const Vec3 EngineGuiRectangle::getOriginalColor() const
{
	return _originalColor;
}

const string& EngineGuiRectangle::getID() const
{
	return _ID;
}

const string& EngineGuiRectangle::getEntityID() const
{
	return _entityID;
}

const string& EngineGuiRectangle::getParentID() const
{
	return _parentID;
}