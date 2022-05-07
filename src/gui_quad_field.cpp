#include "gui_quad_field.hpp"

GuiQuadField::GuiQuadField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
	:
	_id(id),
	_parentId(parentId),
	_quad2dId("@" + parentId + "_" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->quad2d_create(_quad2dId, isCentered);
	_fe3d->quad2d_setPosition(_quad2dId, position);
	_fe3d->quad2d_setSize(_quad2dId, size);
	_fe3d->quad2d_setColor(_quad2dId, color);

	if(!diffuseMapPath.empty())
	{
		_fe3d->quad2d_setDiffuseMap(_quad2dId, ("engine\\assets\\image\\diffuse_map\\" + diffuseMapPath));
	}
}

GuiQuadField::~GuiQuadField()
{
	_fe3d->quad2d_delete(_quad2dId);
}

void GuiQuadField::setVisible(bool value)
{
	_fe3d->quad2d_setVisible(_quad2dId, value);
}

void GuiQuadField::setColor(const fvec3 & value)
{
	_fe3d->quad2d_setColor(_quad2dId, value);
}

void GuiQuadField::setPosition(const fvec2 & value)
{
	_fe3d->quad2d_setPosition(_quad2dId, value);
}

void GuiQuadField::setSize(const fvec2 & value)
{
	_fe3d->quad2d_setSize(_quad2dId, value);
}

void GuiQuadField::setOpacity(float value)
{
	_fe3d->quad2d_setOpacity(_quad2dId, value);
}

void GuiQuadField::setMinClipPosition(const fvec2 & value)
{
	_fe3d->quad2d_setMinClipPosition(_quad2dId, value);
}

void GuiQuadField::setMaxClipPosition(const fvec2 & value)
{
	_fe3d->quad2d_setMaxClipPosition(_quad2dId, value);
}

void GuiQuadField::setDiffuseMap(const string & value)
{
	_fe3d->quad2d_setDiffuseMap(_quad2dId, value);
}

const fvec2 & GuiQuadField::getPosition() const
{
	return _fe3d->quad2d_getPosition(_quad2dId);
}

const fvec2 & GuiQuadField::getSize() const
{
	return _fe3d->quad2d_getSize(_quad2dId);
}

const bool GuiQuadField::isVisible() const
{
	return _fe3d->quad2d_isVisible(_quad2dId);
}

const bool GuiQuadField::isCentered() const
{
	return _fe3d->quad2d_isCentered(_quad2dId);
}

const fvec3 & GuiQuadField::getColor() const
{
	return _fe3d->quad2d_getColor(_quad2dId);
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
	return _fe3d->quad2d_getDiffuseMapPath(_quad2dId);
}