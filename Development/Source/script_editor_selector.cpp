#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::_updateTextSelector(string& newCharacters, unsigned int& cursorLineIndex, 
	unsigned int& cursorCharIndex, int& hoveredLineIndex, bool& textHasChanged)
{
	// Check if any text selected
	if (_firstSelectedLineIndex != -1)
	{
		// Check if user cancels or edits any selected text
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || 
			_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_RIGHT) ||
			_activeActionKey != InputType::NONE || 
			!newCharacters.empty() || 
			(_fe3d.input_getKeyDown(InputType::KEY_LCTRL) && _fe3d.input_getKeyPressed(InputType::KEY_V)) ||
			(_fe3d.input_getKeyDown(InputType::KEY_LCTRL) && _fe3d.input_getKeyPressed(InputType::KEY_X)))
		{
			// Delete selection billboards
			for (auto& ID : _fe3d.billboardEntity_getAllIDs())
			{
				if (ID.substr(0, string("selection_").size()) == "selection_")
				{
					_fe3d.billboardEntity_delete(ID);
				}
			}

			// Copy before removing text
			if (_fe3d.input_getKeyDown(InputType::KEY_LCTRL) && _fe3d.input_getKeyPressed(InputType::KEY_X))
			{
				_copySelectedText();
			}

			// Check if text content has been changed
			if (!newCharacters.empty() || 
				_fe3d.input_getKeyPressed(InputType::KEY_BACKSPACE) ||
				_fe3d.input_getKeyPressed(InputType::KEY_DELETE) ||
				_fe3d.input_getKeyPressed(InputType::KEY_ENTER) ||
				(_fe3d.input_getKeyDown(InputType::KEY_LCTRL) && _fe3d.input_getKeyPressed(InputType::KEY_V)) ||
				(_fe3d.input_getKeyDown(InputType::KEY_LCTRL) && _fe3d.input_getKeyPressed(InputType::KEY_X)))
			{
				if (_lastSelectedLineIndex == -1) // Only 1 line is selected
				{
					_script.getScriptFile(_currentScriptFileID)->removeLine(_firstSelectedLineIndex);
				}
				else
				{
					// Remove selected lines
					int lineIndexToRemove = (_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex;
					for (int i = 0; i <= abs(_firstSelectedLineIndex - _lastSelectedLineIndex); i++)
					{
						_script.getScriptFile(_currentScriptFileID)->removeLine(static_cast<unsigned int>(lineIndexToRemove));
					}
				}

				// Correct cursor position
				if (cursorLineIndex > _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
				{
					cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getLineCount();
				}
				cursorCharIndex = newCharacters.empty() ? 0 : newCharacters.size(); // Index based on amount of newly added characters

				// Add new line
				_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, newCharacters);

				// Add extra line for entering
				if (_fe3d.input_getKeyPressed(InputType::KEY_ENTER))
				{
					// Check if not exceeding the line limit
					if (_script.getScriptFile(_currentScriptFileID)->getLineCount() < _maxLineAmount)
					{
						_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, "");
						cursorLineIndex++;
					}
				}

				// Make sure the script gets re-rendered
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
				// Check if line text is empty
				if (_fe3d.billboardEntity_getTextContent(textID).empty())
				{
					Vec3 lineTextPosition = _fe3d.billboardEntity_getPosition(textID) - Vec3(0.0f, 0.0f, 0.05f);
					lineTextPosition.x = _scriptTextStartingPosition.x + _horizontalLineOffset;
					_fe3d.billBoardEntity_add(selectionID, _selectionColor, lineTextPosition, Vec3(0.0f), _textCharacterSize, false, false);
				}
				else // Line is not empty
				{
					Vec3 lineTextPosition = _fe3d.billboardEntity_getPosition(textID) - Vec3(0.0f, 0.0f, 0.05f);
					Vec2 lineTextSize = _fe3d.billboardEntity_getSize(textID);
					_fe3d.billBoardEntity_add(selectionID, _selectionColor, lineTextPosition, Vec3(0.0f), lineTextSize, false, false);
				}
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
	else // User stopped selecting text
	{
		if (_firstSelectedLineIndex != -1) // Check if any text selected
		{
			if (_lastSelectedLineIndex == -1) // Only 1 line is selected
			{
				cursorLineIndex = _firstSelectedLineIndex;
			}
			else // Multiple lines selected
			{
				// Most upper selected line must be the cursor position
				cursorLineIndex = std::min(_firstSelectedLineIndex, _lastSelectedLineIndex);
			}

			cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
		}

		// Control button combinations
		if (_fe3d.input_getKeyDown(InputType::KEY_LCTRL))
		{
			if (_fe3d.input_getKeyPressed(InputType::KEY_C)) // Copy selected text to clipboard
			{
				_copySelectedText();
			}
			else if (_fe3d.input_getKeyPressed(InputType::KEY_V)) // Paste copied text
			{
				// Check if clipboard is not empty
				if (!_copyClipboard.empty())
				{
					// Paste as much copied text as possible
					unsigned int pastedAmount = 0;
					bool firstLineEmpty = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).empty();
					for (unsigned int i = 0; i < _copyClipboard.size(); i++)
					{
						// Check if next line exists
						if ((cursorLineIndex + i) < _script.getScriptFile(_currentScriptFileID)->getLineCount())
						{
							// Check if text can be placed on current line
							if (_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + i).empty())
							{
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex + i, _copyClipboard[i]);
								pastedAmount++;
								continue;
							}
						}

						// Try to create new line
						if (_script.getScriptFile(_currentScriptFileID)->getLineCount() < _maxLineAmount)
						{
							_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex + i, _copyClipboard[i]);
							pastedAmount++;
						}
						else
						{
							break;
						}
					}

					// Check if anything has been successfully pasted
					if (pastedAmount > 0)
					{
						// Change cursor position
						cursorLineIndex += (pastedAmount - static_cast<int>(firstLineEmpty));
						cursorLineIndex = std::min(cursorLineIndex, (_maxLineAmount - 1));
						cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();

						// Make sure the script gets re-rendered
						textHasChanged = true;
					}
				}
			}
		}
	}
}