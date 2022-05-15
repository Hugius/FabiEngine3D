#include "script_editor.hpp"
#include "tools.hpp"

void ScriptEditor::_updateTextSelector()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !Tools::isCursorInsideDisplay())
	{
		_clearSelection();

		return;
	}

	const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();
	const auto scriptFile = _script->getScriptFile(_currentScriptFileId);

	if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && !hoveredAabbId.empty())
	{
		auto cursorLineIndex = scriptFile->getCursorLineIndex();
		auto cursorCharacterIndex = scriptFile->getCursorCharacterIndex();

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
			cursorCharacterIndex = static_cast<int>(scriptFile->getLine(cursorLineIndex).size());
		}
		else
		{
			cursorCharacterIndex = hoveredCharacterIndex;
		}

		scriptFile->setCursorLineIndex(cursorLineIndex);
		scriptFile->setCursorCharacterIndex(cursorCharacterIndex);
	}

	const auto isControlDown = _fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_CONTROL);
	const auto cursorLineIndex = scriptFile->getCursorLineIndex();
	const auto cursorCharacterIndex = scriptFile->getCursorCharacterIndex();

	_fe3d->text3d_setVisible(CARET_ID, true);

	if(isControlDown && _fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_A) && !scriptFile->getLine(cursorLineIndex).empty())
	{
		if(!(_fe3d->quad3d_isVisible(SELECTION_ID) && (_selectionType == ScriptSelectionType::PART)))
		{
			_fe3d->quad3d_setVisible(SELECTION_ID, true);
			_fe3d->text3d_setVisible(CARET_ID, false);

			_selectionType = ScriptSelectionType::FULL;
			_firstSelectionAabbId = (to_string(cursorLineIndex) + "_0");
			_secondSelectionAabbId = (to_string(cursorLineIndex) + "_" + to_string(scriptFile->getLine(cursorLineIndex).size() - 1));

			const auto firstAabbPosition = _fe3d->aabb_getBasePosition(_firstSelectionAabbId);
			const auto secondAabbPosition = _fe3d->aabb_getBasePosition(_secondSelectionAabbId);
			const auto selectionWidth = (static_cast<float>(scriptFile->getLine(cursorLineIndex).size()) * CHAR_SIZE.x);
			const auto selectionHeight = CHAR_SIZE.y;
			const auto selectionX = ((firstAabbPosition.x + secondAabbPosition.x) * 0.5f);
			const auto selectionY = firstAabbPosition.y;

			_fe3d->quad3d_setPosition(SELECTION_ID, fvec3(selectionX, selectionY, 0.0f));
			_fe3d->quad3d_setSize(SELECTION_ID, fvec2(selectionWidth, selectionHeight));
		}
	}
	else
	{
		if(_fe3d->quad3d_isVisible(SELECTION_ID) && (_selectionType == ScriptSelectionType::FULL))
		{
			_clearSelection();
		}
	}

	if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT) && hoveredAabbId.find('_') != string::npos)
	{
		if(!(_fe3d->quad3d_isVisible(SELECTION_ID) && (_selectionType == ScriptSelectionType::FULL)))
		{
			_fe3d->quad3d_setVisible(SELECTION_ID, true);
			_fe3d->text3d_setVisible(CARET_ID, false);

			_selectionType = ScriptSelectionType::PART;
			_firstSelectionAabbId = (_firstSelectionAabbId.empty() ? hoveredAabbId : _firstSelectionAabbId);
			_secondSelectionAabbId = hoveredAabbId;

			const auto firstAabbPosition = _fe3d->aabb_getBasePosition(_firstSelectionAabbId);
			const auto secondAabbPosition = _fe3d->aabb_getBasePosition(_secondSelectionAabbId);
			const auto selectionWidth = (fabsf(firstAabbPosition.x - secondAabbPosition.x) + CHAR_SIZE.x);
			const auto selectionHeight = CHAR_SIZE.y;

			float selectionX;
			float selectionY;

			if(secondAabbPosition.x < firstAabbPosition.x)
			{
				selectionX = (firstAabbPosition.x - (selectionWidth * 0.5f) + (CHAR_SIZE.x * 0.5f));
				selectionY = firstAabbPosition.y;
			}
			else
			{
				selectionX = (firstAabbPosition.x + (selectionWidth * 0.5f) - (CHAR_SIZE.x * 0.5f));
				selectionY = firstAabbPosition.y;
			}

			_fe3d->quad3d_setPosition(SELECTION_ID, fvec3(selectionX, selectionY, 0.0f));
			_fe3d->quad3d_setSize(SELECTION_ID, fvec2(selectionWidth, selectionHeight));
		}
	}
	else
	{
		if(_fe3d->quad3d_isVisible(SELECTION_ID) && (_selectionType == ScriptSelectionType::PART))
		{
			_clearSelection();
		}
	}

	if(_fe3d->quad3d_isVisible(SELECTION_ID))
	{
		const auto selectionLineIndex = stoi(_firstSelectionAabbId.substr(0, _firstSelectionAabbId.find('_')));
		const auto firstSelectionCharacterIndex = stoi(_firstSelectionAabbId.substr(_firstSelectionAabbId.find('_') + 1));
		const auto secondSelectionCharacterIndex = stoi(_secondSelectionAabbId.substr(_secondSelectionAabbId.find('_') + 1));

		if(isControlDown && (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_C) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_X)))
		{
			const auto lineText = scriptFile->getLine(selectionLineIndex);

			if(firstSelectionCharacterIndex < secondSelectionCharacterIndex)
			{
				_selectionClipboard = lineText.substr(static_cast<size_t>(firstSelectionCharacterIndex), static_cast<size_t>(secondSelectionCharacterIndex - firstSelectionCharacterIndex + 1));
			}
			else
			{
				_selectionClipboard = lineText.substr(static_cast<size_t>(secondSelectionCharacterIndex), static_cast<size_t>(firstSelectionCharacterIndex - secondSelectionCharacterIndex + 1));
			}
		}

		if(isControlDown && (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_Z) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_X)))
		{
			auto lineText = scriptFile->getLine(selectionLineIndex);

			if(firstSelectionCharacterIndex < secondSelectionCharacterIndex)
			{
				lineText.erase(static_cast<size_t>(firstSelectionCharacterIndex), static_cast<size_t>(secondSelectionCharacterIndex - firstSelectionCharacterIndex + 1));
			}
			else
			{
				lineText.erase(static_cast<size_t>(secondSelectionCharacterIndex), static_cast<size_t>(firstSelectionCharacterIndex - secondSelectionCharacterIndex + 1));
			}

			scriptFile->editLine(selectionLineIndex, lineText);

			if((selectionLineIndex == cursorLineIndex) && (cursorCharacterIndex > lineText.size()))
			{
				scriptFile->setCursorCharacterIndex(static_cast<int>(lineText.size()));
			}

			_hasTextChanged = true;

			_clearSelection();
		}
	}
	else
	{
		if(isControlDown && _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_V))
		{
			if(!_selectionClipboard.empty())
			{
				const auto lineText = scriptFile->getLine(cursorLineIndex);
				const auto firstPart = lineText.substr(0, cursorCharacterIndex);
				const auto secondPart = lineText.substr(cursorCharacterIndex);

				scriptFile->editLine(cursorLineIndex, (firstPart + _selectionClipboard + secondPart));

				scriptFile->setCursorCharacterIndex(cursorCharacterIndex + static_cast<int>(_selectionClipboard.size()));

				_hasTextChanged = true;
			}
		}
	}
}