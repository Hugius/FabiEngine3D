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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\spotlight.fe3d");

	auto file = ofstream(filePath);

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		const auto color = _fe3d->spotlight_getColor(spotlightId);
		const auto intensity = _fe3d->spotlight_getIntensity(spotlightId);
		const auto angle = _fe3d->spotlight_getAngle(spotlightId);
		const auto distance = _fe3d->spotlight_getDistance(spotlightId);

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