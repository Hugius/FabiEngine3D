#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::createCustomWorld(const string& id)
{
	_customWorldId = id;
	_hasCustomWorldLighting = false;
	_hasCustomWorldGraphics = false;
	_hasCustomWorldSky = false;
	_hasCustomWorldTerrain = false;
	_hasCustomWorldWater = false;
	_hasCustomWorldGraphics = false;
	_customWorldModelIds.clear();
	_customWorldQuadIds.clear();
	_customWorldAabbIds.clear();
	_customWorldSoundIds.clear();
	_customWorldPointlightIds.clear();
	_customWorldSpotlightIds.clear();
}

void WorldEditor::addLightingToCustomWorld()
{
	if(!_customWorldId.empty())
	{
		_hasCustomWorldLighting = true;
	}
	else
	{
		Logger::throwWarning("Cannot add lighting to custom world");
	}
}

void WorldEditor::addGraphicsToCustomWorld()
{
	if(!_customWorldId.empty())
	{
		_hasCustomWorldGraphics = true;
	}
	else
	{
		Logger::throwWarning("Cannot add graphics to custom world");
	}
}

void WorldEditor::addSkyToCustomWorld()
{
	if(!_customWorldId.empty())
	{
		_hasCustomWorldSky = true;
	}
	else
	{
		Logger::throwWarning("Cannot add sky to custom world");
	}
}

void WorldEditor::addTerrainToCustomWorld()
{
	if(!_customWorldId.empty())
	{
		_hasCustomWorldTerrain = true;
	}
	else
	{
		Logger::throwWarning("Cannot add terrain to custom world");
	}
}

void WorldEditor::addWaterToCustomWorld()
{
	if(!_customWorldId.empty())
	{
		_hasCustomWorldWater = true;
	}
	else
	{
		Logger::throwWarning("Cannot add water to custom world");
	}
}

void WorldEditor::addModelToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldModelIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add model to custom world");
	}
}

void WorldEditor::addQuad3dToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldQuadIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add quad3d to custom world");
	}
}

void WorldEditor::addText3dToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldTextIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add text3d to custom world");
	}
}

void WorldEditor::addAabbToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldAabbIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add AABB to custom world");
	}
}

void WorldEditor::addSoundToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldSoundIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add sound to custom world");
	}
}

void WorldEditor::addPointlightToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldPointlightIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add pointlight to custom world");
	}
}

void WorldEditor::addSpotlightToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldSpotlightIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add spotlight to custom world");
	}
}

void WorldEditor::addReflectionToCustomWorld(const string& id)
{
	if(!_customWorldId.empty())
	{
		_customWorldReflectionIds.push_back(id);
	}
	else
	{
		Logger::throwWarning("Cannot add reflection to custom world");
	}
}