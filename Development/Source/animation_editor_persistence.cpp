#include "animation_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

bool AnimationEditor::loadAnimationsFromFile(bool mustCheckPreviewModel)
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("AnimationEditor::loadAnimationsFromFile");
	}

	// Clear animations list from previous loads
	_animations.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `animation.fe3d` missing!");
		return false;
	}

	// Load animation file
	ifstream file(filePath);

	// Read animation data
	string line;
	while (getline(file, line))
	{
		// Placeholder variables
		string animationID, previewModelID;

		// For file extraction
		istringstream iss(line);

		// Extract general data from file
		iss >> animationID >> previewModelID;

		// Create new animation
		auto newAnimation = make_shared<Animation>(animationID);
		newAnimation->setPreviewModelID(previewModelID);

		// Check if there is any more content in line
		string temp;
		if (iss >> temp)
		{
			// Start reading again
			iss = istringstream(line);
			iss >> animationID >> previewModelID;

			// Clear default empty partID
			newAnimation->setPartIDs({});
			newAnimation->setTotalMovements({});
			newAnimation->setTotalRotations({});
			newAnimation->setTotalScalings({});

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
						int speedType, transformationType;

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
						frame.addTargetTransformation(partID, targetTransformation);
						frame.addRotationOrigin(partID, rotationOrigin);
						frame.addSpeed(partID, speed);
						frame.addSpeedType(partID, AnimationSpeedType(speedType));
						frame.addTransformationType(partID, TransformationType(transformationType));

						// Add all partIDs only once
						if (frames.empty())
						{
							newAnimation->addPartID(partID);

							// Also add total transformation for each partID
							newAnimation->addTotalMovement(partID, Vec3(0.0f));
							newAnimation->addTotalRotation(partID, Vec3(0.0f));
							newAnimation->addTotalScaling(partID, Vec3(0.0f));
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
			auto currentFrames = newAnimation->getFrames();
			currentFrames.insert(currentFrames.end(), frames.begin(), frames.end());
			newAnimation->setFrames(currentFrames);
		}

		// Only if loading animations in editor
		if (mustCheckPreviewModel)
		{
			// Check if preview model is still existing
			if (_fe3d.modelEntity_isExisting(newAnimation->getPreviewModelID()))
			{
				// Check if parts are present
				bool hasAllParts = true;
				for (const auto& partID : newAnimation->getPartIDs())
				{
					// Part cannot be empty
					if (!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(newAnimation->getPreviewModelID(), partID);
					}
				}

				// Check if preview model still has all the parts
				if (hasAllParts)
				{
					newAnimation->setInitialSize(_fe3d.modelEntity_getSize(newAnimation->getPreviewModelID()));
				}
				else // Clear preview model
				{
					newAnimation->setOldPreviewModelID(newAnimation->getPreviewModelID());
					newAnimation->setPreviewModelID("");
					Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->getID() + "\" does not have required animation parts anymore!");
				}
			}
			else // Clear preview model
			{
				newAnimation->setOldPreviewModelID(newAnimation->getPreviewModelID());
				newAnimation->setPreviewModelID("");
				Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->getID() + "\" not existing anymore!");
			}
		}

		// Add new animation
		_animations.push_back(newAnimation);
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Animation data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool AnimationEditor::saveAnimationsToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("AnimationEditor::saveAnimationsToFile");
	}

	// Compose full file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

	// Create or overwrite animation file
	ofstream file(filePath);

	// Write animation data
	for (const auto& animation : _animations)
	{
		// Only if animation has data
		if (!animation->getPreviewModelID().empty() || !animation->getOldPreviewModelID().empty())
		{
			// Retrieve all values
			auto animationID = animation->getID();
			auto previewModelID = animation->getPreviewModelID().empty() ? animation->getOldPreviewModelID() : animation->getPreviewModelID();

			// Export  general data
			file <<
				animationID << " " <<
				previewModelID;

			// Export frame data
			if (animation->getFrames().size() > 1)
			{
				// Add space
				file << " ";

				// For every frame
				for (unsigned int frameIndex = 1; frameIndex < animation->getFrames().size(); frameIndex++)
				{
					// Write the amount of model parts
					file << animation->getPartIDs().size() << " ";

					// For every model part
					unsigned int partIndex = 0;
					for (auto partID : animation->getPartIDs())
					{
						// Retrieve data
						auto frame = animation->getFrames()[frameIndex];
						auto targetTransformation = frame.getTargetTransformations().at(partID);
						auto rotationOrigin = frame.getRotationOrigins().at(partID);
						auto speed = frame.getSpeeds().at(partID);
						auto speedType = static_cast<int>(frame.getSpeedTypes().at(partID));
						auto transformationType = static_cast<int>(frame.getTransformationTypes().at(partID));

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
						if (partIndex != (animation->getPartIDs().size() - 1))
						{
							file << " ";
						}
						partIndex++;
					}

					// Add space
					if (frameIndex != (animation->getFrames().size() - 1))
					{
						file << " ";
					}
				}
			}

			// Add newline
			file << endl;
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Animation data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}