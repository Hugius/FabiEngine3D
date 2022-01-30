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