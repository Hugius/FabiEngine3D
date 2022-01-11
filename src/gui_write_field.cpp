#include "gui_write_field.hpp"

#include <map>
#include <windows.h>

GuiWriteField::GuiWriteField(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
	:
	GuiButton(fe3d, parentID, ID, position, size, color, hoverColor, "", textColor, textHoverColor, isCentered),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{
	_fe3d->text_setContent(_textField->getEntityID(), "|", CHAR_WIDTH);
}

void GuiWriteField::update(bool isHoverable)
{
	_updateHovering(isHoverable && !_isActive);
	_updateActivation();
	_updateTyping();
}

void GuiWriteField::_updateActivation()
{
	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if(_isHovered)
		{
			_isActive = true;
		}
		else
		{
			if(!_mustBeActive)
			{
				_isActive = false;
			}
		}
	}
}

void GuiWriteField::_updateTyping()
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

		if((static_cast<float>(_currentTextContent.size() + 1) * CHAR_WIDTH) < _textField->getInitialSize().x)
		{
			string letterCharacters = " abcdefghijklmnopqrstuvwxyz";

			map<char, char> numberCharacterMap;
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

			map<char, char> specialCharacterMap;
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
				for(const auto& c : letterCharacters)
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
				for(const auto& element : numberCharacterMap)
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
				for(const auto& element : specialCharacterMap)
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

		_fe3d->text_setContent(_textField->getEntityID(), _currentTextContent + (barEnabled ? "|" : " "), CHAR_WIDTH);

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
		_fe3d->text_setContent(_textField->getEntityID(), _currentTextContent, CHAR_WIDTH);
		_confirmedInput = false;
	}
}

void GuiWriteField::setActive(bool active)
{
	_isActive = active;
}

void GuiWriteField::setPermActive(bool active)
{
	_isActive = active;
	_mustBeActive = active;
}

const bool GuiWriteField::confirmedInput() const
{
	return _confirmedInput;
}

const bool GuiWriteField::isActive() const
{
	return _isActive;
}

const bool GuiWriteField::hasTextContentChanged()
{
	bool result = (_lastTextContent != _currentTextContent);
	_lastTextContent = _currentTextContent;
	return result;
}

const string GuiWriteField::getTextContent() const
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

void GuiWriteField::changeTextContent(const string& content)
{
	_currentTextContent = content;
}