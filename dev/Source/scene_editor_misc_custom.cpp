#include "scene_editor.hpp"
#include "logger.hpp"

void SceneEditor::createCustomScene(const string& ID)
{
	_customSceneID = ID;
	_hasCustomSceneLighting = false;
	_hasCustomSceneGraphics = false;
	_hasCustomSceneSky = false;
	_hasCustomSceneTerrain = false;
	_hasCustomSceneWater = false;
	_hasCustomSceneGraphics = false;
	_customSceneModelIDs.clear();
	_customSceneBillboardIDs.clear();
	_customSceneAabbIDs.clear();
	_customSceneSoundIDs.clear();
	_customScenePointlightIDs.clear();
	_customSceneSpotlightIDs.clear();
}

void SceneEditor::addLightingToCustomScene()
{
	if(!_customSceneID.empty())
	{
		_hasCustomSceneLighting = true;
	}
	else
	{
		Logger::throwWarning("Cannot add lighting to custom scene!");
	}
}

void SceneEditor::addGraphicsToCustomScene()
{
	if(!_customSceneID.empty())
	{
		_hasCustomSceneGraphics = true;
	}
	else
	{
		Logger::throwWarning("Cannot add graphics to custom scene!");
	}
}

void SceneEditor::addSkyToCustomScene()
{
	if(!_customSceneID.empty())
	{
		_hasCustomSceneSky = true;
	}
	else
	{
		Logger::throwWarning("Cannot add sky to custom scene!");
	}
}

void SceneEditor::addTerrainToCustomScene()
{
	if(!_customSceneID.empty())
	{
		_hasCustomSceneTerrain = true;
	}
	else
	{
		Logger::throwWarning("Cannot add terrain to custom scene!");
	}
}

void SceneEditor::addWaterToCustomScene()
{
	if(!_customSceneID.empty())
	{
		_hasCustomSceneWater = true;
	}
	else
	{
		Logger::throwWarning("Cannot add water to custom scene!");
	}
}

void SceneEditor::addModelToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneModelIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add model to custom scene!");
	}
}

void SceneEditor::addBillboardToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneBillboardIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add billboard to custom scene!");
	}
}

void SceneEditor::addAabbToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneAabbIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add AABB to custom scene!");
	}
}

void SceneEditor::addSoundToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneSoundIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add sound to custom scene!");
	}
}

void SceneEditor::addPointlightToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customScenePointlightIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add pointlight to custom scene!");
	}
}

void SceneEditor::addSpotlightToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneSpotlightIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add spotlight to custom scene!");
	}
}

void SceneEditor::addReflectionToCustomScene(const string& ID)
{
	if(!_customSceneID.empty())
	{
		_customSceneReflectionIDs.push_back(ID);
	}
	else
	{
		Logger::throwWarning("Cannot add reflection to custom scene!");
	}
}