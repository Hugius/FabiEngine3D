#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuMesh")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("loadDiffuseMap")->isHovered())
		{
			_loadDiffuseMap();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("loadEmissionMap")->isHovered())
		{
			_loadEmissionMap();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("loadReflectionMap")->isHovered())
		{
			_loadReflectionMap();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("loadNormalMap")->isHovered())
		{
			_loadNormalMap();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, "");
			_fe3d.modelEntity_setEmissionMap(_currentModelID, "");
			_fe3d.modelEntity_setReflectionMap(_currentModelID, "");
			_fe3d.modelEntity_setNormalMap(_currentModelID, "");
		}

		// Check if mesh exists
		bool isExisting = _fe3d.modelEntity_isExisting(_currentModelID);
		bool hoverable = false;
		if (isExisting)
		{
			hoverable = (isExisting && !_fe3d.modelEntity_isMultiParted(_currentModelID));
		}

		// Update buttons hoverability
		screen->getButton("loadDiffuseMap")->setHoverable(hoverable);
		screen->getButton("loadEmissionMap")->setHoverable(hoverable);
		screen->getButton("loadReflectionMap")->setHoverable(hoverable);
		screen->getButton("loadNormalMap")->setHoverable(hoverable);
		screen->getButton("clearMaps")->setHoverable(hoverable);
	}
}