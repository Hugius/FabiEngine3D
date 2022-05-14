#include "aabb_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool AabbEditor::saveAabbsToFile() const
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

	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\aabb.fe3d");

	for(const auto & aabbId : _loadedAabbIds)
	{
		const auto size = _fe3d->aabb_getBaseSize(aabbId);
		const auto color = _fe3d->aabb_getColor(aabbId);

		file
			<< aabbId
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

	Logger::throwInfo("AABB editor data saved");

	return true;
}