#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
	:
	_id(id),
	_parentId(parentId)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;
	_quadField = make_shared<GuiQuadField>(fe3d, "GuiButton", (parentId + "_" + id), position, size, diffuseMapPath, defaultQuadColor, isCentered);
	_textField = make_shared<GuiTextField>(fe3d, "GuiButton", (parentId + "_" + id), position, fvec2((size.x * TEXT_WIDTH_MULTIPLIER), (size.y * TEXT_HEIGHT_MULTIPLIER)), textContent, defaultTextColor, isCentered);
	_defaultQuadColor = defaultQuadColor;
	_hoveredQuadColor = hoveredQuadColor;
	_defaultTextColor = defaultTextColor;
	_hoveredTextColor = hoveredTextColor;
}

void GuiButton::update(bool isInteractable)
{
	_updateHovering(isInteractable);
}

void GuiButton::setVisible(bool value)
{
	_quadField->setVisible(value);
	_textField->setVisible(value);
}

void GuiButton::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	if(isVisible())
	{
		const auto cursorPosition = Tools::convertToNdc(Tools::getCursorPosition());
		const auto buttonPosition = _quadField->getPosition();
		const auto buttonSize = _quadField->getSize();

		if(isCentered())
		{
			if(cursorPosition.x > (buttonPosition.x - (buttonSize.x * 0.5f)))
			{
				if(cursorPosition.x < (buttonPosition.x + (buttonSize.x * 0.5f)))
				{
					if(cursorPosition.y > (buttonPosition.y - (buttonSize.y * 0.5f)))
					{
						if(cursorPosition.y < (buttonPosition.y + (buttonSize.y * 0.5f)))
						{
							if(isInteractable && _isHoverable)
							{
								_isHovered = true;
							}
						}
					}
				}
			}
		}
		else
		{
			if(cursorPosition.x > buttonPosition.x)
			{
				if(cursorPosition.x < (buttonPosition.x + buttonSize.x))
				{
					if(cursorPosition.y > buttonPosition.y)
					{
						if(cursorPosition.y < (buttonPosition.y + buttonSize.y))
						{
							if(isInteractable && _isHoverable)
							{
								_isHovered = true;
							}
						}
					}
				}
			}
		}

		if(_isHovered)
		{
			_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);

			_quadField->setColor(_hoveredQuadColor);
			_textField->setColor(_hoveredTextColor);
		}
		else
		{
			_quadField->setColor(_defaultQuadColor);
			_textField->setColor(_defaultTextColor);
		}
	}
}

void GuiButton::setHoverable(bool value, bool mustBeTransparent)
{
	_isHoverable = value;

	if(mustBeTransparent)
	{
		_quadField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
		_textField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
	}
}

void GuiButton::setDefaultQuadColor(const fvec3 & value)
{
	_defaultQuadColor = value;
}

void GuiButton::setHoveredQuadColor(const fvec3 & value)
{
	_hoveredQuadColor = value;
}

void GuiButton::setDefaultTextColor(const fvec3 & value)
{
	_defaultTextColor = value;
}

void GuiButton::setHoveredTextColor(const fvec3 & value)
{
	_hoveredTextColor = value;
}

void GuiButton::setPosition(const fvec2 & value)
{
	_quadField->setPosition(value);
	_textField->setPosition(value);
}

void GuiButton::setSize(const fvec2 & value)
{
	_quadField->setSize(value);
	_textField->setSize(value);
}

void GuiButton::setMinClipPosition(const fvec2 & value)
{
	_quadField->setMinClipPosition(value);
	_textField->setMinClipPosition(value);
}

void GuiButton::setMaxClipPosition(const fvec2 & value)
{
	_quadField->setMaxClipPosition(value);
	_textField->setMaxClipPosition(value);
}

void GuiButton::setDiffuseMap(const string & value)
{
	_quadField->setDiffuseMap(value);
}

void GuiButton::setTextContent(const string & value)
{
	_textField->setTextContent(value);

	_quadField->setSize(fvec2(_textField->getSize() / fvec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER)));
}

const bool GuiButton::isHoverable() const
{
	return _isHoverable;
}

const bool GuiButton::isHovered() const
{
	return _isHovered;
}

const bool GuiButton::isVisible() const
{
	return _quadField->isVisible();
}

const bool GuiButton::isCentered() const
{
	return _quadField->isCentered();
}

const string & GuiButton::getId() const
{
	return _id;
}

const string & GuiButton::getParentId() const
{
	return _parentId;
}

const string & GuiButton::getDiffuseMapPath() const
{
	return _quadField->getDiffuseMapPath();
}

const string & GuiButton::getTextContent() const
{
	return _textField->getTextContent();
}

const fvec3 & GuiButton::getDefaultQuadColor()
{
	return _defaultQuadColor;
}

const fvec3 & GuiButton::getHoveredQuadColor()
{
	return _hoveredQuadColor;
}

const fvec3 & GuiButton::getDefaultTextColor()
{
	return _defaultTextColor;
}

const fvec3 & GuiButton::getHoveredTextColor()
{
	return _hoveredTextColor;
}

const fvec2 & GuiButton::getPosition() const
{
	return _quadField->getPosition();
}

const fvec2 & GuiButton::getSize() const
{
	return _quadField->getSize();
}