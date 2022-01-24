#include "animation2d_editor.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

using std::istringstream;

const bool Animation2dEditor::loadFromFile(bool mustCheckPreviewTexture)
{
	if(!Config::getInst().isApplicationExported() && _currentProjectID.empty())
	{
		Logger::throwError("Animation2dEditor::loadFromFile");
	}

	_animations.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "data\\animation2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `animation2d.fe3d` missing!");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string animationID;
		string previewTexturePath;
		unsigned int rowCount;
		unsigned int columnCount;
		unsigned int framestep;

		istringstream iss(line);

		iss >>
			animationID >>
			previewTexturePath >>
			rowCount >>
			columnCount >>
			framestep;

		previewTexturePath = (previewTexturePath == "?") ? "" : previewTexturePath;

		replace(previewTexturePath.begin(), previewTexturePath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			previewTexturePath = string("projects\\" + _currentProjectID + "\\" + previewTexturePath);
		}

		auto newAnimation = make_shared<Animation2d>(animationID);

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
				Logger::throwWarning("Preview texture of animation with id \"" + newAnimation->getID() + "\" not existing anymore!");
				continue;
			}
		}

		_animations.push_back(newAnimation);
	}

	file.close();

	Logger::throwInfo("Animation2D editor data loaded!");

	return true;
}