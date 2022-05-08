#include "pointlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const bool PointlightEditor::loadPointlightsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\pointlight.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `pointlight.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string pointlightId;
		fvec3 size;
		fvec3 color;

		istringstream iss(line);

		iss
			>> pointlightId
			>> size.x
			>> size.y
			>> size.z
			>> color.r
			>> color.g
			>> color.b;

		_loadedPointlightIds.push_back(pointlightId);
		sort(_loadedPointlightIds.begin(), _loadedPointlightIds.end());

		_fe3d->pointlight_create(pointlightId, false);
		_fe3d->pointlight_setVisible(pointlightId, false);
		_fe3d->pointlight_setBaseSize(pointlightId, size);
		_fe3d->pointlight_setColor(pointlightId, color);
	}

	file.close();

	Logger::throwInfo("Pointlight editor data loaded");

	return true;
}