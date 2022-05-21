#include "captor_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool CaptorEditor::saveCaptorsToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\data\\captor.fe3d");

	auto file = ofstream(filePath);

	for(const auto & captorId : _loadedCaptorIds)
	{
		const auto reflectionQuality = _fe3d->captor_getReflectionQuality(captorId);
		const auto refractionQuality = _fe3d->captor_getRefractionQuality(captorId);

		file
			<< captorId
			<< " "
			<< reflectionQuality
			<< " "
			<< refractionQuality
			<< endl;
	}

	file.close();

	Logger::throwInfo("Captor editor data saved");

	return true;
}