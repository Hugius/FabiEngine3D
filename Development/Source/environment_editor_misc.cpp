#include "environment_editor.hpp"

#include <algorithm>

void EnvironmentEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool EnvironmentEditor::isLoaded()
{
	return _isEditorLoaded;
}

void EnvironmentEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update wireframe rendering
			if (_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if (_fe3d.misc_isWireframeRenderingEnabled())
				{
					_fe3d.misc_disableWireframeRendering();
				}
				else
				{
					_fe3d.misc_enableWireframeRendering();
				}
			}

			// Update debug rendering
			if (_fe3d.input_isKeyPressed(InputType::KEY_H))
			{
				if (_fe3d.misc_isDebugRenderingEnabled())
				{
					_fe3d.misc_disableDebugRendering();
				}
				else
				{
					_fe3d.misc_enableDebugRendering();
				}
			}
		}
	}
}

void EnvironmentEditor::unloadSkyEntities()
{
	for (const auto& ID : _loadedSkyIDs)
	{
		if (_fe3d.skyEntity_isExisting(ID))
		{
			_fe3d.skyEntity_delete(ID);
		}
	}
}

void EnvironmentEditor::unloadTerrainEntities()
{
	for (const auto& ID : _loadedTerrainIDs)
	{
		if (_fe3d.terrainEntity_isExisting(ID))
		{
			_fe3d.terrainEntity_delete(ID);
		}
	}
}

void EnvironmentEditor::unloadWaterEntities()
{
	for (const auto& ID : _loadedWaterIDs)
	{
		if (_fe3d.waterEntity_isExisting(ID))
		{
			_fe3d.waterEntity_delete(ID);
		}
	}
}

const vector<string>& EnvironmentEditor::getLoadedSkyIDs()
{
	std::sort(_loadedSkyIDs.begin(), _loadedSkyIDs.end());
	return _loadedSkyIDs;
}

const vector<string>& EnvironmentEditor::getLoadedTerrainIDs()
{
	std::sort(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end());
	return _loadedTerrainIDs;
}

const vector<string>& EnvironmentEditor::getLoadedWaterIDs()
{
	std::sort(_loadedWaterIDs.begin(), _loadedWaterIDs.end());
	return _loadedWaterIDs;
}