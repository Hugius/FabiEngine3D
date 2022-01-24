#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentID + "_button", ID, position, size, color, isCentered)),
	_textField(make_shared<GuiTextField>(fe3d, parentID + "_button", ID, position, fvec2(size.x* TEXT_WIDTH_MULTIPLIER, size.y* TEXT_HEIGHT_MULTIPLIER), textContent, textColor, isCentered)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor)
{

}

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentID + "_button", ID, position, size, texturePath, isCentered)),
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

	if(_fe3d->quad2d_isVisible(_rectangle->getEntityID()))
	{
		fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d->quad2d_getPosition(_rectangle->getEntityID());
		fvec2 buttonSize = _fe3d->quad2d_getSize(_rectangle->getEntityID());

		if(cursorPosition.x > buttonPosition.x - (buttonSize.x / 2.0f) && cursorPosition.x < buttonPosition.x + (buttonSize.x / 2.0f))
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y / 2.0f) && cursorPosition.y < buttonPosition.y + (buttonSize.y / 2.0f))
			{
				if(isHoverable && _isHoverable)
				{
					_isHovered = true;

					_fe3d->quad2d_setColor(_rectangle->getEntityID(), _hoverColor);

					if(_textField != nullptr)
					{
						_fe3d->text2d_setColor(_textField->getEntityID(), _textHoverColor);
					}
				}
			}
		}

		if(!_isHovered)
		{
			_fe3d->quad2d_setColor(_rectangle->getEntityID(), _rectangle->getInitialColor());

			if(_textField != nullptr)
			{
				_fe3d->text2d_setColor(_textField->getEntityID(), _textField->getInitialColor());
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
		_fe3d->quad2d_setOpacity(_rectangle->getEntityID(), 1.0f);

		if(_textField != nullptr)
		{
			_fe3d->text2d_setOpacity(_textField->getEntityID(), 1.0f);
		}
	}
	else
	{
		_fe3d->quad2d_setOpacity(_rectangle->getEntityID(), 0.25f);

		if(_textField != nullptr)
		{
			_fe3d->text2d_setOpacity(_textField->getEntityID(), 0.25f);
		}
	}
}

void GuiButton::changeTextContent(const string& content)
{
	auto text2dEntityID = getTextField()->getEntityID();

	if(content != _fe3d->text2d_getContent(text2dEntityID))
	{
		auto charWidth = (getTextField()->getInitialSize().x / static_cast<float>(_fe3d->text2d_getContent(text2dEntityID).size()));
		auto charHeight = getTextField()->getInitialSize().y;
		_fe3d->text2d_setContent(text2dEntityID, content, charWidth, charHeight);
		getTextField()->updateInitialSize();

		auto newRectangleSize = fvec2(getTextField()->getInitialSize() / fvec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));
		_fe3d->quad2d_setSize(getRectangle()->getEntityID(), newRectangleSize);
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

const string& GuiButton::getID() const
{
	return _ID;
}

const string& GuiButton::getParentID() const
{
	return _parentID;
}

shared_ptr<GuiRectangle> GuiButton::getRectangle() const
{
	return _rectangle;
}

shared_ptr<GuiTextField> GuiButton::getTextField() const
{
	return _textField;
}