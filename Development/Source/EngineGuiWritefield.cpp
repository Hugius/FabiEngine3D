#include "EngineGuiWriteField.hpp"

EngineGuiWriteField::EngineGuiWriteField(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, 
	vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor) :
	EngineGuiButton(fe3d, parentID, ID, position, size, color, hoverColor, "|", textColor, textHoverColor, false, true)
{

}

void EngineGuiWriteField::update(float delta, bool hoverable)
{
	_updateHovering(hoverable && !_isActive);
	_updateActivation();
	_updateTyping(delta);
}

void EngineGuiWriteField::setActive(bool active)
{
	_isActive = active;
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

void EngineGuiWriteField::_updateActivation()
{
	if (_isHovered)
	{
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			_isActive = true;
		}
	}
}

void EngineGuiWriteField::_updateTyping(float delta)
{
	if (_isActive)
	{
		static float passedBarDelta = 500.0f;
		static float passedBackspaceDelta = 100.0f;
		static bool barEnabled = true;

		// Update bar animation time
		if (passedBarDelta >= 500.0f)
		{
			passedBarDelta = 0.0f;
			
			// Toggle bar animation
			barEnabled = !barEnabled;
		}
		else
		{
			passedBarDelta += delta;
		}

		// Check if not writing out of border
		if ((float(_currentTextContent.size() + 1) * _charWidth) < _textfield->getOriginalSize().x)
		{
			// Writable characters
			string lowercaseCharacters = " abcdefghijklmnopqrstuvwxyz1234567890";
			string specialCharacters = ")!@#$%^&*(";

			// Add character
			for (auto& c : lowercaseCharacters)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(c)))
				{
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT)) // Uppercase character
					{
						// Only if number
						if (isdigit(c))
						{
							_currentTextContent += specialCharacters[int(c-48)];
						}
						else // Convert to uppercase
						{
							_currentTextContent += (c - 32);
						}
					}
					else if (_fe3d.input_getKeyToggled(Input::KEY_CAPSLOCK)) // Uppercase character
					{
						// Only if not a number
						if (!isdigit(c))
						{
							_currentTextContent += (c - 32);
						}
					}
					else
					{
						_currentTextContent += c; // Lowercase character
					}
				}
			}
		}

		// Remove character
		if (_fe3d.input_getKeyDown(Input::KEY_BACKSPACE))
		{
			// Check if enough time passed
			if (passedBackspaceDelta >= 100.0f)
			{
				passedBackspaceDelta = 0.0f;
				_currentTextContent = _currentTextContent.substr(0, _currentTextContent.size() - 1); // Remove last characters
			}
			else
			{
				passedBackspaceDelta += delta;
			}
		}
		else
		{
			passedBackspaceDelta = 100.0f;
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
		_fe3d.textEntity_setTextContent(_textfield->getEntityID(), _currentTextContent, 0.01f);
		_confirmedInput = false;
		_cancelledInput = false;
	}
}