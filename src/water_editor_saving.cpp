#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool WaterEditor::saveWatersToFile() const
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
	const auto filePath = (rootPath + "projects\\" + getCurrentProjectId() + "\\domain\\water.fe3d");

	auto file = ofstream(filePath);

	for(const auto & waterId : _loadedWaterIds)
	{
		const auto color = _fe3d->water_getColor(waterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(waterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(waterId);
		const auto size = _fe3d->water_getSize(waterId);
		const auto textureRepeat = _fe3d->water_getTextureRepeat(waterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(waterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(waterId);
		const auto isEdged = _fe3d->water_isEdged(waterId);
		const auto specularShininess = _fe3d->water_getSpecularShininess(waterId);
		const auto specularIntensity = _fe3d->water_getSpecularIntensity(waterId);
		const auto isSpecular = _fe3d->water_isSpecular(waterId);
		const auto isReflective = _fe3d->water_isReflective(waterId);
		const auto isRefractive = _fe3d->water_isRefractive(waterId);
		const auto lightness = _fe3d->water_getLightness(waterId);
		const auto distortionSize = _fe3d->water_getDistortionSize(waterId);
		const auto distortionFactor = _fe3d->water_getDistortionFactor(waterId);
		const auto captureOffset = _fe3d->water_getCaptureOffset(waterId);
		const auto isCapturingSky = _fe3d->water_isCapturingSky(waterId);
		const auto isCapturingTerrain = _fe3d->water_isCapturingTerrain(waterId);
		const auto isCapturingModels = _fe3d->water_isCapturingModels(waterId);
		const auto isCapturingQuad3ds = _fe3d->water_isCapturingQuad3ds(waterId);
		const auto isCapturingText3ds = _fe3d->water_isCapturingText3ds(waterId);
		const auto isCapturingAabbs = _fe3d->water_isCapturingAabbs(waterId);

		auto dudvMapPath = _fe3d->water_getDudvMapPath(waterId);
		auto normalMapPath = _fe3d->water_getNormalMapPath(waterId);
		auto heightMapPath = _fe3d->water_getHeightMapPath(waterId);

		if(!dudvMapPath.empty())
		{
			dudvMapPath = dudvMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!normalMapPath.empty())
		{
			normalMapPath = normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		if(!heightMapPath.empty())
		{
			heightMapPath = heightMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size());
		}

		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		heightMapPath = (heightMapPath.empty() ? "?" : heightMapPath);

		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');

		file
			<< waterId
			<< " "
			<< dudvMapPath
			<< " "
			<< normalMapPath
			<< " "
			<< heightMapPath
			<< " "
			<< isSpecular
			<< " "
			<< isReflective
			<< " "
			<< isRefractive
			<< " "
			<< color.r
			<< " "
			<< color.g
			<< " "
			<< color.b
			<< " "
			<< size
			<< " "
			<< textureRepeat
			<< " "
			<< waveHeight
			<< " "
			<< rippleSpeed.x
			<< " "
			<< rippleSpeed.y
			<< " "
			<< waveSpeed.x
			<< " "
			<< waveSpeed.y
			<< " "
			<< isEdged
			<< " "
			<< specularShininess
			<< " "
			<< specularIntensity
			<< " "
			<< maxDepth
			<< " "
			<< lightness
			<< " "
			<< distortionSize
			<< " "
			<< distortionFactor
			<< " "
			<< captureOffset
			<< " "
			<< isCapturingSky
			<< " "
			<< isCapturingTerrain
			<< " "
			<< isCapturingModels
			<< " "
			<< isCapturingQuad3ds
			<< " "
			<< isCapturingText3ds
			<< " "
			<< isCapturingAabbs
			<< endl;
	}

	file.close();

	Logger::throwInfo("Water editor data saved");

	return true;
}