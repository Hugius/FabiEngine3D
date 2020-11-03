#include "script_editor.hpp"

void ScriptEditor::_updateTextWriter()
{
	// User must be editing script file & no active GUI overlays
	if (_isLoaded && _isWritingScript && !_gui.getGlobalScreen()->isFocused() && !_wasGuiFocused)
	{
		// Change cursor texture
		if (_fe3d.misc_isCursorInsideViewport())
		{
			_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_text.png");
		}

		// Handy values
		bool textHasChanged = false;
		unsigned int cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getCursorLineIndex();
		unsigned int cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getCursorCharIndex();

		// Check if a billboard is hovered
		auto hoveredBillboardID = _fe3d.collision_checkCursorInAny();
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;
		if (!hoveredBillboardID.empty())
		{
			// Temporary values
			bool extractingLineNumber = true;
			string lineIndexString = "";
			string charIndexString = "";

			// Extract position indices
			for (auto& c : hoveredBillboardID)
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
			for (InputType actionKey : _actionKeys) // Check all possible action keys
			{
				if (_fe3d.input_getKeyPressed(actionKey)) // Check if action key is pressed
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
			if (_passedFrames == _continuousTextActionFrameMinimum)
			{
				_continuousActionAllowed = true;
				_passedFrames = 0;
			}
			else // Keep waiting
			{
				_passedFrames++;
			}
		}

		// Reset timing state if action key released
		if (!_fe3d.input_getKeyDown(_activeActionKey))
		{
			_activeActionKey = InputType::NONE;
			_passedFrames = 0;
			_singleActionAllowed = true;
			_continuousActionAllowed = false;
		}

		// Determine text action type
		if (_fe3d.input_getKeyDown(InputType::KEY_ENTER)) // Add new line
		{
			// Check if not exceeding the line limit
			if (_script.getScriptFile(_currentScriptFileID)->getLineCount() < _maxLineAmount)
			{
				// Check if single or fast new line action
				if (_singleActionAllowed || _continuousActionAllowed)
				{
					if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
					{
						_singleActionAllowed = false;

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
		else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // Move blinking cursor position
		{
			// Check if anything was hovered at all
			if (!hoveredBillboardID.empty())
			{
				// Set line index based on click location
				cursorLineIndex = hoveredLineIndex;

				// Set character index based on click location
				if (hoveredCharacterIndex == -1)
				{
					cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size(); // Place cursor at end of line
				}
				else
				{
					cursorCharIndex = hoveredCharacterIndex; // Place cursor at clicked position
				}
			}
		}
		else if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT)) // Text selection
		{
			_isSelectingLines = true;
		}
		else if (_activeActionKey == InputType::KEY_LEFT) // Left arrow key
		{
			// Check if single or fast cursor move
			if (_singleActionAllowed || _continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
				{
					_singleActionAllowed = false;

					if (cursorCharIndex > 0) // If cursor somewhere on the line
					{
						cursorCharIndex--;
					}
					else // If cursor is at the beginning of the line
					{
						if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
						{
							cursorLineIndex--;
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(InputType::KEY_RIGHT)) // Right arrow key
		{
			// Check if single or fast cursor move
			if (_singleActionAllowed || _continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
				{
					_singleActionAllowed = false;

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
		else if (_fe3d.input_getKeyDown(InputType::KEY_UP)) // Up arrow key
		{
			// Check if single or fast cursor move
			if (_singleActionAllowed || _continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
				{
					_singleActionAllowed = false;

					if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
					{
						cursorLineIndex--;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(InputType::KEY_DOWN)) // Down arrow key
		{
			// Check if single or fast cursor move
			if (_singleActionAllowed || _continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
				{
					_singleActionAllowed = false;

					// Check if trying to move cursor out of screen
					if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						cursorLineIndex++;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else // Other keypresses
		{
			// Temporary values
			string currentLineText = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
			string newCharacters = "";

			// Check if not exceeding character limit of current line
			if (currentLineText.size() < _maxCharactersPerLine)
			{
				// Control button is reserved for copy & paste
				if (!_fe3d.input_getKeyDown(InputType::KEY_LCTRL))
				{
					// Letter characters
					for (auto& c : _letterCharacters)
					{
						// Check if character is pressed on keyboard
						if (_fe3d.input_getKeyPressed(InputType(c)))
						{
							// Spacebar
							if (c == ' ')
							{
								newCharacters += c;
							}
							else // Non-spacebar
							{
								// Uppercase or special character
								if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
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
					for (auto& element : _numberCharacters)
					{
						// Check if character is pressed on keyboard
						if (_fe3d.input_getKeyPressed(InputType(element.first)))
						{
							// Check if shift was pressed
							if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
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
					for (auto& element : _specialCharacters)
					{
						// Check if character is pressed on keyboard
						if (_fe3d.input_getKeyPressed(InputType(element.first)))
						{
							// Check if shift was pressed
							if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
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
					if (_fe3d.input_getKeyPressed(InputType::KEY_TAB))
					{
						newCharacters += "    ";
					}
				}
			}

			// Remove characters from line
			if (_activeActionKey == InputType::KEY_BACKSPACE || _activeActionKey == InputType::KEY_DELETE)
			{
				// Check if user is not selecting text
				if (_firstSelectedLineIndex == -1)
				{
					// Check if single or fast remove
					if (_singleActionAllowed || _continuousActionAllowed)
					{
						if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || _singleActionAllowed)
						{
							_singleActionAllowed = false;

							// Jump to line above if cursor at beginning of line
							if (cursorCharIndex == 0 && _fe3d.input_getKeyDown(InputType::KEY_BACKSPACE))
							{
								// Check if not trying to remove default line
								if (cursorLineIndex > 0)
								{
									// Remove line
									string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
									_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex);
									cursorLineIndex--;

									// Set cursor to last character of line above & merge text from current line
									cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
									_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex,
										_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex) + textToMerge);
									textHasChanged = true;
								}
							}
							else if (cursorCharIndex == currentLineText.size() && _fe3d.input_getKeyDown(InputType::KEY_DELETE))
							{
								// Check if not trying to remove default line
								if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
								{
									// Remove line
									string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + 1);
									_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex + 1);

									// Merge text on current line & save merged line
									currentLineText += textToMerge;
									_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
									textHasChanged = true;
								}
							}
							else if (cursorCharIndex > 0 && _fe3d.input_getKeyDown(InputType::KEY_BACKSPACE)) // Remove previous character from current line
							{
								cursorCharIndex--;
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
							}
							else if (_fe3d.input_getKeyDown(InputType::KEY_DELETE)) // Remove next character from current line
							{
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
							}
						}
					}
				}
			}

			// Add new typed character to line
			if (newCharacters != "")
			{
				if (currentLineText == "" || cursorCharIndex == currentLineText.size()) // First or last character in line
				{
					for (auto& character : newCharacters)
					{
						currentLineText += character;
						cursorCharIndex++;
					}
				}
				else // Inbetween character in line
				{
					for (auto& character : newCharacters)
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

		// Check if any text selected
		if (_firstSelectedLineIndex != -1)
		{
			// Check if user cancels or edits any selected text
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_RIGHT) ||
				_activeActionKey != InputType::NONE || textHasChanged)
			{
				// Delete selection billboards
				for (auto& ID : _fe3d.billboardEntity_getAllIDs())
				{
					if (ID.substr(0, string("selection_").size()) == "selection_")
					{
						_fe3d.billboardEntity_delete(ID);
					}
				}

				// Check if text content has been changed
				if (textHasChanged || _fe3d.input_getKeyPressed(InputType::KEY_BACKSPACE) || _fe3d.input_getKeyPressed(InputType::KEY_DELETE))
				{
					std::cout << _firstSelectedLineIndex << " " << _lastSelectedLineIndex << std::endl;
					if (_lastSelectedLineIndex == -1)
					{
						_script.getScriptFile(_currentScriptFileID)->removeLine(_firstSelectedLineIndex);
					}
					else
					{
						// Remove selected lines
						for (int i = 0; i <= abs(_firstSelectedLineIndex - _lastSelectedLineIndex); i++)
						{
							unsigned int lineIndexToRemove = (_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex;
							_script.getScriptFile(_currentScriptFileID)->removeLine(lineIndexToRemove);
						}
					}

					// Correct cursor position
					if (cursorLineIndex > _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1;

						// Character index
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size() - 1)
						{
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size() - 1;
						}
					}
					
					// Make sure the script gets reloaded
					textHasChanged = true;

					// Make sure only the selected text is removed
					_activeActionKey = InputType::NONE;
				}

				// Reset selection values
				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
			}
		}

		// Update text selection
		if (_isSelectingLines)
		{
			// Check if still holding RMB
			if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				// Check if a line is hovered
				if (hoveredLineIndex != -1)
				{
					string selectionID = ("selection_" + to_string(hoveredLineIndex));
					string textID = ("text_" + to_string(hoveredLineIndex));

					// Check if line has text to be selected
					if (!_fe3d.billboardEntity_isExisting(selectionID) && _fe3d.billboardEntity_isExisting(textID))
					{
						vec3 lineTextPosition = _fe3d.billboardEntity_getPosition(textID) - vec3(0.0f, 0.0f, 0.05f);
						vec2 lineTextSize = _fe3d.billboardEntity_getSize(textID);
						_fe3d.billBoardEntity_add(selectionID, _selectionColor, lineTextPosition, vec3(0.0f), lineTextSize, false, false);
					}

					// Remember first selected line
					if (_firstSelectedLineIndex == -1)
					{
						_firstSelectedLineIndex = hoveredLineIndex;
					}
					else
					{
						// Make sure user can only select in 1 direction
						if (_lastSelectedLineIndex != -1)
						{
							int lastDirection = _firstSelectedLineIndex - _lastSelectedLineIndex;
							int currentDirection = _lastSelectedLineIndex - hoveredLineIndex;

							if ((lastDirection < 0 && currentDirection > 0) ||
								(currentDirection < 0 && lastDirection > 0))
							{
								_fe3d.billboardEntity_delete("selection_" + to_string(_lastSelectedLineIndex));
							}
						}

						// Remember last selected line
						_lastSelectedLineIndex = hoveredLineIndex;
					}
				}
			}
			else
			{
				_isSelectingLines = false;
			}
		}
		else
		{
			// Control button combinations
			if (_fe3d.input_getKeyDown(InputType::KEY_LCTRL))
			{
				if (_fe3d.input_getKeyPressed(InputType::KEY_C)) // Copy selected text to clipboard
				{
					if (_firstSelectedLineIndex != -1) // Check if anything is selected at all
					{
						_copyClipboard.clear(); // Clear last copy

						if (_lastSelectedLineIndex == -1) // Check if only 1 line selected
						{
							_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(_firstSelectedLineIndex));
						}
						else // If multiple selected lines
						{
							// Determine selection direction
							for (int i = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
								i <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); i++)
							{
								_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(i)); // Copy text lines
							}
						}
					}
				}
				else if (_fe3d.input_getKeyPressed(InputType::KEY_V)) // Paste copied text
				{

				}
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
		if (!_fe3d.billboardEntity_isExisting("cursor"))
		{
			_fe3d.billBoardEntity_add("cursor", "", _fontPath, vec3(1.0f), vec3(0.0f), vec3(0.0f), _textCharacterSize, 0, 0);
		}

		// Update cursor billboard text & position
		vec3 position;
		if (cursorCharIndex == 0) // Default line position
		{
			position = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex)) + vec3(_horizontalLineOffset / 2.0f, 0.0f, 0.0f);
		}
		else // Mid-text position
		{
			position = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharIndex - 1));
		}
		position += vec3(_textCharacterSize.x / 2.0f, 0.0f, 0.0f);
		_fe3d.billboardEntity_setPosition("cursor", position);
		_fe3d.billBoardEntity_setTextContent("cursor", ((barEnabled && _firstSelectedLineIndex == -1) ? "|" : " "));

		// Set new cursor indices
		_script.getScriptFile(_currentScriptFileID)->setCursorLineIndex(cursorLineIndex);
		_script.getScriptFile(_currentScriptFileID)->setCursorCharIndex(cursorCharIndex);
	}

	_wasGuiFocused = _gui.getGlobalScreen()->isFocused();
}