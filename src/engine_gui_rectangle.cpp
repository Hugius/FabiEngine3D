#include "engine_gui_rectangle.hpp"

EngineGuiRectangle::EngineGuiRectangle(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
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
	_initialPosition(position),
	_initialSize(size),
	_initialColor(Vec3(1.0f))
{
	_fe3d.imageEntity_create(_entityID, isCentered);
	_fe3d.imageEntity_setPosition(_entityID, position);
	_fe3d.imageEntity_setSize(_entityID, size);
	_fe3d.imageEntity_setDiffuseMap(_entityID, ("engine\\assets\\textures\\" + texturePath));
}

EngineGuiRectangle::~EngineGuiRectangle()
{
	_fe3d.imageEntity_delete(_entityID);
}

void EngineGuiRectangle::setVisible(bool isVisible)
{
	_fe3d.imageEntity_setVisible(_entityID, isVisible);
}

void EngineGuiRectangle::updateInitialPosition()
{
	_initialPosition = _fe3d.imageEntity_getPosition(_entityID);
}

void EngineGuiRectangle::updateInitialSize()
{
	_initialSize = _fe3d.imageEntity_getSize(_entityID);
}

void EngineGuiRectangle::updateInitialColor()
{
	_initialColor = _fe3d.imageEntity_getColor(_entityID);
}

const Vec2 EngineGuiRectangle::getInitialPosition() const
{
	return _initialPosition;
}

const Vec2 EngineGuiRectangle::getInitialSize() const
{
	return _initialSize;
}

const Vec3 EngineGuiRectangle::getInitialColor() const
{
	return _initialColor;
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