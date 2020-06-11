#include "engine_gui_writefield.hpp"

EngineGuiWriteField::EngineGuiWriteField(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, 
	vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters) :
	EngineGuiButton(fe3d, parentID, ID, position, size, color, hoverColor, "|", textColor, textHoverColor, false, true),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters)
{

}

void EngineGuiWriteField::update(bool hoverable)
{
	_updateHovering(hoverable && !_isActive);
	_updateActivation();
	_updateTyping();
}

void EngineGuiWriteField::setActive(bool active)
{
	_isActive = active;
}

void EngineGuiWriteField::setPermActive(bool active)
{
	_isActive = active;
	_mustBeActive = active;
}

bool EngineGuiWriteField::cancelledInput()
{
	return _cancelledInput;
}

bool EngineGuiWriteField::confirmedInput()
{
	return _confirmedInput;
}

string EngineGuiWriteField::getTextContent()
{
	return _currentTextContent;
}

void EngineGuiWriteField::setTextContent(string content)
{
	_currentTextContent = content;
}

void EngineGuiWriteField::_updateActivation()
{
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (_isHovered)
		{
			_isActive = true;
		}
		else
		{
			if (!_mustBeActive)
			{
				_isActive = false;
			}
		}
	}
}

void EngineGuiWriteField::_updateTyping()
{
	if (_isActive)
	{
		static int passedBarFrames = _maxPassedBarFrames;
		static int passedBackspaceFrames = _maxPassedBackspaceFrames;
		static bool barEnabled = true;

		// Update bar animation time
		if (passedBarFrames >= _maxPassedBarFrames)
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
		if ((float(_currentTextContent.size() + 1) * _charWidth) < _textfield->getOriginalSize().x)
		{
			// Writable characters
			string lowercaseCharacters = " abcdefghijklmnopqrstuvwxyz1234567890";
			string specialCharacters   = ")!@#$%^&*(";

			// Add character
			for (auto& c : lowercaseCharacters)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(c)))
				{
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT)) // Uppercase or special character
					{
						// Only if number
						if (isdigit(c))
						{
							if (!_noSpecials) // ! - )
							{
								_currentTextContent += specialCharacters[int(c - 48)];
							}
						}
						else // Convert to uppercase
						{
							if (!_noLetters) // A - Z
							{
								_currentTextContent += (c - 32);
							}
						}
					}
					else if (_fe3d.input_getKeyToggled(Input::KEY_CAPSLOCK)) // Uppercase character
					{
						// Check if number
						if (isdigit(c)) // 0 - 9
						{
							if (!_noNumbers)
							{
								_currentTextContent += c;
							}
						}
						else
						{
							if (!_noLetters && !_noCaps) // A - Z
							{
								_currentTextContent += (c - 32);
							}
						}
					}
					else // Lowercase character
					{
						// Check if number
						if (isdigit(c)) // 0 - 9
						{
							if (!_noNumbers)
							{
								_currentTextContent += c;
							}
						}
						else
						{
							if (!_noLetters) // a- z
							{
								_currentTextContent += c;
							}
						}
					}
				}
			}
		}

		// Remove character
		if (_fe3d.input_getKeyDown(Input::KEY_BACKSPACE))
		{
			// Check if enough time passed
			if (passedBackspaceFrames >= _maxPassedBackspaceFrames)
			{
				passedBackspaceFrames = 0;

				if (_currentTextContent.size() == 1)
				{
					_currentTextContent = "";
				}
				else
				{
					_currentTextContent = _currentTextContent.substr(0, _currentTextContent.size() - 1); // Remove last characters
				}
			}
			else
			{
				passedBackspaceFrames++;
			}
		}
		else
		{
			passedBackspaceFrames = _maxPassedBackspaceFrames;
		}

		// Update text content with or without bar
		_fe3d.textEntity_setTextContent(_textfield->getEntityID(), _currentTextContent + (barEnabled ? "|" : " "), _charWidth);
		
		// Input cancellation
		if (_fe3d.input_getKeyPressed(Input::KEY_ESCAPE))
		{
			_cancelledInput = true;
			_isActive = false;
		}

		// Input confirmation
		if (_fe3d.input_getKeyPressed(Input::KEY_RETURN))
		{
			if (_currentTextContent != "")
			{
				_confirmedInput = true;
				_isActive = false;
			}
		}
	}
	else
	{
		// Update text content
		_fe3d.textEntity_setTextContent(_textfield->getEntityID(), _currentTextContent, _charWidth);
		_confirmedInput = false;
		_cancelledInput = false;
	}
}