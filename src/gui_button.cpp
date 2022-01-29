#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentId + "_button", id, position, size, color, isCentered)),
	_textField(make_shared<GuiTextField>(fe3d, parentId + "_button", id, position, fvec2(size.x* TEXT_WIDTH_MULTIPLIER, size.y* TEXT_HEIGHT_MULTIPLIER), textContent, textColor, isCentered)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor)
{

}

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentId + "_button", id, position, size, texturePath, isCentered)),
	_hoverColor(hoverColor)
{

}

void GuiButton::update(bool isHoverable)
{
	_updateHovering(isHoverable);
}

void GuiButton::setVisible(bool isVisible)
{
	_rectangle->setVisible(isVisible);

	if(_textField != nullptr)
	{
		_textField->setVisible(isVisible);
	}
}

void GuiButton::_updateHovering(bool isHoverable)
{
	_isHovered = false;

	if(_fe3d->quad2d_isVisible(_rectangle->getEntityId()))
	{
		fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d->quad2d_getPosition(_rectangle->getEntityId());
		fvec2 buttonSize = _fe3d->quad2d_getSize(_rectangle->getEntityId());

		if(cursorPosition.x > buttonPosition.x - (buttonSize.x * 0.5f) && cursorPosition.x < buttonPosition.x + (buttonSize.x * 0.5f))
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y * 0.5f) && cursorPosition.y < buttonPosition.y + (buttonSize.y * 0.5f))
			{
				if(isHoverable && _isHoverable)
				{
					_isHovered = true;

					_fe3d->quad2d_setColor(_rectangle->getEntityId(), _hoverColor);

					if(_textField != nullptr)
					{
						_fe3d->text2d_setColor(_textField->getEntityId(), _textHoverColor);
					}
				}
			}
		}

		if(!_isHovered)
		{
			_fe3d->quad2d_setColor(_rectangle->getEntityId(), _rectangle->getInitialColor());

			if(_textField != nullptr)
			{
				_fe3d->text2d_setColor(_textField->getEntityId(), _textField->getInitialColor());
			}
		}
	}

	if(_isHovered)
	{
		_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
	}
}

void GuiButton::setHoverable(bool isHoverable)
{
	_isHoverable = isHoverable;

	if(isHoverable)
	{
		_fe3d->quad2d_setOpacity(_rectangle->getEntityId(), 1.0f);

		if(_textField != nullptr)
		{
			_fe3d->text2d_setOpacity(_textField->getEntityId(), 1.0f);
		}
	}
	else
	{
		_fe3d->quad2d_setOpacity(_rectangle->getEntityId(), 0.25f);

		if(_textField != nullptr)
		{
			_fe3d->text2d_setOpacity(_textField->getEntityId(), 0.25f);
		}
	}
}

void GuiButton::changeTextContent(const string& content)
{
	auto text2dEntityId = getTextField()->getEntityId();

	if(content != _fe3d->text2d_getContent(text2dEntityId))
	{
		auto charWidth = (getTextField()->getInitialSize().x / static_cast<float>(_fe3d->text2d_getContent(text2dEntityId).size()));
		auto charHeight = getTextField()->getInitialSize().y;
		_fe3d->text2d_setContent(text2dEntityId, content, charWidth, charHeight);
		getTextField()->updateInitialSize();

		auto newRectangleSize = fvec2(getTextField()->getInitialSize() / fvec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));
		_fe3d->quad2d_setSize(getRectangle()->getEntityId(), newRectangleSize);
		getRectangle()->updateInitialSize();
	}
}

const bool GuiButton::isHoverable() const
{
	return _isHoverable;
}

const bool GuiButton::isHovered() const
{
	return _isHovered;
}

const string& GuiButton::getId() const
{
	return _id;
}

const string& GuiButton::getParentId() const
{
	return _parentId;
}

shared_ptr<GuiRectangle> GuiButton::getRectangle() const
{
	return _rectangle;
}

shared_ptr<GuiTextField> GuiButton::getTextField() const
{
	return _textField;
}