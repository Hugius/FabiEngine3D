#include "script_editor.hpp"

void ScriptEditor::_updateTextSelector()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !_fe3d->misc_isCursorInsideDisplay())
	{
		_clearCharacterSelection();

		return;
	}

	const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();
	const auto scriptFile = _script->getScriptFile(_currentScriptFileId);
	const auto isControlDown = (_fe3d->input_isKeyDown(InputType::KEY_LCTRL) || _fe3d->input_isKeyDown(InputType::KEY_RCTRL));

	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !hoveredAabbId.empty())
	{
		auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;

		if(hoveredAabbId.find('_') == string::npos)
		{
			hoveredLineIndex = stoi(hoveredAabbId);
		}
		else
		{
			hoveredLineIndex = stoi(hoveredAabbId.substr(0, hoveredAabbId.find('_')));
			hoveredCharacterIndex = stoi(hoveredAabbId.substr(hoveredAabbId.find('_') + 1));
		}

		cursorLineIndex = hoveredLineIndex;

		if(hoveredCharacterIndex == -1)
		{
			cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLine(cursorLineIndex).size());
		}
		else
		{
			cursorCharacterIndex = hoveredCharacterIndex;
		}

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharacterIndex(cursorCharacterIndex);
	}

	if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE) && hoveredAabbId.find('_') != string::npos && _canSelectCharacter)
	{
		_fe3d->quad3d_setVisible("selection", true);
		_fe3d->text3d_setVisible("cursor", false);

		if(_characterSelectionFirstAabbId.empty())
		{
			_characterSelectionFirstAabbId = hoveredAabbId;
		}

		const auto firstAabbPosition = _fe3d->aabb_getBasePosition(_characterSelectionFirstAabbId);
		const auto hoveredAabbPosition = _fe3d->aabb_getBasePosition(hoveredAabbId);
		const auto selectionWidth = (fabsf(firstAabbPosition.x - hoveredAabbPosition.x) + TEXT_CHARACTER_SIZE.x);

		if(hoveredAabbPosition.x < firstAabbPosition.x)
		{
			_fe3d->quad3d_setPosition("selection", fvec2((firstAabbPosition.x - (selectionWidth / 2.0f) + (TEXT_CHARACTER_SIZE.x / 2.0f)), firstAabbPosition.y));
		}
		else
		{
			_fe3d->quad3d_setPosition("selection", fvec2((firstAabbPosition.x + (selectionWidth / 2.0f) - (TEXT_CHARACTER_SIZE.x / 2.0f)), firstAabbPosition.y));
		}

		_fe3d->quad3d_setSize("selection", fvec2(selectionWidth, TEXT_CHARACTER_SIZE.y));

		_characterSelectionSecondAabbId = hoveredAabbId;
	}
	else
	{
		_clearCharacterSelection();

		_fe3d->text3d_setVisible("cursor", true);
	}

	if(_fe3d->quad3d_isVisible("selection"))
	{
		const auto lineIndex = static_cast<unsigned int>(stoi(_characterSelectionFirstAabbId.substr(0, _characterSelectionFirstAabbId.find('_'))));
		const auto firstCharacterIndex = static_cast<unsigned int>(stoi(_characterSelectionFirstAabbId.substr(_characterSelectionFirstAabbId.find('_') + 1)));
		const auto secondCharacterIndex = static_cast<unsigned int>(stoi(_characterSelectionSecondAabbId.substr(_characterSelectionSecondAabbId.find('_') + 1)));

		if(isControlDown && _fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			auto lineText = scriptFile->getLine(lineIndex);

			if(firstCharacterIndex < secondCharacterIndex)
			{
				lineText.erase(static_cast<size_t>(firstCharacterIndex), static_cast<size_t>(secondCharacterIndex - firstCharacterIndex + 1));
			}
			else
			{
				lineText.erase(static_cast<size_t>(secondCharacterIndex), static_cast<size_t>(firstCharacterIndex - secondCharacterIndex + 1));
			}

			scriptFile->editLine(lineIndex, lineText);

			if(scriptFile->getCursorCharacterIndex() > lineText.size())
			{
				scriptFile->setCursorCharacterIndex(static_cast<unsigned int>(lineText.size()));
			}

			_hasTextChanged = true;

			_clearCharacterSelection();
		}

		if(isControlDown && _fe3d->input_isKeyPressed(InputType::KEY_C))
		{
			const auto lineText = scriptFile->getLine(lineIndex);

			if(firstCharacterIndex < secondCharacterIndex)
			{
				_characterSelectionClipboard = lineText.substr(static_cast<size_t>(firstCharacterIndex), static_cast<size_t>(secondCharacterIndex - firstCharacterIndex + 1));
			}
			else
			{
				_characterSelectionClipboard = lineText.substr(static_cast<size_t>(secondCharacterIndex), static_cast<size_t>(firstCharacterIndex - secondCharacterIndex + 1));
			}
		}
	}
	else
	{
		if(isControlDown && _fe3d->input_isKeyPressed(InputType::KEY_V))
		{
			if(!_characterSelectionClipboard.empty())
			{
				const auto lineText = scriptFile->getLine(scriptFile->getCursorLineIndex());
				const auto firstPart = lineText.substr(0, scriptFile->getCursorCharacterIndex());
				const auto secondPart = lineText.substr(scriptFile->getCursorCharacterIndex());

				scriptFile->editLine(scriptFile->getCursorLineIndex(), (firstPart + _characterSelectionClipboard + secondPart));

				scriptFile->setCursorCharacterIndex(scriptFile->getCursorCharacterIndex() + static_cast<unsigned int>(_characterSelectionClipboard.size()));

				_hasTextChanged = true;
			}
		}
	}
}