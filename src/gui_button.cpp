#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_quadField(make_shared<GuiQuadField>(fe3d, "GuiButton", (parentId + "_" + id), position, size, defaultQuadColor, isCentered)),
	_textField(make_shared<GuiTextField>(fe3d, "GuiButton", (parentId + "_" + id), position, fvec2((size.x * TEXT_WIDTH_MULTIPLIER), (size.y * TEXT_HEIGHT_MULTIPLIER)), textContent, defaultTextColor, isCentered)),
	_defaultQuadColor(defaultQuadColor),
	_hoveredQuadColor(hoveredQuadColor),
	_defaultTextColor(defaultTextColor),
	_hoveredTextColor(hoveredTextColor)
{

}

GuiButton::GuiButton(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const string & texturePath, const fvec3 & hoveredQuadColor, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_quadField(make_shared<GuiQuadField>(fe3d, "GuiButton", (parentId + "_" + id), position, size, texturePath, isCentered)),
	_defaultQuadColor(fvec3(1.0f)),
	_hoveredQuadColor(hoveredQuadColor)
{

}

void GuiButton::update(bool isHoverable)
{
	_updateHovering(isHoverable);

	_quadField->setVisible(_isVisible);
	_quadField->setOpacity(_isHoverable ? DEFAULT_OPACITY : HOVER_OPACITY);

	if(_textField != nullptr)
	{
		_textField->setVisible(_isVisible);
		_textField->setOpacity(_isHoverable ? DEFAULT_OPACITY : HOVER_OPACITY);
	}
}

void GuiButton::setVisible(bool value)
{
	_isVisible = value;
}

void GuiButton::_updateHovering(bool isHoverable)
{
	_isHovered = false;

	if(_isVisible)
	{
		const auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
		const auto buttonPosition = _quadField->getPosition();
		const auto buttonSize = _quadField->getSize();

		if(cursorPosition.x > (buttonPosition.x - (buttonSize.x * 0.5f)))
		{
			if(cursorPosition.x < (buttonPosition.x + (buttonSize.x * 0.5f)))
			{
				if(cursorPosition.y > (buttonPosition.y - (buttonSize.y * 0.5f)))
				{
					if(cursorPosition.y < (buttonPosition.y + (buttonSize.y * 0.5f)))
					{
						if(isHoverable && _isHoverable)
						{
							_isHovered = true;
						}
					}
				}
			}
		}

		if(_isHovered)
		{
			_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

			_quadField->setColor(_hoveredQuadColor);

			if(_textField != nullptr)
			{
				_textField->setColor(_hoveredTextColor);
			}
		}
		else
		{
			_quadField->setColor(_defaultQuadColor);

			if(_textField != nullptr)
			{
				_textField->setColor(_defaultTextColor);
			}
		}
	}
}

void GuiButton::setHoverable(bool value)
{
	_isHoverable = value;
}

void GuiButton::changeTextContent(const string & content)
{
	_textField->changeTextContent(content);

	auto newQuadFieldSize = fvec2(_textField->getSize() / fvec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));

	_quadField->setSize(newQuadFieldSize);
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

const string & GuiButton::getId() const
{
	return _id;
}

const string & GuiButton::getParentId() const
{
	return _parentId;
}