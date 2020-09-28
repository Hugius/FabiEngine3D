#include "script_editor.hpp"

void ScriptEditor::_updateTextWriter()
{
	if (_isLoaded && _isWritingScript)
	{
		bool textHasChanged = false;
		
		if (_fe3d.input_getKeyPressed(Input::KEY_ENTER)) // New line
		{
			_cursorPlaceIndex = 0; // Set cursor to beginning of new line
			_cursorLineIndex++;
			_script->getScriptFile(_currentScriptFileID)->addNewLine("");
			textHasChanged = true;
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE) && _cursorPlaceIndex == 0) // Remove line
		{
			// Check if not trying to remove default line
			if (_cursorLineIndex > 0)
			{
				// Remove line
				_script->getScriptFile(_currentScriptFileID)->removeLine(_cursorLineIndex);
				_cursorLineIndex--;

				// Set cursor to last character of line above
				_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
				textHasChanged = true;
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_LEFT)) // Left
		{
			if (_cursorPlaceIndex > 0)
			{
				_cursorPlaceIndex--;
			}
			else
			{
				if (_cursorLineIndex > 0)
				{
					_cursorLineIndex--;
					_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
				}
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_RIGHT)) // Right
		{
			if (_cursorPlaceIndex < _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size())
			{
				_cursorPlaceIndex++;
			}
			else
			{
				if (_cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount())
				{
					_cursorLineIndex++;
					_cursorPlaceIndex = 0;
				}
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_UP)) // Up
		{
			if (_cursorLineIndex > 0)
			{
				_cursorLineIndex--;

				if (_cursorPlaceIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size())
				{
					_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
				}
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_DOWN)) // Down
		{
			if (_cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
			{
				_cursorLineIndex++;

				if (_cursorPlaceIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size())
				{
					_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
				}
			}
		}
		else // Other keypresses
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

			// All characters of current line
			string lineText = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex);
			string newCharacter = "";

			// Letter characters
			for (auto& c : letterCharacters)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(c)))
				{
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT)) // Uppercase or special character
					{
						newCharacter = (c - 32);
					}
					else if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // CAPSLOCK
					{
						newCharacter = (c - 32);
					}
					else // Lowercase character
					{
						newCharacter = c;
					}
				}
			}

			// Number characters
			for (auto& element : numberCharacterMap)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(element.first)))
				{
					// Check if shift was pressed
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT))
					{
						newCharacter = element.second;
					}
					else
					{
						newCharacter = element.first;
					}
				}
			}

			// Special characters
			for (auto& element : specialCharacterMap)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(element.first)))
				{
					// Check if shift was pressed
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT))
					{
						newCharacter = element.second;
					}
					else
					{
						newCharacter = element.first;
					}
				}
			}

			// Remove character from line
			if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
			{
				if (_cursorPlaceIndex > 0)
				{
					_cursorPlaceIndex--;
					lineText.erase(lineText.begin() + _cursorPlaceIndex);
					textHasChanged = true;
				}
			}

			// Add new typed character to line
			if (newCharacter != "")
			{
				if (lineText == "") // First character in line
				{
					lineText = newCharacter;
					_cursorPlaceIndex++;
				}
				else if (_cursorPlaceIndex == lineText.size()) // Last character in line
				{
					lineText += newCharacter;
					_cursorPlaceIndex++;
				}
				else // Inbetween character in line
				{
					_cursorPlaceIndex++;
				}

				textHasChanged = true;
			}

			// Save new line
			_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, lineText);
		}

		// Reload text display when altered
		if (textHasChanged)
		{
			_reloadScriptTextDisplay();
		}

		// Update blinking cursor
		static unsigned int passedBarFrames = _maxPassedBarFrames;
		static bool barEnabled = true;
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

		// If cursor billboard not existing, create new one
		vec2 charSize = _fe3d.billboardEntity_getSize("0");
		if (!_fe3d.billboardEntity_isExisting("cursor"))
		{
			_fe3d.billBoardEntity_add("cursor", "", _fontPath, vec3(1.0f), vec3(0.0f), vec3(0.0f), charSize, 0, 0);
		}

		// Update cursor billboard text
		vec3 position;
		if (_cursorPlaceIndex == 0)
		{
			position = _fe3d.billboardEntity_getPosition(to_string(_cursorLineIndex)) + vec3(_horizontalLineOffset / 2.0f, 0.0f, 0.0f);
		}
		else
		{
			position = _fe3d.billboardEntity_getPosition(to_string(_cursorLineIndex) + "_" + to_string(_cursorPlaceIndex - 1));
		}
		position += vec3(charSize.x / 2.0f, 0.0f, 0.0f);
		_fe3d.billboardEntity_setPosition("cursor", position);
		_fe3d.billBoardEntity_setTextContent("cursor", (barEnabled ? "|" : " "));
	}
}