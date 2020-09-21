#include "script_editor.hpp"

void ScriptEditor::_updateScriptlineCreation()
{
	if (_isCreatingScriptline && _allowedToAddScriptLine)
	{
		// Placeholders
		static bool firstTime = true;
		static bool needsValueFilling = false;
		static bool finishedValueFilling = false;
		static shared_ptr<ScriptEvent> event = nullptr;
		static shared_ptr<ScriptAction> action = nullptr;
		
		// Fill the event & action placeholders
		if (firstTime)
		{
			firstTime = false;

			// For every choicelist that has been added
			for (auto& choiceList : _choiceListStack)
			{
				// Chosen option index
				int optionIndex = choiceList.selectedOptionIndex;

				// Determine choicelist sort
				if (choiceList.sort == ChoiceListSort::EVENT)
				{
					// Determine choicelist type
					switch (choiceList.type)
					{
						// Event types
						case ChoiceListType::EVENT_TYPES:
						{
							if (choiceList.selectedOptionIndex == 0) event = make_shared<ScriptEventInitialization>(_fe3d, ScriptEventType::INITIALIZATION);
							if (choiceList.selectedOptionIndex == 1) event = make_shared<ScriptEventInput>(_fe3d, ScriptEventType::INPUT);
							if (choiceList.selectedOptionIndex == 2) event = make_shared<ScriptEventCollision>(_fe3d, ScriptEventType::COLLISION);
							if (choiceList.selectedOptionIndex == 3) event = make_shared<ScriptEventTime>(_fe3d, ScriptEventType::TIME);
							if (choiceList.selectedOptionIndex == 4) event = make_shared<ScriptEventCondition>(_fe3d, ScriptEventType::CONDITION);
							break;
						}

						// Input event
						case ChoiceListType::EVENT_INPUT_TYPES:
						{
							dynamic_pointer_cast<ScriptEventInput>(event)->setInputType(static_cast<InputEventType>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::EVENT_INPUT_MOUSE_TYPES:
						{
							dynamic_pointer_cast<ScriptEventInput>(event)->setMouseType(static_cast<InputEventMouseType>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::EVENT_INPUT_KEY_NAMES:
						case ChoiceListType::EVENT_INPUT_MOUSE_BUTTONS:
						{
							dynamic_pointer_cast<ScriptEventInput>(event)->setInputElement(choiceList.optionNames[optionIndex]);
							break;
						}
						case ChoiceListType::EVENT_INPUT_METHODS:
						{
							dynamic_pointer_cast<ScriptEventInput>(event)->setInputMethod(static_cast<InputEventMethod>(choiceList.selectedOptionIndex));
							break;
						}
					}
				}
				else if (choiceList.sort == ChoiceListSort::ACTION)
				{
					// Determine choicelist type
					switch (choiceList.type)
					{
						// Action types
						case ChoiceListType::ACTION_TYPES:
						{
							if (choiceList.selectedOptionIndex == 0) action = make_shared<ScriptActionCamera>(_fe3d, ScriptActionType::CAMERA);
							break;
						}

						// Camera action
						case ChoiceListType::ACTION_CAMERA_TYPES:
						{
							dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraType(static_cast<CameraActionType>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::ACTION_CAMERA_DIRECTIONS:
						{
							dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraDirection(static_cast<CameraActionDirection>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::ACTION_CAMERA_FOLLOWS:
						{
							dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraFollow(static_cast<CameraActionFollow>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::ACTION_CAMERA_METHODS:
						{
							dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraMethod(static_cast<CameraActionMethod>(choiceList.selectedOptionIndex));
							break;
						}
						case ChoiceListType::ACTION_CAMERA_TOGGLE:
						{
							dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraToggle(static_cast<CameraActionToggle>(choiceList.selectedOptionIndex));
							break;
						}
					}
				}
			}

			// Add valuefields for action
			switch (action->getType())
			{
				case ScriptActionType::CAMERA:
				{
					// Needed values
					auto type = dynamic_pointer_cast<ScriptActionCamera>(action)->getCameraType();
					auto direction = dynamic_pointer_cast<ScriptActionCamera>(action)->getCameraDirection();
					auto method = dynamic_pointer_cast<ScriptActionCamera>(action)->getCameraMethod();
					auto toggle = dynamic_pointer_cast<ScriptActionCamera>(action)->getCameraToggle();

					// Determine type of value filling
					if (type == CameraActionType::LOOKAT && toggle == CameraActionToggle::ON) // Lookat position
					{
						_gui->getGlobalScreen()->addValueForm("camX", "Lookat X", 0.0f, vec2(-0.4f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("camY", "Lookat Y", 0.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("camZ", "Lookat Z", 0.0f, vec2(0.4f, 0.0f), vec2(0.2f, 0.1f));
						needsValueFilling = true;
					}
					else if (type == CameraActionType::POSITION && direction == CameraActionDirection::XYZ) // Set XYZ position
					{
						_gui->getGlobalScreen()->addValueForm("camX", "Position X", 0.0f, vec2(-0.4f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("camY", "Position Y", 0.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("camZ", "Position Z", 0.0f, vec2(0.4f, 0.0f), vec2(0.2f, 0.1f));
						needsValueFilling = true;
					}
					else if (method == CameraActionMethod::SET)
					{
						string title;
						if (type == CameraActionType::POSITION) // Set X or Y or Z
						{
							if (direction == CameraActionDirection::X) title = "Position X";
							if (direction == CameraActionDirection::Y) title = "Position Y";
							if (direction == CameraActionDirection::Z) title = "Position Z";
							_gui->getGlobalScreen()->addValueForm("camValue", title, 0.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						}
						else // Set pitch or yaw
						{
							if (type == CameraActionType::YAW)	 title = "Yaw";
							if (type == CameraActionType::PITCH) title = "Pitch";
							_gui->getGlobalScreen()->addValueForm("camValue", title, 0.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						}
						needsValueFilling = true;
					}
					else if (((type == CameraActionType::POSITION || type == CameraActionType::YAW || type == CameraActionType::PITCH)
						&& method == CameraActionMethod::UPDATE) || type == CameraActionType::FOLLOW) // Update values
					{
						_gui->getGlobalScreen()->addValueForm("camValue", "Speed value", 0.0f, vec2(0.0f), vec2(0.2f, 0.1f));
						needsValueFilling = true;
					}
					break;
				}
			}
		}

		// Update value filling
		if (needsValueFilling && !finishedValueFilling)
		{
			// Camera action
			if (_gui->getGlobalScreen()->isValueFormExisting("camX"))
			{
				vec3 camPos;
				if (_gui->getGlobalScreen()->checkValueForm("camX", camPos.x) && 
					_gui->getGlobalScreen()->checkValueForm("camY", camPos.y) && 
					_gui->getGlobalScreen()->checkValueForm("camZ", camPos.z))
				{
					dynamic_pointer_cast<ScriptActionCamera>(action)->setVectorArgument(camPos);
					finishedValueFilling = true;
				}
			}
			else if (_gui->getGlobalScreen()->isValueFormExisting("camValue"))
			{
				float camValue;
				if (_gui->getGlobalScreen()->checkValueForm("camValue", camValue))
				{
					dynamic_pointer_cast<ScriptActionCamera>(action)->setFloatArgument(camValue);
					finishedValueFilling = true;
				}
			}
			else
			{
				// Reset the creation process
				_isCreatingScriptline = false;
				firstTime = true;
				needsValueFilling = false;
				finishedValueFilling = false;
				event = nullptr;
				action = nullptr;
				return;
			}
		}

		// Create new scriptLine
		if (finishedValueFilling || !needsValueFilling)
		{
			// Clear everything after creating
			_script->addLine(to_string(_script->getLineCount() + 1), event, action);
			_clearChoiceLists();
			_allowedToAddScriptLine = false;

			// Reset the creation process
			_isCreatingScriptline = false;
			firstTime = true;
			needsValueFilling = false;
			finishedValueFilling = false;
			event = nullptr;
			action = nullptr;
		}
	}
}