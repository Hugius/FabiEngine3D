#include "scene_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

bool SceneEditor::_loadScene()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string filePath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Scenes\\scene.fe3d";

	// Check if scene file existing
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Load scene file
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string entityType;

			// For item extraction
			std::istringstream iss(line);

			// Extract type from file
			iss >> entityType;

			// Load entity according to type
			if (entityType == "MODEL")
			{
				// Values
				string modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath;
				vec3 position, rotation, size, color, aabbSize;
				float uvRepeat, specularFactor, specularIntensity, lightness;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isReflective, isFrozen;

				// Load model data
				iss >>
					modelID >>
					position.x >>
					position.y >>
					position.z >>
					rotation.x >>
					rotation.y >>
					rotation.z >>
					size.x >>
					size.y >>
					size.z >>
					objPath >>
					diffuseMapPath >>
					lightMapPath >>
					reflectionMapPath >>
					isFrozen >>
					isFaceculled >>
					isShadowed >>
					isTransparent >>
					isReflective >>
					isSpecular >>
					specularFactor >>
					specularIntensity >>
					lightness >>
					color.r >>
					color.g >>
					color.b >>
					uvRepeat >>
					aabbSize.x >>
					aabbSize.y >>
					aabbSize.z;

				// Perform empty string & space conversions
				objPath = (objPath == "?") ? "" : objPath;
				diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
				lightMapPath = (lightMapPath == "?") ? "" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "?") ? "" : reflectionMapPath;
				std::replace(objPath.begin(), objPath.end(), '?', ' ');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
				std::replace(lightMapPath.begin(), lightMapPath.end(), '?', ' ');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), '?', ' ');

				// Add the model
				_placeModel(modelID, position, rotation, size, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, isFrozen,
					isFaceculled, isShadowed, isTransparent, isReflective, isSpecular, specularFactor, specularIntensity, lightness,
					color, uvRepeat, aabbSize);
			}
			else if (entityType == "BILLBOARD")
			{

			}
			else if (entityType == "AMBIENT")
			{
				// Values
				vec3 ambientLightingColor;
				float ambientLightingIntensity;

				// Extract
				iss >> ambientLightingColor.r >> ambientLightingColor.g >> ambientLightingColor.b >> ambientLightingIntensity;

				// Apply
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else if (entityType == "DIRECTIONAL")
			{
				// Values
				vec3 directionalLightingPosition, directionalLightingColor;
				float directionalLightingIntensity, billboardSize;

				// Extract
				iss >> directionalLightingPosition.x >> directionalLightingPosition.y >> directionalLightingPosition.z >>
					directionalLightingColor.r >> directionalLightingColor.g >> directionalLightingColor.b >>
					directionalLightingIntensity >> billboardSize;

				// Apply
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
				_fe3d.billBoardEntity_add("@@lightSource", "Engine\\Textures\\light_source.png", directionalLightingPosition, vec3(0.0f), vec2(billboardSize), true, true, true, true);
			}
			else if (entityType == "POINT")
			{
				// Values
				string ID;
				vec3 position, color;
				float intensity, distance;

				// Extract line data
				iss >> ID >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b >> intensity >> distance;

				// Add entities
				_fe3d.gameEntity_add("@" + ID, "Engine\\OBJs\\lamp.obj", position, vec3(0.0f), _defaultLightbulbSize);
				_fe3d.gameEntity_setShadowed("@" + ID, false);
				_fe3d.gameEntity_setDepthMapIncluded("@" + ID, false);
				_fe3d.aabbEntity_bindToGameEntity("@" + ID, _defaultLightbulbAabbSize, true);
				_fe3d.lightEntity_add(ID, position, color, intensity, distance);
			}
			else if (entityType == "EDITOR_SPEED")
			{
				iss >> _customCameraSpeed;
			}
			else if (entityType == "EDITOR_POSITION")
			{
				vec3 position;
				iss >> position.x >> position.y >> position.z;
				_fe3d.camera_setPosition(position);
			}
			else if (entityType == "EDITOR_YAW")
			{
				float yaw;
				iss >> yaw;
				_fe3d.camera_setYaw(yaw);
			}
			else if (entityType == "EDITOR_PITCH")
			{
				float pitch;
				iss >> pitch;
				_fe3d.camera_setPitch(pitch);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" loaded!");

		return true;
	}
	else
	{
		return false;
	}
}

void SceneEditor::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Scenes\\scene.fe3d");

		// Write game entities data into file
		for (auto& entityID : _fe3d.gameEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				// Retrieve all values to be saved
				auto position = _fe3d.gameEntity_getPosition(entityID);
				auto rotation = _fe3d.gameEntity_getRotation(entityID);
				auto size = _fe3d.gameEntity_getSize(entityID);
				auto objPath = _fe3d.gameEntity_getObjPath(entityID);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(entityID);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(entityID);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(entityID);
				auto isFrozen = _fe3d.gameEntity_isStaticToCamera(entityID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(entityID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(entityID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(entityID);
				auto isReflective = _fe3d.gameEntity_isSceneReflective(entityID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(entityID);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(entityID);
				auto specularIntensity = _fe3d.gameEntity_getSpecularIntensity(entityID);
				auto lightness = _fe3d.gameEntity_getLightness(entityID);
				auto color = _fe3d.gameEntity_getColor(entityID);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(entityID);
				auto aabbSize = _fe3d.aabbEntity_getSize(entityID);

				// Perform empty string & space conversions
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
				std::replace(objPath.begin(), objPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');

				// 1 model -> 1 line in file
				file <<
					"MODEL " <<
					entityID << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					rotation.x << " " <<
					rotation.y << " " <<
					rotation.z << " " <<
					size.x << " " <<
					size.y << " " <<
					size.z << " " <<
					objPath << " " <<
					diffuseMapPath << " " <<
					lightMapPath << " " <<
					reflectionMapPath << " " <<
					isFrozen << " " <<
					isFaceCulled << " " <<
					isShadowed << " " <<
					isTransparent << " " <<
					isReflective << " " <<
					isSpecular << " " <<
					specularFactor << " " <<
					specularIntensity << " " <<
					lightness << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					aabbSize.x << " " <<
					aabbSize.y << " " <<
					aabbSize.z << std::endl;
			}
		}

		// Ambient lighting
		vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
		float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

		file <<
			"AMBIENT " <<
			ambientLightingColor.r << " " <<
			ambientLightingColor.g << " " <<
			ambientLightingColor.b << " " <<
			ambientLightingIntensity << std::endl;

		// Directional lighting
		vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
		vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
		float directionalLightingIntensity = _fe3d.gfx_geDirectionalLightingIntensity();
		float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

		file <<
			"DIRECTIONAL " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << " " <<
			billboardSize << std::endl;

		// Point lights
		for (auto& entityID : _fe3d.lightEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				auto position = _fe3d.lightEntity_getPosition(entityID);
				auto color = _fe3d.lightEntity_getColor(entityID);
				auto intensity = _fe3d.lightEntity_getIntensity(entityID);
				auto distance = _fe3d.lightEntity_getDistanceFactor(entityID);

				// Write line to file
				file <<
					"POINT " <<
					entityID << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					intensity << " " <<
					distance << std::endl;
			}
		}

		// Camera FOV
		file << "CAMERA_FOV " << _fe3d.camera_getFOV() << std::endl;

		// Editor camera speed
		file << "EDITOR_SPEED " << _customCameraSpeed << std::endl;

		// Editor camera position
		vec3 position = _fe3d.camera_getPosition();
		file << "EDITOR_POSITION " << position.x << " " << position.y << " " << position.z << std::endl;

		// Editor camera yaw
		file << "EDITOR_YAW " << _fe3d.camera_getYaw() << std::endl;

		// Editor camera pitch
		file << "EDITOR_PITCH " << _fe3d.camera_getPitch() << std::endl;

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" saved!");
	}
}