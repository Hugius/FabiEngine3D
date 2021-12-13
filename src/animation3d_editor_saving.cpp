#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Animation3dEditor::saveToFile() const
{
	// Editor must be loaded
	if(!_isEditorLoaded)
	{
		return false;
	}

	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("Animation3dEditor::saveToFile");
	}

	// Create or overwrite file
	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\animation3d.fe3d");

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

				// Iterate through frames
				for(unsigned int frameIndex = 1; frameIndex < animation->getFrames().size(); frameIndex++)
				{
					// Write the amount of model parts
					file << animation->getPartIDs().size() << " ";

					// Iterate through model parts
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
	Logger::throwInfo("3D animation data saved!");

	// Return
	return true;
}