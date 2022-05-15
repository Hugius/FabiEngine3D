#include "gui_input_box.hpp"
#include "tools.hpp"

GuiInputBox::GuiInputBox(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered)
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
			const auto isCapsLockToggled = _fe3d->input_isKeyboardToggled(KeyboardKeyType::KEY_CAPSLOCK);
			const auto isShiftHeld = _fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT);

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SPACEBAR))
			{
				if(_isLettersAllowed)
				{
					textContent += ' ';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_A))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'A' : 'a');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_B))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'B' : 'b');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_C))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'C' : 'c');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_D))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'D' : 'd');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_E))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'E' : 'e');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'F' : 'f');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'G' : 'g');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_H))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'H' : 'h');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_I))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'I' : 'i');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_J))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'J' : 'j');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_K))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'K' : 'k');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_L))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'L' : 'l');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_M))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'M' : 'm');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_N))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'N' : 'n');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_O))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'O' : 'o');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_P))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'P' : 'p');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Q))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'Q' : 'q');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'R' : 'r');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_S))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'S' : 's');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_T))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled || isShiftHeld) ? 'T' : 't');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_U))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'U' : 'u');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_V))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'V' : 'v');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_W))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'W' : 'w');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_X))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'X' : 'x');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Y))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'Y' : 'y');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Z))
			{
				if(_isLettersAllowed)
				{
					textContent += ((isCapsLockToggled != isShiftHeld) ? 'Z' : 'z');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_0))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '0';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += ')';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_1))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '1';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '!';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_2))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '2';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '@';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_3))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '3';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '#';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_4))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '4';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '$';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_5))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '5';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '%';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_6))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '6';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '^';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_7))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '7';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '&';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_8))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '8';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '*';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_9))
			{
				if(_isNumbersAllowed && !isShiftHeld)
				{
					textContent += '9';
				}

				if(_isSpecialsAllowed && isShiftHeld)
				{
					textContent += '(';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD0))
			{
				if(_isNumbersAllowed)
				{
					textContent += '0';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD1))
			{
				if(_isNumbersAllowed)
				{
					textContent += '1';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD2))
			{
				if(_isNumbersAllowed)
				{
					textContent += '2';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD3))
			{
				if(_isNumbersAllowed)
				{
					textContent += '3';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD4))
			{
				if(_isNumbersAllowed)
				{
					textContent += '4';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD5))
			{
				if(_isNumbersAllowed)
				{
					textContent += '5';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD6))
			{
				if(_isNumbersAllowed)
				{
					textContent += '6';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD7))
			{
				if(_isNumbersAllowed)
				{
					textContent += '7';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD8))
			{
				if(_isNumbersAllowed)
				{
					textContent += '8';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD9))
			{
				if(_isNumbersAllowed)
				{
					textContent += '9';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SEMICOLON))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? ':' : ';');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_EQUAL))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '+' : '=');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_COMMA))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '<' : ',');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_MINUS))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '_' : '-');
				}
				else
				{
					if(!isShiftHeld && _isNumbersAllowed && !_isLettersAllowed && textContent.empty())
					{
						textContent += '-';
					}
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_PERIOD))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '>' : '.');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_FORWARDSLASH))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '?' : '/');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_GRAVE))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '~' : '`');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_LEFTBRACKET))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '{' : '[');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_BACKWARDSLASH))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '|' : '\\');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_RIGHTBRACKET))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '}' : ']');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_QUOTE))
			{
				if(_isSpecialsAllowed)
				{
					textContent += (isShiftHeld ? '"' : '\'');
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_MULTIPLY))
			{
				if(_isSpecialsAllowed)
				{
					textContent += '*';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DIVIDE))
			{
				if(_isSpecialsAllowed)
				{
					textContent += '/';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ADD))
			{
				if(_isSpecialsAllowed)
				{
					textContent += '+';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SUBTRACT))
			{
				if(_isSpecialsAllowed || (_isNumbersAllowed && !_isLettersAllowed && textContent.empty()))
				{
					textContent += '-';
				}
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DECIMAL))
			{
				if(_isSpecialsAllowed)
				{
					textContent += '.';
				}
			}
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_BACKSPACE))
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

		if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / BAR_UPDATE_DIVIDER)) == 0)
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

const int GuiInputBox::getMaxCharacterCount() const
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

void GuiInputBox::setMaxCharacterCount(int value)
{
	_maxCharacterCount = max(0, value);
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
		const auto cursorPosition = Tools::convertToNdc(Tools::getCursorPosition());
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
				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_POINTING_TEXTURE_PATH);
			}
		}
		else
		{
			_quadField->setColor(_defaultQuadColor);
			_textField->setColor(_defaultTextColor);
		}
	}
}