#include "LeftViewportController.hpp"

void LeftViewportController::update(float delta)
{
	// Getting hovered button
	string activeScreenID = _gui->getViewport("leftViewport")->getWindow("mainWindow")->getActiveScreen()->getID();
	string hoveredItemID = _gui->getViewport("leftViewport")->getWindow("mainWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (activeScreenID == "mainScreen") // Main screen
		{
			if (hoveredItemID == "modelEditor")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
			}
			else if (hoveredItemID == "worldEditor")
			{
				_worldlEditorEnabled = true;
			}
			else if (hoveredItemID == "placingEditor")
			{
				_placingEditorEnabled = true;
			}
			else if (hoveredItemID == "lightingEditor")
			{
				_lightingEditorEnabled = true;
			}
			else if (hoveredItemID == "scriptEditor")
			{
				_scriptEditorEnabled = true;
			}
		}
		else if (activeScreenID == "modelManagementScreen") // Model management screen
		{
			if (hoveredItemID == "addModel")
			{
				_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
				_gui->getGlobalScreen()->addWritefield("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
				_gui->getGlobalScreen()->getWritefield("newModelName")->setActive(true);
				_gui->setFocus(true);
				_modelCreationEnabled = true;
			}
			else if (hoveredItemID == "editModel")
			{
				_modelEditingEnabled = true;
			}
			else if (hoveredItemID == "deleteModel")
			{
				_modelRemovalEnabled = true;
			}
			else if (hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
			}
		}
		else if (activeScreenID == "modelEditingScreen") // Model editing screen
		{
			if (hoveredItemID == "loadOBJ")
			{
				
			}
			else if (hoveredItemID == "loadDiffuseMap")
			{
				
			}
			else if (hoveredItemID == "loadLightMap")
			{
				
			}
			else if (hoveredItemID == "loadReflectionMap")
			{
				
			}
			else if (hoveredItemID == "back")
			{
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
			}
		}
	}

	// Update specific processes
	_updateModelCreation();
	_updateModelEditing();
	_updateModelRemoval();

	_updateWorldEditor();
	_updatePlacingEditor();
	_updateLightingEditor();
	_updateScriptEditor();
}

void LeftViewportController::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWritefield("newModelName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWritefield("newModelName")->confirmedInput())
		{
			// Extract new name
			string modelName = _gui->getGlobalScreen()->getWritefield("newModelName")->getTextContent();

			// Create new project
			if (_gui->getGlobalScreen()->getWritefield("newModelName")->confirmedInput())
			{
				_modelEditingEnabled = true;
				_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelEditingScreen");
			}

			// Cleanup
			_modelCreationEnabled = false;
			_gui->setFocus(false);
			_gui->getGlobalScreen()->deleteTextfield("newModelName");
			_gui->getGlobalScreen()->deleteWritefield("newModelName");
		}
	}
}

void LeftViewportController::_updateModelEditing()
{

}

void LeftViewportController::_updateModelRemoval()
{

}

void LeftViewportController::_updateWorldEditor()
{
	if (_worldlEditorEnabled)
	{

	}
}

void LeftViewportController::_updatePlacingEditor()
{
	if (_placingEditorEnabled)
	{

	}
}

void LeftViewportController::_updateLightingEditor()
{
	if (_lightingEditorEnabled)
	{

	}
}

void LeftViewportController::_updateScriptEditor()
{
	if (_scriptEditorEnabled)
	{

	}
}