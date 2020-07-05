#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateEditingScreen()
{
	if (_modelEditingEnabled && _currentModelName != "")
	{
		static bool firstTime = true;
		auto screen = _leftWindow->getScreen("modelEditingMain");

		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(), 
				"Model: " + _currentModelName.substr(1, _currentModelName.size()), 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
			_leftWindow->setActiveScreen("modelEditingMain");
		}
		
		// GUI management
		if (_leftWindow->getActiveScreen()->getID() == "modelEditingMain")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mesh")->isHovered())
				{
					_leftWindow->setActiveScreen("modelEditingMesh");
				}
				else if (screen->getButton("options")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_leftWindow->setActiveScreen("modelEditingOptions");
					}
				}
				else if (screen->getButton("size")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_leftWindow->setActiveScreen("modelEditingSize");
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
					_leftWindow->setActiveScreen("modelManagement");
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
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditingMesh")
		{
			_updateModelEditingMesh();
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditingOptions")
		{
			_updateModelEditingOptions();
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditingSize")
		{
			_updateModelEditingSize();
		}
	}
}

void ModelEditor::_updateModelEditingMesh()
{
	auto screen = _leftWindow->getScreen("modelEditingMesh");

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
			_leftWindow->setActiveScreen("modelEditingMain");
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