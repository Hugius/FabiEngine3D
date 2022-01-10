#include "base_editor.hpp"

void BaseEditor::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void BaseEditor::inject(shared_ptr<GuiManager> gui)
{
	_gui = gui;
}