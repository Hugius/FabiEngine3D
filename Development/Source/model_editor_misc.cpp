#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_loadDiffuseMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadEmissionMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\emission_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setEmissionMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadReflectionMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\reflection_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setReflectionMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::_loadNormalMap()
{
	// Get the chosen filename
	const string rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
	const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

	// Check if user chose a filename
	if (filePath != "")
	{
		// Check if user did not switch directory
		if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
		{
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.modelEntity_setNormalMap(_currentModelID, newFilePath);
		}
		else
		{
			Logger::throwWarning("Invalid filepath, directory switching not allowed!");
		}
	}
}

void ModelEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool ModelEditor::isLoaded()
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedModelIDs()
{
	sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}