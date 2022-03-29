#include "script_editor.hpp"
#include <windows.h>

void ScriptEditor::_updateTextWriter()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || _fe3d->quad3d_isVisible("selection"))
	{
		return;
	}

	if(_fe3d->input_isKeyPressed(InputType::KEY_LEFT))
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
				cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyPressed(InputType::KEY_RIGHT))
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
	else if(_fe3d->input_isKeyPressed(InputType::KEY_UP))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorLineIndex > 0)
		{
			cursorLineIndex--;

			if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size())
			{
				cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyPressed(InputType::KEY_DOWN))
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
		{
			cursorLineIndex++;

			if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size())
			{
				cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}
	else if(_fe3d->input_isKeyPressed(InputType::KEY_ENTER))
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
		}
	}
	else if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
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
	else if(_fe3d->input_isKeyPressed(InputType::KEY_BACKSPACE))
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
				cursorCharacterIndex = static_cast<unsigned int>(previousLineText.size());
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

		if(!_fe3d->input_isKeyDown(InputType::KEY_LCTRL) && !_fe3d->input_isKeyDown(InputType::KEY_RCTRL))
		{
			string newCharacters = "";

			for(const auto & character : ALPHABET_CHARACTERS)
			{
				if(_fe3d->input_isKeyPressed(InputType(character)))
				{
					if(character == ' ')
					{
						newCharacters += character;
					}
					else
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += (character - 32);
						}
						else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
						{
							newCharacters += (character - 32);
						}
						else
						{
							newCharacters += character;
						}
					}
				}
			}

			for(const auto & [normalCharacter, shiftCharacter] : NUMBER_CHARACTERS)
			{
				if(_fe3d->input_isKeyPressed(InputType(normalCharacter)))
				{
					if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
					{
						newCharacters += shiftCharacter;
					}
					else
					{
						newCharacters += normalCharacter;
					}
				}
			}

			for(const auto & [normalCharacter, shiftCharacter] : SPECIAL_CHARACTERS)
			{
				if(_fe3d->input_isKeyPressed(InputType(normalCharacter)))
				{
					if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
					{
						newCharacters += shiftCharacter;
					}
					else
					{
						newCharacters += normalCharacter;
					}
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_TAB))
			{
				newCharacters += "    ";
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