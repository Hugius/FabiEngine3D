#include "scene_editor.hpp"
#include "logger.hpp"

void SceneEditor::_updatePointlightEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected lamp from last frame
	if(!_dontResetSelectedLamp)
	{
		_selectedLampID = "";
	}
	else
	{
		_dontResetSelectedLamp = false;
	}

	// User must not be in placement mode
	if(_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a lamp model
		for(const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be pointlight preview entity
			if(entityID.substr(0, string("@@lamp").size()) == "@@lamp")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered lamp
					_selectPointlight(entityID.substr(string("@@lamp_").size()));

					// Check if user clicked lamp
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same lamp is not clicked again
						if(_selectedLampID != _activeLampID)
						{
							_activatePointlight(_selectedLampID.substr(string("@@lamp_").size()));
						}
					}
				}
				else
				{
					// Don't reset if lamp is active or selected
					if((entityID != _activeLampID) && (entityID != _selectedLampID))
					{
						_fe3d.modelEntity_setBaseSize(entityID, DEFAULT_LAMP_SIZE);
						_fe3d.aabbEntity_setLocalSize(entityID, DEFAULT_LAMP_AABB_SIZE);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if pointlight is active
				if(_activeLampID != "")
				{
					// Check if active pointlight cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedLampID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeLampID = "";
						rightWindow->setActiveScreen("sceneEditorControls");
					}
				}
			}
		}

		// Update lamp animations
		if(_selectedLampID != _activeLampID)
		{
			_updateLampAnimation(_selectedLampID, _selectedLampSizeDirection);
		}
		_updateLampAnimation(_activeLampID, _activeLampSizeDirection);

		// Update properties screen
		if(!_activeLampID.empty())
		{
			// Temporary values
			const string activePointlightID = _activeLampID.substr(string("@@lamp_").size());
			auto screen = rightWindow->getScreen("pointlightPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("pointlightPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("radius")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(false);
					screen->getButton("color")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(false);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("shape")->isHovered())
				{
					if(_fe3d.pointlightEntity_getShape(activePointlightID) == PointlightShape::CIRCLE)
					{
						_fe3d.pointlightEntity_setShape(activePointlightID, PointlightShape::SQUARE);
					}
					else
					{
						_fe3d.pointlightEntity_setShape(activePointlightID, PointlightShape::CIRCLE);
					}
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeLampID);
					_fe3d.pointlightEntity_delete(activePointlightID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeLampID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(_activeLampID);
				_fe3d.pointlightEntity_delete(activePointlightID);
				rightWindow->setActiveScreen("sceneEditorControls");
				_activeLampID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.pointlightEntity_getPosition(activePointlightID);
			auto radius = _fe3d.pointlightEntity_getRadius(activePointlightID);
			auto color = _fe3d.pointlightEntity_getColor(activePointlightID);
			auto intensity = _fe3d.pointlightEntity_getIntensity(activePointlightID);

			// Handle position, radius, color
			if(!screen->getButton("position")->isHoverable())
			{
				// Set value form descriptions
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				// Update value forms
				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));

				// Update entity
				_fe3d.pointlightEntity_setPosition(activePointlightID, position);
			}
			else if(!screen->getButton("radius")->isHoverable())
			{
				// Set value form descriptions
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				// Update value forms
				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", radius.x, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", radius.x, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", radius.y, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", radius.y, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", radius.z, (_editorSpeed / 100.0f), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", radius.z, -(_editorSpeed / 100.0f), 1.0f, 0.0f);

				// Update entity
				_fe3d.pointlightEntity_setRadius(activePointlightID, radius);
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				// Set value form descriptions
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("R");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("G");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("B");

				// Update value forms
				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", color.r, POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", color.r, -POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", color.g, POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", color.g, -POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", color.b, POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", color.b, -POINTLIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);

				// Update entities
				_fe3d.modelEntity_setColor(_activeLampID, "", color);
				_fe3d.pointlightEntity_setColor(activePointlightID, color);
			}

			// Handle intensity
			_handleValueChanging("pointlightPropertiesMenu", "intensityPlus", "intensity", intensity, POINTLIGHT_INTENSITY_CHANGING_SPEED, 10.0f, 0.0f);
			_handleValueChanging("pointlightPropertiesMenu", "intensityMinus", "intensity", intensity, -POINTLIGHT_INTENSITY_CHANGING_SPEED, 10.0f, 0.0f);
			_fe3d.pointlightEntity_setIntensity(activePointlightID, intensity);

			// Handle shape
			const auto imageEntityID = screen->getButton("shape")->getRectangle()->getEntityID();
			if(_fe3d.pointlightEntity_getShape(activePointlightID) == PointlightShape::CIRCLE)
			{
				_fe3d.imageEntity_setDiffuseMap(imageEntityID, "engine\\assets\\textures\\shape_circle.png");
			}
			else
			{
				_fe3d.imageEntity_setDiffuseMap(imageEntityID, "engine\\assets\\textures\\shape_square.png");
			}
		}
	}
}