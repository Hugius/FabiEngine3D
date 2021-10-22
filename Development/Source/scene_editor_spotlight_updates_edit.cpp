#include "scene_editor.hpp"
#include "logger.hpp"

void SceneEditor::_updateSpotlightEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected torch from last frame
	if (!_dontResetSelectedTorch)
	{
		_selectedTorchID = "";
	}
	else
	{
		_dontResetSelectedTorch = false;
	}

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a torch model
		for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be spotlight preview entity
			if (entityID.substr(0, string("@@torch").size()) == "@@torch")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered torch
					_selectSpotlight(entityID.substr(string("@@torch_").size()));

					// Check if user clicked torch
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same torch is not clicked again
						if (_selectedTorchID != _activeTorchID)
						{
							_activateSpotlight(_selectedTorchID.substr(string("@@torch_").size()));
						}
					}
				}
				else
				{
					// Don't reset if torch is active or selected
					if ((entityID != _activeTorchID) && (entityID != _selectedTorchID))
					{
						_fe3d.modelEntity_setBaseSize(entityID, DEFAULT_TORCH_SIZE);
						_fe3d.aabbEntity_setLocalSize(entityID, DEFAULT_TORCH_AABB_SIZE);
					}
				}
			}
		}

		// Check if RMB not down
		if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if spotlight is active
				if (_activeTorchID != "")
				{
					// Check if active spotlight cancelled
					if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedTorchID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeTorchID = "";
						rightWindow->setActiveScreen("sceneEditorControls");
					}
				}
			}
		}

		// Update torch animations
		if (_selectedTorchID != _activeTorchID)
		{
			_updateTorchAnimation(_selectedTorchID, _selectedTorchSizeDirection);
		}
		_updateTorchAnimation(_activeTorchID, _activeTorchSizeDirection);

		// Update properties screen
		if (!_activeTorchID.empty())
		{
			// Temporary values
			const string activeSpotlightID = _activeTorchID.substr(string("@@torch_").size());
			auto screen = rightWindow->getScreen("spotlightPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("spotlightPropertiesMenu");

			// Button management
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(true);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("radius")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(false);
					screen->getButton("color")->setHoverable(true);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(false);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeTorchID);
					_fe3d.spotlightEntity_delete(activeSpotlightID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeTorchID = "";
					return;
				}
			}

			// Alternative way of deleting
			if (_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(_activeTorchID);
				_fe3d.spotlightEntity_delete(activeSpotlightID);
				rightWindow->setActiveScreen("sceneEditorControls");
				_activeTorchID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.spotlightEntity_getPosition(activeSpotlightID);
			auto color = _fe3d.spotlightEntity_getColor(activeSpotlightID);
			auto intensity = _fe3d.spotlightEntity_getIntensity(activeSpotlightID);

			// Handle position, radius, color
			if (!screen->getButton("position")->isHoverable())
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
				_fe3d.spotlightEntity_setPosition(activeSpotlightID, position);
			}
			else if (!screen->getButton("color")->isHoverable())
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
				_fe3d.modelEntity_setColor(_activeTorchID, "", color);
				_fe3d.spotlightEntity_setColor(activeSpotlightID, color);
			}

			// Handle intensity
			_handleValueChanging("spotlightPropertiesMenu", "intensityPlus", "intensity", intensity, SPOTLIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "intensityMinus", "intensity", intensity, -SPOTLIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
			_fe3d.spotlightEntity_setIntensity(activeSpotlightID, intensity);
		}
	}
}