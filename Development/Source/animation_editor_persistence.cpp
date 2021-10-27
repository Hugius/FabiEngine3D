#include "animation_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

bool AnimationEditor::loadAnimationsFromFile(bool mustCheckPreviewModel)
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("AnimationEditor::loadAnimationsFromFile");
	}

	// Clear animations list from previous loads
	_animations.clear();

	// Compose file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: file `animation.fe3d` missing!");
		return false;
	}

	// Load animation file
	ifstream file(filePath);

	// Read animation data
	string line;
	while(getline(file, line))
	{
		// Data placeholders
		string animationID, previewModelID;

		// For file extraction
		istringstream iss(line);

		// Read data from file
		iss >> animationID >> previewModelID;

		// Create new animation
		auto newAnimation = make_shared<Animation>(animationID);
		newAnimation->setPreviewModelID(previewModelID);

		// Create default frame
		AnimationFrame defaultFrame;

		// Check if there is any more content in line
		string temp;
		if(iss >> temp)
		{
			// For file extraction
			iss = istringstream(line);

			// Read data from file
			iss >> animationID >> previewModelID;

			// Read frame data
			vector<AnimationFrame> customFrames;
			while(true)
			{
				// Check if file has frame data left
				unsigned int modelPartCount;
				if(iss >> modelPartCount)
				{
					// Create custom frame
					AnimationFrame customFrame;

					// For every model part
					for(unsigned int i = 0; i < modelPartCount; i++)
					{
						// Temporary values
						string partID;
						Vec3 targetTransformation, rotationOrigin, speed;
						int speedType, transformationType;

						// Read data from file
						iss >> partID >> targetTransformation.x >> targetTransformation.y >> targetTransformation.z >>
							rotationOrigin.x >> rotationOrigin.y >> rotationOrigin.z >>
							speed.x >> speed.y >> speed.z >>
							speedType >> transformationType;

						// Questionmark means empty partID
						if(partID == "?")
						{
							partID = "";
						}

						// Add part to animation only once
						if(customFrames.empty())
						{
							newAnimation->addPart(partID, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
						}

						// Add part to default frame only once
						if(customFrames.empty())
						{
							defaultFrame.addPart(partID, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), AnimationSpeedType::LINEAR, TransformationType::MOVEMENT);
						}

						// Add part to custom frame
						customFrame.addPart(partID, targetTransformation, rotationOrigin, speed, AnimationSpeedType(speedType), TransformationType(transformationType));
					}

					// Add custom frame
					customFrames.push_back(customFrame);
				}
				else
				{
					break;
				}
			}

			// Add default frame to animation
			newAnimation->addFrame(defaultFrame);

			// Add custom frames to animation
			for(const auto& customFrame : customFrames)
			{
				newAnimation->addFrame(customFrame);
			}
		}

		// Only if loading animations in editor
		if(mustCheckPreviewModel)
		{
			// Check if preview model is still existing
			if(_fe3d.modelEntity_isExisting(newAnimation->getPreviewModelID()))
			{
				// Check if parts are present
				bool hasAllParts = true;
				for(const auto& partID : newAnimation->getPartIDs())
				{
					// Part cannot be empty
					if(!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(newAnimation->getPreviewModelID(), partID);
					}
				}

				// Check if preview model still has all the parts
				if(hasAllParts)
				{
					newAnimation->setInitialSize(_fe3d.modelEntity_getBaseSize(newAnimation->getPreviewModelID()));
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
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("AnimationEditor::saveAnimationsToFile");
	}

	// Compose full file path
	const string filePath = Tools::getRootDirectory() + (_fe3d.application_isExported() ? "" :
														 ("projects\\" + _currentProjectID)) + "\\data\\animation.fe3d";

	// Create or overwrite animation file
	ofstream file(filePath);

	// Write animation data
	for(const auto& animation : _animations)
	{
		// Only if animation has data
		if(!animation->getPreviewModelID().empty() || !animation->getOldPreviewModelID().empty())
		{
			// Retrieve all values
			auto animationID = animation->getID();
			auto previewModelID = animation->getPreviewModelID().empty() ? animation->getOldPreviewModelID() : animation->getPreviewModelID();

			// Write data to file
			file << animationID << " " << previewModelID;

			// Check if animation has custom frames
			if(animation->getFrames().size() > 1)
			{
				// Add space
				file << " ";

				// For every frame
				for(unsigned int frameIndex = 1; frameIndex < animation->getFrames().size(); frameIndex++)
				{
					// Write the amount of model parts
					file << animation->getPartIDs().size() << " ";

					// For every model part
					unsigned int partIndex = 0;
					for(auto partID : animation->getPartIDs())
					{
						// Retrieve data
						auto frame = animation->getFrames()[frameIndex];
						auto targetTransformation = frame.getTargetTransformations().at(partID);
						auto rotationOrigin = frame.getRotationOrigins().at(partID);
						auto speed = frame.getSpeeds().at(partID);
						auto speedType = static_cast<int>(frame.getSpeedTypes().at(partID));
						auto transformationType = static_cast<int>(frame.getTransformationTypes().at(partID));

						// Questionmark means empty partID
						if(partID.empty())
						{
							partID = "?";
						}

						// Write data to file
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
						if(partIndex != (animation->getPartIDs().size() - 1))
						{
							file << " ";
						}
						partIndex++;
					}

					// Add space
					if(frameIndex != (animation->getFrames().size() - 1))
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