#include "base_editor.hpp"

void BaseEditor::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void BaseEditor::inject(shared_ptr<GuiManager> gui)
{
	_gui = gui;
}

void BaseEditor::setCurrentProjectId(const string & currentProjectId)
{
	_currentProjectId = currentProjectId;
}

void BaseEditor::load()
{
	_isLoading = true;

	_loadGUI();
	_load();

	_isLoading = false;
	_isLoaded = true;
}

void BaseEditor::update()
{
	_update();
}

void BaseEditor::unload()
{
	_unload();
	_unloadGUI();

	_isLoaded = false;
}

const bool BaseEditor::isLoading() const
{
	return _isLoading;
}

const bool BaseEditor::isLoaded() const
{
	return _isLoaded;
}

const string & BaseEditor::getCurrentProjectId() const
{
	return _currentProjectId;
}