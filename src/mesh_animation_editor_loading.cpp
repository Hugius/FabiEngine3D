#include "mesh_animation_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const bool MeshAnimationEditor::loadAnimationsFromFile(bool mustCheckPreviewModel)
{
	// Error checking
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("AnimationEditor::loadAnimationsFromFile");
	}

	// Clear animations list from previous loads
	_animations.clear();

	// Compose file path
	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\mesh_animation.fe3d");

	// Warning checking
	if(!Tools::isFileExisting(filePath))
	{
		Logger::throwWarning("Project corrupted: file `mesh_animation.fe3d` missing!");
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
		auto newAnimation = make_shared<MeshAnimation>(animationID);
		newAnimation->setPreviewModelID(previewModelID);

		// Create default frame
		MeshAnimationFrame defaultFrame;

		// Add default part
		newAnimation->addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
		defaultFrame.addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), MeshAnimationSpeedType::LINEAR, TransformationType::MOVEMENT);

		// Add custom parts
		auto partIDs = _fe3d.model_getPartIDs(previewModelID);
		if (partIDs.size() > 1)
		{
			// Iterate through parts
			for (const auto& partID : partIDs)
			{
				// Add part to animation
				newAnimation->addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));

				// Add part to frame
				defaultFrame.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), MeshAnimationSpeedType::LINEAR, TransformationType::MOVEMENT);
			}
		}

		// Add default frame to animation
		newAnimation->addFrame(defaultFrame);

		// Check if there is any more content in line
		string temp;
		if(iss >> temp)
		{
			// For file extraction
			iss = istringstream(line);

			// Read data from file
			iss >> animationID >> previewModelID;

			// Read frame data
			vector<MeshAnimationFrame> customFrames;
			while(true)
			{
				// Check if file has frame data left
				unsigned int modelPartCount;
				if(iss >> modelPartCount)
				{
					// Create custom frame
					MeshAnimationFrame customFrame;

					// Iterate through model parts
					for(unsigned int i = 0; i < modelPartCount; i++)
					{
						// Temporary values
						string partID;
						fvec3 targetTransformation, rotationOrigin, speed;
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
							newAnimation->addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
						}

						// Add part to default frame only once
						if(customFrames.empty())
						{
							defaultFrame.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), MeshAnimationSpeedType::LINEAR, TransformationType::MOVEMENT);
						}

						// Add part to custom frame
						customFrame.addPart(partID, targetTransformation, rotationOrigin, speed, MeshAnimationSpeedType(speedType), TransformationType(transformationType));
					}

					// Add custom frame
					customFrames.push_back(customFrame);
				}
				else
				{
					break;
				}
			}

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
			if(_fe3d.model_isExisting(newAnimation->getPreviewModelID()))
			{
				// Check if parts are present
				bool hasAllParts = true;
				for(const auto& partID : newAnimation->getPartIDs())
				{
					// Part cannot be empty
					if(!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d.model_hasPart(newAnimation->getPreviewModelID(), partID);
					}
				}

				// Check if preview model still has all the parts
				if(hasAllParts)
				{
					newAnimation->setInitialSize(_fe3d.model_getBaseSize(newAnimation->getPreviewModelID()));
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
	Logger::throwInfo("Mesh animation data loaded!");

	// Return
	return true;
}