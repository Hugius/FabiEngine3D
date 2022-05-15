#include "aabb_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const bool AabbEditor::loadAabbsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\aabb.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `aabb.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string aabbId;
		fvec3 size;
		fvec3 color;

		auto iss = istringstream(line);

		iss
			>> aabbId
			>> size.x
			>> size.y
			>> size.z
			>> color.r
			>> color.g
			>> color.b;

		_fe3d->aabb_create(aabbId, false);
		_fe3d->aabb_setVisible(aabbId, false);
		_fe3d->aabb_setBaseSize(aabbId, size);
		_fe3d->aabb_setColor(aabbId, color);

		_loadedAabbIds.push_back(aabbId);

		sort(_loadedAabbIds.begin(), _loadedAabbIds.end());
	}

	file.close();

	Logger::throwInfo("AABB editor data loaded");

	return true;
}