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
		auto partIds = _fe3d->model_getPartIds(modelId);
		auto aabbIds = _fe3d->model_getChildAabbIds(modelId);
		auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto modelSize = _fe3d->model_getBaseSize(modelId);
		auto levelOfDetailId = _fe3d->model_getLevelOfDetailId(modelId);
		auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		auto rotationOrder = static_cast<int>(_fe3d->model_getRotationOrder(modelId));
		auto isShadowed = _fe3d->model_isShadowed(modelId);
		auto isReflected = _fe3d->model_isReflected(modelId);

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
			<< endl;

		for(auto partId : partIds)
		{
			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto refractionMapPath = _fe3d->model_getRefractionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);
			auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			auto lightness = _fe3d->model_getLightness(modelId, partId);
			auto color = _fe3d->model_getColor(modelId, partId);
			auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			auto isReflective = _fe3d->model_isReflective(modelId, partId);
			auto reflectionType = static_cast<int>(_fe3d->model_getReflectionType(modelId, partId));
			auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			auto isBright = _fe3d->model_isBright(modelId, partId);
			auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			auto opacity = _fe3d->model_getOpacity(modelId, partId);
			auto minTextureAlpha = _fe3d->model_getMinTextureAlpha(modelId, partId);

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
				<< isSpecular
				<< " "
				<< isReflective
				<< " "
				<< specularShininess
				<< " "
				<< specularIntensity
				<< " "
				<< reflectivity
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
			auto position = _fe3d->aabb_getLocalPosition(aabbId);
			auto size = _fe3d->aabb_getLocalSize(aabbId);

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