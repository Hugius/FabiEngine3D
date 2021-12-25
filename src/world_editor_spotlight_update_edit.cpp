#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightEditing()
{
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateBillboardID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Reset selected torch from last frame
		if(!_dontResetSelectedTorch)
		{
			_selectedTorchID = "";
		}
		else
		{
			_dontResetSelectedTorch = false;
		}

		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a torch model
		for(const auto& ID : _fe3d.model_getIDs())
		{
			// Must be spotlight template entity
			if(ID.substr(0, string("@@torch").size()) == "@@torch")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hoveredAabbID == ID && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getOverlay()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered torch
					_selectSpotlight(ID.substr(string("@@torch_").size()));

					// Check if user clicked torch
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same torch is not clicked again
						if(_selectedTorchID != _activeTorchID)
						{
							_activateSpotlight(_selectedTorchID.substr(string("@@torch_").size()));
						}
					}
				}
				else
				{
					// Unselect if necessary
					if((ID != _selectedTorchID) && (ID != _activeTorchID))
					{
						_unselectSpotlight(ID);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				// Check if spotlight is active
				if(!_activeTorchID.empty())
				{
					// Check if active spotlight cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedTorchID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeTorchID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		// Update torch highlighting
		if(_selectedTorchID != _activeTorchID)
		{
			_updateTorchHighlighting(_selectedTorchID, _selectedTorchHighlightDirection);
		}
		_updateTorchHighlighting(_activeTorchID, _activeTorchHighlightDirection);

		// Update properties screen
		if(!_activeTorchID.empty())
		{
			// Temporary values
			const string activeSpotlightID = _activeTorchID.substr(string("@@torch_").size());
			auto screen = rightWindow->getScreen("spotlightPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("spotlightPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("color")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("color")->setHoverable(false);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.model_delete(_activeTorchID);
					_fe3d.spotlight_delete(activeSpotlightID);
					rightWindow->setActiveScreen("main");
					_activeTorchID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.model_delete(_activeTorchID);
				_fe3d.spotlight_delete(activeSpotlightID);
				rightWindow->setActiveScreen("main");
				_activeTorchID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.spotlight_getPosition(activeSpotlightID);
			auto color = _fe3d.spotlight_getColor(activeSpotlightID);
			auto yaw = _fe3d.spotlight_getYaw(activeSpotlightID);
			auto pitch = _fe3d.spotlight_getPitch(activeSpotlightID);
			auto intensity = _fe3d.spotlight_getIntensity(activeSpotlightID);
			auto angle = _fe3d.spotlight_getAngle(activeSpotlightID);
			auto distance = _fe3d.spotlight_getDistance(activeSpotlightID);

			// Handle position, color
			if(!screen->getButton("position")->isHoverable())
			{
				// Set value form descriptions
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				// Update value forms
				_handleValueChanging("spotlightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("spotlightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("spotlightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("spotlightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("spotlightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("spotlightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));

				// Update entity
				_fe3d.spotlight_setPosition(activeSpotlightID, position);
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				// Set value form descriptions
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->changeTextContent("R");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->changeTextContent("G");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->changeTextContent("B");

				// Update value forms
				_handleValueChanging("spotlightPropertiesMenu", "xPlus", "x", color.r, SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "xMinus", "x", color.r, -SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "yPlus", "y", color.g, SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "yMinus", "y", color.g, -SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "zPlus", "z", color.b, SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "zMinus", "z", color.b, -SPOTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);

				// Update entities
				_fe3d.model_setColor(_activeTorchID, "", color);
				_fe3d.spotlight_setColor(activeSpotlightID, color);
			}

			// Handle yaw
			_handleValueChanging("spotlightPropertiesMenu", "yawPlus", "yaw", yaw, SPOTLIGHT_YAW_CHANGING_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "yawMinus", "yaw", yaw, -SPOTLIGHT_YAW_CHANGING_SPEED);
			_fe3d.model_setBaseRotation(_activeTorchID, fvec3(0.0f, -yaw, _fe3d.model_getBaseRotation(_activeTorchID).z));
			_fe3d.spotlight_setYaw(activeSpotlightID, yaw);

			// Handle pitch
			_handleValueChanging("spotlightPropertiesMenu", "pitchPlus", "pitch", pitch, SPOTLIGHT_PITCH_CHANGING_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "pitchMinus", "pitch", pitch, -SPOTLIGHT_PITCH_CHANGING_SPEED);
			_fe3d.model_setBaseRotation(_activeTorchID, fvec3(0.0f, _fe3d.model_getBaseRotation(_activeTorchID).y, pitch));
			_fe3d.spotlight_setPitch(activeSpotlightID, pitch);

			// Handle intensity
			_handleValueChanging("spotlightPropertiesMenu", "intensityPlus", "intensity", intensity, SPOTLIGHT_INTENSITY_CHANGING_SPEED, 10.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "intensityMinus", "intensity", intensity, -SPOTLIGHT_INTENSITY_CHANGING_SPEED, 10.0f, 0.0f);
			_fe3d.spotlight_setIntensity(activeSpotlightID, intensity);

			// Handle angle
			_handleValueChanging("spotlightPropertiesMenu", "anglePlus", "angle", angle, SPOTLIGHT_ANGLE_CHANGING_SPEED, 1.0f, 0.0f, 45.0f);
			_handleValueChanging("spotlightPropertiesMenu", "angleMinus", "angle", angle, -SPOTLIGHT_ANGLE_CHANGING_SPEED, 1.0f, 0.0f, 45.0f);
			_fe3d.spotlight_setAngle(activeSpotlightID, angle);

			// Handle distance
			_handleValueChanging("spotlightPropertiesMenu", "distancePlus", "distance", distance, (_editorSpeed / 100.0f), 1.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "distanceMinus", "distance", distance, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
			_fe3d.spotlight_setDistance(activeSpotlightID, distance);
		}
	}
}