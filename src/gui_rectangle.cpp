#include "gui_rectangle.hpp"

GuiRectangle::GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(id),
	_entityId("@" + parentID + "_" + id),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad2d_create(_entityId, isCentered);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);
}

GuiRectangle::GuiRectangle(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(id),
	_entityId("@" + parentID + "_" + id),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(fvec3(1.0f))
{
	_fe3d->quad2d_create(_entityId, isCentered);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setDiffuseMap(_entityId, ("engine\\assets\\image\\diffuse_map\\" + texturePath));
}

GuiRectangle::~GuiRectangle()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiRectangle::setVisible(bool isVisible)
{
	_fe3d->quad2d_setVisible(_entityId, isVisible);
}

void GuiRectangle::updateInitialPosition()
{
	_initialPosition = _fe3d->quad2d_getPosition(_entityId);
}

void GuiRectangle::updateInitialSize()
{
	_initialSize = _fe3d->quad2d_getSize(_entityId);
}

void GuiRectangle::updateInitialColor()
{
	_initialColor = _fe3d->quad2d_getColor(_entityId);
}

const fvec2& GuiRectangle::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2& GuiRectangle::getInitialSize() const
{
	return _initialSize;
}

const fvec3& GuiRectangle::getInitialColor() const
{
	return _initialColor;
}

const string& GuiRectangle::getId() const
{
	return _ID;
}

const string& GuiRectangle::getEntityId() const
{
	return _entityId;
}

const string& GuiRectangle::getParentID() const
{
	return _parentID;
}