#include "script_editor.hpp"

void ScriptEditor::_updateTextSelector()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused())
	{
		return;
	}

	bool isSelecting = false;

	if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideDisplay())
	{
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!hoveredAabbId.empty() && hoveredAabbId.find('_') != string::npos)
		{
			const auto hoveredAabbPosition = _fe3d->aabb_getBasePosition(hoveredAabbId);

			if(_fe3d->quad3d_isVisible("selection"))
			{
				const auto rootAabbPosition = _fe3d->aabb_getBasePosition(_characterSelectionRootAabbId);

				if(hoveredAabbPosition.y == rootAabbPosition.y)
				{
					const auto selectionWidth = (fabsf(rootAabbPosition.x - hoveredAabbPosition.x) + TEXT_CHARACTER_SIZE.x);

					if(hoveredAabbPosition.x < rootAabbPosition.x)
					{
						_fe3d->quad3d_setPosition("selection", fvec2((rootAabbPosition.x - (selectionWidth / 2.0f) + (TEXT_CHARACTER_SIZE.x / 2.0f)), rootAabbPosition.y));
					}
					else
					{
						_fe3d->quad3d_setPosition("selection", fvec2((rootAabbPosition.x + (selectionWidth / 2.0f) - (TEXT_CHARACTER_SIZE.x / 2.0f)), rootAabbPosition.y));
					}

					_fe3d->quad3d_setSize("selection", fvec2(selectionWidth, TEXT_CHARACTER_SIZE.y));

					isSelecting = true;
				}
			}
			else
			{
				_fe3d->quad3d_setVisible("selection", true);
				_fe3d->text3d_setVisible("cursor", false);

				_characterSelectionRootAabbId = hoveredAabbId;

				isSelecting = true;
			}

			const auto rootLineIndex = stoi(_characterSelectionRootAabbId.substr(0, _characterSelectionRootAabbId.find('_')));
			const auto rootCharacterIndex = stoi(_characterSelectionRootAabbId.substr(_characterSelectionRootAabbId.find('_') + 1));
			const auto hoveredLineIndex = stoi(hoveredAabbId.substr(0, hoveredAabbId.find('_')));
			const auto hoveredCharacterIndex = stoi(hoveredAabbId.substr(hoveredAabbId.find('_') + 1));

			_script->getScriptFile(_currentScriptFileId)->getLineText(rootLineIndex)[rootCharacterIndex];
		}
	}

	if(!isSelecting)
	{
		_fe3d->quad3d_setVisible("selection", false);
		_fe3d->text3d_setVisible("cursor", true);

		_fe3d->quad3d_setPosition("selection", fvec3(0.0f));
		_fe3d->quad3d_setSize("selection", fvec2(0.0f));
	}
}