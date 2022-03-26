#include "gui_quad_field.hpp"

GuiQuadField::GuiQuadField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_entityId("@" + parentId + "_" + id),
	_parentId(parentId)
{
	_fe3d->quad2d_create(_entityId, isCentered);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);
}

GuiQuadField::GuiQuadField(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_entityId("@" + parentId + "_" + id),
	_parentId(parentId)
{
	_fe3d->quad2d_create(_entityId, isCentered);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setDiffuseMap(_entityId, ("engine\\assets\\image\\diffuse_map\\" + texturePath));
}

GuiQuadField::~GuiQuadField()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiQuadField::setVisible(bool isVisible)
{
	_fe3d->quad2d_setVisible(_entityId, isVisible);
}

const fvec2& GuiQuadField::getPosition() const
{
	return _fe3d->quad2d_getPosition(_entityId);
}

const fvec2& GuiQuadField::getSize() const
{
	return _fe3d->quad2d_getSize(_entityId);
}

const fvec3& GuiQuadField::getColor() const
{
	return _fe3d->quad2d_getColor(_entityId);
}

const string& GuiQuadField::getId() const
{
	return _id;
}

const string& GuiQuadField::getEntityId() const
{
	return _entityId;
}

const string& GuiQuadField::getParentId() const
{
	return _parentId;
}