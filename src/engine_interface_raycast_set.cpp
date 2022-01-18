#include "engine_interface.hpp"
#include "engine_core.hpp"

using std::numeric_limits;

void EngineInterface::raycast_enableTerrainPointing(float distance, float precision)
{
	if(_core->getRaycaster()->isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to enable terrain raycast pointing: already enabled!");
		return;
	}

	_core->getRaycaster()->setTerrainPointingEnabled(true);
	_core->getRaycaster()->setTerrainPointingDistance(distance);
	_core->getRaycaster()->setTerrainPointingPrecision(precision);
}

void EngineInterface::raycast_disableTerrainPointing()
{
	if(!_core->getRaycaster()->isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to disable terrain raycast pointing: not enabled!");
		return;
	}

	_core->getRaycaster()->setTerrainPointingEnabled(false);
}