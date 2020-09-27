#include "script_editor.hpp"

void ScriptEditor::_updateTextWriter()
{
	if (_isWritingScript)
	{
		bool textHasChanged = false;

		if (_fe3d.input_getKeyPressed(Input::KEY_ENTER))
		{
			_cursorLineIndex++;
			_script->getScriptFile(_currentScriptFileID)->addNewLine("");
			_reloadLineNumbersDisplay();
			textHasChanged = true;
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE) && _cursorPlaceIndex == 0)
		{
			if (_cursorLineIndex > 0)
			{
				_cursorLineIndex--;
				_script->getScriptFile(_currentScriptFileID)->removeLastLine();
				_reloadLineNumbersDisplay();
				textHasChanged = true;
			}
		}
		else
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
						std::cout << c << std::endl;
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

			// Remove last character
			if (_fe3d.input_getKeyDown(Input::KEY_BACKSPACE))
			{
				if (!lineText.empty())
				{
					lineText.pop_back();
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
	}
}