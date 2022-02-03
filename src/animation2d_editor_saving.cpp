#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool Animation2dEditor::saveToFile() const
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
	ofstream file(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\animation2d.fe3d");

	for(const auto& animation : _animations)
	{
		auto animationId = animation->getId();
		auto previewTexturePath = animation->getPreviewTexturePath();
		auto rowCount = animation->getRowCount();
		auto columnCount = animation->getColumnCount();
		auto interval = animation->getInterval();

		if(!previewTexturePath.empty())
		{
			previewTexturePath = string(previewTexturePath.empty() ? "" : previewTexturePath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

			previewTexturePath = (previewTexturePath.empty()) ? "?" : previewTexturePath;

			replace(previewTexturePath.begin(), previewTexturePath.end(), ' ', '?');

			file <<
				animationId << " " <<
				previewTexturePath << " " <<
				rowCount << " " <<
				columnCount << " " <<
				interval << endl;
		}
	}

	file.close();

	Logger::throwInfo("Animation2D editor data saved");

	return true;
}