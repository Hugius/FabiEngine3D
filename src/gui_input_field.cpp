#include "gui_input_field.hpp"
#include "tools.hpp"

#include <windows.h>

GuiInputField::GuiInputField(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(id),
	_defaultQuadColor(defaultQuadColor),
	_hoveredQuadColor(hoveredQuadColor),
	_defaultTextColor(defaultTextColor),
	_hoveredTextColor(hoveredTextColor),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{
	_quadField = make_shared<GuiQuadField>(fe3d, id, parentId, position, size, "", defaultQuadColor, isCentered);
	_textField = make_shared<GuiTextField>(fe3d, id, parentId, position, size, "", defaultTextColor, isCentered);
}

void GuiInputField::update(bool isFocused)
{
	_updateHovering(isFocused);
	_updateActivation();
	_updateTyping();
}

void GuiInputField::_updateActivation()
{
	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		_isActive = _isHovered;
	}
}

void GuiInputField::_updateTyping()
{
	if(_isActive)
	{
		static int passedBarFrames = MAX_PASSED_BAR_FRAMES;
		static int passedBackspaceFrames = MAX_PASSED_BACKSPACE_FRAMES;
		static bool barEnabled = true;

		if(passedBarFrames >= MAX_PASSED_BAR_FRAMES)
		{
			passedBarFrames = 0;

			barEnabled = !barEnabled;
		}
		else
		{
			passedBarFrames++;
		}

		if((static_cast<float>(_currentTextContent.size() + 1) * CHAR_WIDTH) < _textField->getSize().x)
		{
			string letterCharacters = " abcdefghijklmnopqrstuvwxyz";

			unordered_map<char, char> numberCharacterMap;
			numberCharacterMap['0'] = ')';
			numberCharacterMap['1'] = '!';
			numberCharacterMap['2'] = '@';
			numberCharacterMap['3'] = '#';
			numberCharacterMap['4'] = '$';
			numberCharacterMap['5'] = '%';
			numberCharacterMap['6'] = '^';
			numberCharacterMap['7'] = '&';
			numberCharacterMap['8'] = '*';
			numberCharacterMap['9'] = '(';

			unordered_map<char, char> specialCharacterMap;
			specialCharacterMap['.'] = '>';
			specialCharacterMap[','] = '<';
			specialCharacterMap['/'] = '?';
			specialCharacterMap[';'] = ':';
			specialCharacterMap['\''] = '\"';
			specialCharacterMap['['] = '{';
			specialCharacterMap[']'] = '}';
			specialCharacterMap['\\'] = '|';
			specialCharacterMap['-'] = '_';
			specialCharacterMap['='] = '+';

			if(!_noLetters)
			{
				for(const auto & c : letterCharacters)
				{
					if(_fe3d->input_isKeyPressed(InputType(c)))
					{
						if(c == ' ')
						{
							_currentTextContent += c;
						}
						else
						{
							if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
							{
								{
									_currentTextContent += (c - 32);
								}
							}
							else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
							{
								if(!_noCaps)
								{
									_currentTextContent += (c - 32);
								}
							}
							else
							{
								_currentTextContent += c;
							}
						}
					}
				}
			}

			if(!_noNumbers)
			{
				for(const auto & element : numberCharacterMap)
				{
					if(_fe3d->input_isKeyPressed(InputType(element.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							_currentTextContent += element.second;
						}
						else
						{
							_currentTextContent += element.first;
						}
					}
				}
			}

			if(!_noSpecials)
			{
				for(const auto & element : specialCharacterMap)
				{
					if(_fe3d->input_isKeyPressed(InputType(element.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							_currentTextContent += element.second;
						}
						else
						{
							_currentTextContent += element.first;
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
						if(_currentTextContent.empty())
						{
							_currentTextContent += '-';
						}
					}
				}
			}
		}

		if(_fe3d->input_isKeyDown(InputType::KEY_BACKSPACE))
		{
			if(passedBackspaceFrames >= MAX_PASSED_BACKSPACE_FRAMES)
			{
				passedBackspaceFrames = 0;

				if(_currentTextContent.size() == 1)
				{
					_currentTextContent = "";
				}
				else
				{
					_currentTextContent = _currentTextContent.substr(0, _currentTextContent.size() - 1);
				}
			}
			else
			{
				passedBackspaceFrames++;
			}
		}
		else
		{
			passedBackspaceFrames = MAX_PASSED_BACKSPACE_FRAMES;
		}

		_fe3d->text2d_setContent(_textField->getEntityId(), _currentTextContent + (barEnabled ? "|" : " "));
		_fe3d->text2d_setSize(_textField->getEntityId(), fvec2(CHAR_WIDTH * static_cast<float>(_currentTextContent.size()), _fe3d->text2d_getSize(_textField->getEntityId()).y));

		if(_fe3d->input_isKeyPressed(InputType::KEY_ENTER))
		{
			if(!_currentTextContent.empty())
			{
				_confirmedInput = true;
				_isActive = false;
			}
		}
	}
	else
	{
		_fe3d->text2d_setContent(_textField->getEntityId(), _currentTextContent);
		_fe3d->text2d_setSize(_textField->getEntityId(), fvec2(CHAR_WIDTH * static_cast<float>(_currentTextContent.size()), _fe3d->text2d_getSize(_textField->getEntityId()).y));
		_confirmedInput = false;
	}

	_lastTextContent = _currentTextContent;
}

void GuiInputField::setActive(bool value)
{
	_isActive = value;
}

const bool GuiInputField::isHovered() const
{
	return _isHovered;
}

const bool GuiInputField::isHoverable() const
{
	return _isHoverable;
}

const bool GuiInputField::isVisible() const
{
	return _quadField->isVisible();
}

const bool GuiInputField::confirmedInput() const
{
	return _confirmedInput;
}

const bool GuiInputField::isActive() const
{
	return _isActive;
}

const bool GuiInputField::hasTextContentChanged() const
{
	return (_lastTextContent != _currentTextContent);
}

const bool GuiInputField::isCentered() const
{
	return _quadField->isCentered();
}

const string GuiInputField::getTextContent() const
{
	if(_currentTextContent == "-" && _noSpecials && _minusAllowed)
	{
		return "";
	}
	else
	{
		return _currentTextContent;
	}
}

const fvec2 & GuiInputField::getPosition() const
{
	return _quadField->getPosition();
}

const fvec2 & GuiInputField::getSize() const
{
	return _quadField->getSize();
}

void GuiInputField::setTextContent(const string & content)
{
	_currentTextContent = content;
}

void GuiInputField::setVisible(bool value)
{
	_quadField->setVisible(value);
	_textField->setVisible(value);
}

void GuiInputField::setHoverable(bool value)
{
	_isHoverable = value;

	_quadField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
	_textField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);
}

const string GuiInputField::getId() const
{
	return _id;
}

const string GuiInputField::getParentId() const
{
	return _parentId;
}

void GuiInputField::_updateHovering(bool isFocused)
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