#include "animation3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const bool Animation3dEditor::loadAnimation3dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
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
		string animation3dId;
		int partCount;
		int frameCount;

		auto iss = istringstream(line);

		iss
			>> animation3dId
			>> partCount
			>> frameCount;

		_loadedAnimation3dIds.push_back(animation3dId);
		sort(_loadedAnimation3dIds.begin(), _loadedAnimation3dIds.end());

		_fe3d->animation3d_create(animation3dId);

		for(int partIndex = 0; partIndex < partCount; partIndex++)
		{
			string partId;

			iss >> partId;

			if(partId == "?")
			{
				partId = "";
			}

			_fe3d->animation3d_createPart(animation3dId, partId);
		}

		const auto partIds = _fe3d->animation3d_getPartIds(animation3dId);

		for(int frameIndex = 0; frameIndex < frameCount; frameIndex++)
		{
			_fe3d->animation3d_createFrame(animation3dId, frameIndex);

			for(int partIndex = 0; partIndex < partCount; partIndex++)
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

				_fe3d->animation3d_setTargetTransformation(animation3dId, frameIndex, partIds[partIndex], targetTransformation);
				_fe3d->animation3d_setRotationOrigin(animation3dId, frameIndex, partIds[partIndex], rotationOrigin);
				_fe3d->animation3d_setSpeed(animation3dId, frameIndex, partIds[partIndex], speed);
				_fe3d->animation3d_setSpeedType(animation3dId, frameIndex, partIds[partIndex], SpeedType(speedType));
				_fe3d->animation3d_setTransformationType(animation3dId, frameIndex, partIds[partIndex], TransformationType(transformationType));
			}
		}
	}

	file.close();

	Logger::throwInfo("Animation3D editor data loaded");

	return true;
}