#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::saveSceneToFile()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Check if a scene is currently being edited
		if (_currentSceneName != "")
		{
			// Create or overwrite models file
			std::ofstream file;
			file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\scenes\\" + _currentSceneName + ".fe3d");

			// Save LOD IDs
			vector<string> lodIDs;
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Check if not preview model
				if (entityID[0] != '@')
				{
					// Check if entity has LOD ID
					if (_fe3d.gameEntity_getLevelOfDetailEntityID(entityID) != "")
					{
						lodIDs.push_back(_fe3d.gameEntity_getLevelOfDetailEntityID(entityID));
					}
				}
			}

			// Write SKY entity data into file
			if (_currentSkyID != "")
			{
				auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID);
				float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
				float lightness = _fe3d.skyEntity_getOriginalLightness(_currentSkyID);
				Vec3 color = _fe3d.skyEntity_getColor(_currentSkyID);

				// Perform empty string & space conversions
				for (auto& diffuseMapPath : diffuseMapPaths)
				{
					diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
					std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				}

				// Write name to file
				file << "SKY " << _currentSkyID << " ";

				// Write paths to file
				for (auto& diffuseMapPath : diffuseMapPaths)
				{
					file << diffuseMapPath << " ";
				}

				// Write options to file
				file <<
					rotationSpeed << " " <<
					lightness << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << std::endl;
			}

			// Write TERRAIN entity data into file
			if (_currentTerrainID != "")
			{
				// Values
				string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(_currentTerrainID);
				string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(_currentTerrainID);
				string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(_currentTerrainID);
				string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR(_currentTerrainID);
				string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG(_currentTerrainID);
				string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB(_currentTerrainID);
				float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
				float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
				float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
				float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
				float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
				float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
				float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
				bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped(_currentTerrainID);
				bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);

				// Perform empty string & space conversions
				heightMapPath = (heightMapPath == "") ? "?" : heightMapPath;
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				blendMapPath = (blendMapPath == "") ? "?" : blendMapPath;
				blendMapPathR = (blendMapPathR == "") ? "?" : blendMapPathR;
				blendMapPathG = (blendMapPathG == "") ? "?" : blendMapPathG;
				blendMapPathB = (blendMapPathB == "") ? "?" : blendMapPathB;
				std::replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
				std::replace(blendMapPathR.begin(), blendMapPathR.end(), ' ', '?');
				std::replace(blendMapPathG.begin(), blendMapPathG.end(), ' ', '?');
				std::replace(blendMapPathB.begin(), blendMapPathB.end(), ' ', '?');

				// Write terrain data to file
				file <<
					"TERRAIN " <<
					_currentTerrainID << " " <<
					heightMapPath << " " <<
					diffuseMapPath << " " <<
					maxHeight << " " <<
					uvRepeat << " " <<
					lightness << " " <<
					isBlendMapped << " " <<
					blendMapPath << " " <<
					blendMapPathR << " " <<
					blendMapPathG << " " <<
					blendMapPathB << " " <<
					blendRepeatR << " " <<
					blendRepeatG << " " <<
					blendRepeatB << " " <<
					isSpecular << " " <<
					specularIntensity << std::endl;
			}

			// Write WATER entity data into file
			if (_currentWaterID != "")
			{
				// Values
				string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(_currentWaterID);
				string normalMapPath = _fe3d.waterEntity_getNormalMapPath(_currentWaterID);
				string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(_currentWaterID);
				bool isWaving = _fe3d.waterEntity_isWaving(_currentWaterID);
				bool isRippling = _fe3d.waterEntity_isRippling(_currentWaterID);
				bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(_currentWaterID);
				bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
				bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
				Vec3 color = _fe3d.waterEntity_getColor(_currentWaterID);
				float size = _fe3d.waterEntity_getSize(_currentWaterID);
				Vec3 position = _fe3d.waterEntity_getPosition(_currentWaterID);
				float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);
				float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(_currentWaterID);
				Vec2 speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
				float transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
				float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(_currentWaterID);
				float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(_currentWaterID);

				// Perform empty string & space conversions
				dudvMapPath = (dudvMapPath == "" ? "?" : dudvMapPath);
				normalMapPath = (normalMapPath == "" ? "?" : normalMapPath);
				displacementMapPath = (displacementMapPath == "" ? "?" : displacementMapPath);
				std::replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
				std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
				std::replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

				// Write data to file
				file <<
					"WATER " <<
					_currentWaterID << " " <<
					dudvMapPath << " " <<
					normalMapPath << " " <<
					displacementMapPath << " " <<
					isWaving << " " <<
					isRippling << " " <<
					isSpecularLighted << " " <<
					isReflective << " " <<
					isRefractive << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					size << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					uvRepeat << " " <<
					waveHeightFactor << " " <<
					speed.x << " " <<
					speed.y << " " <<
					transparency << " " <<
					specularFactor << " " <<
					specularIntensity << std::endl;
			}

			// Write GAME entities data into file
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Check if not a preview model or an LOD entity
				if (entityID[0] != '@' || std::find(lodIDs.begin(), lodIDs.end(), entityID) != lodIDs.end())
				{
					// General data
					auto position = _fe3d.gameEntity_getPosition(entityID);
					auto rotation = _fe3d.gameEntity_getRotation(entityID);
					auto size = _fe3d.gameEntity_getSize(entityID);
					auto objPath = _fe3d.gameEntity_getObjPath(entityID);
					auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(entityID);
					auto lightMapPath = _fe3d.gameEntity_getLightMapPath(entityID);
					auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(entityID);
					auto normalMapPath = _fe3d.gameEntity_getNormalMapPath(entityID);
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
					auto lodEntityID = _fe3d.gameEntity_getLevelOfDetailEntityID(entityID);
					auto isInstanced = _fe3d.gameEntity_isInstanced(entityID);
					auto instancedOffsets = _fe3d.gameEntity_getInstancedOffsets(entityID);

					// AABB data
					vector<string> aabbNames;
					vector<Vec3> aabbPositions;
					vector<Vec3> aabbSizes;
					for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(entityID, true, false))
					{
						aabbNames.push_back(aabbID.substr(string(entityID + "_").size()));
						aabbPositions.push_back(_fe3d.aabbEntity_getPosition(aabbID));
						aabbSizes.push_back(_fe3d.aabbEntity_getSize(aabbID));
					}

					// Perform empty string & space conversions
					diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
					lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
					reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
					normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
					lodEntityID = (lodEntityID == "") ? "?" : lodEntityID;
					std::replace(objPath.begin(), objPath.end(), ' ', '?');
					std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
					std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
					std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
					std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
					std::replace(lodEntityID.begin(), lodEntityID.end(), ' ', '?');

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
						normalMapPath << " " <<
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
						lodEntityID << " " <<
						isInstanced;

					// Write instanced offset data
					if (isInstanced)
					{
						if (!instancedOffsets.empty()) file << " ";
						for (unsigned int i = 0; i < instancedOffsets.size(); i++)
						{
							file <<
								instancedOffsets[i].x << " " <<
								instancedOffsets[i].y << " " <<
								instancedOffsets[i].z;

							// Add space
							if (i != (instancedOffsets.size() - 1))
							{
								file << " ";
							}
						}
					}

					// Write AABB data
					if (!aabbNames.empty()) file << " ";
					for (unsigned int i = 0; i < aabbNames.size(); i++)
					{
						file <<
							aabbNames[i] << " " <<
							aabbPositions[i].x << " " <<
							aabbPositions[i].y << " " <<
							aabbPositions[i].z << " " <<
							aabbSizes[i].x << " " <<
							aabbSizes[i].y << " " <<
							aabbSizes[i].z;

						// Add space
						if (i != (aabbNames.size() - 1))
						{
							file << " ";
						}
					}

					// New line
					file << std::endl;
				}
			}

			// Write BILLBOARD entities data into file
			for (auto& entityID : _fe3d.billboardEntity_getAllIDs())
			{
				// Check if not a preview entity
				if (entityID[0] != '@')
				{
					// Retrieve all valus
					auto position = _fe3d.billboardEntity_getPosition(entityID);
					auto rotation = _fe3d.billboardEntity_getRotation(entityID);
					auto size = _fe3d.billboardEntity_getSize(entityID);
					auto color = _fe3d.billboardEntity_getColor(entityID);
					auto diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(entityID);
					auto fontPath = _fe3d.billboardEntity_getFontPath(entityID);
					auto textContent = _fe3d.billboardEntity_getTextContent(entityID);
					auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(entityID);
					auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(entityID);
					auto isTransparent = _fe3d.billboardEntity_isTransparent(entityID);
					auto isAnimated = _fe3d.billboardEntity_isAnimationPlaying(entityID);
					auto animationRows = _fe3d.billboardEntity_getAnimationRows(entityID);
					auto animationColumns = _fe3d.billboardEntity_getAnimationColumns(entityID);
					auto animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(entityID);

					// Perform empty string & space conversions
					diffusePath = (diffusePath == "") ? "?" : diffusePath;
					fontPath = (fontPath == "") ? "?" : fontPath;
					textContent = (textContent == "") ? "?" : textContent;
					std::replace(diffusePath.begin(), diffusePath.end(), ' ', '?');
					std::replace(fontPath.begin(), fontPath.end(), ' ', '?');
					std::replace(textContent.begin(), textContent.end(), ' ', '?');

					// Export data
					file <<
						"BILLBOARD " <<
						entityID << " " <<
						position.x << " " <<
						position.y << " " <<
						position.z << " " <<
						rotation.x << " " <<
						rotation.y << " " <<
						rotation.z << " " <<
						size.x << " " <<
						size.y << " " <<
						color.r << " " <<
						color.g << " " <<
						color.b << " " <<
						isFacingX << " " <<
						isFacingY << " " <<
						diffusePath << " " <<
						isTransparent << " " <<
						fontPath << " " <<
						textContent << " " <<
						isAnimated << " " <<
						animationRows << " " <<
						animationColumns << " " <<
						animationFramestep << std::endl;
				}
			}

			// Ambient lighting
			Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			file <<
				"AMBIENT_LIGHT " <<
				ambientLightingColor.r << " " <<
				ambientLightingColor.g << " " <<
				ambientLightingColor.b << " " <<
				ambientLightingIntensity << std::endl;

			// Directional lighting
			Vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			Vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			float directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
			float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

			file <<
				"DIRECTIONAL_LIGHT " <<
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

			// LOD distance
			file << "LOD_DISTANCE " << _fe3d.gameEntity_getLevelOfDetailDistance() << std::endl;

			// Editor camera speed
			file << "EDITOR_SPEED " << _customCameraSpeed << std::endl;

			// Editor camera position
			Vec3 position = _fe3d.camera_getPosition();
			file << "EDITOR_POSITION " << position.x << " " << position.y << " " << position.z << std::endl;

			// Editor camera yaw
			file << "EDITOR_YAW " << _fe3d.camera_getYaw() << std::endl;

			// Editor camera pitch
			file << "EDITOR_PITCH " << _fe3d.camera_getPitch() << std::endl;

			// Shadow settings
			bool enabled = _fe3d.gfx_isShadowsEnabled();
			if (enabled)
			{
				float size = _fe3d.gfx_getShadowSize();
				position = _fe3d.gfx_getShadowEyePosition();
				Vec3 center = _fe3d.gfx_getShadowCenter();
				bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
				int interval = _fe3d.gfx_getShadowInterval();
				file << "GRAPHICS_SHADOWS " << enabled << " " << size << " " << _fe3d.misc_vec2str(position) << " " <<
					_fe3d.misc_vec2str(center) << " " << isFollowingCamera << " " << interval << std::endl;
			}

			// Motion blur settings
			enabled = _fe3d.gfx_isMotionBlurEnabled();
			if (enabled)
			{
				float strength = _fe3d.gfx_getMotionBlurStrength();
				file << "GRAPHICS_MOTIONBLUR " << enabled << " " << strength << std::endl;
			}

			// DOF settings
			enabled = _fe3d.gfx_isDofEnabled();
			if (enabled)
			{
				bool dynamic = _fe3d.gfx_isDofDynamic();
				float blurDistance = _fe3d.gfx_getDofBlurDistance();
				float maxDistance = _fe3d.gfx_getDofMaxDistance();
				file << "GRAPHICS_DOF " << enabled << " " << dynamic << " " << blurDistance << " " << maxDistance << std::endl;
			}

			// Fog settings
			enabled = _fe3d.gfx_isFogEnabled();
			if (enabled)
			{
				float minDistance = _fe3d.gfx_getFogMinDistance();
				float maxDistance = _fe3d.gfx_getFogMaxDistance();
				float defaultFactor = _fe3d.gfx_getFogDefaultFactor();
				Vec3 color = _fe3d.gfx_getFogColor();
				file << "GRAPHICS_FOG " << enabled << " " << minDistance << " " << maxDistance << " " << defaultFactor << " " << _fe3d.misc_vec2str(color) << std::endl;
			}

			// Lens flare settings
			enabled = _fe3d.gfx_isLensFlareEnabled();
			if (enabled)
			{
				string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
				float intensity = _fe3d.gfx_getLensFlareIntensity();
				float multiplier = _fe3d.gfx_getLensFlareMultiplier();
				file << "GRAPHICS_LENSFLARE " << enabled << " " << flareMapPath << " " << intensity << " " << multiplier << std::endl;
			}

			// Sky HDR settings
			enabled = _fe3d.gfx_isSkyHdrEnabled();
			if (enabled)
			{
				float intensity = _fe3d.gfx_getSkyHdrBrightnessFactor();
				file << "GRAPHICS_SKYHDR " << enabled << " " << intensity << std::endl;
			}

			// Close file
			file.close();

			// Logging
			_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectName + "\" saved!");
		}
	}
}