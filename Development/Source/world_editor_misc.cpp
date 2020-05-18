#include "world_editor.hpp"

void WorldEditor::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}