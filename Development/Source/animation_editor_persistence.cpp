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
				// Read the amount of model parts
				unsigned int modelPartCount;

				// Check if file has frame data left
				if (iss >> modelPartCount)
				{
					// Create frame
					AnimationFrame frame;

					// For every model part
					for (unsigned int i = 0; i < modelPartCount; i++)
					{
						// Temporary values
						string partName;
						Vec3 targetTransformation;
						float speed;
						int speedType;

						// Extract data
						iss >> partName >> targetTransformation.x >> targetTransformation.y >> targetTransformation.z >> speed >> speedType;
						
						// Questionmark means empty partname
						if (partName == "?")
						{
							partName = "";
						}

						// Add part to frame
						frame.targetTransformations.insert(make_pair(partName, targetTransformation));
						frame.speeds.insert(make_pair(partName, speed));
						frame.speedTypes.insert(make_pair(partName, AnimationSpeedType(speedType)));
					}

					// Add frame
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
					newAnimation->initialColor = _fe3d.gameEntity_getColor(newAnimation->previewModelID);
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
					// Write the amount of model parts
					file << animation->frames[i].targetTransformations.size();
					
					// Retrieve all partnames
					vector<string> partNames;
					for (auto& [key, val] : animation->frames[i].targetTransformations)
					{
						// Convert empty partname to questionmark
						if (key.empty())
						{
							partNames.push_back(key);
						}
						else
						{
							partNames.push_back("?");
						}
					}

					// For every model part
					unsigned int partIndex = 0;
					for (auto& partName : partNames)
					{
						// Retrieve data
						const auto& targetTransformation = animation->frames[i].targetTransformations[partName];
						const auto& speed = animation->frames[i].speeds[partName];
						const auto& speedType = static_cast<int>(animation->frames[i].speedTypes[partName]);

						// Write data
						file <<
							partName << " " <<
							targetTransformation.x << " " <<
							targetTransformation.y << " " <<
							targetTransformation.z << " " <<
							speed << " " <<
							speedType;

						// Add space
						if (partIndex != (partNames.size() - 1))
						{
							file << " ";
						}
						partIndex++;
					}

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
