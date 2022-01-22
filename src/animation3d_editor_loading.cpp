#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const bool Animation3dEditor::loadFromFile(bool mustCheckPreviewModel)
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Animation3dEditor::loadFromFile");
	}

	_animations.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\animation3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `animation3d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string animationID;
		string previewModelID;

		istringstream iss(line);

		iss >> animationID >> previewModelID;

		auto newAnimation = make_shared<Animation3d>(animationID);
		newAnimation->setPreviewModelID(previewModelID);

		Animation3dFrame defaultFrame;

		newAnimation->addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
		defaultFrame.addPart("", fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);

		auto partIDs = _fe3d->model_getPartIDs(previewModelID);
		if(partIDs.size() > 1)
		{
			for(const auto& partID : partIDs)
			{
				newAnimation->addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));

				defaultFrame.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
			}
		}

		newAnimation->addFrame(defaultFrame);

		string temp;
		if(iss >> temp)
		{
			iss = istringstream(line);

			iss >> animationID >> previewModelID;

			vector<Animation3dFrame> customFrames;
			while(true)
			{
				unsigned int modelPartCount;
				if(iss >> modelPartCount)
				{
					Animation3dFrame customFrame;

					for(unsigned int i = 0; i < modelPartCount; i++)
					{
						string partID;
						fvec3 targetTransformation, rotationOrigin, speed;
						int speedType, transformationType;

						iss >> partID >> targetTransformation.x >> targetTransformation.y >> targetTransformation.z >>
							rotationOrigin.x >> rotationOrigin.y >> rotationOrigin.z >>
							speed.x >> speed.y >> speed.z >>
							speedType >> transformationType;

						if(partID == "?")
						{
							partID = "";
						}

						if(customFrames.empty())
						{
							newAnimation->addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f));
						}

						if(customFrames.empty())
						{
							defaultFrame.addPart(partID, fvec3(0.0f), fvec3(0.0f), fvec3(0.0f), Animation3dSpeedType::LINEAR, TransformationType::MOVEMENT);
						}

						customFrame.addPart(partID, targetTransformation, rotationOrigin, speed, Animation3dSpeedType(speedType), TransformationType(transformationType));
					}

					customFrames.push_back(customFrame);
				}
				else
				{
					break;
				}
			}

			for(const auto& customFrame : customFrames)
			{
				newAnimation->addFrame(customFrame);
			}
		}

		if(mustCheckPreviewModel)
		{
			if(_fe3d->model_isExisting(newAnimation->getPreviewModelID()))
			{
				bool hasAllParts = true;
				for(const auto& partID : newAnimation->getPartIDs())
				{
					if(!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d->model_hasPart(newAnimation->getPreviewModelID(), partID);
					}
				}

				if(hasAllParts)
				{
					newAnimation->setInitialSize(_fe3d->model_getBaseSize(newAnimation->getPreviewModelID()));
				}
				else
				{
					Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->getID() + "\" does not have required animation parts anymore!");
					continue;
				}
			}
			else
			{
				Logger::throwWarning("Preview model of animation with ID \"" + newAnimation->getID() + "\" not existing anymore!");
				continue;
			}
		}

		_animations.push_back(newAnimation);
	}

	file.close();

	Logger::throwInfo("Animation3D editor data loaded!");

	return true;
}