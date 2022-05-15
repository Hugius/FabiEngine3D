#include "gui_text_field.hpp"

GuiTextField::GuiTextField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & color, bool isCentered)
	:
	_id(id),
	_parentId(parentId),
	_text2dId("@@" + parentId + "_" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->text2d_create(_text2dId, FONT_MAP_PATH, isCentered);
	_fe3d->text2d_setPosition(_text2dId, position);
	_fe3d->text2d_setSize(_text2dId, size);
	_fe3d->text2d_setColor(_text2dId, color);
	_fe3d->text2d_setContent(_text2dId, textContent);
}

GuiTextField::~GuiTextField()
{
	_fe3d->text2d_delete(_text2dId);
}

void GuiTextField::setVisible(bool value)
{
	_fe3d->text2d_setVisible(_text2dId, value);
}

void GuiTextField::setColor(const fvec3 & value)
{
	_fe3d->text2d_setColor(_text2dId, value);
}

void GuiTextField::setPosition(const fvec2 & value)
{
	_fe3d->text2d_setPosition(_text2dId, value);
}

void GuiTextField::setSize(const fvec2 & value)
{
	_fe3d->text2d_setSize(_text2dId, value);
}

void GuiTextField::setTextContent(const string & value)
{
	const auto currentContent = _fe3d->text2d_getContent(_text2dId);

	if(value != currentContent)
	{
		_fe3d->text2d_setContent(_text2dId, value);

		const auto textSize = getSize();

		if(currentContent.empty())
		{
			_fe3d->text2d_setSize(_text2dId, fvec2((textSize.x * static_cast<float>(value.size())), textSize.y));
		}
		else
		{
			const auto characterWidth = (textSize.x / static_cast<float>(currentContent.size()));
			const auto characterHeight = textSize.y;

			if(value.empty())
			{
				_fe3d->text2d_setSize(_text2dId, fvec2(characterWidth, characterHeight));
			}
			else
			{
				_fe3d->text2d_setSize(_text2dId, fvec2((characterWidth * static_cast<float>(value.size())), characterHeight));
			}
		}
	}
}

void GuiTextField::setOpacity(float value)
{
	_fe3d->text2d_setOpacity(_text2dId, value);
}

void GuiTextField::setMinClipPosition(const fvec2 & value)
{
	_fe3d->text2d_setMinClipPosition(_text2dId, value);
}

void GuiTextField::setMaxClipPosition(const fvec2 & value)
{
	_fe3d->text2d_setMaxClipPosition(_text2dId, value);
}

const fvec2 & GuiTextField::getPosition() const
{
	return _fe3d->text2d_getPosition(_text2dId);
}

const fvec2 & GuiTextField::getSize() const
{
	return _fe3d->text2d_getSize(_text2dId);
}

const bool GuiTextField::isVisible() const
{
	return _fe3d->text2d_isVisible(_text2dId);
}

const bool GuiTextField::isCentered() const
{
	return _fe3d->text2d_isCentered(_text2dId);
}

const fvec3 & GuiTextField::getColor() const
{
	return _fe3d->text2d_getColor(_text2dId);
}

const string & GuiTextField::getId() const
{
	return _id;
}

const string & GuiTextField::getTextContent() const
{
	return _fe3d->text2d_getContent(_text2dId);
}

const string & GuiTextField::getParentId() const
{
	return _parentId;
}