#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditingMesh()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuMesh")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("loadMesh")->isHovered())
			{
				_loadMesh();
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
			else if (screen->getButton("loadNormalMap")->isHovered())
			{
				_loadNormalMap();
			}
		}

		// Check if mesh exists
		bool existing = _fe3d.modelEntity_isExisting(_currentModelID);
		bool hoverable = false;
		if (existing)
		{
			hoverable = existing && !_fe3d.modelEntity_isMultiParted(_currentModelID);
		}

		// Editing buttons hoverability
		screen->getButton("loadMesh")->setHoverable(!existing);
		screen->getButton("loadDiffuseMap")->setHoverable(hoverable);
		screen->getButton("loadLightMap")->setHoverable(hoverable);
		screen->getButton("loadNormalMap")->setHoverable(hoverable);
		screen->getButton("loadReflectionMap")->setHoverable(hoverable);
	}
}