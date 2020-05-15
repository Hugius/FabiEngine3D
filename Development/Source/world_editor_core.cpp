#include "world_editor.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void WorldEditor::initializeGUI()
{
	// Private window instance of left viewport
	_window = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - worldManagement
	_window->addScreen("worldManagement");
	_window->getScreen("worldManagement")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Add model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Edit model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Delete model", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void WorldEditor::loadProject()
{

}

void WorldEditor::saveProject()
{

}

void WorldEditor::unloadProject()
{

}

void WorldEditor::update(float delta)
{

}

void WorldEditor::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}