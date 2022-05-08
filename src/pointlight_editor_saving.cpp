#include "pointlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool PointlightEditor::savePointlightsToFile() const
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
	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\pointlight.fe3d");

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		auto radius = _fe3d->pointlight_getRadius(pointlightId);
		auto color = _fe3d->pointlight_getColor(pointlightId);
		auto intensity = _fe3d->pointlight_getIntensity(pointlightId);
		auto shape = static_cast<int>(_fe3d->pointlight_getShape(pointlightId));

		file
			<< pointlightId
			<< " "
			<< radius.x
			<< " "
			<< radius.y
			<< " "
			<< radius.z
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< intensity
			<< " "
			<< shape
			<< endl;
	}

	file.close();

	Logger::throwInfo("Pointlight editor data saved");

	return true;
}