#include "spotlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool SpotlightEditor::saveSpotlightsToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\spotlight.fe3d");

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		auto color = _fe3d->spotlight_getColor(spotlightId);
		auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		auto angle = _fe3d->spotlight_getAngle(spotlightId);
		auto distance = _fe3d->spotlight_getDistance(spotlightId);

		file
			<< spotlightId
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< angle
			<< " "
			<< distance
			<< endl;
	}

	file.close();

	Logger::throwInfo("Spotlight editor data saved");

	return true;
}