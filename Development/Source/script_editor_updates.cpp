#include "script_editor.hpp"

void ScriptEditor::update()
{
	if (_isLoaded)
	{
		// Update choice lists hoverability


		// Reset last hovered option color
		static string lastHoveredEntityID = "";
		if (lastHoveredEntityID != "")
		{
			if (_fe3d.billboardEntity_isExisting(lastHoveredEntityID))
			{
				_fe3d.billboardEntity_setColor(lastHoveredEntityID, vec3(1.0f));
			}
			lastHoveredEntityID = "";
		}

		// Hovering over options
		string hoveredEntityID = _fe3d.collision_checkCursorInAny();
		if (hoveredEntityID != "")
		{
			_fe3d.billboardEntity_setColor(hoveredEntityID, vec3(0.0f));
			lastHoveredEntityID = hoveredEntityID;
		}

		// Clicking an option
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (hoveredEntityID != "")
			{
				lastHoveredEntityID = "";
				addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
		{
			removeChoiceList();
		}
	}
}