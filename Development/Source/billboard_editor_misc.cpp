#include "billboard_editor.hpp"

void BillboardEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool BillboardEditor::isLoaded()
{
	return _isLoaded;
}