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
				float minY = (_fe3d.gameEntity_getPosition("background").y - (_fe3d.gameEntity_getSize("background") / 3.0f)).y;
				float halfHeight = (_optionBillboardHeight / 2.0f);
				static bool hasCollided = false;

				// Check if list is long enough to be scrollable
				if ((firstPosition.y - lastPosition.y) > (maxY - minY))
				{
					// Update scrolling movement
					_scrollingAcceleration += -(static_cast<float>(scrollingSpeed) * 0.05f);
					if (hasCollided)
					{
						_scrollingAcceleration = 0.0f;
						hasCollided = false;
					}

					// Movement constraints
					if ((firstPosition.y + halfHeight) < maxY) // Top movement constraint
					{
						_scrollingAcceleration = maxY - (firstPosition.y + halfHeight);
						hasCollided = true;
					}
					else if ((lastPosition.y - halfHeight) > minY) // Bottom movement constraint
					{
						_scrollingAcceleration = -((lastPosition.y - halfHeight) - minY);
						hasCollided = true;
					}

					// Limit acceleration
					_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
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
				auto listType = _choiceListStack.back().first;

				// Calculate character index of underscore before option-index
				int underscoreIndex = 0;
				for (size_t i = 0; i < hoveredEntityID.size(); i++)
				{
					if (hoveredEntityID[i] == '_')
					{
						underscoreIndex = i;
					}
				}

				// Index of option in name vector
				int optionIndex = stoi(hoveredEntityID.substr(underscoreIndex + 1, hoveredEntityID.size() - (underscoreIndex + 1)));

				// Determine type of choice list
				switch (listType)
				{
					case ChoiceListType::EVENT_TYPES:
					{
						string option = _eventTypeNames[optionIndex];

						if (option == "INIT_EVENT")
						{

						}
						else if (option == "INPUT_EVENT")
						{
							addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
						}
						else if (option == "COLLISION_EVENT")
						{

						}
						else if (option == "TIME_EVENT")
						{

						}
						else if (option == "CONDITION_EVENT")
						{

						}
						break;
					}

					case ChoiceListType::INPUT_KEY_NAMES:
					{
						string option = _eventTypeNames[optionIndex];
						break;
					}
				}
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