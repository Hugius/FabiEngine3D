#include "model_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::ofstream;

const bool ModelEditor::saveToFile() const
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

	for(const auto& modelId : _loadedModelIds)
	{
		auto partIds = _fe3d->model_getPartIds(modelId);
		auto aabbIds = _fe3d->aabb_getChildIds(modelId, AabbParentEntityType::MODEL);
		auto isMultiParted = _fe3d->model_isMultiParted(modelId);
		auto meshPath = _fe3d->model_getMeshPath(modelId);
		auto modelSize = _fe3d->model_getBaseSize(modelId);
		auto levelOfDetailEntityId = _fe3d->model_getLevelOfDetailEntityId(modelId);
		auto levelOfDetailDistance = _fe3d->model_getLevelOfDetailDistance(modelId);
		auto rotationOrder = static_cast<unsigned int>(_fe3d->model_getRotationOrder(modelId));
		auto isShadowed = _fe3d->model_isShadowed(modelId);
		auto isReflected = _fe3d->model_isReflected(modelId);

		meshPath = string(meshPath.empty() ? "" : meshPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

		meshPath = (meshPath.empty()) ? "?" : meshPath;
		levelOfDetailEntityId = (levelOfDetailEntityId.empty()) ? "?" : levelOfDetailEntityId;

		replace(meshPath.begin(), meshPath.end(), ' ', '?');
		replace(levelOfDetailEntityId.begin(), levelOfDetailEntityId.end(), ' ', '?');

		file <<
			"MODEL " <<
			modelId << " " <<
			meshPath << " " <<
			modelSize.x << " " <<
			modelSize.y << " " <<
			modelSize.z << " " <<
			levelOfDetailEntityId << " " <<
			levelOfDetailDistance << " " <<
			rotationOrder << " " <<
			isShadowed << " " <<
			isReflected << endl;

		for(size_t i = 0; i < partIds.size(); i++)
		{
			auto partId = partIds[i];
			auto diffuseMapPath = _fe3d->model_getDiffuseMapPath(modelId, partId);
			auto emissionMapPath = _fe3d->model_getEmissionMapPath(modelId, partId);
			auto specularMapPath = _fe3d->model_getSpecularMapPath(modelId, partId);
			auto reflectionMapPath = _fe3d->model_getReflectionMapPath(modelId, partId);
			auto normalMapPath = _fe3d->model_getNormalMapPath(modelId, partId);
			auto isSpecular = _fe3d->model_isSpecular(modelId, partId);
			auto specularShininess = _fe3d->model_getSpecularShininess(modelId, partId);
			auto specularIntensity = _fe3d->model_getSpecularIntensity(modelId, partId);
			auto reflectivity = _fe3d->model_getReflectivity(modelId, partId);
			auto lightness = _fe3d->model_getLightness(modelId, partId);
			auto color = _fe3d->model_getColor(modelId, partId);
			auto textureRepeat = _fe3d->model_getTextureRepeat(modelId, partId);
			auto isReflective = _fe3d->model_isReflective(modelId, partId);
			auto reflectionType = static_cast<unsigned int>(_fe3d->model_getReflectionType(modelId, partId));
			auto isFaceCulled = _fe3d->model_isFaceCulled(modelId, partId);
			auto isBright = _fe3d->model_isBright(modelId, partId);
			auto emissionIntensity = _fe3d->model_getEmissionIntensity(modelId, partId);
			auto opacity = _fe3d->model_getOpacity(modelId, partId);
			auto minTextureAlpha = _fe3d->model_getMinTextureAlpha(modelId, partId);

			diffuseMapPath = string(diffuseMapPath.empty() ? "" : diffuseMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
			emissionMapPath = string(emissionMapPath.empty() ? "" : emissionMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
			specularMapPath = string(specularMapPath.empty() ? "" : specularMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
			reflectionMapPath = string(reflectionMapPath.empty() ? "" : reflectionMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));
			normalMapPath = string(normalMapPath.empty() ? "" : normalMapPath.substr(string("projects\\" + getCurrentProjectId() + "\\").size()));

			partId = (partId.empty()) ? "?" : partId;
			diffuseMapPath = (diffuseMapPath.empty()) ? "?" : diffuseMapPath;
			emissionMapPath = (emissionMapPath.empty()) ? "?" : emissionMapPath;
			specularMapPath = (specularMapPath.empty()) ? "?" : specularMapPath;
			reflectionMapPath = (reflectionMapPath.empty()) ? "?" : reflectionMapPath;
			normalMapPath = (normalMapPath.empty()) ? "?" : normalMapPath;

			replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			replace(emissionMapPath.begin(), emissionMapPath.end(), ' ', '?');
			replace(specularMapPath.begin(), specularMapPath.end(), ' ', '?');
			replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
			replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');

			file <<
				"PART " <<
				modelId << " " <<
				partId << " " <<
				diffuseMapPath << " " <<
				emissionMapPath << " " <<
				specularMapPath << " " <<
				reflectionMapPath << " " <<
				normalMapPath << " " <<
				reflectionType << " " <<
				isSpecular << " " <<
				isReflective << " " <<
				specularShininess << " " <<
				specularIntensity << " " <<
				reflectivity << " " <<
				lightness << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				textureRepeat << " " <<
				isFaceCulled << " " <<
				isBright << " " <<
				emissionIntensity << " " <<
				opacity << " " <<
				minTextureAlpha << endl;
		}

		for(size_t i = 0; i < aabbIds.size(); i++)
		{
			auto aabbId = aabbIds[i];
			auto position = _fe3d->aabb_getPosition(aabbId);
			auto size = _fe3d->aabb_getSize(aabbId);

			file <<
				"AABB " <<
				modelId << " " <<
				aabbId << " " <<
				position.x << " " <<
				position.y << " " <<
				position.z << " " <<
				size.x << " " <<
				size.y << " " <<
				size.z << endl;
		}
	}

	file.close();

	Logger::throwInfo("Model editor data saved");

	return true;
}