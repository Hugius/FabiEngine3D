#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_loadDiffuseMap()
{
	// Get the chosen filename
	const auto rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

	// Validate target directory
	if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
	{
		Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
		return;
	}

	// Validate chosen file
	const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
	if (filePath.empty())
	{
		return;
	}

	// Validate directory of file
	if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
		filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
	{
		Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
		return;
	}

	// Set diffuse map
	const string finalFilePath = filePath.substr(rootDirectory.size());
	_fe3d.misc_clearTextureCache2D(finalFilePath);
	_fe3d.modelEntity_setDiffuseMap(_currentModelID, finalFilePath);
}

void ModelEditor::_loadEmissionMap()
{
	// Get the chosen filename
	const auto rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\emission_maps\\");

	// Validate target directory
	if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
	{
		Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
		return;
	}

	// Validate chosen file
	const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
	if (filePath.empty())
	{
		return;
	}

	// Validate directory of file
	if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
		filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
	{
		Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
		return;
	}

	// Set emission map
	const string finalFilePath = filePath.substr(rootDirectory.size());
	_fe3d.misc_clearTextureCache2D(finalFilePath);
	_fe3d.modelEntity_setEmissionMap(_currentModelID, finalFilePath);
}

void ModelEditor::_loadReflectionMap()
{
	// Get the chosen filename
	const auto rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\reflection_maps\\");

	// Validate target directory
	if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
	{
		Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
		return;
	}

	// Validate chosen file
	const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
	if (filePath.empty())
	{
		return;
	}

	// Validate directory of file
	if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
		filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
	{
		Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
		return;
	}

	// Set reflection map
	const string finalFilePath = filePath.substr(rootDirectory.size());
	_fe3d.misc_clearTextureCache2D(finalFilePath);
	_fe3d.modelEntity_setReflectionMap(_currentModelID, finalFilePath);
}

void ModelEditor::_loadNormalMap()
{
	// Get the chosen filename
	const auto rootDirectory = _fe3d.misc_getRootDirectory();
	const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

	// Validate target directory
	if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
	{
		Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
		return;
	}

	// Validate chosen file
	const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
	if (filePath.empty())
	{
		return;
	}

	// Validate directory of file
	if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
		filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
	{
		Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
		return;
	}

	// Set normal map
	const string finalFilePath = filePath.substr(rootDirectory.size());
	_fe3d.misc_clearTextureCache2D(finalFilePath);
	_fe3d.modelEntity_setNormalMap(_currentModelID, finalFilePath);
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