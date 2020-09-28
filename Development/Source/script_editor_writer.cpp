#include "script_editor.hpp"

void ScriptEditor::_updateTextWriter()
{
	if (_isLoaded && _isWritingScript)
	{
		bool textHasChanged = false;

		// Timing functionality for continuous actions
		const vector<Input> actionKeys = 
		{ Input::KEY_ENTER, Input::KEY_BACKSPACE, Input::KEY_DELETE, Input::KEY_LEFT, Input::KEY_RIGHT, Input::KEY_UP, Input::KEY_DOWN };
		static Input activeActionKey = Input::NONE;
		static unsigned int passedFrames = 0;
		static bool singleActionAllowed = true;
		static bool continuousActionAllowed = false;

		// Timer for continuous actions
		if (activeActionKey == Input::NONE)
		{
			for (Input actionKey : actionKeys) // Check all possible action keys
			{
				if (_fe3d.input_getKeyDown(actionKey)) // Check if action key is down
				{
					// Remember currently pressed action key
					activeActionKey = actionKey;
					break;
				}
			}
		}
		else
		{
			// Check if waited long enough for continuous action
			if (passedFrames == _continuousTextActionFrameMinimum)
			{
				continuousActionAllowed = true;
				passedFrames = 0;
			}
			else // Keep waiting
			{
				passedFrames++;
			}
		}

		// Reset timing state if action key released
		if (!_fe3d.input_getKeyDown(activeActionKey))
		{
			activeActionKey = Input::NONE;
			passedFrames = 0;
			singleActionAllowed = true;
			continuousActionAllowed = false;
		}

		// Determine text action type
		if (_fe3d.input_getKeyDown(Input::KEY_ENTER)) // New line
		{
			// Check if single or fast new line action
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					// Set cursor to beginning of new line
					_cursorPlaceIndex = 0;
					_cursorLineIndex++;
					_script->getScriptFile(_currentScriptFileID)->addNewLine("");
					textHasChanged = true;
				}
			}
		}
		else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{

		}
		else if (activeActionKey == Input::KEY_LEFT) // Left arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (_cursorPlaceIndex > 0) // If cursor somewhere on the line
					{
						_cursorPlaceIndex--;
					}
					else // If cursor is at the beginning of the line
					{
						if (_cursorLineIndex > 0) // Check if trying to move cursor out of screen
						{
							_cursorLineIndex--;
							_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_RIGHT)) // Right arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (_cursorPlaceIndex < _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size()) // If cursor somewhere on the line
					{
						_cursorPlaceIndex++;
					}
					else // If cursor is at the end of the line
					{
						// Check if trying to move cursor out of screen
						if (_cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
						{
							_cursorLineIndex++;
							_cursorPlaceIndex = 0;
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_UP)) // Up arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (_cursorLineIndex > 0) // Check if trying to move cursor out of screen
					{
						_cursorLineIndex--;

						// Change place index accordingly
						if (_cursorPlaceIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size())
						{
							_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_DOWN)) // Down arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					// Check if trying to move cursor out of screen
					if (_cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						_cursorLineIndex++;

						// Change place index accordingly
						if (_cursorPlaceIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size())
						{
							_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
						}
					}
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
			string currentLineText = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex);
			string newCharacters = "";

			// Letter characters
			for (auto& c : letterCharacters)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(c)))
				{
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT)) // Uppercase or special character
					{
						newCharacters += (c - 32);
					}
					else if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // CAPSLOCK
					{
						newCharacters += (c - 32);
					}
					else // Lowercase character
					{
						newCharacters += c;
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
						newCharacters = element.second;
					}
					else
					{
						newCharacters = element.first;
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
						newCharacters += element.second;
					}
					else
					{
						newCharacters += element.first;
					}
				}
			}

			// Remove characters from line
			if (activeActionKey == Input::KEY_BACKSPACE || activeActionKey == Input::KEY_DELETE)
			{
				// Check if single or fast remove
				if (singleActionAllowed || continuousActionAllowed)
				{
					if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
					{
						singleActionAllowed = false;

						// Jump to line above if cursor at beginning of line
						if (_cursorPlaceIndex == 0 && _fe3d.input_getKeyDown(Input::KEY_BACKSPACE))
						{
							// Check if not trying to remove default line
							if (_cursorLineIndex > 0)
							{
								// Remove line
								string textToMerge = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex);
								_script->getScriptFile(_currentScriptFileID)->removeLine(_cursorLineIndex);
								_cursorLineIndex--;

								// Set cursor to last character of line above
								_cursorPlaceIndex = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex).size();
								currentLineText += textToMerge;
								_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, currentLineText);
								textHasChanged = true;
							}
						}
						else if (_cursorPlaceIndex == currentLineText.size() && _fe3d.input_getKeyDown(Input::KEY_DELETE))
						{
							// Check if not trying to remove default line
							if (_cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
							{
								// Remove line
								string textToMerge = _script->getScriptFile(_currentScriptFileID)->getLineText(_cursorLineIndex + 1);
								_script->getScriptFile(_currentScriptFileID)->removeLine(_cursorLineIndex + 1);

								// Merge text on current line & save merged line
								currentLineText += textToMerge;
								_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, currentLineText);
								textHasChanged = true;
							}
						}
						else if (_cursorPlaceIndex > 0 && _fe3d.input_getKeyDown(Input::KEY_BACKSPACE)) // Remove previous character from current line
						{
							_cursorPlaceIndex--;
							currentLineText.erase(currentLineText.begin() + _cursorPlaceIndex);
							textHasChanged = true;
							_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, currentLineText); // Save new line text
						}
						else if (_fe3d.input_getKeyDown(Input::KEY_DELETE)) // Remove next character from current line
						{
							currentLineText.erase(currentLineText.begin() + _cursorPlaceIndex);
							textHasChanged = true;
							_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, currentLineText); // Save new line text
						}
					}
				}
			}

			// Add new typed character to line
			if (newCharacters != "")
			{
				if (currentLineText == "" || _cursorPlaceIndex == currentLineText.size()) // First or last character in line
				{
					for (auto& character : newCharacters)
					{
						currentLineText += character;
						_cursorPlaceIndex++;
					}
				}
				else // Inbetween character in line
				{
					for (auto& character : newCharacters)
					{
						currentLineText.insert(currentLineText.begin() + _cursorPlaceIndex, character);
						_cursorPlaceIndex++;
					}
				}

				textHasChanged = true;

				// Save new line
				_script->getScriptFile(_currentScriptFileID)->setLineText(_cursorLineIndex, currentLineText);
			}
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