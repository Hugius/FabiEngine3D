#include "animation_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool AnimationEditor::saveAnimationsToFile() const
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
	const string filePath = Tools::getRootDirectoryPath() + (Config::getInst().isApplicationExported() ? "" :
														 ("game\\" + _currentProjectID)) + "\\data\\animation.fe3d";

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