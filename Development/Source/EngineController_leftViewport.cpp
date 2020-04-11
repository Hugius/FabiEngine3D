#include "EngineController.hpp"

void EngineController::_updateLeftViewport()
{
	auto vp = _gui->getViewport("leftViewport");

	// Getting hovered button
	string activeScreenID = vp->getWindow("mainWindow")->getActiveScreen()->getID();
	string hoveredItemID = vp->getWindow("mainWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (activeScreenID == "mainScreen") // Main screen
		{
			if (hoveredItemID == "modelEditor")
			{
				_modelEditorEnabled = true;
				vp->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
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

			}
			else if (hoveredItemID == "editModel")
			{

			}
			else if (hoveredItemID == "deleteModel")
			{

			}
			else if (hoveredItemID == "back")
			{
				vp->getWindow("mainWindow")->setActiveScreen("mainScreen");
			}
		}
	}

	// Update specific processes
	_updateModelEditor();
	_updateWorldEditor();
	_updatePlacingEditor();
	_updateLightingEditor();
	_updateScriptEditor();
}

void EngineController::_updateModelEditor()
{
	if (_modelEditorEnabled)
	{

	}
}

void EngineController::_updateWorldEditor()
{
	if (_worldlEditorEnabled)
	{

	}
}

void EngineController::_updatePlacingEditor()
{
	if (_placingEditorEnabled)
	{

	}
}

void EngineController::_updateLightingEditor()
{
	if (_lightingEditorEnabled)
	{

	}
}

void EngineController::_updateScriptEditor()
{
	if (_scriptEditorEnabled)
	{

	}
}