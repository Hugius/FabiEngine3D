#include "gui_text_field.hpp"

GuiTextField::GuiTextField(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(id),
	_entityId("@" + parentID + "_" + id),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->text2d_create(_entityId, FONT_MAP_PATH, isCentered);
	_fe3d->text2d_setPosition(_entityId, position);
	_fe3d->text2d_setSize(_entityId, size);
	_fe3d->text2d_setColor(_entityId, color);
	_fe3d->text2d_setContent(_entityId, textContent);
}

GuiTextField::~GuiTextField()
{
	_fe3d->text2d_delete(_entityId);
}

void GuiTextField::setVisible(bool isVisible)
{
	_fe3d->text2d_setVisible(_entityId, isVisible);
}

void GuiTextField::changeTextContent(const string& content)
{
	if(content != _fe3d->text2d_getContent(_entityId))
	{
		auto charWidth = (_initialSize.x / static_cast<float>(_fe3d->text2d_getContent(_entityId).size()));
		auto charHeight = _initialSize.y;
		_fe3d->text2d_setContent(_entityId, content, charWidth, charHeight);
		updateInitialSize();
	}
}

void GuiTextField::updateInitialPosition()
{
	_initialPosition = _fe3d->text2d_getPosition(_entityId);
}

void GuiTextField::updateInitialSize()
{
	_initialSize = _fe3d->text2d_getSize(_entityId);
}

void GuiTextField::updateInitialColor()
{
	_initialColor = _fe3d->text2d_getColor(_entityId);
}

const fvec2& GuiTextField::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2& GuiTextField::getInitialSize() const
{
	return _initialSize;
}

const fvec3& GuiTextField::getInitialColor() const
{
	return _initialColor;
}

const string& GuiTextField::getId() const
{
	return _ID;
}

const string& GuiTextField::getEntityId() const
{
	return _entityId;
}

const string& GuiTextField::getParentID() const
{
	return _parentID;
}