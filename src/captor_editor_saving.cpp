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
		const auto size = _fe3d->captor_getBaseSize(captorId);
		const auto color = _fe3d->captor_getColor(captorId);

		file
			<< captorId
			<< " "
			<< size.x
			<< " "
			<< size.y
			<< " "
			<< size.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< endl;
	}

	file.close();

	Logger::throwInfo("CAPTOR editor data saved");

	return true;
}