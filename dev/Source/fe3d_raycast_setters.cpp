#include "fe3d.hpp"
#include "core_engine.hpp"

using std::numeric_limits;

void FabiEngine3D::raycast_enableTerrainPointing(float distance, float precision)
{
	if(_core->_raycaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to enable terrain raycast pointing: already enabled!");
		return;
	}

	_core->_raycaster.setTerrainPointingEnabled(true);
	_core->_raycaster.setTerrainPointingDistance(distance);
	_core->_raycaster.setTerrainPointingPrecision(precision);
}

void FabiEngine3D::raycast_disableTerrainPointing()
{
	if(!_core->_raycaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to disable terrain raycast pointing: not enabled!");
		return;
	}

	_core->_raycaster.setTerrainPointingEnabled(false);
}