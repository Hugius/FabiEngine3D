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
			string animationID, previewModelID;
			int transformationType;

			// For file extraction
			std::istringstream iss(line);

			// Extract general data from file
			iss >> animationID >> previewModelID >> transformationType;

			// Extract frame data from file
			vector<AnimationFrame> frames;
			while (true)
			{
				// Temporary values
				Vec3 targetTransformation;
				float speed;
				int speedType;

				// Check if file has frame data left
				if (iss >> targetTransformation.x)
				{
					iss >> targetTransformation.y >> targetTransformation.z >> speed >> speedType;
					AnimationFrame frame;
					frame.targetTransformation = targetTransformation;
					frame.speed = speed;
					frame.speedType = AnimationSpeedType(speedType);
					frames.push_back(frame);
				}
				else
				{
					break;
				}
			}

			// Create new animation
			auto newAnimation = make_shared<Animation>(animationID);
			newAnimation->previewModelID = previewModelID;
			newAnimation->transformationType = TransformationType(transformationType);
			newAnimation->frames.insert(newAnimation->frames.end(), frames.begin(), frames.end());

			// Check if preview model is still existing for the editor
			if (_isEditorLoading)
			{
				if (_fe3d.gameEntity_isExisting(newAnimation->previewModelID))
				{
					newAnimation->initialTranslation = _fe3d.gameEntity_getPosition(newAnimation->previewModelID);
					newAnimation->initialRotation = _fe3d.gameEntity_getRotation(newAnimation->previewModelID);
					newAnimation->initialScaling = _fe3d.gameEntity_getSize(newAnimation->previewModelID);
				}
				else // Clear preview model
				{
					newAnimation->previewModelID = "";
					_fe3d.logger_throwWarning("Preview model of animation with ID \"" + newAnimation->ID + "\" not existing anymore!");
				}
			}

			// Add new animation
			_animations.push_back(newAnimation);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Audio data from project \"" + _currentProjectName + "\" loaded!");
	}
}

void AnimationEditor::stopAllAnimations()
{
	_playingAnimations.clear();
}

void AnimationEditor::saveAnimationsToFile()
{
	if (_isEditorLoaded)
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
			auto transformationType = static_cast<int>(animation->transformationType);

			// Export  general data
			file <<
				animationID << " " <<
				previewModelID << " " <<
				transformationType;

			// Add space
			if (animation->frames.size() > 1)
			{
				file << " ";
			}

			// Export frame data
			if (animation->frames.size() > 1)
			{
				for (unsigned int i = 1; i < animation->frames.size(); i++)
				{
					auto targetTransformation = animation->frames[i].targetTransformation;
					auto speed = animation->frames[i].speed;
					auto speedType = static_cast<int>(animation->frames[i].speedType);

					file <<
						targetTransformation.x << " " <<
						targetTransformation.y << " " <<
						targetTransformation.z << " " <<
						speed << " " <<
						speedType;

					// Add space
					if (i != (animation->frames.size() - 1))
					{
						file << " ";
					}
				}
			}

			// Add newline
			file << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Animation data from project \"" + _currentProjectName + "\" saved!");
	}
}
