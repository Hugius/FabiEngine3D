#include "gui_input_box.hpp"
#include "tools.hpp"

#include <windows.h>

GuiInputBox::GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(id),
	_defaultQuadColor(defaultQuadColor),
	_hoveredQuadColor(hoveredQuadColor),
	_defaultTextColor(defaultTextColor),
	_hoveredTextColor(hoveredTextColor),
	_maxCharacterCount(maxCharacterCount),
	_isLettersAllowed(isLettersAllowed),
	_isNumbersAllowed(isNumbersAllowed),
	_isSpecialsAllowed(isSpecialsAllowed)
{
	if(_id.empty())
	{
		abort();
	}

	_quadField = make_shared<GuiQuadField>(fe3d, "GuiInputBox", (parentId + "_" + id), position, size, "", defaultQuadColor, isCentered);
	_textField = make_shared<GuiTextField>(fe3d, "GuiInputBox", (parentId + "_" + id), position, fvec2((size.x / static_cast<float>(maxCharacterCount + 1)), size.y), " ", fvec3(1.0f), isCentered);
}

void GuiInputBox::update(bool isInteractable)
{
	_updateHovering(isInteractable);
	_updateTyping();
}

void GuiInputBox::_updateTyping()
{
	auto textContent = getTextContent();

	if(_isActive || _isHovered)
	{
		if(textContent.size() < _maxCharacterCount)
		{
			if(_isLettersAllowed || _isSpecialsAllowed)
			{
				if(_fe3d->input_isKeyPressed(InputType::KEY_SPACEBAR))
				{
					textContent += ' ';
				}
			}

			if(_fe3d->input_isKeyDown(InputType::KEY_SHIFT) || ((GetKeyState(VK_CAPITAL) & 0x0001) != 0))
			{
				for(const auto & [key, character] : SECOND_ALPHABET_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(_isLettersAllowed)
						{
							textContent += character;
						}
					}
				}
			}
			else
			{
				for(const auto & [key, character] : FIRST_ALPHABET_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(_isLettersAllowed)
						{
							textContent += character;
						}
					}
				}
			}

			if(_fe3d->input_isKeyDown(InputType::KEY_SHIFT))
			{
				for(const auto & [key, character] : SECOND_NUMBER_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(_isSpecialsAllowed)
						{
							textContent += character;
						}
					}
				}
			}
			else
			{
				for(const auto & [key, character] : FIRST_NUMBER_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(_isNumbersAllowed)
						{
							textContent += character;
						}
					}
				}
			}

			if(_fe3d->input_isKeyDown(InputType::KEY_SHIFT))
			{
				for(const auto & [key, character] : SECOND_SPECIAL_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(_isSpecialsAllowed)
						{
							textContent += character;
						}
					}
				}
			}
			else
			{
				for(const auto & [key, character] : FIRST_SPECIAL_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(key))
					{
						if(!_isLettersAllowed && _isNumbersAllowed && !_isSpecialsAllowed)
						{
							if((character == "-") && textContent.empty())
							{
								textContent += character;
							}
						}
						else
						{
							if(_isSpecialsAllowed)
							{
								textContent += character;
							}
						}
					}
				}
			}
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_BACKSPACE))
		{
			if(textContent.size() == 1)
			{
				textContent = "";
			}
			else
			{
				textContent = textContent.substr(0, textContent.size() - 1);
			}
		}

		if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 2)) == 0)
		{
			_isBarVisible = !_isBarVisible;
		}
	}
	else
	{
		_isBarVisible = false;
	}

	_textField->setTextContent(textContent + (_isBarVisible ? "|" : " "));
}

void GuiInputBox::setActive(bool value)
{
	_isActive = value;
}

const bool GuiInputBox::isHovered() const
{
	return _isHovered;
}

const bool GuiInputBox::isHoverable() const
{
	return _isHoverable;
}

const bool GuiInputBox::isVisible() const
{
	return _quadField->isVisible();
}

const bool GuiInputBox::isActive() const
{
	return _isActive;
}

const bool GuiInputBox::isCentered() const
{
	return _quadField->isCentered();
}

const string GuiInputBox::getTextContent() const
{
	const auto textContent = _textField->getTextContent();

	return textContent.substr(0, (textContent.size() - 1));
}

const fvec3 & GuiInputBox::getDefaultQuadColor()
{
	return _defaultQuadColor;
}

const fvec3 & GuiInputBox::getHoveredQuadColor()
{
	return _hoveredQuadColor;
}

const fvec3 & GuiInputBox::getDefaultTextColor()
{
	return _defaultTextColor;
}

const fvec3 & GuiInputBox::getHoveredTextColor()
{
	return _hoveredTextColor;
}

const fvec2 & GuiInputBox::getPosition() const
{
	return _quadField->getPosition();
}

const fvec2 & GuiInputBox::getSize() const
{
	return _quadField->getSize();
}

const unsigned int GuiInputBox::getMaxCharacterCount() const
{
	return _maxCharacterCount;
}

void GuiInputBox::setTextContent(const string & value)
{
	_textField->setTextContent(value + (_isBarVisible ? "|" : " "));
}

void GuiInputBox::setVisible(bool value)
{
	_quadField->setVisible(value);
	_textField->setVisible(value);
}

void GuiInputBox::setHoverable(bool value)
{
	_isHoverable = value;

	_quadField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
	_textField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
}

void GuiInputBox::setMaxCharacterCount(unsigned int value)
{
	_maxCharacterCount = value;
}

const string GuiInputBox::getId() const
{
	return _id;
}

const string GuiInputBox::getParentId() const
{
	return _parentId;
}

void GuiInputBox::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	if(isVisible())
	{
		const auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
		const auto boxPosition = getPosition();
		const auto boxSize = getSize();

		if(cursorPosition.x > (boxPosition.x - (boxSize.x * 0.5f)))
		{
			if(cursorPosition.x < (boxPosition.x + (boxSize.x * 0.5f)))
			{
				if(cursorPosition.y > (boxPosition.y - (boxSize.y * 0.5f)))
				{
					if(cursorPosition.y < (boxPosition.y + (boxSize.y * 0.5f)))
					{
						if(isInteractable && _isHoverable)
						{
							_isHovered = true;
						}
					}
				}
			}
		}

		if(_isActive || _isHovered)
		{
			_quadField->setColor(_hoveredQuadColor);
			_textField->setColor(_hoveredTextColor);

			if(_isHovered)
			{
				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
		}
		else
		{
			_quadField->setColor(_defaultQuadColor);
			_textField->setColor(_defaultTextColor);
		}
	}
}