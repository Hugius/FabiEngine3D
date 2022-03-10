#include "script_editor.hpp"
#include <iostream>
#include <windows.h>

void ScriptEditor::_updateTextWriter()
{
	if(isLoaded() && _isWritingScript && !_gui->getOverlay()->isFocused() && !_wasGuiFocused)
	{
		if(_fe3d->misc_isCursorInsideDisplay())
		{
			_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_text.tga");
		}

		string newCharacters = "";
		bool hasTextChanged = false;

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideDisplay())
		{
			const auto hoveredTextId = _fe3d->raycast_getClosestAabbId();

			if(!hoveredTextId.empty())
			{
				auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
				auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
				int hoveredLineIndex = -1;
				int hoveredCharacterIndex = -1;

				if(hoveredTextId.find('_') == string::npos)
				{
					hoveredLineIndex = stoi(hoveredTextId);
				}
				else
				{
					hoveredLineIndex = stoi(hoveredTextId.substr(0, hoveredTextId.find('_')));
					hoveredCharacterIndex = stoi(hoveredTextId.substr(hoveredTextId.find('_') + 1));
				}

				cursorLineIndex = hoveredLineIndex;

				if(hoveredCharacterIndex == -1)
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
				else
				{
					cursorCharacterIndex = hoveredCharacterIndex;
				}

				_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
				_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
			}
		}
		else if(_fe3d->input_isKeyPressed(InputType::KEY_LEFT))
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
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
			}

			_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
			_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
		}
		else if(_fe3d->input_isKeyPressed(InputType::KEY_RIGHT))
		{
			auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
			auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

			if(cursorCharacterIndex < _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
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

				if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
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

				if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
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
				auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

				_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharacterIndex));
				cursorLineIndex++;
				_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex, currentLineText.substr(cursorCharacterIndex));
				cursorCharacterIndex = 0;
				hasTextChanged = true;

				_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
				_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
			}
		}
		else if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
		{
			auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
			auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
			auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

			if(cursorCharacterIndex == currentLineText.size())
			{
				const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();

				if(cursorLineIndex < (lineCount - 1))
				{
					const auto nextLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex + 1);

					_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, (currentLineText + nextLineText));
					_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex + 1);
					hasTextChanged = true;
				}
			}
			else
			{
				currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);
				_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
				hasTextChanged = true;
			}

			_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
			_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
		}
		else if(_fe3d->input_isKeyPressed(InputType::KEY_BACKSPACE))
		{
			auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
			auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
			auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

			if(cursorCharacterIndex == 0)
			{
				if(cursorLineIndex > 0)
				{
					const auto previousLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex - 1);

					_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex);
					cursorLineIndex--;
					_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, previousLineText + currentLineText);
					cursorCharacterIndex = static_cast<unsigned int>(previousLineText.size());
					hasTextChanged = true;
				}
			}
			else
			{
				cursorCharacterIndex--;
				currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);
				_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
				hasTextChanged = true;
			}

			_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
			_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
		}
		else
		{
			auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
			auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
			auto currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

			if(!_fe3d->input_isKeyDown(InputType::KEY_LCTRL) && !_fe3d->input_isKeyDown(InputType::KEY_RCTRL))
			{
				for(const auto& c : ALPHABET_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(c)))
					{
						if(c == ' ')
						{
							newCharacters += c;
						}
						else
						{
							if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
							{
								newCharacters += (c - 32);
							}
							else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
							{
								newCharacters += (c - 32);
							}
							else
							{
								newCharacters += c;
							}
						}
					}
				}

				for(const auto& [normalCharacter, shiftCharacter] : NUMBER_CHARACTERS)
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

				for(const auto& [normalCharacter, shiftCharacter] : SPECIAL_CHARACTERS)
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
						for(const auto& character : newCharacters)
						{
							currentLineText += character;
							cursorCharacterIndex++;
						}
					}
					else
					{
						for(const auto& character : newCharacters)
						{
							currentLineText.insert(currentLineText.begin() + cursorCharacterIndex, character);
							cursorCharacterIndex++;
						}
					}

					hasTextChanged = true;

					_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
				}
			}

			_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
			_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
		}

		if(hasTextChanged)
		{
			_deleteScriptDisplayEntities();
			_createScriptDisplayEntities();
		}

		if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 2)) == 0)
		{
			if(_fe3d->text3d_getContent("cursor") == "|")
			{
				_fe3d->text3d_setContent("cursor", " ");
			}
			else
			{
				_fe3d->text3d_setContent("cursor", "|");
			}
		}

		const auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		const auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

		if(cursorCharacterIndex == 0)
		{
			const auto linePosition = _fe3d->aabb_getBasePosition(to_string(_script->getScriptFile(_currentScriptFileId)->getCursorLineIndex()));
			const auto cursorPosition = fvec3((TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET - CHARACTER_OFFSET + (TEXT_CHARACTER_SIZE.x * 0.5f)), linePosition.y, linePosition.z);

			_fe3d->text3d_setPosition("cursor", cursorPosition);
		}
		else
		{
			const auto characterPosition = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharacterIndex - 1));
			const auto cursorOffset = fvec3((TEXT_CHARACTER_SIZE.x * 0.5f), 0.0f, 0.0f);
			const auto cursorPosition = (characterPosition + cursorOffset);

			_fe3d->text3d_setPosition("cursor", cursorPosition);
		}
	}

	_wasGuiFocused = _gui->getOverlay()->isFocused();
}