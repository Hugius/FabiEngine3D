#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuMesh")
	{
		// Temporary values
		auto size = _fe3d.modelEntity_getSize(_currentModelID, "");

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeZ", "Z", (size.z * 100.0f), Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}

		// Check if mesh exists
		bool isExisting = _fe3d.modelEntity_isExisting(_currentModelID);
		bool isHoverable = false;
		if (isExisting)
		{
			isHoverable = (isExisting && !_fe3d.modelEntity_isMultiParted(_currentModelID));
		}

		// Update buttons hoverability
		screen->getButton("loadDiffuseMap")->setHoverable(isHoverable);
		screen->getButton("loadEmissionMap")->setHoverable(isHoverable);
		screen->getButton("loadReflectionMap")->setHoverable(isHoverable);
		screen->getButton("loadNormalMap")->setHoverable(isHoverable);
		screen->getButton("clearMaps")->setHoverable(isHoverable);
	}
}