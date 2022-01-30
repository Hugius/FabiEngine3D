#include "base_editor.hpp"

void BaseEditor::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void BaseEditor::inject(shared_ptr<GuiManager> gui)
{
	_gui = gui;
}

void BaseEditor::setCurrentProjectId(const string& currentProjectId)
{
	_currentProjectId = currentProjectId;
}

void BaseEditor::load()
{
	_loadGUI();
	_load();

	_isEditorLoaded = true;
}

void BaseEditor::unload()
{
	_unload();
	_unloadGUI();

	_isEditorLoaded = false;
}

const bool BaseEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const string& BaseEditor::getCurrentProjectId() const
{
	return _currentProjectId;
}