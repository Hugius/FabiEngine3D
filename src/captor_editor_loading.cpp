#include "captor_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const bool CaptorEditor::loadCaptorsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\captor.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `captor.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string captorId;
		int reflectionQuality;
		int refractionQuality;

		auto iss = istringstream(line);

		iss
			>> captorId
			>> reflectionQuality
			>> refractionQuality;

		_fe3d->captor_create(captorId);
		_fe3d->captor_setReflectionQuality(captorId, reflectionQuality);
		_fe3d->captor_setRefractionQuality(captorId, refractionQuality);

		_loadedCaptorIds.push_back(captorId);

		sort(_loadedCaptorIds.begin(), _loadedCaptorIds.end());
	}

	file.close();

	Logger::throwInfo("Captor editor data loaded");

	return true;
}