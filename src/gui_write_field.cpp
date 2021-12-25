#include "gui_write_field.hpp"

#include <map>
#include <windows.h>

GuiWriteField::GuiWriteField(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
	:
	GuiButton(fe3d, parentID, ID, position, size, color, hoverColor, "", textColor, textHoverColor, false, true, isCentered),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{
	_fe3d.text_setContent(_textField->getEntityID(), "|", CHAR_WIDTH);
}

void GuiWriteField::update(bool hoverable)
{
	_updateHovering(hoverable && !_isActive);
	_updateActivation();
	_updateTyping();
}

void GuiWriteField::_updateActivation()
{
	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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

		// Update bar animation time
		if(passedBarFrames >= MAX_PASSED_BAR_FRAMES)
		{
			passedBarFrames = 0;

			// Toggle bar animation
			barEnabled = !barEnabled;
		}
		else
		{
			passedBarFrames++;
		}

		// Check if not writing out of border
		if((static_cast<float>(_currentTextContent.size() + 1) * CHAR_WIDTH) < _textField->getInitialSize().x)
		{
			// Letter characters
			string letterCharacters = " abcdefghijklmnopqrstuvwxyz";

			// Number characters
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

			// Special characters
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

			// Letter characters
			if(!_noLetters)
			{
				for(const auto& c : letterCharacters)
				{
					// Check if character is pressed on keyboard
					if(_fe3d.input_isKeyPressed(InputType(c)))
					{
						// Spacebar
						if(c == ' ')
						{
							_currentTextContent += c;
						}
						else // Non-spacebar
						{
							if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT)) // Uppercase or special character
							{
								// Convert to uppercase
								{
									_currentTextContent += (c - 32);
								}
							}
							else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // Uppercase character
							{
								if(!_noCaps) // A - Z
								{
									// Convert to uppercase
									_currentTextContent += (c - 32);
								}
							}
							else // Lowercase character
							{
								_currentTextContent += c;
							}
						}
					}
				}
			}

			// Number characters
			if(!_noNumbers)
			{
				for(const auto& element : numberCharacterMap)
				{
					// Check if character is pressed on keyboard
					if(_fe3d.input_isKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
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

			// Special characters
			if(!_noSpecials)
			{
				for(const auto& element : specialCharacterMap)
				{
					// Check if character is pressed on keyboard
					if(_fe3d.input_isKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
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
			else if(_minusAllowed && !_noNumbers) // Minus character (for numbers)
			{
				if(_fe3d.input_isKeyPressed(InputType('-')))
				{
					if(!_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) && !_fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
					{
						if(_currentTextContent.empty()) // Minus can only before any number
						{
							_currentTextContent += '-';
						}
					}
				}
			}
		}

		// Remove character
		if(_fe3d.input_isKeyDown(InputType::KEY_BACKSPACE))
		{
			// Check if enough time passed
			if(passedBackspaceFrames >= MAX_PASSED_BACKSPACE_FRAMES)
			{
				passedBackspaceFrames = 0;

				if(_currentTextContent.size() == 1)
				{
					_currentTextContent = "";
				}
				else
				{
					_currentTextContent = _currentTextContent.substr(0, _currentTextContent.size() - 1); // Remove last character
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

		// Update text content with or without bar
		_fe3d.text_setContent(_textField->getEntityID(), _currentTextContent + (barEnabled ? "|" : " "), CHAR_WIDTH);

		// Input confirmation
		if(_fe3d.input_isKeyPressed(InputType::KEY_ENTER))
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
		// Update text content
		_fe3d.text_setContent(_textField->getEntityID(), _currentTextContent, CHAR_WIDTH);
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