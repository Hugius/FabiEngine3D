#include "animation_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

void AnimationEditor::loadAnimationsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AnimationEditor::loadAnimationsFromFile() --> no current project loaded!");
	}

	// Clear names list from previous loads
	_animations.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

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

				// Clear default empty partID
				newAnimation->partIDs.clear();
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
							string partID;
							Vec3 targetTransformation, rotationOrigin, speed;
							int speedType, transformationType;;

							// Extract data
							iss >> partID >> targetTransformation.x >> targetTransformation.y >> targetTransformation.z >>
								rotationOrigin.x >> rotationOrigin.y >> rotationOrigin.z >> 
								speed.x >> speed.y >> speed.z >> 
								speedType >> transformationType;

							// Questionmark means empty partID
							if (partID == "?")
							{
								partID = "";
							}

							// Add part to frame
							frame.targetTransformations.insert(make_pair(partID, targetTransformation));
							frame.rotationOrigins.insert(make_pair(partID, rotationOrigin));
							frame.speeds.insert(make_pair(partID, speed));
							frame.speedTypes.insert(make_pair(partID, AnimationSpeedType(speedType)));
							frame.transformationTypes.insert(make_pair(partID, TransformationType(transformationType)));

							// Add all partIDs 1 time only
							if (frames.empty())
							{
								newAnimation->partIDs.push_back(partID);

								// Also add total transformation for each partID
								newAnimation->totalTranslations.insert(make_pair(partID, Vec3(0.0f)));
								newAnimation->totalRotations.insert(make_pair(partID, Vec3(0.0f)));
								newAnimation->totalScalings.insert(make_pair(partID, Vec3(0.0f)));
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
				if (_fe3d.modelEntity_isExisting(newAnimation->previewModelID))
				{
					// Check if parts are present
					bool hasAllParts = true;
					for (const auto& partID : newAnimation->partIDs)
					{
						// Part cannot be empty
						if (!partID.empty())
						{
							hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(newAnimation->previewModelID, partID);
						}
					}

					// Check if preview model still has all the parts
					if (hasAllParts)
					{
						newAnimation->initialScaling = _fe3d.modelEntity_getSize(newAnimation->previewModelID);
						newAnimation->initialColor = _fe3d.modelEntity_getColor(newAnimation->previewModelID);
					}
					else // Clear preview model
					{
						newAnimation->oldPreviewModelID = newAnimation->previewModelID;
						newAnimation->previewModelID = "";
						Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->ID + "\" does not have required animation parts anymore!");
					}
				}
				else // Clear preview model
				{
					newAnimation->oldPreviewModelID = newAnimation->previewModelID;
					newAnimation->previewModelID = "";
					Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->ID + "\" not existing anymore!");
				}
			}

			// Add new animation
			_animations.push_back(newAnimation);
		}

		// Close file
		file.close();

		// Logging
		Logger::throwInfo("Animation data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"animation.fe3d\" missing!");
	}
}

void AnimationEditor::saveAnimationsToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AnimationEditor::saveAnimationsToFile() --> no current project loaded!");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

	// Create or overwrite animation file
	std::ofstream file;
	file.open(filePath);

	// Write animation data into file
	for (const auto& animation : _animations)
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
					file << animation->partIDs.size() << " ";

					// For every model part
					unsigned int partIndex = 0;
					for (auto partID : animation->partIDs)
					{
						// Retrieve data
						const auto& targetTransformation = animation->frames[i].targetTransformations[partID];
						const auto& rotationOrigin = animation->frames[i].rotationOrigins[partID];
						const auto& speed = animation->frames[i].speeds[partID];
						const auto& speedType = static_cast<int>(animation->frames[i].speedTypes[partID]);
						const auto& transformationType = static_cast<int>(animation->frames[i].transformationTypes[partID]);

						// Questionmark means empty partID
						if (partID.empty())
						{
							partID = "?";
						}

						// Write data
						file <<
							partID << " " <<
							targetTransformation.x << " " <<
							targetTransformation.y << " " <<
							targetTransformation.z << " " <<
							rotationOrigin.x << " " <<
							rotationOrigin.y << " " <<
							rotationOrigin.z << " " <<
							speed.x << " " <<
							speed.y << " " <<
							speed.z << " " <<
							speedType << " " <<
							transformationType;

						// Add space
						if (partIndex != (animation->partIDs.size() - 1))
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
	Logger::throwInfo("Animation data from project \"" + _currentProjectID + "\" saved!");
}