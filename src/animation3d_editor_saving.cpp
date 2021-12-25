#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Animation3dEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("Animation3dEditor::saveToFile");
	}

	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\animation3d.fe3d");

	for(const auto& animation : _animations)
	{
		auto animationID = animation->getID();
		auto previewModelID = animation->getPreviewModelID();

		if(!previewModelID.empty())
		{
			file << animationID << " " << previewModelID;

			if(animation->getFrames().size() > 1)
			{
				file << " ";

				for(unsigned int frameIndex = 1; frameIndex < animation->getFrames().size(); frameIndex++)
				{
					file << animation->getPartIDs().size() << " ";

					unsigned int partIndex = 0;
					for(auto partID : animation->getPartIDs())
					{
						auto frame = animation->getFrames()[frameIndex];
						auto targetTransformation = frame.getTargetTransformations().at(partID);
						auto rotationOrigin = frame.getRotationOrigins().at(partID);
						auto speed = frame.getSpeeds().at(partID);
						auto speedType = static_cast<int>(frame.getSpeedTypes().at(partID));
						auto transformationType = static_cast<int>(frame.getTransformationTypes().at(partID));

						if(partID.empty())
						{
							partID = "?";
						}

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

						if(partIndex != (animation->getPartIDs().size() - 1))
						{
							file << " ";
						}
						partIndex++;
					}

					if(frameIndex != (animation->getFrames().size() - 1))
					{
						file << " ";
					}
				}
			}

			file << endl;
		}
	}

	file.close();

	Logger::throwInfo("Animation3D data saved!");

	return true;
}