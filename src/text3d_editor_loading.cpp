#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text3dEditor::getImagePathsFromFile() const
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\text3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\text3d.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths = {};
	string line = "";

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "TEXT3D")
		{
			string text3dId;
			string fontMapPath;

			iss
				>> text3dId
				>> fontMapPath;

			fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

			replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

			if(!fontMapPath.empty())
			{
				if(!Tools::isApplicationExported())
				{
					fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
				}

				imagePaths.push_back(fontMapPath);
			}
		}
	}

	file.close();

	return imagePaths;
}

const bool Text3dEditor::loadText3dsFromFile()
{
	if(!Tools::isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "domain\\text3d.fe3d");

	auto file = ifstream(filePath);

	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `domain\\text3d.fe3d` does not exist");

		return false;
	}

	string line = "";

	while(getline(file, line))
	{
		string lineType;

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "TEXT3D")
		{
			string text3dId;
			string fontMapPath;
			string content;
			fvec2 size;
			fvec3 color;
			float lightness;
			float opacity;
			float minAlpha;
			int rotationOrder;
			bool isFacingCameraHorizontally;
			bool isFacingCameraVertically;
			bool isHorizontallyFlipped;
			bool isVerticallyFlipped;
			bool isReflected;
			bool isRefracted;
			bool isShadowed;
			bool isBright;

			iss
				>> text3dId
				>> fontMapPath
				>> size.x
				>> size.y
				>> color.r
				>> color.g
				>> color.b
				>> isFacingCameraHorizontally
				>> isFacingCameraVertically
				>> isHorizontallyFlipped
				>> isVerticallyFlipped
				>> isReflected
				>> isRefracted
				>> isShadowed
				>> lightness
				>> isBright
				>> opacity
				>> minAlpha
				>> rotationOrder
				>> content;

			fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;
			content = (content == "?") ? "" : content;

			replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');
			replace(content.begin(), content.end(), '?', ' ');

			if(!Tools::isApplicationExported())
			{
				fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			_fe3d->text3d_create(text3dId, fontMapPath, false);

			if(_fe3d->text3d_isExisting(text3dId))
			{
				_fe3d->text3d_setVisible(text3dId, false);
				_fe3d->text3d_setSize(text3dId, size);
				_fe3d->text3d_setColor(text3dId, color);
				_fe3d->text3d_setLightness(text3dId, lightness);
				_fe3d->text3d_setFacingCameraHorizontally(text3dId, isFacingCameraHorizontally);
				_fe3d->text3d_setFacingCameraVertically(text3dId, isFacingCameraVertically);
				_fe3d->text3d_setHorizontallyFlipped(text3dId, isHorizontallyFlipped);
				_fe3d->text3d_setVerticallyFlipped(text3dId, isVerticallyFlipped);
				_fe3d->text3d_setShadowed(text3dId, isShadowed);
				_fe3d->text3d_setReflected(text3dId, isReflected);
				_fe3d->text3d_setRefracted(text3dId, isRefracted);
				_fe3d->text3d_setBright(text3dId, isBright);
				_fe3d->text3d_setOpacity(text3dId, opacity);
				_fe3d->text3d_setMinAlpha(text3dId, minAlpha);
				_fe3d->text3d_setRotationOrder(text3dId, DirectionOrderType(rotationOrder));
				_fe3d->text3d_setContent(text3dId, content);

				_loadedText3dIds.push_back(text3dId);

				sort(_loadedText3dIds.begin(), _loadedText3dIds.end());
			}
		}
		else if(lineType == "AABB")
		{
			string text3dId;
			string aabbId;

			iss
				>> text3dId
				>> aabbId;

			if(!_fe3d->text3d_isExisting(text3dId))
			{
				continue;
			}

			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_setParentId(aabbId, text3dId);
			_fe3d->aabb_setParentType(aabbId, AabbParentType::TEXT3D);
		}
		else
		{
			abort();
		}
	}

	file.close();

	Logger::throwInfo("Text3D editor data loaded");

	return true;
}