#include "entity_placer.hpp"

bool EntityPlacer::isLoaded()
{
	return _isLoaded;
}

void EntityPlacer::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}