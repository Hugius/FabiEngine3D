#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text3dEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` does not exist");

		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string text3dId;
		string fontMapPath;

		istringstream iss(line);

		iss
			>> text3dId
			>> fontMapPath;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!fontMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text3dEditor::loadText3dsFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string text3dId;
		string fontMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float opacity;
		float minTextureAlpha;
		int rotationOrder;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;
		bool isReflected;
		bool isRefracted;
		bool isShadowed;
		bool isBright;
		bool hasAabb;

		istringstream iss(line);

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
			>> minTextureAlpha
			>> rotationOrder
			>> hasAabb;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
		}

		_fe3d->text3d_create(text3dId, fontMapPath, false);

		if(_fe3d->text3d_isExisting(text3dId))
		{
			_loadedText3dIds.push_back(text3dId);
			sort(_loadedText3dIds.begin(), _loadedText3dIds.end());

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
			_fe3d->text3d_setMinTextureAlpha(text3dId, minTextureAlpha);
			_fe3d->text3d_setRotationOrder(text3dId, DirectionOrderType(rotationOrder));

			if(hasAabb)
			{
				_fe3d->aabb_create(text3dId, false);
				_fe3d->aabb_setVisible(text3dId, false);
				_fe3d->aabb_setParentId(text3dId, text3dId);
				_fe3d->aabb_setParentType(text3dId, AabbParentType::TEXT3D);
			}
		}
	}

	file.close();

	Logger::throwInfo("Text3D editor data loaded");

	return true;
}