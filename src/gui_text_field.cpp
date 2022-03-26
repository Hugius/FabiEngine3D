#include "gui_text_field.hpp"

GuiTextField::GuiTextField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & color, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_entityId("@" + parentId + "_" + id)
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

void GuiTextField::setVisible(bool value)
{
	_fe3d->text2d_setVisible(_entityId, value);
}

void GuiTextField::setColor(const fvec3 & value)
{
	_fe3d->text2d_setColor(_entityId, value);
}

void GuiTextField::setPosition(const fvec2 & value)
{
	_fe3d->text2d_setPosition(_entityId, value);
}

void GuiTextField::setSize(const fvec2 & value)
{
	_fe3d->text2d_setSize(_entityId, value);
}

void GuiTextField::changeTextContent(const string & content)
{
	const auto currentContent = _fe3d->text2d_getContent(_entityId);

	if(content != currentContent)
	{
		const auto textSize = getSize();
		const auto characterWidth = (textSize.x / static_cast<float>(currentContent.size()));
		const auto characterHeight = textSize.y;

		_fe3d->text2d_setContent(_entityId, content);
		_fe3d->text2d_setSize(_entityId, fvec2((characterWidth * static_cast<float>(content.size())), characterHeight));
	}
}

void GuiTextField::setOpacity(float value)
{
	_fe3d->text2d_setOpacity(_entityId, value);
}

const fvec2 & GuiTextField::getPosition() const
{
	return _fe3d->text2d_getPosition(_entityId);
}

const fvec2 & GuiTextField::getSize() const
{
	return _fe3d->text2d_getSize(_entityId);
}

const bool GuiTextField::isVisible() const
{
	return _fe3d->text2d_isVisible(_entityId);
}

const fvec3 & GuiTextField::getColor() const
{
	return _fe3d->text2d_getColor(_entityId);
}

const string & GuiTextField::getId() const
{
	return _id;
}

const string & GuiTextField::getEntityId() const
{
	return _entityId;
}

const string & GuiTextField::getParentId() const
{
	return _parentId;
}