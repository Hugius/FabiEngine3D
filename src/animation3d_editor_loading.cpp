#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const bool Animation3dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\animation3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `animation3d.fe3d` does not exist");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string animationId;
		unsigned int partCount;
		unsigned int frameCount;

		istringstream iss(line);

		iss
			>> animationId
			>> partCount
			>> frameCount;

		_loadedAnimationIds.push_back(animationId);
		sort(_loadedAnimationIds.begin(), _loadedAnimationIds.end());

		_fe3d->animation3d_create(animationId);

		for(unsigned int partIndex = 0; partIndex < partCount; partIndex++)
		{
			string partId;

			iss >> partId;

			if(partId == "?")
			{
				partId = "";
			}

			_fe3d->animation3d_createPart(animationId, partId);
		}

		const auto partIds = _fe3d->animation3d_getPartIds(animationId);

		for(unsigned int frameIndex = 0; frameIndex < frameCount; frameIndex++)
		{
			_fe3d->animation3d_createFrame(animationId, frameIndex);

			for(unsigned int partIndex = 0; partIndex < partCount; partIndex++)
			{
				fvec3 targetTransformation;
				fvec3 rotationOrigin;
				fvec3 speed;
				int speedType;
				int transformationType;

				iss
					>> targetTransformation.x
					>> targetTransformation.y
					>> targetTransformation.z
					>> rotationOrigin.x
					>> rotationOrigin.y
					>> rotationOrigin.z
					>> speed.x
					>> speed.y
					>> speed.z
					>> speedType
					>> transformationType;

				_fe3d->animation3d_setTargetTransformation(animationId, frameIndex, partIds[partIndex], targetTransformation);
				_fe3d->animation3d_setRotationOrigin(animationId, frameIndex, partIds[partIndex], rotationOrigin);
				_fe3d->animation3d_setSpeed(animationId, frameIndex, partIds[partIndex], speed);
				_fe3d->animation3d_setSpeedType(animationId, frameIndex, partIds[partIndex], Animation3dSpeedType(speedType));
				_fe3d->animation3d_setTransformationType(animationId, frameIndex, partIds[partIndex], TransformationType(transformationType));
			}
		}
	}

	file.close();

	Logger::throwInfo("Animation3D editor data loaded");

	return true;
}