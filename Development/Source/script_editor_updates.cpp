#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	if (_isLoaded)
	{
		// Update hoverability & color & scrolling
		for (auto& list : _choiceListStack)
		{
			// General values
			int listIndex = static_cast<int>(list.first);
			bool isResponsive = (listIndex == static_cast<int>(_choiceListStack.back().first));
			int scrollingSpeed = _fe3d.input_getMouseWheelY();

			// Check if allowed to scroll
			if (isResponsive)
			{
				// Scrolling values
				string baseID = std::to_string(listIndex) + "_option_";
				vec3 firstPosition = _fe3d.billboardEntity_getPosition(baseID + "0");
				vec3 lastPosition = _fe3d.billboardEntity_getPosition(baseID + std::to_string(list.second-1));
				float optionOffsetY = _fe3d.billboardEntity_getPosition(baseID + "0").y - _fe3d.billboardEntity_getPosition(baseID + "1").y;
				float maxY = _fe3d.gameEntity_getPosition(std::to_string(listIndex) + "_header").y - optionOffsetY;
				float minY = (_fe3d.gameEntity_getPosition("background").y - (_fe3d.gameEntity_getSize("background") / 2.0f)).y;

				// Check if list is long enough to be scrollable
				if ((firstPosition.y - lastPosition.y) > (maxY - minY))
				{
					// Update scrolling movement
					_scrollingAcceleration += -(static_cast<float>(scrollingSpeed) * 0.1f);

					// Movement constraints
					if (firstPosition.y < maxY || lastPosition.y > minY)
					{
						_scrollingAcceleration = 0.0f;
					}

					_scrollingAcceleration = std::clamp(_scrollingAcceleration, -0.25f, 0.25f);
				}
			}
			
			// Update every AABB
			for (int i = 0; i < list.second; i++)
			{
				// Determine entity ID
				string ID = std::to_string(listIndex) + "_option_" + std::to_string(i);

				// AABB responsiveness
				_fe3d.aabbEntity_setResponsiveness(ID, isResponsive);

				// Update current choice list
				if (isResponsive)
				{
					// Reset hover color
					_fe3d.billboardEntity_setColor(ID, vec3(1.0f));

					// Applying scrolling
					_fe3d.billboardEntity_move(ID, vec3(0.0f, _scrollingAcceleration, 0.0f));
				}
			}
		}

		// Hovering over options
		string hoveredEntityID = _fe3d.collision_checkCursorInAny();
		if (hoveredEntityID != "")
		{
			_fe3d.billboardEntity_setColor(hoveredEntityID, vec3(0.0f));
		}

		// Clicking an option
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (hoveredEntityID != "")
			{
				addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
		{
			removeChoiceList();
		}

		// Miscellaneous
		_scrollingAcceleration *= 0.95f;
	}
}