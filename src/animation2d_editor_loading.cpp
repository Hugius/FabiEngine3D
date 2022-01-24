#include "animation2d_editor.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

const bool Animation2dEditor::loadFromFile(bool mustCheckPreviewTexture)
{
	if(!Config::getInst().isApplicationExported() && _currentProjectId.empty())
	{
		Logger::throwError("Animation2dEditor::loadFromFile");
	}

	_animations.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "data\\animation2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `animation2d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string animationId;
		string previewTexturePath;
		unsigned int rowCount;
		unsigned int columnCount;
		unsigned int framestep;

		istringstream iss(line);

		iss >>
			animationId >>
			previewTexturePath >>
			rowCount >>
			columnCount >>
			framestep;

		previewTexturePath = (previewTexturePath == "?") ? "" : previewTexturePath;

		replace(previewTexturePath.begin(), previewTexturePath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			previewTexturePath = string("projects\\" + _currentProjectId + "\\" + previewTexturePath);
		}

		auto newAnimation = make_shared<Animation2d>(animationId);

		newAnimation->setPreviewTexturePath(previewTexturePath);
		newAnimation->setRowCount(rowCount);
		newAnimation->setColumnCount(columnCount);
		newAnimation->setFramestep(framestep);

		if(mustCheckPreviewTexture)
		{
			if(Tools::isFileExisting(rootPath + previewTexturePath))
			{
				_fe3d->misc_cacheImage(previewTexturePath);
			}
			else
			{
				Logger::throwWarning("Preview texture of animation with id \"" + newAnimation->getId() + "\" not existing anymore!");
				continue;
			}
		}

		_animations.push_back(newAnimation);
	}

	file.close();

	Logger::throwInfo("Animation2D editor data loaded!");

	return true;
}