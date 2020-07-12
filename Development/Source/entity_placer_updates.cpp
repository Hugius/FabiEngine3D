#include "entity_placer.hpp"

#include <algorithm>

void EntityPlacer::update()
{
	// Menus
	_updateManagementScreen();
	_updateModelScreen();
	_updateBillboardScreen();
	_updateLightScreen();

	// Placement
	_updateModelPlacing();
	_updateBilboardPlacing();
	_updateLightPlacing();

	// Editing
	_updateModelEditing();
	_updateBillboardEditing();
	_updateLightEditing();

	// Miscellaneous
	_updateCamera();
	_updateMiscellaneous();
}

void EntityPlacer::_updateManagementScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("placingManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("placeModel")->isHovered()) // Add model button
			{
				_leftWindow->setActiveScreen("modelPlaceManagement");
			}
			else if (screen->getButton("placeBillboard")->isHovered()) // Place billboard button
			{
				_leftWindow->setActiveScreen("billboardPlaceManagement");
			}
			else if (screen->getButton("placeLight")->isHovered()) // Place light button
			{
				_leftWindow->setActiveScreen("lightManagement");
			}
			else if (screen->getButton("setSpeed")->isHovered()) // Set speed button
			{
				_gui->getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _customCameraSpeed, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_gui->getGlobalScreen()->addAnswerForm("exitEntityPlacer", "Save changes?", vec2(0.0f, 0.25f));
			}
		}

		// Setting camera speed
		_gui->getGlobalScreen()->checkValueForm("setSpeed", _customCameraSpeed, {});

		// Check if user wants to save changes
		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitEntityPlacer"))
		{
			save();
			_leftWindow->setActiveScreen("main");
			unload();
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitEntityPlacer"))
		{
			_leftWindow->setActiveScreen("main");
			unload();
		}
	}
}

void EntityPlacer::_updateModelScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("modelPlaceManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			// Loop over every created model
			for (auto& modelName : _modelEditor.getModelNames())
			{
				// Check if model has a game entity
				if (_fe3d.gameEntity_isExisting(modelName))
				{
					// Check if button is hovered
					if (screen->getScrollingList("modelList")->getButton(modelName)->isHovered())
					{
						// Hide old preview model
						if (_currentModelName != "")
						{
							_fe3d.gameEntity_hide(_currentModelName);
						}

						// Set new preview model
						_currentModelName = modelName;
						_fe3d.gameEntity_show(_currentModelName);
						string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
						_fe3d.textEntity_show(textEntityID);
						_fe3d.textEntity_setTextContent(textEntityID, "Model: " + _currentModelName.substr(1, _currentModelName.size()), 0.025f);
						break;
					}
				}
			}

			// Back button
			if (screen->getButton("back")->isHovered()) 
			{
				_leftWindow->setActiveScreen("placingManagement");
				_currentModelName = "";
			}
		}
	}
}

void EntityPlacer::_updateBillboardScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("billboardPlaceManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			// Back button
			if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("placingManagement");
			}
		}
	}
}

void EntityPlacer::_updateLightScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("lightManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("ambient")->isHovered()) // Ambient light button
			{
				_leftWindow->setActiveScreen("ambientLightManagement");
			}
			else if (screen->getButton("directional")->isHovered()) // Directional light button
			{
				_leftWindow->setActiveScreen("directionalLightManagement");
			}
			else if (screen->getButton("point")->isHovered()) // Point light button
			{
				_leftWindow->setActiveScreen("pointLightManagement");
			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_leftWindow->setActiveScreen("placingManagement");
			}
		}

		// Update all lighting screens
		_updateAmbientLightScreen();
		_updateDirectionalLightScreen();
		_updatePointLightScreen();
	}
}

void EntityPlacer::_updateAmbientLightScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("ambientLightManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("ambientColorG", "G(0-255)", _ambientLightColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("ambientColorR", "R(0-255)", _ambientLightColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("ambientColorB", "B(0-255)", _ambientLightColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("ambientIntensity", "Ambient intensity", _ambientLightIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("lightManagement");
			}
		}

		// Ambient value conversion
		if (_gui->getGlobalScreen()->checkValueForm("ambientIntensity", _ambientLightIntensity))
		{
			_ambientLightIntensity /= 100.0f;
		}

		// Color R values conversion
		if (_gui->getGlobalScreen()->checkValueForm("ambientColorR", _ambientLightColor.r))
		{
			_ambientLightColor.r = std::clamp(_ambientLightColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui->getGlobalScreen()->checkValueForm("ambientColorG", _ambientLightColor.g))
		{
			_ambientLightColor.g = std::clamp(_ambientLightColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui->getGlobalScreen()->checkValueForm("ambientColorB", _ambientLightColor.b))
		{
			_ambientLightColor.b = std::clamp(_ambientLightColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Update ambient lighting
		_fe3d.gfx_enableAmbientLighting(_ambientLightColor, _ambientLightIntensity);
	}
}

void EntityPlacer::_updateDirectionalLightScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("directionalLightManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("directionalColorG", "G(0-255)", _directionalLightColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("directionalColorR", "R(0-255)", _directionalLightColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("directionalColorB", "B(0-255)", _directionalLightColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("positionY", "Y", _directionalLightPosition.y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionX", "X", _directionalLightPosition.x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionZ", "Z", _directionalLightPosition.z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("directionalIntensity", "Directional intensity", _directionalLightIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("lightManagement");
			}
		}

		// Ambient value conversion
		if (_gui->getGlobalScreen()->checkValueForm("directionalIntensity", _directionalLightIntensity))
		{
			_directionalLightIntensity /= 100.0f;
		}

		// Color R values conversion
		if (_gui->getGlobalScreen()->checkValueForm("directionalColorR", _directionalLightColor.r))
		{
			_directionalLightColor.r = std::clamp(_directionalLightColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui->getGlobalScreen()->checkValueForm("directionalColorG", _directionalLightColor.g))
		{
			_directionalLightColor.g = std::clamp(_directionalLightColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui->getGlobalScreen()->checkValueForm("directionalColorB", _directionalLightColor.b))
		{
			_directionalLightColor.b = std::clamp(_directionalLightColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Get position values
		_gui->getGlobalScreen()->checkValueForm("positionX", _directionalLightPosition.x);
		_gui->getGlobalScreen()->checkValueForm("positionY", _directionalLightPosition.y);
		_gui->getGlobalScreen()->checkValueForm("positionZ", _directionalLightPosition.z);

		// Update directional lighting
		_fe3d.gfx_enableDirectionalLighting(_directionalLightPosition, _directionalLightColor, _directionalLightIntensity);
	}
}

void EntityPlacer::_updatePointLightScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("pointLightManagement");
		
		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("add")->isHovered())
			{
				_isPlacingPointlight = true;
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("lightManagement");
				_isPlacingPointlight = false;
			}
		}
	}
}

void EntityPlacer::_updateCamera()
{
	if (_isLoaded)
	{
		// Camera looking
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.misc_isMouseInsideViewport())
			{
				_fe3d.gfx_enableMotionBlur();
				_fe3d.camera_enableFirstPersonView(10.0f);
				_fe3d.camera_disableLookat();
				_fe3d.misc_hideCursor();
			}
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
			_fe3d.camera_disableFirstPersonView();
			_fe3d.misc_showCursor();
		}

		// Camera movement
		if (!_gui->getGlobalScreen()->isFocused())
		{
			// X movement
			if (_fe3d.input_getKeyDown(Input::KEY_A))
			{
				_fe3d.camera_translateFollowX(-_customCameraSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_D))
			{
				_fe3d.camera_translateFollowX(_customCameraSpeed);
			}

			// Y movement
			if (_fe3d.input_getKeyDown(Input::KEY_SPACE))
			{
				_fe3d.camera_translate(vec3(0.0f, _customCameraSpeed / 50.0f, 0.0f));
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT))
			{
				_fe3d.camera_translate(vec3(0.0f, -(_customCameraSpeed / 50.0f), 0.0f));
			}

			// Z movement
			if (_fe3d.input_getKeyDown(Input::KEY_W))
			{
				_fe3d.camera_translateFollowZ(_customCameraSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_S))
			{
				_fe3d.camera_translateFollowZ(-_customCameraSpeed);
			}
		}
	}
}
