#include "animation_editor.hpp"

#include <fstream>

void AnimationEditor::loadAnimationsFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded!");
	}

	// Clear names list from previous loads
	_animations.clear();

	// Compose full folder path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\animation.fe3d";

	// Check if audio file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string name, audioPath;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
			iss >> name >> audioPath;

			// Perform empty string & space conversions
			//audioPath = (audioPath == "?") ? "" : audioPath;
			//std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

			//// Add audio name
			//_audioNames.push_back(name);
			//_fe3d.audioEntity_add2D(name, audioPath);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void AnimationEditor::saveAnimationsToFile()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite audio file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\animation.fe3d");

		// Write audio data into file
		for (auto& animation : _animations)
		{
			// Retrieve all values
			auto animationID = animation->ID;
			auto previewModelID = animation->previewModelID;
			auto initialTranslation = animation->initialTranslation;
			auto initialRotation = animation->initialRotation;
			auto initialScaling = animation->initialScaling;
			auto transformationType = static_cast<int>(animation->transformationType);

			// Export data
			file << 
				animationID << " " << 
				previewModelID << " " << 
				initialTranslation.x << " " <<
				initialTranslation.y << " " <<
				initialTranslation.z << " " <<
				initialRotation.x << " " <<
				initialRotation.y << " " <<
				initialRotation.z << " " <<
				initialScaling.x << " " <<
				initialScaling.y << " " <<
				initialScaling.z << " " <<
				transformationType << " " << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectName + "\" saved!");
	}
}
