#include "script_editor.hpp"
#include "script_event_init.hpp"
#include "script_event_input.hpp"
#include "script_event_time.hpp"
#include "script_event_collision.hpp"
#include "script_event_condition.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	_updateGUI();
	_updateChoiceLists();
	_updateNavigation();
	_updateMiscellaneous();
}

void ScriptEditor::_updateGUI()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("scriptEditorMenuMain");
		
		// Check if LMB is pressed
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("addLine")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("newScriptLineName", "New script name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("deleteLine")->isHovered())
			{
				_script.removeLine(_currentScriptLineID);
				_currentScriptLineID = "";
			}
			else if (screen->getButton("createLine")->isHovered())
			{
				// Clear all previous choice lists
				while (!_choiceListStack.empty())
				{
					_removeChoiceList();
				}

				// Add default choicelist
				_addChoiceList(ChoiceListType::EVENT_TYPES);
				_isCreatingScript = true;
			}
			else if (screen->getButton("viewLine")->isHovered())
			{
				_gui->getGlobalScreen()->addChoiceForm("scriptLinesList", "View script", vec2(0.0f, 0.0f), _script.getAllScriptIDs());
			}
			else if (screen->getButton("back")->isHovered())
			{
				save();
				unload();
				_leftWindow->setActiveScreen("main");
			}
		}
	}
}

void ScriptEditor::_updateChoiceLists()
{
	if (_isLoaded && _isCreatingScript)
	{
		// Update hoverability & color & scrolling
		for (auto& list : _choiceListStack)
		{
			// General values
			int listIndex = static_cast<int>(list.type);
			bool isResponsive = (listIndex == static_cast<int>(_choiceListStack.back().type));
			int scrollingSpeed = _fe3d.input_getMouseWheelY();

			// Check if allowed to scroll
			if (isResponsive)
			{
				// Scrolling values
				string baseID = std::to_string(listIndex) + "_option_";
				vec3 firstPosition = _fe3d.billboardEntity_getPosition(baseID + "0");
				vec3 lastPosition = _fe3d.billboardEntity_getPosition(baseID + std::to_string(list.total - 1));
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
			for (int i = 0; i < list.total; i++)
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
	}
}

void ScriptEditor::_updateNavigation()
{
	if (_isLoaded)
	{
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
				auto listType = _choiceListStack.back().type;

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
							_addChoiceList(ChoiceListType::INPUT_TYPES);
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

					case ChoiceListType::INPUT_TYPES:
					{
						string option = _eventTypeNames[optionIndex];
						if (option == "KEYBOARD")
						{
							_addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
						}
						else if (option == "MOUSE")
						{
							_addChoiceList(ChoiceListType::INPUT_MOUSE_NAMES);
						}

						break;
					}

					case ChoiceListType::INPUT_KEY_NAMES:
					{
						string option = _eventTypeNames[optionIndex];
						_currentEventToAdd = make_shared<ScriptEventInput>(_fe3d, InputType::KEYBOARD, InputTypeMethod::);
						break;
					}

					case ChoiceListType::INPUT_MOUSE_NAMES:
					{
						string option = _eventTypeNames[optionIndex];
						_currentEventToAdd = make_shared<ScriptEventInput>(_fe3d, InputType::KEYBOARD, InputTypeMethod::);
						break;
					}

					case ChoiceListType::INPUT_METHODS:
					{
						string option = _eventTypeNames[optionIndex];
						if (option == "DOWN")
						{
							_addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
						}
						else if (option == "PRESSED")
						{
							_addChoiceList(ChoiceListType::INPUT_MOUSE_NAMES);
						}
						else if (option == "TOGGLED")
						{

						}

						break;
					}
				}
			}
		}
		else if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
		{
			// Cannot remove default choice list
			if (_choiceListStack.size() > 1)
			{
				_removeChoiceList();
			}
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Scrolling movement smoothing
		_scrollingAcceleration *= 0.95f;

		// Add & delete buttons hoverability
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("addLine")->setHoverable(_currentEventToAdd != nullptr);
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("deleteLine")->setHoverable(_currentScriptLineID != "");

		// Check if new script line name filled in
		string newScriptLineName = "";
		if (_gui->getGlobalScreen()->checkValueForm("newScriptLineName", newScriptLineName))
		{
			// Check if name not existing yet
			if (!_script.isExisting(newScriptLineName))
			{
				_script.addLine(newScriptLineName, nullptr, nullptr);
			}
		}

		// Check if existing script line chosen for viewing
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptLinesList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				_generateScriptLineInterface(_script.getScriptLine(selectedButtonID));
				_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
				_isCreatingScript = false;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptLinesList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
		}
	}
}