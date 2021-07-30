#include "script_editor.hpp"

#include <windows.h>

void ScriptEditor::_updateTextWriter()
{
	// User must be editing script file & no active GUI overlays
	if (_isEditorLoaded && _isWritingScript && !_gui.getGlobalScreen()->isFocused() && !_wasGuiFocused)
	{
		// Change cursor texture
		if (_fe3d.misc_isCursorInsideViewport())
		{
			_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_text.png");
		}

		// Reload all AABB entities when LMB is pressed
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isCursorInsideViewport())
		{
			_reloadScriptTextDisplay(true);
			_hasClickedLMB = true;
			return;
		}

		// Temporary values
		bool textHasChanged = false;
		unsigned int cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getCursorLineIndex();
		unsigned int cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getCursorCharIndex();
		string newCharacters = "";
		
		// Check if a billboard is hovered
		auto hoveredBillboardID = _fe3d.collision_checkCursorInAny().first;
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;
		if (!hoveredBillboardID.empty())
		{
			// Temporary values
			bool extractingLineNumber = true;
			string lineIndexString = "";
			string charIndexString = "";

			// Extract position indices
			for (const auto& c : hoveredBillboardID)
			{
				// Add to string
				if (extractingLineNumber)
				{
					lineIndexString += c;
				}
				else
				{
					charIndexString += c;
				}

				// Check if character billboard
				if (c == '_')
				{
					extractingLineNumber = false;
				}
			}

			// Assign indices
			hoveredLineIndex = stoi(lineIndexString);
			if (!charIndexString.empty())
			{
				hoveredCharacterIndex = stoi(charIndexString);
			}
		}

		// Timer for continuous actions
		if (_activeActionKey == InputType::NONE)
		{
			for (InputType actionKey : ACTION_KEYS) // Check all possible action keys
			{
				if (_fe3d.input_isKeyPressed(actionKey)) // Check if action key is pressed
				{
					// Remember currently pressed action key
					_activeActionKey = actionKey;
					break;
				}
			}
		}
		else
		{
			// Check if waited long enough for continuous action
			if (_passedFrames == CONTINUOUS_TEXT_ACTION_FRAME_MINIMUM)
			{
				_isContinuousActionAllowed = true;
				_passedFrames = 0;
			}
			else // Keep waiting
			{
				_passedFrames++;
			}
		}

		// Reset timing state if action key released
		if (!_fe3d.input_isKeyDown(_activeActionKey))
		{
			_activeActionKey = InputType::NONE;
			_passedFrames = 0;
			_isSingleActionAllowed = true;
			_isContinuousActionAllowed = false;
		}

		// Determine text functionality type
		if (_hasClickedLMB)
		{
			// Check if anything was hovered at all
			if (!hoveredBillboardID.empty())
			{
				// Set line index based on click location
				cursorLineIndex = hoveredLineIndex;

				// Set character index based on click location
				if (hoveredCharacterIndex == -1)
				{
					// Place cursor at end of the line
					cursorCharIndex = static_cast<unsigned int>(_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
				}
				else
				{
					cursorCharIndex = hoveredCharacterIndex; // Place cursor at clicked position
				}
			}
		}
		else if (_activeActionKey == InputType::KEY_ENTER) // Add new line
		{
			// Check if user is not selecting text
			if (_firstSelectedLineIndex == -1)
			{
				// Check if not exceeding the line limit
				if (_script.getScriptFile(_currentScriptFileID)->getLineCount() < MAX_LINE_AMOUNT)
				{
					// Check if single or fast new line action
					if (_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							// Extract remaining text in current line from cursor position
							string currentLineText = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
							string textToExtract = currentLineText;
							textToExtract = textToExtract.substr(cursorCharIndex, textToExtract.size() - cursorCharIndex);

							// Remove extracted text from current line
							_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharIndex));

							// Set cursor to beginning of new line
							cursorCharIndex = 0;
							cursorLineIndex++;

							// Add text on new line
							_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, textToExtract);
							textHasChanged = true;
						}
					}
				}
			}
		}
		else if (_activeActionKey == InputType::KEY_LEFT) // Left arrow key
		{
			// Check if single or fast cursor move
			if (_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if (cursorCharIndex > 0) // If cursor somewhere on the line
					{
						cursorCharIndex--;
					}
					else // If cursor is at the beginning of the line
					{
						if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
						{
							cursorLineIndex--;
							cursorCharIndex = static_cast<unsigned int>(_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if (_activeActionKey == InputType::KEY_RIGHT) // Right arrow key
		{
			// Check if single or fast cursor move
			if (_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					// If cursor somewhere on the line
					if (cursorCharIndex < _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
					{
						cursorCharIndex++;
					}
					else // If cursor is at the end of the line
					{
						// Check if trying to move cursor out of screen
						if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
						{
							cursorLineIndex++;
							cursorCharIndex = 0;
						}
					}
				}
			}
		}
		else if (_activeActionKey == InputType::KEY_UP) // Up arrow key
		{
			// Check if single or fast cursor move
			if (_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
					{
						cursorLineIndex--;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if (_activeActionKey == InputType::KEY_DOWN) // Down arrow key
		{
			// Check if single or fast cursor move
			if (_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					// Check if trying to move cursor out of screen
					if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						cursorLineIndex++;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else // Other keypresses
		{
			// Temporary values
			string currentLineText = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);

			// Control button is reserved for copy & paste
			if (!_fe3d.input_isKeyDown(InputType::KEY_LCTRL) && !_fe3d.input_isKeyDown(InputType::KEY_RCTRL))
			{
				// Letter characters
				for (const auto& c : ALPHABET_CHARACTERS)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_isKeyPressed(InputType(c)))
					{
						// Spacebar
						if (c == ' ')
						{
							newCharacters += c;
						}
						else // Non-spacebar
						{
							// Uppercase or special character
							if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
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
				}

				// Number characters
				for (const auto& element : NUMBER_CHARACTERS)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_isKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += element.second;
						}
						else
						{
							newCharacters += element.first;
						}
					}
				}

				// Special characters
				for (const auto& element : SPECIAL_CHARACTERS)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_isKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += element.second;
						}
						else
						{
							newCharacters += element.first;
						}
					}
				}

				// Insert 4 spaces (TAB)
				if (_fe3d.input_isKeyPressed(InputType::KEY_TAB))
				{
					newCharacters += "    ";
				}
			}

			// Remove characters from line
			if (_activeActionKey == InputType::KEY_BACKSPACE || _activeActionKey == InputType::KEY_DELETE)
			{
				// Check if user is not selecting text
				if (_firstSelectedLineIndex == -1)
				{
					// Check if single or fast remove
					if (_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if (_fe3d.misc_checkInterval(CONTINUOUS_TEXT_ACTION_INTERVAL) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							// Jump to line above if cursor at beginning of line
							if (cursorCharIndex == 0 && _activeActionKey == InputType::KEY_BACKSPACE)
							{
								// Check if not trying to remove default line
								if (cursorLineIndex > 0)
								{
									// Remove line
									string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
									_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex);
									cursorLineIndex--;

									// Set cursor to last character of line above & merge text from current line
									cursorCharIndex = static_cast<unsigned int>(_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
									_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex,
										_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex) + textToMerge);
									textHasChanged = true;
								}
							}
							else if (cursorCharIndex == currentLineText.size() && _activeActionKey == InputType::KEY_DELETE)
							{
								// Check if not trying to remove default line
								if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
								{
									// Save next line's textLove
									string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + 1);

									// Check if lines together is not exceeding the character limit
									if ((currentLineText.size() + textToMerge.size()) <= MAX_CHARACTERS_PER_LINE)
									{
										// Remove line
										_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex + 1);

										// Merge text on current line & save merged line
										currentLineText += textToMerge;
										_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
										textHasChanged = true;
									}
								}
							}
							else if (cursorCharIndex > 0 && _fe3d.input_isKeyDown(InputType::KEY_BACKSPACE)) // Remove previous character from current line
							{
								cursorCharIndex--;
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
							}
							else if (_fe3d.input_isKeyDown(InputType::KEY_DELETE)) // Remove next character from current line
							{
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
							}
						}
					}
				}
			}

			// Check if not exceeding character limit of current line
			if (static_cast<unsigned int>(currentLineText.size() + newCharacters.size()) <= MAX_CHARACTERS_PER_LINE)
			{
				// Check if user is not selecting text
				if (_firstSelectedLineIndex == -1)
				{
					// Add newly typed character to line
					if (!newCharacters.empty())
					{
						if (currentLineText.empty() || cursorCharIndex == currentLineText.size()) // First or last character in line
						{
							for (const auto& character : newCharacters)
							{
								currentLineText += character;
								cursorCharIndex++;
							}
						}
						else // Inbetween character in line
						{
							for (const auto& character : newCharacters)
							{
								currentLineText.insert(currentLineText.begin() + cursorCharIndex, character);
								cursorCharIndex++;
							}
						}

						textHasChanged = true;

						// Save new line
						_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
					}
				}
			}
		}

		// Update text selection
		_updateTextSelector(newCharacters, cursorLineIndex, cursorCharIndex, hoveredLineIndex, textHasChanged);

		// Reload text display when altered
		if (textHasChanged || _hasClickedLMB)
		{
			_reloadScriptTextDisplay(false);
		}

		// Update blinking cursor
		static unsigned int passedBarFrames = MAX_PASSED_BAR_FRAMES;
		static bool barEnabled = true;
		if (passedBarFrames >= MAX_PASSED_BAR_FRAMES)
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
		if (!_fe3d.billboardEntity_isExisting("cursor"))
		{
			_fe3d.billboardEntity_create("cursor", "", FONT_PATH, Vec3(1.0f), Vec3(0.0f), Vec3(0.0f), TEXT_CHARACTER_SIZE, 0, 0);
		}

		// Update cursor billboard text & position
		Vec3 position;
		if (cursorCharIndex == 0) // Default line position
		{
			Vec3 linePosition = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex));
			position = Vec3(SCRIPT_TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET - HORIZONTAL_CHARACTER_OFFSET, linePosition.y, linePosition.z);
		}
		else // Mid-text position
		{
			position = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharIndex - 1));
		}
		position += Vec3(TEXT_CHARACTER_SIZE.x / 2.0f, 0.0f, 0.0f);
		_fe3d.billboardEntity_setPosition("cursor", position);
		bool showBar = ((barEnabled && _firstSelectedLineIndex == -1) || _activeActionKey != InputType::NONE);
		_fe3d.billboardEntity_setTextContent("cursor", (showBar ? "|" : " "));

		// Set new cursor indices
		_script.getScriptFile(_currentScriptFileID)->setCursorLineIndex(cursorLineIndex);
		_script.getScriptFile(_currentScriptFileID)->setCursorCharIndex(cursorCharIndex);
	}

	// Miscellaneous
	_wasGuiFocused = _gui.getGlobalScreen()->isFocused();
	_hasClickedLMB = false;
}