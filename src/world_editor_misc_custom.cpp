#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::createCustomWorld(const string& ID)
{
	_customWorldID = ID;
	_hasCustomWorldLighting = false;
	_hasCustomWorldGraphics = false;
	_hasCustomWorldSky = false;
	_hasCustomWorldTerrain = false;
	_hasCustomWorldWater = false;
	_hasCustomWorldGraphics = false;
	_customWorldModelIDs.clear();
	_customWorldBillboardIDs.clear();
	_customWorldAabbIDs.clear();
	_customWorldSoundIDs.clear();
	_customWorldPointlightIDs.clear();
	_customWorldSpotlightIDs.clear();
}

void WorldEditor::addLightingToCustomWorld()
{
	if(!_customWorldID.empty())
	{
		_hasCustomWorldLighting = true;
	}
	else
	{
		Logger::throwWarning("Cannot add lighting to custom world!");
	}
}

void WorldEditor::addGraphicsToCustomWorld()
{
	if(!_customWorldID.empty())
	{
		_hasCustomWorldGraphics = true;
	}
	else
	{
		Logger::throwWarning("Cannot add graphics to custom world!");
	}
}

void WorldEditor::addSkyToCustomWorld()
{
	if(!_customWorldID.empty())
	{
		_hasCustomWorldSky = true;
	}
	else
	{
		Logger::throwWarning("Cannot add sky to custom world!");
	}
}

void WorldEditor::addTerrainToCustomWorld()
{
	if(!_customWorldID.empty())
	{
		_hasCustomWorldTerrain = true;
	}
	else
	{
		Logger::throwWarning("Cannot add terrain to custom world!");
	}
}

void WorldEditor::addWaterToCustomWorld()
{
	if(!_customWorldID.empty())
	{
		_hasCustomWorldWater = true;
	}
	else
	{
		Logger::throwWarning("Cannot add water to custom world!");
	}
}

void WorldEditor::addModelToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldModelIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add model to custom world!");
	}
}

void WorldEditor::addBillboardToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldBillboardIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add billboard to custom world!");
	}
}

void WorldEditor::addAabbToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldAabbIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add AABB to custom world!");
	}
}

void WorldEditor::addSoundToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldSoundIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add sound to custom world!");
	}
}

void WorldEditor::addPointlightToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldPointlightIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add pointlight to custom world!");
	}
}

void WorldEditor::addSpotlightToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldSpotlightIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add spotlight to custom world!");
	}
}

void WorldEditor::addReflectionToCustomWorld(const string& ID)
{
	if(!_customWorldID.empty())
	{
		_customWorldReflectionIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add reflection to custom world!");
	}
}