#include "gui_input_box.hpp"
#include "tools.hpp"

#include <windows.h>

GuiInputBox::GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, unsigned int maxCharacterCount, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(id),
	_defaultQuadColor(defaultQuadColor),
	_hoveredQuadColor(hoveredQuadColor),
	_defaultTextColor(defaultTextColor),
	_hoveredTextColor(hoveredTextColor),
	_maxCharacterCount(maxCharacterCount),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{
	if(_id.empty())
	{
		abort();
	}

	_quadField = make_shared<GuiQuadField>(fe3d, "GuiInputBox", (parentId + "_" + id), position, size, "", defaultQuadColor, isCentered);
	_textField = make_shared<GuiTextField>(fe3d, "GuiInputBox", (parentId + "_" + id), position, fvec2((size.x / static_cast<float>(maxCharacterCount)), size.y), "", fvec3(1.0f), isCentered);
}

void GuiInputBox::update(bool isFocused)
{
	_updateHovering(isFocused);
	_updateActivation();
	_updateTyping();
}

void GuiInputBox::_updateActivation()
{
	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		_isActive = _isHovered;
	}
}

void GuiInputBox::_updateTyping()
{
	auto textContent = _textField->getTextContent();

	if(_isActive)
	{
		if(textContent.size() < _maxCharacterCount)
		{
			if(!_noLetters)
			{
				for(const auto & character : ALPHABET_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(character)))
					{
						if(character == ' ')
						{
							textContent += character;
						}
						else
						{
							if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
							{
								textContent += (character - 32);
							}
							else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
							{
								if(!_noCaps)
								{
									textContent += (character - 32);
								}
							}
							else
							{
								textContent += character;
							}
						}
					}
				}
			}

			if(!_noNumbers)
			{
				for(const auto & character : NUMBER_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(character.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							textContent += character.second;
						}
						else
						{
							textContent += character.first;
						}
					}
				}
			}

			if(!_noSpecials)
			{
				for(const auto & character : SPECIAL_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(character.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							textContent += character.second;
						}
						else
						{
							textContent += character.first;
						}
					}
				}
			}
			else if(_minusAllowed && !_noNumbers)
			{
				if(_fe3d->input_isKeyPressed(InputType('-')))
				{
					if(!_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) && !_fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
					{
						if(textContent.empty())
						{
							textContent += '-';
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
			_textField->setTextContent(textContent);
		}
		else
		{
			_textField->setTextContent(textContent);
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_ENTER))
		{
			if(!textContent.empty())
			{
				_isConfirmed = true;
				_isActive = false;
			}
		}
	}
	else
	{
		_textField->setTextContent(textContent);
		_isConfirmed = false;
	}

	_lastTextContent = textContent;
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

const bool GuiInputBox::isConfirmed() const
{
	return _isConfirmed;
}

const bool GuiInputBox::isActive() const
{
	return _isActive;
}

const bool GuiInputBox::hasTextContentChanged() const
{
	return (_lastTextContent != getTextContent());
}

const bool GuiInputBox::isCentered() const
{
	return _quadField->isCentered();
}

const string GuiInputBox::getTextContent() const
{
	//if(textContent == "-" && _noSpecials && _minusAllowed)
	//{
	//	return "";
	//}
	//else
	//{
	//	return textContent;
	//}

	return _textField->getTextContent();
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

void GuiInputBox::setTextContent(const string & content)
{
	_textField->setTextContent(content);
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

void GuiInputBox::_updateHovering(bool isFocused)
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
						if(isFocused && _isHoverable)
						{
							_isHovered = true;
						}
					}
				}
			}
		}

		if(_isHovered)
		{
			_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

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