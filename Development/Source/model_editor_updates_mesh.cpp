#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateEditingScreen()
{
	if (_modelEditingEnabled && _currentModelName != "")
	{
		static bool firstTime = true;
		auto screen = _window->getScreen("modelEditingMain");

		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(), 
				"Model: " + _currentModelName.substr(1, _currentModelName.size()), 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
			_window->setActiveScreen("modelEditingMain");
		}
		
		// GUI management
		if (_window->getActiveScreen()->getID() == "modelEditingMain")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mesh")->isHovered())
				{
					_window->setActiveScreen("modelEditingMesh");
				}
				else if (screen->getButton("options")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_window->setActiveScreen("modelEditingOptions");
					}
				}
				else if (screen->getButton("size")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_window->setActiveScreen("modelEditingSize");
					}
				}
				else if (screen->getButton("back")->isHovered())
				{
					// Hide game entity
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_fe3d.gameEntity_hide(_currentModelName);
					}

					firstTime = true;
					_modelEditingEnabled = false;
					_currentModelName = "";
					_window->setActiveScreen("modelManagement");
					_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
				}
			}

			// Check if OBJ exists
			bool existing = _fe3d.gameEntity_isExisting(_currentModelName);
			bool hoverable = false;
			if (existing)
			{
				hoverable = existing && !_fe3d.gameEntity_isMultiTextured(_currentModelName);

				// Show OBJ model
				_fe3d.gameEntity_show(_currentModelName);
			}

			// Editing buttons hoverability
			screen->getButton("options")->setHoverable(hoverable);
			screen->getButton("size")->setHoverable(hoverable);
		}
		else if (_window->getActiveScreen()->getID() == "modelEditingMesh")
		{
			_updateModelEditingMesh();
		}
		else if (_window->getActiveScreen()->getID() == "modelEditingOptions")
		{
			_updateModelEditingOptions();
		}
		else if (_window->getActiveScreen()->getID() == "modelEditingSize")
		{
			_updateModelEditingSize();
		}
	}
}

void ModelEditor::_updateModelEditingMesh()
{
	auto screen = _window->getScreen("modelEditingMesh");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("loadOBJ")->isHovered())
		{
			_loadOBJ();
		}
		else if (screen->getButton("loadDiffuseMap")->isHovered())
		{
			_loadDiffuseMap();
		}
		else if (screen->getButton("loadLightMap")->isHovered())
		{
			_loadLightMap();
		}
		else if (screen->getButton("loadReflectionMap")->isHovered())
		{
			_loadReflectionMap();
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("modelEditingMain");
		}
	}

	// Check if OBJ exists
	bool existing = _fe3d.gameEntity_isExisting(_currentModelName);
	bool hoverable = false;
	if (existing)
	{
		hoverable = existing && !_fe3d.gameEntity_isMultiTextured(_currentModelName);
	}

	// Editing buttons hoverability
	screen->getButton("loadDiffuseMap")->setHoverable(hoverable);
	screen->getButton("loadLightMap")->setHoverable(hoverable);
	screen->getButton("loadReflectionMap")->setHoverable(hoverable);
}