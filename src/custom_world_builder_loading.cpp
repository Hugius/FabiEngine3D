#include "custom_world_builder.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

const bool CustomWorldBuilder::loadWorldFromFile(const string & fileName)
{
	if(!Configuration::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "worlds\\custom\\" + fileName + ".fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		return false;
	}

	string line;

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "SKY")
		{

		}
		else if(lineType == "TERRAIN")
		{

		}
		else if(lineType == "WATER")
		{

		}
		else if(lineType == "MODEL")
		{

		}
		else if(lineType == "MODEL_PART")
		{

		}
		else if(lineType == "MODEL_AABB")
		{

		}
		else if(lineType == "MODEL_ANIMATION3D")
		{

		}
		else if(lineType == "QUAD3D")
		{

		}
		else if(lineType == "QUAD3D_AABB")
		{

		}
		else if(lineType == "QUAD3D_ANIMATION2D")
		{

		}
		else if(lineType == "TEXT3D")
		{

		}
		else if(lineType == "TEXT3D_AABB")
		{

		}
		else if(lineType == "AABB")
		{

		}
		else if(lineType == "POINTLIGHT")
		{

		}
		else if(lineType == "SPOTLIGHT")
		{

		}
		else if(lineType == "SOUND3D")
		{

		}
		else if(lineType == "CAPTOR")
		{

		}
		else if(lineType == "GRAPHICS_AMBIENT_LIGHTING")
		{

		}
		else if(lineType == "GRAPHICS_DIRECTIONAL_LIGHTING")
		{

		}
		else if(lineType == "GRAPHICS_SHADOWS")
		{

		}
		else if(lineType == "GRAPHICS_REFLECTIONS")
		{

		}
		else if(lineType == "GRAPHICS_REFRACTIONS")
		{

		}
		else if(lineType == "GRAPHICS_DOF")
		{

		}
		else if(lineType == "GRAPHICS_FOG")
		{

		}
		else if(lineType == "GRAPHICS_LENS_FLARE")
		{

		}
		else if(lineType == "GRAPHICS_SKY_EXPOSURE")
		{

		}
		else if(lineType == "GRAPHICS_BLOOM")
		{

		}
		else
		{
			abort();
		}
	}

	file.close();

	_loadedWorldId = fileName;

	Logger::throwInfo("Custom world data loaded");

	return true;
}