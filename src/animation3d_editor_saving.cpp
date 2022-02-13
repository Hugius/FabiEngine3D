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
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\animation3d.fe3d");

	for(const auto& animationId : _loadedAnimationIds)
	{
		const auto frameCount = _fe3d->animation3d_getFrameCount(animationId);
		const auto partIds = _fe3d->animation3d_getPartIds(animationId);

		file
			<< animationId << " "
			<< _fe3d->animation3d_getPartIds(animationId).size() << " ";

		for(unsigned int frameIndex = 1; frameIndex < frameCount; frameIndex++)
		{
			for(unsigned int partIndex = 1; partIndex < partIds.size(); partIndex++)
			{
				auto partId = partIds[partIndex];
				auto targetTransformation = _fe3d->animation3d_getTargetTransformation(animationId, frameIndex, partId);
				auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(animationId, frameIndex, partId);
				auto speed = _fe3d->animation3d_getSpeed(animationId, frameIndex, partId);
				auto speedType = static_cast<int>(_fe3d->animation3d_getSpeedType(animationId, frameIndex, partId));
				auto transformationType = static_cast<int>(_fe3d->animation3d_getTransformationType(animationId, frameIndex, partId));

				if(partId.empty())
				{
					partId = "?";
				}

				file
					<< partId << " "
					<< targetTransformation.x << " "
					<< targetTransformation.y << " "
					<< targetTransformation.z << " "
					<< rotationOrigin.x << " "
					<< rotationOrigin.y << " "
					<< rotationOrigin.z << " "
					<< speed.x << " "
					<< speed.y << " "
					<< speed.z << " "
					<< speedType << " "
					<< transformationType;

				if(partIndex != (partIds.size() - 1))
				{
					file << " ";
				}
			}

			if(frameIndex != (frameCount - 1))
			{
				file << " ";
			}
		}

		file << endl;
	}

	file.close();

	Logger::throwInfo("Animation3D editor data saved");

	return true;
}