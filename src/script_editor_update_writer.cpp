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

		const auto hoveredTextId = _fe3d->raycast_getClosestAabbId();
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;

		if(!hoveredTextId.empty())
		{
			if(hoveredTextId.find('_') == string::npos)
			{
				hoveredLineIndex = stoi(hoveredTextId);
			}
			else
			{
				hoveredLineIndex = stoi(hoveredTextId.substr(0, hoveredTextId.find('_')));
				hoveredCharacterIndex = stoi(hoveredTextId.substr(hoveredTextId.find('_') + 1));
			}
		}

		_pressedActionKey = InputType::NONE;

		for(InputType actionKey : ACTION_KEYS)
		{
			if(_fe3d->input_isKeyPressed(actionKey))
			{
				_pressedActionKey = actionKey;
				break;
			}
		}

		string newCharacters = "";
		unsigned int cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		unsigned int cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
		bool hasTextChanged = false;

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideDisplay())
		{
			if(!hoveredTextId.empty())
			{
				cursorLineIndex = hoveredLineIndex;

				if(hoveredCharacterIndex == -1)
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
				else
				{
					cursorCharacterIndex = hoveredCharacterIndex;
				}
			}
		}
		else if(_pressedActionKey == InputType::KEY_ENTER)
		{
			if(_firstSelectedLineIndex == -1)
			{
				if(_script->getScriptFile(_currentScriptFileId)->getLineCount() < MAX_LINE_COUNT)
				{
					string currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);
					string textToExtract = currentLineText;
					textToExtract = textToExtract.substr(cursorCharacterIndex, textToExtract.size() - cursorCharacterIndex);

					_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharacterIndex));

					cursorCharacterIndex = 0;
					cursorLineIndex++;

					_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex, textToExtract);
					hasTextChanged = true;
				}
			}
		}
		else if(_pressedActionKey == InputType::KEY_LEFT)
		{
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
		}
		else if(_pressedActionKey == InputType::KEY_RIGHT)
		{

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
		}
		else if(_pressedActionKey == InputType::KEY_UP)
		{
			if(cursorLineIndex > 0)
			{
				cursorLineIndex--;

				if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
			}
		}
		else if(_pressedActionKey == InputType::KEY_DOWN)
		{
			if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
			{
				cursorLineIndex++;

				if(cursorCharacterIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
				{
					cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
			}
		}
		else
		{
			string currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

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
			}

			if(_pressedActionKey == InputType::KEY_BACKSPACE || _pressedActionKey == InputType::KEY_DELETE)
			{
				if(_firstSelectedLineIndex == -1)
				{
					if(cursorCharacterIndex == 0 && _pressedActionKey == InputType::KEY_BACKSPACE)
					{
						if(cursorLineIndex > 0)
						{
							string textToMerge = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);
							_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex);
							cursorLineIndex--;

							cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
							_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex,
																					  _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex) + textToMerge);
							hasTextChanged = true;
						}
					}
					else if(cursorCharacterIndex == currentLineText.size() && _pressedActionKey == InputType::KEY_DELETE)
					{
						if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
						{
							string textToMerge = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex + 1);

							if((currentLineText.size() + textToMerge.size()) <= MAX_CHARACTERS_PER_LINE)
							{
								_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex + 1);

								currentLineText += textToMerge;
								_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
								hasTextChanged = true;
							}
						}
					}
					else if(cursorCharacterIndex > 0 && _fe3d->input_isKeyDown(InputType::KEY_BACKSPACE))
					{
						cursorCharacterIndex--;
						currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);
						hasTextChanged = true;
						_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
					}
					else if(_fe3d->input_isKeyDown(InputType::KEY_DELETE))
					{
						currentLineText.erase(currentLineText.begin() + cursorCharacterIndex);
						hasTextChanged = true;
						_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
					}
				}
			}

			if(static_cast<unsigned int>(currentLineText.size() + newCharacters.size()) <= MAX_CHARACTERS_PER_LINE)
			{
				if(_firstSelectedLineIndex == -1)
				{
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
			}
		}

		const auto isControlKeyDown = (_fe3d->input_isKeyDown(InputType::KEY_LCTRL) || _fe3d->input_isKeyDown(InputType::KEY_RCTRL));

		if(_firstSelectedLineIndex != -1)
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) ||
			   _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT) ||
			   _pressedActionKey != InputType::NONE ||
			   !newCharacters.empty() ||
			   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_V)) ||
			   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_X)))
			{
				_fe3d->quad3d_setVisible("selection", false);

				if(isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_X))
				{
					_copySelectedText();
				}

				if(!newCharacters.empty() ||
				   _fe3d->input_isKeyPressed(InputType::KEY_BACKSPACE) ||
				   _fe3d->input_isKeyPressed(InputType::KEY_DELETE) ||
				   _fe3d->input_isKeyPressed(InputType::KEY_ENTER) ||
				   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_V) && !_copyClipboard.empty()) ||
				   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_X)))
				{
					if(_lastSelectedLineIndex == -1)
					{
						_script->getScriptFile(_currentScriptFileId)->deleteLine(_firstSelectedLineIndex);
					}
					else
					{
						int lineIndexToDelete = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
						for(int index = 0; index <= abs(_firstSelectedLineIndex - _lastSelectedLineIndex); index++)
						{
							_script->getScriptFile(_currentScriptFileId)->deleteLine(static_cast<unsigned int>(lineIndexToDelete));
						}
					}

					if(hoveredLineIndex > static_cast<int>(_script->getScriptFile(_currentScriptFileId)->getLineCount() - 1))
					{
						hoveredLineIndex = static_cast<int>(_script->getScriptFile(_currentScriptFileId)->getLineCount());
					}

					if(cursorLineIndex > _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
					{
						cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getLineCount();
					}

					cursorCharacterIndex = newCharacters.empty() ? 0 : static_cast<unsigned int>(newCharacters.size());

					_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex, newCharacters);

					if(_fe3d->input_isKeyPressed(InputType::KEY_ENTER))
					{
						if(_script->getScriptFile(_currentScriptFileId)->getLineCount() < MAX_LINE_COUNT)
						{
							_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex, "");
							cursorLineIndex++;
						}
					}

					hasTextChanged = true;

					_pressedActionKey = InputType::NONE;
				}

				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
			}
		}

		if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && _fe3d->misc_isCursorInsideDisplay())
		{
			if(hoveredLineIndex != -1)
			{
				const auto selectionId = ("selection_" + to_string(hoveredLineIndex));
				const auto textId = ("text_" + to_string(hoveredLineIndex));

				if(!_fe3d->quad3d_isExisting(selectionId) && _fe3d->text3d_isExisting(textId))
				{
					if(_fe3d->text3d_getContent(textId).empty())
					{
						fvec3 lineTextPosition = (_fe3d->text3d_getPosition(textId));
						lineTextPosition.x = (TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET);
						lineTextPosition.z -= SELECTION_DEPTH;

						_fe3d->quad3d_setVisible(selectionId, true);
						_fe3d->quad3d_setPosition(selectionId, lineTextPosition);
					}
					else
					{
						const auto lineTextPosition = (_fe3d->text3d_getPosition(textId) - fvec3(0.0f, 0.0f, SELECTION_DEPTH));
						const auto lineTextSize = (_fe3d->text3d_getSize(textId));

						_fe3d->quad3d_setVisible(selectionId, true);
						_fe3d->quad3d_setPosition(selectionId, lineTextPosition);
						_fe3d->quad3d_setSize(selectionId, lineTextSize);
					}
				}

				if(_firstSelectedLineIndex == -1)
				{
					_firstSelectedLineIndex = hoveredLineIndex;
				}
				else
				{
					if(_lastSelectedLineIndex != -1)
					{
						int lastDirection = _firstSelectedLineIndex - _lastSelectedLineIndex;
						int currentDirection = _lastSelectedLineIndex - hoveredLineIndex;

						if(((lastDirection < 0) && (currentDirection > 0)) || ((currentDirection < 0) && (lastDirection > 0)))
						{
							//_fe3d->quad3d_setsi("selection_" + to_string(_lastSelectedLineIndex));
						}
					}

					_lastSelectedLineIndex = hoveredLineIndex;
				}
			}
		}
		else
		{
			if(_firstSelectedLineIndex != -1)
			{
				if(_lastSelectedLineIndex == -1)
				{
					cursorLineIndex = _firstSelectedLineIndex;
				}
				else
				{
					cursorLineIndex = min(_firstSelectedLineIndex, _lastSelectedLineIndex);
				}

				cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
			}

			if(isControlKeyDown)
			{
				if(_fe3d->input_isKeyPressed(InputType::KEY_C))
				{
					_copySelectedText();
				}
				else if(_fe3d->input_isKeyPressed(InputType::KEY_V))
				{
					if(!_copyClipboard.empty())
					{
						unsigned int pastedCount = 0;
						bool firstLineEmpty = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).empty();

						for(unsigned int index = 0; index < _copyClipboard.size(); index++)
						{
							if((cursorLineIndex + index) < _script->getScriptFile(_currentScriptFileId)->getLineCount())
							{
								if(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex + static_cast<unsigned int>(index)).empty())
								{
									_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex + static_cast<unsigned int>(index), _copyClipboard[index]);
									pastedCount++;
									continue;
								}
							}

							if(_script->getScriptFile(_currentScriptFileId)->getLineCount() < MAX_LINE_COUNT)
							{
								_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex + static_cast<unsigned int>(index), _copyClipboard[index]);
								pastedCount++;
							}
							else
							{
								break;
							}
						}

						if(pastedCount > 0)
						{
							cursorLineIndex += (pastedCount - static_cast<int>(firstLineEmpty));
							cursorLineIndex = min(cursorLineIndex, (MAX_LINE_COUNT - 1));
							cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());

							hasTextChanged = true;
						}
					}
				}
			}
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);

		if(hasTextChanged)
		{
			_unloadScriptDisplayEntities();
			_loadScriptDisplayEntities();
		}

		if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 2)) == 0)
		{
			if(_firstSelectedLineIndex != -1)
			{
				_fe3d->text3d_setContent("cursor", " ");
			}
			else
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
		}

		if(cursorCharacterIndex == 0)
		{
			const auto linePosition = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex));
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