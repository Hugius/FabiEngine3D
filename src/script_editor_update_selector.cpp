#include "script_editor.hpp"

void ScriptEditor::_updateTextSelector()
{
	if(_isWritingScript && !_gui->getOverlay()->isFocused())
	{
		if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideDisplay())
		{
			const auto hoveredTextId = _fe3d->raycast_getClosestAabbId();

			if(!hoveredTextId.empty() && hoveredTextId.find('_') != string::npos)
			{
				const auto aabbPosition = _fe3d->aabb_getBasePosition(hoveredTextId);

				if(_fe3d->quad3d_isVisible("selection"))
				{
					if(aabbPosition.y == _selectionPosition.y)
					{
						_selectionSize.x = (fabsf(_selectionPosition.x - aabbPosition.x) + TEXT_CHARACTER_SIZE.x);

						if(aabbPosition.x < _selectionPosition.x)
						{
							_fe3d->quad3d_setPosition("selection", fvec2((_selectionPosition.x - (_selectionSize.x / 2.0f) + (TEXT_CHARACTER_SIZE.x / 2.0f)), _selectionPosition.y));
						}
						else
						{
							_fe3d->quad3d_setPosition("selection", fvec2((_selectionPosition.x + (_selectionSize.x / 2.0f) - (TEXT_CHARACTER_SIZE.x / 2.0f)), _selectionPosition.y));
						}

						_fe3d->quad3d_setSize("selection", _selectionSize);
					}
				}
				else
				{
					_selectionPosition = aabbPosition;
					_selectionSize.y = TEXT_CHARACTER_SIZE.y;

					_fe3d->quad3d_setVisible("selection", true);
					_fe3d->text3d_setVisible("cursor", false);
				}
			}
		}
		else
		{
			_fe3d->quad3d_setPosition("selection", fvec3(0.0f));
			_fe3d->quad3d_setSize("selection", fvec2(0.0f));

			_fe3d->quad3d_setVisible("selection", false);
			_fe3d->text3d_setVisible("cursor", true);
		}
	}
}