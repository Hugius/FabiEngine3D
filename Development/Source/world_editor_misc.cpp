#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool WorldEditor::isLoaded()
{
	return _isLoaded;
}