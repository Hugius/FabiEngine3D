#include "gui_quad_field.hpp"

GuiQuadField::GuiQuadField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
	:
	_id(id),
	_parentId(parentId),
	_entityId("@" + parentId + "_" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->quad2d_create(_entityId, isCentered);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);

	if(!diffuseMapPath.empty())
	{
		_fe3d->quad2d_setDiffuseMap(_entityId, ("engine\\assets\\image\\diffuse_map\\" + diffuseMapPath));
	}
}

GuiQuadField::~GuiQuadField()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiQuadField::setVisible(bool value)
{
	_fe3d->quad2d_setVisible(_entityId, value);
}

void GuiQuadField::setColor(const fvec3 & value)
{
	_fe3d->quad2d_setColor(_entityId, value);
}

void GuiQuadField::setPosition(const fvec2 & value)
{
	_fe3d->quad2d_setPosition(_entityId, value);
}

void GuiQuadField::setSize(const fvec2 & value)
{
	_fe3d->quad2d_setSize(_entityId, value);
}

void GuiQuadField::setOpacity(float value)
{
	_fe3d->quad2d_setOpacity(_entityId, value);
}

void GuiQuadField::setMinClippingPosition(const fvec2 & value)
{
	_fe3d->quad2d_setMinClippingPosition(_entityId, value);
}

void GuiQuadField::setMaxClippingPosition(const fvec2 & value)
{
	_fe3d->quad2d_setMaxClippingPosition(_entityId, value);
}

void GuiQuadField::setDiffuseMap(const string & value)
{
	_fe3d->quad2d_setDiffuseMap(_entityId, value);
}

const fvec2 & GuiQuadField::getPosition() const
{
	return _fe3d->quad2d_getPosition(_entityId);
}

const fvec2 & GuiQuadField::getSize() const
{
	return _fe3d->quad2d_getSize(_entityId);
}

const bool GuiQuadField::isVisible() const
{
	return _fe3d->quad2d_isVisible(_entityId);
}

const bool GuiQuadField::isCentered() const
{
	return _fe3d->quad2d_isCentered(_entityId);
}

const fvec3 & GuiQuadField::getColor() const
{
	return _fe3d->quad2d_getColor(_entityId);
}

const string & GuiQuadField::getId() const
{
	return _id;
}

const string & GuiQuadField::getParentId() const
{
	return _parentId;
}

const string & GuiQuadField::getDiffuseMapPath() const
{
	return _fe3d->quad2d_getDiffuseMapPath(_entityId);
}