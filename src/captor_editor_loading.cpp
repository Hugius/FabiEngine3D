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
		fvec3 size;
		fvec3 color;

		auto iss = istringstream(line);

		iss
			>> captorId
			>> size.x
			>> size.y
			>> size.z
			>> color.r
			>> color.g
			>> color.b;

		_fe3d->captor_create(captorId, false);
		_fe3d->captor_setVisible(captorId, false);
		_fe3d->captor_setBaseSize(captorId, size);
		_fe3d->captor_setColor(captorId, color);

		_loadedCaptorIds.push_back(captorId);

		sort(_loadedCaptorIds.begin(), _loadedCaptorIds.end());
	}

	file.close();

	Logger::throwInfo("CAPTOR editor data loaded");

	return true;
}