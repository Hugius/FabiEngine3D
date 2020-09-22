#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditingMesh()
{
	auto screen = _leftWindow->getScreen("modelEditorMenuMesh");

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
		else if (screen->getButton("loadNormalMap")->isHovered())
		{
			_loadNormalMap();
		}
		else if (screen->getButton("back")->isHovered())
		{
			_leftWindow->setActiveScreen("modelEditorMenuChoice");
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
	screen->getButton("loadNormalMap")->setHoverable(hoverable);
	screen->getButton("loadReflectionMap")->setHoverable(hoverable);
}