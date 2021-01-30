#include "animation_editor.hpp"

#include <fstream>
#include <algorithm>

void AnimationEditor::loadAnimationsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		_fe3d.logger_throwError("No current project loaded --> AnimationEditor::loadAnimationsFromFile()");
	}

	// Clear names list from previous loads
	_animations.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectID + "\\data\\animation.fe3d";

	// Check if animation file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string animationID, previewModelID;

			// For file extraction
			std::istringstream iss(line);

			// Extract general data from file
			iss >> animationID >> previewModelID;

			// Create new animation
			auto newAnimation = make_shared<Animation>(animationID);
			newAnimation->previewModelID = previewModelID;

			// Check if there is any more content in line
			string temp;
			if (iss >> temp)
			{
				// Start reading again
				iss = std::istringstream(line);
				iss >> animationID >> previewModelID;

				// Clear default empty partname
				newAnimation->partNames.clear();
				newAnimation->totalTranslations.clear();
				newAnimation->totalRotations.clear();
				newAnimation->totalScalings.clear();

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
							Vec3 targetTransformation, rotationOrigin;
							float speed;
							int speedType, transformationType;;

							// Extract data
							iss >> partName >> targetTransformation.x >> targetTransformation.y >> targetTransformation.z >>
								rotationOrigin.x >> rotationOrigin.y >> rotationOrigin.z >> speed >> speedType >> transformationType;

							// Questionmark means empty partname
							if (partName == "?")
							{
								partName = "";
							}

							// Add part to frame
							frame.targetTransformations.insert(make_pair(partName, targetTransformation));
							frame.rotationOrigins.insert(make_pair(partName, rotationOrigin));
							frame.speeds.insert(make_pair(partName, speed));
							frame.speedTypes.insert(make_pair(partName, AnimationSpeedType(speedType)));
							frame.transformationTypes.insert(make_pair(partName, TransformationType(transformationType)));

							// Add all partnames 1 time only
							if (frames.empty())
							{
								newAnimation->partNames.push_back(partName);

								// Also add total transformation for each partname
								newAnimation->totalTranslations.insert(make_pair(partName, Vec3(0.0f)));
								newAnimation->totalRotations.insert(make_pair(partName, Vec3(0.0f)));
								newAnimation->totalScalings.insert(make_pair(partName, Vec3(0.0f)));
							}
						}

						// Add frame
						frames.push_back(frame);
					}
					else
					{
						break;
					}
				}

				// Add frames to animation
				newAnimation->frames.insert(newAnimation->frames.end(), frames.begin(), frames.end());
			}

			// Only if loading animations in editor
			if (_isEditorLoading)
			{
				// Check if preview model is still existing
				if (_fe3d.gameEntity_isExisting(newAnimation->previewModelID))
				{
					// Check if parts are present
					bool hasAllParts = true;
					for (auto& partName : newAnimation->partNames)
					{
						// Part cannot be empty
						if (!partName.empty())
						{
							hasAllParts = hasAllParts && _fe3d.gameEntity_hasPart(newAnimation->previewModelID, partName);
						}
					}

					// Check if preview model still has all the parts
					if (hasAllParts)
					{
						newAnimation->initialScaling = _fe3d.gameEntity_getSize(newAnimation->previewModelID);
						newAnimation->initialColor = _fe3d.gameEntity_getColor(newAnimation->previewModelID);
					}
					else // Clear preview model
					{
						newAnimation->oldPreviewModelID = newAnimation->previewModelID;
						newAnimation->previewModelID = "";
						_fe3d.logger_throwWarning("Preview model of animation with ID \"" + newAnimation->ID + "\" does not have required animation parts anymore!");
					}
				}
				else // Clear preview model
				{
					newAnimation->oldPreviewModelID = newAnimation->previewModelID;
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
		_fe3d.logger_throwInfo("Animation data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: animation.fe3d missing!");
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
		if (_currentProjectID == "")
		{
			_fe3d.logger_throwError("No current project loaded --> AnimationEditor::saveAnimationsToFile()");
		}

		// Compose full file path
		string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectID + "\\data\\animation.fe3d";

		// Create or overwrite animation file
		std::ofstream file;
		file.open(filePath);

		// Write animation data into file
		for (auto& animation : _animations)
		{
			// Only if animation has data
			if (!animation->previewModelID.empty() || !animation->oldPreviewModelID.empty())
			{
				// Retrieve all values
				auto animationID = animation->ID;
				auto previewModelID = animation->previewModelID.empty() ? animation->oldPreviewModelID : animation->previewModelID;

				// Export  general data
				file <<
					animationID << " " <<
					previewModelID;

				// Export frame data
				if (animation->frames.size() > 1)
				{
					// Add space
					file << " ";

					// For every frame
					for (unsigned int i = 1; i < animation->frames.size(); i++)
					{
						// Write the amount of model parts
						file << animation->partNames.size() << " ";

						// For every model part
						unsigned int partIndex = 0;
						for (auto partName : animation->partNames)
						{
							// Retrieve data
							const auto& targetTransformation = animation->frames[i].targetTransformations[partName];
							const auto& rotationOrigin = animation->frames[i].rotationOrigins[partName];
							const auto& speed = animation->frames[i].speeds[partName];
							const auto& speedType = static_cast<int>(animation->frames[i].speedTypes[partName]);
							const auto& transformationType = static_cast<int>(animation->frames[i].transformationTypes[partName]);

							// Questionmark means empty partname
							if (partName.empty())
							{
								partName = "?";
							}

							// Write data
							file <<
								partName << " " <<
								targetTransformation.x << " " <<
								targetTransformation.y << " " <<
								targetTransformation.z << " " <<
								rotationOrigin.x << " " <<
								rotationOrigin.y << " " <<
								rotationOrigin.z << " " <<
								speed << " " <<
								speedType << " " <<
								transformationType;

							// Add space
							if (partIndex != (animation->partNames.size() - 1))
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
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Animation data from project \"" + _currentProjectID + "\" saved!");
	}
}