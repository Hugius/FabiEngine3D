#include "entity_placer.hpp"

bool EntityPlacer::isLoaded()
{
	return _isLoaded;
}

void EntityPlacer::setCurrentProjectName(string projectName)
{
	_currentProjectName = projectName;
}

void EntityPlacer::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		_fe3d.input_setKeyTogglingLocked(_gui->getGlobalScreen()->isFocused() || !_fe3d.misc_isMouseInsideViewport());

		// Update bounding box visibility
		if (_fe3d.input_getKeyToggled(Input::KEY_B))
		{
			_fe3d.collision_enableFrameRendering();
		}
		else
		{
			_fe3d.collision_disableFrameRendering();
		}
	}
}