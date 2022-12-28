#include "script_editor.hpp"
#include "tools.hpp"

void ScriptEditor::_updateTextWriter()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !Tools::isCursorInsideDisplay() || _fe3d->quad3d_isVisible(SELECTION_ID))
	{
		return;
	}

	if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_LEFT))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorCharacterIndex > 0)
		{
			cursorCharacterIndex--;
		}
		else
		{
			if(cursorLineIndex > 0)
			{
				cursorLineIndex--;
				cursorCharacterIndex = static_cast<int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_RIGHT))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorCharacterIndex < _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size())
		{
			cursorCharacterIndex++;
		}
		else
		{
			if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
			{
				cursorLineIndex++;
				cursorCharacterIndex = 0;
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_UP))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorLineIndex > 0)
		{
			cursorLineIndex--;

			if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size())
			{
				cursorCharacterIndex = static_cast<int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DOWN))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
		{
			cursorLineIndex++;

			if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size())
			{
				cursorCharacterIndex = static_cast<int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ENTER))
	{
		if(_script->getScriptFile(_currentScriptFileId)->getLineCount() < MAX_LINE_COUNT)
		{
			auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
			auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
			auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex);

			_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, currentLineText.substr(0, cursorCharacterIndex));

			cursorLineIndex++;

			_script->getScriptFile(_currentScriptFileId)->createLine(cursorLineIndex, currentLineText.substr(cursorCharacterIndex));

			cursorCharacterIndex = 0;

			_hasTextChanged = true;

			_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
			_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);

			const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();

			if(cursorLineIndex == (lineCount - 1))
			{
				auto cameraPosition = _fe3d->camera_getPosition();

				cameraPosition.y -= VERTICAL_LINE_OFFSET;

				_fe3d->camera_setPosition(cameraPosition);
			}
		}
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
		auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex);

		if(cursorCharacterIndex == currentLineText.size())
		{
			const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();

			if(cursorLineIndex < (lineCount - 1))
			{
				const auto nextLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex + 1);

				_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, (currentLineText + nextLineText));
				_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex + 1);

				_hasTextChanged = true;
			}
		}
		else
		{
			currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);

			_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, currentLineText);

			_hasTextChanged = true;
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_BACKSPACE))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
		auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex);

		if(cursorCharacterIndex == 0)
		{
			if(cursorLineIndex > 0)
			{
				const auto previousLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex - 1);

				_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex);

				cursorLineIndex--;

				_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, previousLineText + currentLineText);

				cursorCharacterIndex = static_cast<int>(previousLineText.size());

				_hasTextChanged = true;
			}
		}
		else
		{
			cursorCharacterIndex--;

			currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);

			_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, currentLineText);

			_hasTextChanged = true;
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
		auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex);

		if(!_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_CONTROL))
		{
			const auto isCapsLockToggled = _fe3d->input_isKeyboardToggled(KeyboardKeyType::KEY_CAPSLOCK);
			const auto isShiftHeld = _fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT);

			string newCharacters = "";

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_TAB))
			{
				newCharacters += ' ';
				newCharacters += ' ';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SPACEBAR))
			{
				newCharacters += ' ';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_A))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'A' : 'a');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_B))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'B' : 'b');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_C))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'C' : 'c');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_D))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'D' : 'd');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_E))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'E' : 'e');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'F' : 'f');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'G' : 'g');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_H))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'H' : 'h');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_I))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'I' : 'i');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_J))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'J' : 'j');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_K))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'K' : 'k');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_L))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'L' : 'l');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_M))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'M' : 'm');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_N))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'N' : 'n');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_O))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'O' : 'o');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_P))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'P' : 'p');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Q))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'Q' : 'q');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'R' : 'r');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_S))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'S' : 's');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_T))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'T' : 't');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_U))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'U' : 'u');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_V))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'V' : 'v');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_W))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'W' : 'w');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_X))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'X' : 'x');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Y))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'Y' : 'y');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Z))
			{
				newCharacters += ((isCapsLockToggled != isShiftHeld) ? 'Z' : 'z');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_0))
			{
				newCharacters += (isShiftHeld ? ')' : '0');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_1))
			{
				newCharacters += (isShiftHeld ? '!' : '1');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_2))
			{
				newCharacters += (isShiftHeld ? '@' : '2');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_3))
			{
				newCharacters += (isShiftHeld ? '#' : '3');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_4))
			{
				newCharacters += (isShiftHeld ? '$' : '4');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_5))
			{
				newCharacters += (isShiftHeld ? '%' : '5');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_6))
			{
				newCharacters += (isShiftHeld ? '^' : '6');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_7))
			{
				newCharacters += (isShiftHeld ? '&' : '7');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_8))
			{
				newCharacters += (isShiftHeld ? '*' : '8');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_9))
			{
				newCharacters += (isShiftHeld ? '(' : '9');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD0))
			{
				newCharacters += '0';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD1))
			{
				newCharacters += '1';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD2))
			{
				newCharacters += '2';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD3))
			{
				newCharacters += '3';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD4))
			{
				newCharacters += '4';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD5))
			{
				newCharacters += '5';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD6))
			{
				newCharacters += '6';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD7))
			{
				newCharacters += '7';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD8))
			{
				newCharacters += '8';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_NUMPAD9))
			{
				newCharacters += '9';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SEMICOLON))
			{
				newCharacters += (isShiftHeld ? ':' : ';');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_EQUAL))
			{
				newCharacters += (isShiftHeld ? '+' : '=');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_COMMA))
			{
				newCharacters += (isShiftHeld ? '<' : ',');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_MINUS))
			{
				newCharacters += (isShiftHeld ? '_' : '-');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_PERIOD))
			{
				newCharacters += (isShiftHeld ? '>' : '.');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_FORWARDSLASH))
			{
				newCharacters += (isShiftHeld ? '?' : '/');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_GRAVE))
			{
				newCharacters += (isShiftHeld ? '~' : '`');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_LEFTBRACKET))
			{
				newCharacters += (isShiftHeld ? '{' : '[');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_BACKWARDSLASH))
			{
				newCharacters += (isShiftHeld ? '|' : '\\');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_RIGHTBRACKET))
			{
				newCharacters += (isShiftHeld ? '}' : ']');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_QUOTE))
			{
				newCharacters += (isShiftHeld ? '"' : '\'');
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_MULTIPLY))
			{
				newCharacters += '*';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DIVIDE))
			{
				newCharacters += '/';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ADD))
			{
				newCharacters += '+';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_SUBTRACT))
			{
				newCharacters += '-';
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DECIMAL))
			{
				newCharacters += '.';
			}

			if(!newCharacters.empty())
			{
				if(currentLineText.empty() || cursorCharacterIndex == currentLineText.size())
				{
					for(const auto & character : newCharacters)
					{
						currentLineText += character;
						cursorCharacterIndex++;
					}
				}
				else
				{
					for(const auto & character : newCharacters)
					{
						currentLineText.insert(currentLineText.begin() + cursorCharacterIndex, character);
						cursorCharacterIndex++;
					}
				}

				_hasTextChanged = true;

				_script->getScriptFile(_currentScriptFileId)->editLine(cursorLineIndex, currentLineText);
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
}