#include "script_editor.hpp"

void ScriptEditor::_updateTextSelector()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !_fe3d->misc_isCursorInsideDisplay())
	{
		_fe3d->quad3d_setVisible("selection", false);
		return;
	}

	const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

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
			cursorCharacterIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
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
		else
		{
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
	}
	else
	{
		if(_canSelectCharacter)
		{
			if(_fe3d->quad3d_isVisible("selection"))
			{
				_canSelectCharacter = false;
			}
		}
		else
		{
			if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_canSelectCharacter = true;
			}
		}

		_fe3d->quad3d_setVisible("selection", false);
		_fe3d->text3d_setVisible("cursor", true);

		_fe3d->quad3d_setPosition("selection", fvec3(0.0f));
		_fe3d->quad3d_setSize("selection", fvec2(0.0f));

		_characterSelectionFirstAabbId = "";
		_characterSelectionSecondAabbId = "";
	}

	if(!_characterSelectionFirstAabbId.empty() && !_characterSelectionSecondAabbId.empty())
	{
		const auto lineIndex = stoi(_characterSelectionFirstAabbId.substr(0, _characterSelectionFirstAabbId.find('_')));
		const auto rootCharacterIndex = stoi(_characterSelectionFirstAabbId.substr(_characterSelectionFirstAabbId.find('_') + 1));
		const auto hoveredCharacterIndex = stoi(_characterSelectionSecondAabbId.substr(_characterSelectionSecondAabbId.find('_') + 1));

		_script->getScriptFile(_currentScriptFileId)->getLineText(lineIndex)[rootCharacterIndex];
	}
}