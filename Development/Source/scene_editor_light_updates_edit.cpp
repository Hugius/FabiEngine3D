#include "scene_editor.hpp"
#include "logger.hpp"

void SceneEditor::_updateLightEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected light from last frame
	_selectedLampID = "";

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingLight)
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

		// Check if user selected a lamp model
		for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be light preview entity
			if (entityID.substr(0, string("@@lamp").size()) == "@@lamp")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Set new selected lamp
					_selectedLampID = entityID;

					// Change cursor
					_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

					// Check if user clicked lamp
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same lamp is not clicked again
						if (_selectedLampID != _activeLampID)
						{
							// Set new active light
							_activeLampID = _selectedLampID;

							// Update buttons hoverability
							rightWindow->getScreen("lightPropertiesMenu")->getButton("position")->setHoverable(false);
							rightWindow->getScreen("lightPropertiesMenu")->getButton("radius")->setHoverable(true);
							rightWindow->getScreen("lightPropertiesMenu")->getButton("color")->setHoverable(true);

							// Filling writeFields
							Vec3 position = _fe3d.modelEntity_getPosition(_activeLampID);
							rightWindow->getScreen("lightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
							rightWindow->getScreen("lightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
							rightWindow->getScreen("lightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
						}
					}
				}
				else
				{
					// Don't reset if lamp is active
					if (entityID != _activeLampID)
					{
						_fe3d.modelEntity_setSize(entityID, DEFAULT_LAMP_SIZE);
						_fe3d.aabbEntity_setSize(entityID, DEFAULT_LAMP_AABB_SIZE);
					}
				}
			}
		}

		// Check if user made the active lamp inactive
		if ((_selectedLampID.empty()) && (_activeLampID != "") && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_activeLampID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update lamp animations
		if (_selectedLampID != _activeLampID)
		{
			_updateLampAnimation(_selectedLampID, _selectedLampSizeDirection);
		}
		_updateLampAnimation(_activeLampID, _activeLampSizeDirection);

		// Update properties screen
		if (!_activeLampID.empty())
		{
			// Temporary values
			const string activeLightID = _activeLampID.substr(string("@@lamp_").size());
			auto screen = rightWindow->getScreen("lightPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("lightPropertiesMenu");

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(true);
				}
				else if (screen->getButton("radius")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(false);
					screen->getButton("color")->setHoverable(true);
				}
				else if (screen->getButton("color")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(false);
				}
				else if (screen->getButton("shape")->isHovered())
				{
					if (_fe3d.lightEntity_getShape(activeLightID) == LightShape::CIRCLE)
					{
						_fe3d.lightEntity_setShape(activeLightID, LightShape::SQUARE);
					}
					else
					{
						_fe3d.lightEntity_setShape(activeLightID, LightShape::CIRCLE);
					}
				}
				else if (screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeLampID);
					_fe3d.lightEntity_delete(activeLightID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeLampID = "";
					return;
				}
			}

			// Get current values
			auto position = _fe3d.lightEntity_getPosition(activeLightID);
			auto radius = _fe3d.lightEntity_getRadius(activeLightID);
			auto color = _fe3d.lightEntity_getColor(activeLightID);
			auto intensity = _fe3d.lightEntity_getIntensity(activeLightID);

			// Handle position, radius, color
			if (!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("lightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("lightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("lightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("lightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("lightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("lightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
				_fe3d.lightEntity_setPosition(activeLightID, position);
			}
			else if (!screen->getButton("radius")->isHoverable())
			{
				_handleValueChanging("lightPropertiesMenu", "xPlus", "x", radius.x, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("lightPropertiesMenu", "xMinus", "x", radius.x, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("lightPropertiesMenu", "yPlus", "y", radius.y, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("lightPropertiesMenu", "yMinus", "y", radius.y, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("lightPropertiesMenu", "zPlus", "z", radius.z, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("lightPropertiesMenu", "zMinus", "z", radius.z, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
				_fe3d.lightEntity_setRadius(activeLightID, radius);
			}
			else if (!screen->getButton("color")->isHoverable())
			{
				_handleValueChanging("lightPropertiesMenu", "xPlus", "x", color.r, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("lightPropertiesMenu", "xMinus", "x", color.r, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("lightPropertiesMenu", "yPlus", "y", color.g, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("lightPropertiesMenu", "yMinus", "y", color.g, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("lightPropertiesMenu", "zPlus", "z", color.b, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("lightPropertiesMenu", "zMinus", "z", color.b, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_fe3d.modelEntity_setColor(_activeLampID, color);
				_fe3d.lightEntity_setColor(activeLightID, color);
			}

			// Handle intensity
			_handleValueChanging("lightPropertiesMenu", "intensityPlus", "intensity", intensity, LIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
			_handleValueChanging("lightPropertiesMenu", "intensityMinus", "intensity", intensity, -LIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
			_fe3d.lightEntity_setIntensity(activeLightID, intensity);

			// Handle shape
			const auto imageEntityID = screen->getButton("shape")->getRectangle()->getEntityID();
			if (_fe3d.lightEntity_getShape(activeLightID) == LightShape::CIRCLE)
			{
				_fe3d.imageEntity_setDiffuseMap(imageEntityID, "engine_assets\\textures\\shape_circle.png");
			}
			else
			{
				_fe3d.imageEntity_setDiffuseMap(imageEntityID, "engine_assets\\textures\\shape_square.png");
			}
		}
	}
}