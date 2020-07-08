#include "billboard_editor.hpp"

void BillboardEditor::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

bool BillboardEditor::isLoaded()
{
	return _isLoaded;
}