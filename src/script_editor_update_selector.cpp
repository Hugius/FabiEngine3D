#include "script_editor.hpp"

#include <algorithm>

using std::min;

void ScriptEditor::_updateTextSelector(string& newCharacters, unsigned int& cursorLineIndex,
									   unsigned int& cursorCharIndex, int& hoveredLineIndex, bool& textHasChanged)
{
	bool isControlKeyDown = (_fe3d->input_isKeyDown(InputType::KEY_LCTRL) || _fe3d->input_isKeyDown(InputType::KEY_RCTRL));

	if(_firstSelectedLineIndex != -1)
	{
		if(_hasClickedLMB || _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT) ||
		   _activeActionKey != InputType::NONE ||
		   !newCharacters.empty() ||
		   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_V)) ||
		   (isControlKeyDown && _fe3d->input_isKeyPressed(InputType::KEY_X)))
		{
			for(const auto& id : _fe3d->text3d_getIds())
			{
				if(id.substr(0, string("selection_").size()) == "selection_")
				{
					_fe3d->text3d_delete(id);
				}
			}

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
					_script->getScriptFile(_currentScriptFileID)->deleteLine(_firstSelectedLineIndex);
				}
				else
				{
					int lineIndexToDelete = (_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex;
					for(int i = 0; i <= abs(_firstSelectedLineIndex - _lastSelectedLineIndex); i++)
					{
						_script->getScriptFile(_currentScriptFileID)->deleteLine(static_cast<unsigned int>(lineIndexToDelete));
					}
				}

				if(hoveredLineIndex > static_cast<int>(_script->getScriptFile(_currentScriptFileID)->getLineCount() - 1))
				{
					hoveredLineIndex = static_cast<int>(_script->getScriptFile(_currentScriptFileID)->getLineCount());
				}

				if(cursorLineIndex > _script->getScriptFile(_currentScriptFileID)->getLineCount() - 1)
				{
					cursorLineIndex = _script->getScriptFile(_currentScriptFileID)->getLineCount();
				}

				cursorCharIndex = newCharacters.empty() ? 0 : static_cast<unsigned int>(newCharacters.size());

				_script->getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, newCharacters);

				if(_fe3d->input_isKeyPressed(InputType::KEY_ENTER))
				{
					if(_script->getScriptFile(_currentScriptFileID)->getLineCount() < MAX_LINE_COUNT)
					{
						_script->getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, "");
						cursorLineIndex++;
					}
				}

				textHasChanged = true;

				_activeActionKey = InputType::NONE;
			}

			_firstSelectedLineIndex = -1;
			_lastSelectedLineIndex = -1;
		}
	}

	if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && _fe3d->misc_isCursorInsideViewport())
	{
		if(hoveredLineIndex != -1)
		{
			string selectionID = ("selection_" + to_string(hoveredLineIndex));
			string textId = ("text_" + to_string(hoveredLineIndex));

			if(!_fe3d->text3d_isExisting(selectionID) && _fe3d->text3d_isExisting(textId))
			{
				if(_fe3d->text3d_getContent(textId).empty())
				{
					fvec3 lineTextPosition = (_fe3d->text3d_getPosition(textId));
					lineTextPosition.x = (SCRIPT_TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET);
					lineTextPosition.z -= SELECTION_DEPTH;
					_fe3d->quad3d_create(selectionID, false);
					_fe3d->quad3d_setColor(selectionID, SELECTION_COLOR);
					_fe3d->quad3d_setPosition(selectionID, lineTextPosition);
					_fe3d->quad3d_setSize(selectionID, TEXT_CHARACTER_SIZE);
				}
				else
				{
					const fvec3 lineTextPosition = (_fe3d->text3d_getPosition(textId) - fvec3(0.0f, 0.0f, SELECTION_DEPTH));
					const auto lineTextSize = (_fe3d->text3d_getSize(textId));
					_fe3d->quad3d_create(selectionID, false);
					_fe3d->quad3d_setColor(selectionID, SELECTION_COLOR);
					_fe3d->quad3d_setPosition(selectionID, lineTextPosition);
					_fe3d->quad3d_setSize(selectionID, lineTextSize);
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

					if((lastDirection < 0 && currentDirection > 0) ||
					   (currentDirection < 0 && lastDirection > 0))
					{
						_fe3d->text3d_delete("selection_" + to_string(_lastSelectedLineIndex));
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

			cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());
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
					bool firstLineEmpty = _script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).empty();
					for(size_t i = 0; i < _copyClipboard.size(); i++)
					{
						if((cursorLineIndex + i) < _script->getScriptFile(_currentScriptFileID)->getLineCount())
						{
							if(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + static_cast<unsigned int>(i)).empty())
							{
								_script->getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex + static_cast<unsigned int>(i), _copyClipboard[i]);
								pastedCount++;
								continue;
							}
						}

						if(_script->getScriptFile(_currentScriptFileID)->getLineCount() < MAX_LINE_COUNT)
						{
							_script->getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex + static_cast<unsigned int>(i), _copyClipboard[i]);
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
						cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size());

						textHasChanged = true;
					}
				}
			}
		}
	}
}