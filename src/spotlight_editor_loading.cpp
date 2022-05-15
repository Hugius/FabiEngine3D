#include "spotlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const bool SpotlightEditor::loadSpotlightsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\spotlight.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `spotlight.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string spotlightId;
		fvec3 color;
		float intensity;
		float angle;
		float distance;

		auto iss = istringstream(line);

		iss
			>> spotlightId
			>> color.r
			>> color.g
			>> color.b
			>> intensity
			>> angle
			>> distance;

		_fe3d->spotlight_create(spotlightId);
		_fe3d->spotlight_setVisible(spotlightId, false);
		_fe3d->spotlight_setPosition(spotlightId, SPOTLIGHT_POSITION);
		_fe3d->spotlight_setPitch(spotlightId, -90.0f);
		_fe3d->spotlight_setColor(spotlightId, color);
		_fe3d->spotlight_setIntensity(spotlightId, intensity);
		_fe3d->spotlight_setAngle(spotlightId, angle);
		_fe3d->spotlight_setDistance(spotlightId, distance);

		_loadedSpotlightIds.push_back(spotlightId);

		sort(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end());
	}

	file.close();

	Logger::throwInfo("Spotlight editor data loaded");

	return true;
}