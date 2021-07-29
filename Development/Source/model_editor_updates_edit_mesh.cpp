#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditingMesh()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuMesh")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
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
			else if (screen->getButton("loadEmissionMap")->isHovered())
			{
				_loadEmissionMap();
			}
			else if (screen->getButton("loadReflectionMap")->isHovered())
			{
				_loadReflectionMap();
			}
			else if (screen->getButton("loadNormalMap")->isHovered())
			{
				_loadNormalMap();
			}
			else if (screen->getButton("clearMaps")->isHovered())
			{
				_fe3d.modelEntity_setDiffuseMap(_currentModelID, "");
				_fe3d.modelEntity_setEmissionMap(_currentModelID, "");
				_fe3d.modelEntity_setReflectionMap(_currentModelID, "");
				_fe3d.modelEntity_setNormalMap(_currentModelID, "");
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
		screen->getButton("loadEmissionMap")->setHoverable(hoverable);
		screen->getButton("loadReflectionMap")->setHoverable(hoverable);
		screen->getButton("loadNormalMap")->setHoverable(hoverable);
		screen->getButton("clearMaps")->setHoverable(hoverable);
	}
}