#include "gui_input_field.hpp"

#include <windows.h>

GuiInputField::GuiInputField(shared_ptr<EngineInterface> fe3d, const string & parentId, const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
	:
	GuiButton(fe3d, parentId, id, position, size, "", color, hoverColor, "", textColor, textHoverColor, isCentered),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{
	_fe3d->text2d_setContent(_textField->getEntityId(), "|");
	_fe3d->text2d_setSize(_textField->getEntityId(), fvec2(CHAR_WIDTH, _fe3d->text2d_getSize(_textField->getEntityId()).y));
}

void GuiInputField::update(bool isFocused)
{
	_updateHovering(isFocused && !_isActive);
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
}

void GuiInputField::setActive(bool active)
{
	_isActive = active;
}

const bool GuiInputField::confirmedInput() const
{
	return _confirmedInput;
}

const bool GuiInputField::isActive() const
{
	return _isActive;
}

const bool GuiInputField::hasTextContentChanged()
{
	bool result = (_lastTextContent != _currentTextContent);

	_lastTextContent = _currentTextContent;

	return result;
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

void GuiInputField::changeTextContent(const string & content)
{
	_currentTextContent = content;
}