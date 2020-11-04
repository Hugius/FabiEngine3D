#include "script_editor.hpp"

void ScriptEditor::_updateTextSelector(string& newCharacters, unsigned int& cursorLineIndex, 
	unsigned int& cursorCharIndex, int& hoveredLineIndex, bool& textHasChanged)
{
	// Check if any text selected
	if (_firstSelectedLineIndex != -1)
	{
		// Check if user cancels or edits any selected text
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_RIGHT) ||
			_activeActionKey != InputType::NONE || !newCharacters.empty())
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
			if (!newCharacters.empty() || _fe3d.input_getKeyPressed(InputType::KEY_BACKSPACE) ||
				_fe3d.input_getKeyPressed(InputType::KEY_DELETE) || _fe3d.input_getKeyPressed(InputType::KEY_ENTER))
			{
				if (_lastSelectedLineIndex == -1) // Only 1 line is selected
				{
					_script.getScriptFile(_currentScriptFileID)->removeLine(_firstSelectedLineIndex);
				}
				else
				{
					// Remove selected lines
					for (int i = 0; i <= abs(_firstSelectedLineIndex - _lastSelectedLineIndex); i++)
					{
						int lineIndexToRemove = (_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex;
						_script.getScriptFile(_currentScriptFileID)->removeLine(static_cast<unsigned int>(lineIndexToRemove));
					}
				}

				// Correct cursor position
				if (cursorLineIndex > _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
				{
					cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getLineCount();
				}
				_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, newCharacters); // Add new line
				cursorCharIndex = newCharacters.empty() ? 0 : newCharacters.size(); // 

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
					vec3 lineTextPosition = _fe3d.billboardEntity_getPosition(textID) - vec3(0.0f, 0.0f, 0.05f);
					lineTextPosition.x = _scriptTextStartingPosition.x + _horizontalCharacterOffset + _textCharacterSize.x;
					_fe3d.billBoardEntity_add(selectionID, _selectionColor, lineTextPosition, vec3(0.0f), _textCharacterSize, false, false);
				}
				else
				{
					vec3 lineTextPosition = _fe3d.billboardEntity_getPosition(textID) - vec3(0.0f, 0.0f, 0.05f);
					vec2 lineTextSize = _fe3d.billboardEntity_getSize(textID);
					_fe3d.billBoardEntity_add(selectionID, _selectionColor, lineTextPosition, vec3(0.0f), lineTextSize, false, false);
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
}