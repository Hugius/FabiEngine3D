#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool ModelEditor::saveModelsToFile() const
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

	auto file = ofstream(rootPath + "projects\\" + getCurrentProjectId() + "\\data\\model.fe3d");

	for(const auto & modelId : _loadedModelIds)
	{
		const auto partIds = _fe3d->model_getPartIds(modelId);
		const auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		const auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		const auto modelSize = _fe3d->model_getBaseSize(modelId);
		const auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		const auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(modelId));
		const auto isShadowed = _fe3d->model_isShadowed(modelId);
		const auto isReflected = _fe3d->model_isReflected(modelId);
		const auto isRefracted = _fe3d->model_isRefracted(modelId);

		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(modelId);

		meshPath = (meshPath.empty() ? "" : meshPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailId = (levelOfDetailId.empty()) ? "?" : levelOfDetailId;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailId.begin(), levelOfDetailId.end(), ' ', '?');

		file
			<< "MODEL "
			<< modelId
			<< " "
			<< meshPath
			<< " "
			<< modelSize.x
			<< " "
			<< modelSize.y
			<< " "
			<< modelSize.z
			<< " "
			<< levelOfDetailId
			<< " "
			<< levelOfDetailDistance
			<< " "
			<< rotationOrder
			<< " "
			<< isShadowed
			<< " "
			<< isReflected
			<< " "
			<< isRefracted
			<< endl;

		for(auto partId : partIds)
		{
			const auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			const auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			const auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			const auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			const auto refractivity = _fe3d->model_getRefractivity(modelId, partId);
			const auto lightness = _fe3d->model_getLightness(modelId, partId);
			const auto color = _fe3d->model_getColor(modelId, partId);
			const auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			const auto isReflective = _fe3d->model_isReflective(modelId, partId);
			const auto isRefractive = _fe3d->model_isRefractive(modelId, partId);
			const auto reflectionType = static_cast<int>(_fe3d->model_getReflectionType(modelId, partId));
			const auto refractionType = static_cast<int>(_fe3d->model_getRefractionType(modelId, partId));
			const auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			const auto isBright = _fe3d->model_isBright(modelId, partId);
			const auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			const auto opacity = _fe3d->model_getOpacity(modelId, partId);
			const auto minTextureAlpha = _fe3d->model_getMinTextureAlpha(modelId, partId);

			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);

			diffuseMapPath = (diffuseMapPath.empty() ? "" : diffuseMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			emissionMapPath = (emissionMapPath.empty() ? "" : emissionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			specularMapPath = (specularMapPath.empty() ? "" : specularMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			reflectionMapPath = (reflectionMapPath.empty() ? "" : reflectionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			refractionMapPath = (refractionMapPath.empty() ? "" : refractionMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));
			normalMapPath = (normalMapPath.empty() ? "" : normalMapPath.substr(("projects\\" + getCurrentProjectId() + "\\").size()));

			partId = (partId.empty()) ? "?" : partId;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			refractionMapPath = (refractionMapPath.empty()) ? "?" : refractionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(refractionMapPath.begin(), refractionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			file
				<< "PART "
				<< modelId
				<< " "
				<< partId
				<< " "
				<< diffuseMapPath
				<< " "
				<< emissionMapPath
				<< " "
				<< specularMapPath
				<< " "
				<< reflectionMapPath
				<< " "
				<< refractionMapPath
				<< " "
				<< normalMapPath
				<< " "
				<< reflectionType
				<< " "
				<< refractionType
				<< " "
				<< isSpecular
				<< " "
				<< isReflective
				<< " "
				<< isRefractive
				<< " "
				<< specularShininess
				<< " "
				<< specularIntensity
				<< " "
				<< reflectivity
				<< " "
				<< refractivity
				<< " "
				<< lightness
				<< " "
				<< color.r
				<< " "
				<< color.g
				<< " "
				<< color.b
				<< " "
				<< textureRepeat
				<< " "
				<< isFaceCulled
				<< " "
				<< isBright
				<< " "
				<< emissionIntensity
				<< " "
				<< opacity
				<< " "
				<< minTextureAlpha
				<< endl;
		}

		for(const auto & aabbId : aabbIds)
		{
			const auto position = _fe3d->aabb_getLocalPosition(aabbId);
			const auto size = _fe3d->aabb_getLocalSize(aabbId);

			file
				<< "AABB "
				<< modelId
				<< " "
				<< aabbId
				<< " "
				<< position.x
				<< " "
				<< position.y
				<< " "
				<< position.z
				<< " "
				<< size.x
				<< " "
				<< size.y
				<< " "
				<< size.z
				<< endl;
		}
	}

	file.close();

	Logger::throwInfo("Model editor data saved");

	return true;
}