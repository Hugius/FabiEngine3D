#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Animation3dEditor::saveToFile() const
{
	if(!isLoaded())
	{
		return false;
	}

	if(getCurrentProjectId().empty())
	{
		Logger::throwError("Animation3dEditor::saveToFile");
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\animation3d.fe3d");

	for(const auto& animation : _animations)
	{
		auto animationId = animation->getId();
		auto previewModelId = animation->getPreviewModelId();

		if(!previewModelId.empty())
		{
			file << animationId << " " << previewModelId;

			if(animation->getFrames().size() > 1)
			{
				file << " ";

				for(unsigned int frameIndex = 1; frameIndex < animation->getFrames().size(); frameIndex++)
				{
					file << animation->getPartIds().size() << " ";

					unsigned int partIndex = 0;
					for(auto partId : animation->getPartIds())
					{
						auto frame = animation->getFrames()[frameIndex];
						auto targetTransformation = frame.getTargetTransformations().at(partId);
						auto rotationOrigin = frame.getRotationOrigins().at(partId);
						auto speed = frame.getSpeeds().at(partId);
						auto speedType = static_cast<int>(frame.getSpeedTypes().at(partId));
						auto transformationType = static_cast<int>(frame.getTransformationTypes().at(partId));

						if(partId.empty())
						{
							partId = "?";
						}

						file <<
							partId << " " <<
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

						if(partIndex != (animation->getPartIds().size() - 1))
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

	Logger::throwInfo("Animation3D editor data saved!");

	return true;
}