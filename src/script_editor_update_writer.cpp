#include "script_editor.hpp"

#include <windows.h>

void ScriptEditor::_updateTextWriter()
{
	if(_isEditorLoaded && _isWritingScript && !_gui->getOverlay()->isFocused() && !_wasGuiFocused)
	{
		if(_fe3d->misc_isCursorInsideViewport())
		{
			_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_text.tga");
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideViewport())
		{
			_reloadScriptTextDisplay(true);
			_hasClickedLMB = true;
			return;
		}

		bool textHasChanged = false;
		unsigned int cursorLineIndex = _script->getScriptFile(_currentScriptFileID)->getCursorLineIndex();
		unsigned int cursorCharIndex = _script->getScriptFile(_currentScriptFileID)->getCursorCharIndex();
		string newCharacters = "";

		auto hoveredTextID = _fe3d->raycast_checkCursorInAny().first;
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;
		if(!hoveredTextID.empty())
		{
			bool extractingLineNumber = true;
			string lineIndexString = "";
			string charIndexString = "";

			for(const auto& c : hoveredTextID)
			{
				if(extractingLineNumber)
				{
					lineIndexString += c;
				}
				else
				{
					charIndexString += c;
				}

				if(c == '_')
				{
					extractingLineNumber = false;
				}
			}

			hoveredLineIndex = stoi(lineIndexString);
			if(!charIndexString.empty())
			{
				hoveredCharacterIndex = stoi(charIndexString);
			}
		}

		if(_activeActionKey == InputType::NONE)
		{
			for(InputType actionKey : ACTION_KEYS)
			{
				if(_fe3d->input_isKeyPressed(actionKey))
				{
					_activeActionKey = actionKey;
					break;
				}
			}
		}
		else
		{
			if(_passedFrames == CONTINUOUS_TEXT_ACTION_FRAME_MINIMUM)
			{
				_isContinuousActionAllowed = true;
				_passedFrames = 0;
			}
			else
			{
				_passedFrames++;
			}
		}

		if(!_fe3d->input_isKeyDown(_activeActionKey))
		{
			_activeActionKey = InputType::NONE;
			_passedFrames = 0;
			_isSingleActionAllowed = true;
			_isContinuousActionAllowed = false;
		}

		if(_hasClickedLMB)
		{
			if(!hoveredTextID.empty())
			{
				cursorLineIndex = hoveredLineIndex;

				if(hoveredCharacterIndex == -1)
				{
					cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
				}
				else
				{
					cursorCharIndex = hoveredCharacterIndex;
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_ENTER)
		{
			if(_firstSelectedLineIndex == -1)
			{
				if(_script->getScriptFile(_currentScriptFileID)->getLineCount() < MAX_LINE_COUNT)
				{
					if(_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							string currentLineText = _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
							string textToExtract = currentLineText;
							textToExtract = textToExtract.substr(cursorCharIndex, textToExtract.size() - cursorCharIndex);

							_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharIndex));

							cursorCharIndex = 0;
							cursorLineIndex++;

							_script->getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, textToExtract);
							textHasChanged = true;
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_LEFT)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorCharIndex > 0)
					{
						cursorCharIndex--;
					}
					else
					{
						if(cursorLineIndex > 0)
						{
							cursorLineIndex--;
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_RIGHT)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorCharIndex < _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
					{
						cursorCharIndex++;
					}
					else
					{
						if(cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
						{
							cursorLineIndex++;
							cursorCharIndex = 0;
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_UP)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorLineIndex > 0)
					{
						cursorLineIndex--;

						if(cursorCharIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_DOWN)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						cursorLineIndex++;

						if(cursorCharIndex > _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else
		{
			string currentLineText = _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);

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

				for(const auto& element : NUMBER_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(element.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += element.second;
						}
						else
						{
							newCharacters += element.first;
						}
					}
				}

				for(const auto& element : SPECIAL_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(element.first)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += element.second;
						}
						else
						{
							newCharacters += element.first;
						}
					}
				}

				if(_fe3d->input_isKeyPressed(InputType::KEY_TAB))
				{
					newCharacters += "    ";
				}
			}

			if(_activeActionKey == InputType::KEY_BACKSPACE || _activeActionKey == InputType::KEY_DELETE)
			{
				if(_firstSelectedLineIndex == -1)
				{
					if(_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if(_fe3d->misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							if(cursorCharIndex == 0 && _activeActionKey == InputType::KEY_BACKSPACE)
							{
								if(cursorLineIndex > 0)
								{
									string textToMerge = _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
									_script->getScriptFile(_currentScriptFileID)->deleteLine(cursorLineIndex);
									cursorLineIndex--;

									cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
									_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex,
																							  _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex) + textToMerge);
									textHasChanged = true;
								}
							}
							else if(cursorCharIndex == currentLineText.size() && _activeActionKey == InputType::KEY_DELETE)
							{
								if(cursorLineIndex < _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
								{
									string textToMerge = _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + 1);

									if((currentLineText.size() + textToMerge.size()) <= MAX_CHARACTERS_PER_LINE)
									{
										_script->getScriptFile(_currentScriptFileID)->deleteLine(cursorLineIndex + 1);

										currentLineText += textToMerge;
										_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
										textHasChanged = true;
									}
								}
							}
							else if(cursorCharIndex > 0 && _fe3d->input_isKeyDown(InputType::KEY_BACKSPACE))
							{
								cursorCharIndex--;
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
							}
							else if(_fe3d->input_isKeyDown(InputType::KEY_DELETE))
							{
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
							}
						}
					}
				}
			}

			if(static_cast<unsigned int>(currentLineText.size() + newCharacters.size()) <= MAX_CHARACTERS_PER_LINE)
			{
				if(_firstSelectedLineIndex == -1)
				{
					if(!newCharacters.empty())
					{
						if(currentLineText.empty() || cursorCharIndex == currentLineText.size())
						{
							for(const auto& character : newCharacters)
							{
								currentLineText += character;
								cursorCharIndex++;
							}
						}
						else
						{
							for(const auto& character : newCharacters)
							{
								currentLineText.insert(currentLineText.begin() + cursorCharIndex, character);
								cursorCharIndex++;
							}
						}

						textHasChanged = true;

						_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
					}
				}
			}
		}

		_updateTextSelector(newCharacters, cursorLineIndex, cursorCharIndex, hoveredLineIndex, textHasChanged);

		if(textHasChanged || _hasClickedLMB)
		{
			_reloadScriptTextDisplay(false);
		}

		static unsigned int passedBarFrames = MAX_PASSED_BAR_FRAMES;
		static bool barEnabled = true;
		if(passedBarFrames >= MAX_PASSED_BAR_FRAMES)
		{
			passedBarFrames = 0;

			barEnabled = !barEnabled;
		}
		else
		{
			passedBarFrames++;
		}

		if(!_fe3d->text3d_isExisting("cursor"))
		{
			_fe3d->text3d_create("cursor", FONT_MAP_PATH, false);
			_fe3d->text3d_setSize("cursor", TEXT_CHARACTER_SIZE);
		}

		fvec3 position;
		if(cursorCharIndex == 0)
		{
			fvec3 linePosition = _fe3d->text3d_getPosition(to_string(cursorLineIndex));
			position = fvec3(SCRIPT_TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET - HORIZONTAL_CHARACTER_OFFSET, linePosition.y, linePosition.z);
		}
		else
		{
			position = _fe3d->text3d_getPosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharIndex - 1));
		}
		position += fvec3(TEXT_CHARACTER_SIZE.x / 2.0f, 0.0f, 0.0f);
		_fe3d->text3d_setPosition("cursor", position);
		bool showBar = ((barEnabled && _firstSelectedLineIndex == -1) || _activeActionKey != InputType::NONE);
		_fe3d->text3d_setContent("cursor", (showBar ? "|" : " "));

		_script->getScriptFile(_currentScriptFileID)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileID)->setCursorCharIndex(cursorCharIndex);
	}

	_wasGuiFocused = _gui->getOverlay()->isFocused();
	_hasClickedLMB = false;
}