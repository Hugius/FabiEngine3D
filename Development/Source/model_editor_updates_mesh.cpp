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
		auto isMultiParted = _fe3d.modelEntity_isMultiParted(_currentModelID);

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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			auto lambda = [this]() { _loadDiffuseMap(); };
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			auto lambda = [this]() { _loadEmissionMap(); };
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionMap")->isHovered())
		{
			auto lambda = [this]() { _loadReflectionMap(); };
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			auto lambda = [this]() { _loadNormalMap(); };
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setEmissionMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setReflectionMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setNormalMap(_currentModelID, _currentPartID, "");
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

		// Update buttons hoverability
		screen->getButton("clearMaps")->setHoverable(!isMultiParted && (
			_fe3d.modelEntity_hasDiffuseMap(_currentModelID, "") ||
			_fe3d.modelEntity_hasEmissionMap(_currentModelID, "") ||
			_fe3d.modelEntity_hasReflectionMap(_currentModelID, "") ||
			_fe3d.modelEntity_hasNormalMap(_currentModelID, "")));
	}
}