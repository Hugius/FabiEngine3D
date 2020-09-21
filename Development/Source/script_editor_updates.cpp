#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	_updateGUI();
	_updateChoiceLists();
	_updateNavigation();
	_updateScriptlineCreation();
	_updateMiscellaneous();
}

void ScriptEditor::_updateGUI()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("scriptEditorMenuMain");
		
		// Check if LMB is pressed
		if (!_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("addLine")->isHovered())
				{
					_isCreatingScriptline = true;
				}
				else if (screen->getButton("deleteLine")->isHovered())
				{
					// Remove line from script
					_clearChoiceLists();
					_script->removeLine(_currentScriptLineID);
					_calibrateScriptLines();
					_currentScriptLineID = "";
				}
				else if (screen->getButton("createLine")->isHovered())
				{
					// Add default choicelist
					_clearChoiceLists();
					_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_TYPES);
					_isCreatingScript = true;
					_allowedToAddScriptLine = false;
				}
				else if (screen->getButton("viewLine")->isHovered())
				{
					_gui->getGlobalScreen()->addChoiceForm("scriptLinesList", "View script", vec2(0.0f, 0.0f), _script->getAllScriptLineIDs());
				}
				else if (screen->getButton("back")->isHovered())
				{
					_gui->getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}
		}

		// Check if user wants to save changes
		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
		{
			save();
			unload();
			_leftWindow->setActiveScreen("main");
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
		{
			unload();
			_leftWindow->setActiveScreen("main");
		}
	}
}

void ScriptEditor::_updateChoiceLists()
{
	if (_isLoaded && _isCreatingScript && !_allowedToAddScriptLine && !_gui->getGlobalScreen()->isFocused())
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
				string baseID = to_string(listIndex) + "_option_";
				vec3 firstPosition = _fe3d.billboardEntity_getPosition(baseID + "0"); // Position of top option
				vec3 lastPosition = _fe3d.billboardEntity_getPosition(baseID + to_string(list.total - 1)); // Position of bottom option

				// Calculate distance between 2 options
				float optionOffsetY;
				if (_fe3d.billboardEntity_isExisting(baseID + "1"))
				{
					optionOffsetY = _fe3d.billboardEntity_getPosition(baseID + "0").y - _fe3d.billboardEntity_getPosition(baseID + "1").y;
				}
				else
				{
					optionOffsetY = 0.0f;
				}

				// Calculate scrolling list bounds
				float maxY = _fe3d.gameEntity_getPosition(to_string(listIndex) + "_header").y - optionOffsetY;
				float minY = _fe3d.gameEntity_getPosition("background").y - (_fe3d.gameEntity_getSize("background").y / 15.0f);
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
				string ID = to_string(listIndex) + "_option_" + to_string(i);

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
	if (_isLoaded && _isCreatingScript && !_gui->getGlobalScreen()->isFocused())
	{
		// Hovering over options
		string hoveredEntityID = _fe3d.collision_checkCursorInAny();
		if (hoveredEntityID != "" && !_allowedToAddScriptLine)
		{
			_fe3d.billboardEntity_setColor(hoveredEntityID, vec3(0.0f, 1.0f, 0.0f));
			_fe3d.lightEntity_setPosition("@@selectionLight", _fe3d.billboardEntity_getPosition(hoveredEntityID) + vec3(0.0f, 0.0f, 1.0f));
			_fe3d.lightEntity_show("@@selectionLight");
		}
		else
		{
			_fe3d.lightEntity_hide("@@selectionLight");
		}

		// Clicking a hovered option
		if (!_allowedToAddScriptLine)
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (hoveredEntityID != "")
				{
					auto listType = _choiceListStack.back().type;

					// Point light
					_fe3d.lightEntity_add(to_string(++_pointLightCounter), _fe3d.billboardEntity_getPosition(hoveredEntityID) + vec3(0.0f, 0.0f, 1.0f),
						vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f);

					// Calculate character index of underscore before option-index
					int underscoreIndex = 0;
					for (size_t i = 0; i < hoveredEntityID.size(); i++)
					{
						if (hoveredEntityID[i] == '_')
						{
							underscoreIndex = i;
						}
					}

					// Needed values
					int optionIndex = stoi(hoveredEntityID.substr(underscoreIndex + 1, hoveredEntityID.size() - (underscoreIndex + 1)));
					_choiceListStack.back().selectedOptionIndex = optionIndex;
					string optionName = _choiceListStack.back().optionNames[optionIndex];

					// Determine type of choicelist
					switch (listType)
					{
						// Event types
						case ChoiceListType::EVENT_TYPES:
						{
							// Determine event type
							if (optionName == "INIT_EVENT")
							{
								// Event chosen, go to action choosing
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPES);
							}
							else if (optionName == "INPUT_EVENT")
							{
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_TYPES);
							}
							else if (optionName == "COLLISION_EVENT")
							{

							}
							else if (optionName == "TIME_EVENT")
							{

							}
							else if (optionName == "CONDITION_EVENT")
							{

							}
							break;
						}

						// Input event
						case ChoiceListType::EVENT_INPUT_TYPES:
						{
							// Determine input type
							if (optionName == "KEYBOARD")
							{
								// Display all keyboard keys
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_KEY_NAMES);
							}
							else if (optionName == "MOUSE")
							{
								// Display all mouse types
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_TYPES);
							}
							break;
						}
						case ChoiceListType::EVENT_INPUT_MOUSE_TYPES:
						{
							// Determine input type
							if (optionName == "BUTTON")
							{
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_BUTTONS);
							}
							else if (optionName == "SCROLL_UP" || optionName == "SCROLL_DOWN")
							{
								// Event chosen, go to action choosing
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPES);
							}
							break;
						}
						case ChoiceListType::EVENT_INPUT_KEY_NAMES:
						case ChoiceListType::EVENT_INPUT_MOUSE_BUTTONS:
						{
							// Display input methods
							_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_METHODS);
							break;
						}
						case ChoiceListType::EVENT_INPUT_METHODS:
						{
							// Event chosen, go to action choosing
							_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPES);
							break;
						}

						// Action types
						case ChoiceListType::ACTION_TYPES:
						{
							// Determine action type
							if (optionName == "CAMERA_ACTION")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TYPES);
							}
							break;
						}

						// Camera action
						case ChoiceListType::ACTION_CAMERA_TYPES:
						{
							// Determine camera type
							if (optionName == "POSITION")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_DIRECTIONS);
							}
							else if (optionName == "FOLLOW")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_FOLLOWS);
							}
							else if (optionName == "YAW" || optionName == "PITCH")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHODS);
							}
							else if (optionName == "LOOK_AT" || optionName == "FIRST_PERSON")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TOGGLE);
							}
							break;
						}
						case ChoiceListType::ACTION_CAMERA_DIRECTIONS:
						{
							if (optionName == "XYZ")
							{
								_allowedToAddScriptLine = true;
							}
							else
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHODS);
							}
							break;
						}
						case ChoiceListType::ACTION_CAMERA_FOLLOWS:
						case ChoiceListType::ACTION_CAMERA_METHODS:
						case ChoiceListType::ACTION_CAMERA_TOGGLE:
						{
							_allowedToAddScriptLine = true;
							break;
						}
					}
				}
			}
		}

		// Update value filling

		// Remove last chosen option
		if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
		{
			// Cannot remove default choice list
			if (_choiceListStack.size() > 1)
			{
				_removeChoiceList();
				_fe3d.lightEntity_delete(to_string(_pointLightCounter));
				_pointLightCounter--;

				// Script cannot be added if last option is removed
				if (_allowedToAddScriptLine)
				{
					_allowedToAddScriptLine = false;
				}
			}
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		//  Smooth scrolling movement
		_scrollingAcceleration *= 0.95f;

		if (!_gui->getGlobalScreen()->isFocused())
		{
			// Camear movement input
			if (_fe3d.input_getKeyDown(Input::KEY_A))
			{
				_cameraAcceleration -= 0.005f;
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_D))
			{
				_cameraAcceleration += 0.005f;
			}
		}

		// Smooth camera movement
		_cameraAcceleration = std::clamp(_cameraAcceleration, -0.3f, 0.3f);
		_cameraAcceleration *= 0.965f;

		// Cannot go out of screen
		if (_fe3d.camera_getPosition().x < _cameraStartingPosition.x)
		{
			_cameraAcceleration = 0.0f;
			_fe3d.camera_setPosition(_cameraStartingPosition);
		}

		// Move camera
		_fe3d.camera_translate(vec3(_cameraAcceleration, 0.0f, 0.0f));

		// Add & delete buttons hoverability
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("addLine")->setHoverable(_allowedToAddScriptLine);
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("deleteLine")->setHoverable(_currentScriptLineID != "");

		// Check if existing script line chosen for viewing
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptLinesList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				_generateScriptLineOverview(_script->getScriptLine(selectedButtonID));
				_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
				_currentScriptLineID = selectedButtonID;
				_isCreatingScript = false;
				_allowedToAddScriptLine = false;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptLinesList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
		}
	}
}