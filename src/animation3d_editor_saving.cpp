#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool Animation3dEditor::saveAnimationsToFile() const
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

	for(const auto & animationId : _loadedAnimation3dIds)
	{
		const auto partIds = _fe3d->animation3d_getPartIds(animationId);
		const auto partCount = partIds.size();
		const auto frameCount = _fe3d->animation3d_getFrameCount(animationId);

		file
			<< animationId
			<< " "
			<< partCount
			<< " "
			<< frameCount
			<< " ";

		for(auto partId : partIds)
		{
			if(partId.empty())
			{
				partId = "?";
			}

			file
				<< partId
				<< " ";
		}

		for(int frameIndex = 0; frameIndex < frameCount; frameIndex++)
		{
			for(int partIndex = 0; partIndex < partCount; partIndex++)
			{
				auto targetTransformation = _fe3d->animation3d_getTargetTransformation(animationId, frameIndex, partIds[partIndex]);
				auto rotationOrigin = _fe3d->animation3d_getRotationOrigin(animationId, frameIndex, partIds[partIndex]);
				auto speed = _fe3d->animation3d_getSpeed(animationId, frameIndex, partIds[partIndex]);
				auto speedType = static_cast<int>(_fe3d->animation3d_getSpeedType(animationId, frameIndex, partIds[partIndex]));
				auto transformationType = static_cast<int>(_fe3d->animation3d_getTransformationType(animationId, frameIndex, partIds[partIndex]));

				file
					<< targetTransformation.x
					<< " "
					<< targetTransformation.y
					<< " "
					<< targetTransformation.z
					<< " "
					<< rotationOrigin.x
					<< " "
					<< rotationOrigin.y
					<< " "
					<< rotationOrigin.z
					<< " "
					<< speed.x
					<< " "
					<< speed.y
					<< " "
					<< speed.z
					<< " "
					<< speedType
					<< " "
					<< transformationType;

				if(partIndex != (partCount - 1))
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