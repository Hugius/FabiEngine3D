#include "entity_placer.hpp"

void EntityPlacer::update()
{
	_updateCamera();
	_updateManagementScreen();
	_updateModelScreen();
	_updateBillboardScreen();
	_updateLightScreen();
	_updateMiscellaneous();
}

void EntityPlacer::_updateManagementScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("placeManagement");

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
				_leftWindow->setActiveScreen("lightPlaceManagement");
			}
			else if (screen->getButton("setSpeed")->isHovered()) // Set speed button
			{
				_gui->getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _cameraMovementSpeed, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_gui->getGlobalScreen()->addAnswerForm("exitEntityPlacer", "Save changes?", vec2(0.0f, 0.25f));
			}
		}

		// Setting camera speed
		_gui->getGlobalScreen()->checkValueForm("setSpeed", _cameraMovementSpeed, {});

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
			for (auto& modelName : _modelEditor.getModelNames())
			{
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

			// Back button
			if (screen->getButton("back")->isHovered()) 
			{
				_leftWindow->setActiveScreen("placeManagement");
			}
		}

		// Update model placing
		if (_currentModelName != "")
		{
			if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
			{
				// Show preview model
				_fe3d.gameEntity_show(_currentModelName);

				// Update preview model position
				_fe3d.gameEntity_setPosition(_currentModelName, _fe3d.terrainEntity_getMousePoint());

				// Placing model
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					string newID = _currentModelName + std::to_string(_counterMap[_currentModelName]);
					_fe3d.gameEntity_add(newID, _fe3d.gameEntity_getObjPath(_currentModelName),
						_fe3d.terrainEntity_getMousePoint(), vec3(0.0f), _fe3d.gameEntity_getSize(_currentModelName));

					// Model properties
					_fe3d.gameEntity_setFaceCulled(newID, _fe3d.gameEntity_isFaceCulled(_currentModelName));
					_fe3d.gameEntity_setShadowed(newID, _fe3d.gameEntity_isShadowed(_currentModelName));
					_fe3d.gameEntity_setTransparent(newID, _fe3d.gameEntity_isTransparent(_currentModelName));
					_fe3d.gameEntity_setSpecularLighted(newID, _fe3d.gameEntity_isSpecularLighted(_currentModelName));
					_fe3d.gameEntity_setUvRepeat(newID, _fe3d.gameEntity_getUvRepeat(_currentModelName));
					_fe3d.gameEntity_setColor(newID, _fe3d.gameEntity_getColor(_currentModelName));
					_fe3d.aabbEntity_bindToGameEntity(newID, _fe3d.aabbEntity_getSize(_currentModelName), true);

					// Diffuse map
					if (_fe3d.gameEntity_getDiffuseMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setDiffuseMap(newID, _fe3d.gameEntity_getDiffuseMapPath(_currentModelName));
					}

					// Light map
					if (_fe3d.gameEntity_getLightMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setLightMap(newID, _fe3d.gameEntity_getLightMapPath(_currentModelName));
						_fe3d.gameEntity_setLightmapped(newID, true);
					}

					// Reflection map
					if (_fe3d.gameEntity_getReflectionMapPath(_currentModelName) != "")
					{
						_fe3d.gameEntity_setReflectionMap(newID, _fe3d.gameEntity_getReflectionMapPath(_currentModelName));
						_fe3d.gameEntity_setSkyReflective(newID, true);
					}

					// Increase 
					_counterMap[_currentModelName]++;
				}
				else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_MIDDLE)) // Cancelling model placement
				{
					// Hide preview model
					_fe3d.gameEntity_hide(_currentModelName);
					_currentModelName = "";
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview model
				_fe3d.gameEntity_hide(_currentModelName);
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
				_leftWindow->setActiveScreen("placeManagement");
			}
		}
	}
}

void EntityPlacer::_updateLightScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("lightPlaceManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			// Back button
			if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("placeManagement");
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
				_fe3d.camera_translateFollowX(-_cameraMovementSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_D))
			{
				_fe3d.camera_translateFollowX(_cameraMovementSpeed);
			}

			// Y movement
			if (_fe3d.input_getKeyDown(Input::KEY_SPACE))
			{
				_fe3d.camera_translate(vec3(0.0f, _cameraMovementSpeed / 50.0f, 0.0f));
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT))
			{
				_fe3d.camera_translate(vec3(0.0f, -(_cameraMovementSpeed / 50.0f), 0.0f));
			}

			// Z movement
			if (_fe3d.input_getKeyDown(Input::KEY_W))
			{
				_fe3d.camera_translateFollowZ(_cameraMovementSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_S))
			{
				_fe3d.camera_translateFollowZ(-_cameraMovementSpeed);
			}
		}
	}
}