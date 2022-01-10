#include "gui_rectangle.hpp"

GuiRectangle::GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad_create(_entityID, isCentered);
	_fe3d->quad_setPosition(_entityID, position);
	_fe3d->quad_setSize(_entityID, size);
	_fe3d->quad_setColor(_entityID, color);
}

GuiRectangle::GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(fvec3(1.0f))
{
	_fe3d->quad_create(_entityID, isCentered);
	_fe3d->quad_setPosition(_entityID, position);
	_fe3d->quad_setSize(_entityID, size);
	_fe3d->quad_setDiffuseMap(_entityID, ("engine\\assets\\image\\diffuse_map\\" + texturePath));
}

GuiRectangle::~GuiRectangle()
{
	_fe3d->quad_delete(_entityID);
}

void GuiRectangle::setVisible(bool isVisible)
{
	_fe3d->quad_setVisible(_entityID, isVisible);
}

void GuiRectangle::updateInitialPosition()
{
	_initialPosition = _fe3d->quad_getPosition(_entityID);
}

void GuiRectangle::updateInitialSize()
{
	_initialSize = _fe3d->quad_getSize(_entityID);
}

void GuiRectangle::updateInitialColor()
{
	_initialColor = _fe3d->quad_getColor(_entityID);
}

const fvec2 GuiRectangle::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2 GuiRectangle::getInitialSize() const
{
	return _initialSize;
}

const fvec3 GuiRectangle::getInitialColor() const
{
	return _initialColor;
}

const string& GuiRectangle::getID() const
{
	return _ID;
}

const string& GuiRectangle::getEntityID() const
{
	return _entityID;
}

const string& GuiRectangle::getParentID() const
{
	return _parentID;
}