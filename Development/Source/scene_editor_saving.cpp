#include "scene_editor.hpp"

#include <fstream>
#include <algorithm>

void SceneEditor::saveSceneToFile(bool isCustomScene, const string& customFileName)
{
	// Error checking
	if (_currentProjectID == "" && !isCustomScene)
	{
		_fe3d.logger_throwError("No current project loaded --> SceneEditor::saveSceneToFile()");
	}

	// Check if scene directory still exists
	string directoryPath = _fe3d.misc_getRootDirectory() + (_fe3d.engine_isGameExported() ? "" : ("projects\\" + _currentProjectID)) + "\\scenes\\";
	if (!_fe3d.misc_isDirectory(directoryPath) ||
		!_fe3d.misc_isDirectory(directoryPath + "custom\\") ||
		!_fe3d.misc_isDirectory(directoryPath + "editor\\"))
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectID + "\" corrupted: scenes folder(s) missing!");
	}

	// Check if a scene is able to save (editing a scene or saving a custom scene)
	if (!_currentSceneID.empty() || isCustomScene)
	{
		// Create or overwrite file
		string fullFileName = (isCustomScene ? ("custom\\" + customFileName) : ("editor\\" + _currentSceneID));
		string fullFilePath = (directoryPath + fullFileName + ".fe3d");
		std::ofstream file(fullFilePath);

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
		string skyID = _fe3d.skyEntity_getSelectedID();
		if (!skyID.empty())
		{
			auto diffuseMapPaths = _fe3d.skyEntity_getDiffuseMapPaths(skyID);
			float rotationSpeed = _fe3d.skyEntity_getRotationSpeed(skyID);
			float lightness = _fe3d.skyEntity_getOriginalLightness(skyID);
			Vec3 color = _fe3d.skyEntity_getColor(skyID);

			// Perform empty string & space conversions
			for (auto& diffuseMapPath : diffuseMapPaths)
			{
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			}

			// Write name to file
			file << "SKY " << skyID << " ";

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
		string terrainID = _fe3d.terrainEntity_getSelectedID();
		if (!terrainID.empty())
		{
			// Values
			string heightMapPath = _fe3d.terrainEntity_getHeightMapPath(terrainID);
			string diffuseMapPath = _fe3d.terrainEntity_getDiffuseMapPath(terrainID);
			string normalMapPath = _fe3d.terrainEntity_getNormalMapPath(terrainID);
			string normalMapPathR = _fe3d.terrainEntity_getNormalMapPathR(terrainID);
			string normalMapPathG = _fe3d.terrainEntity_getNormalMapPathG(terrainID);
			string normalMapPathB = _fe3d.terrainEntity_getNormalMapPathB(terrainID);
			string blendMapPath = _fe3d.terrainEntity_getBlendMapPath(terrainID);
			string blendMapPathR = _fe3d.terrainEntity_getBlendMapPathR(terrainID);
			string blendMapPathG = _fe3d.terrainEntity_getBlendMapPathG(terrainID);
			string blendMapPathB = _fe3d.terrainEntity_getBlendMapPathB(terrainID);
			float maxHeight = _fe3d.terrainEntity_getMaxHeight(terrainID);
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat(terrainID);
			float lightness = _fe3d.terrainEntity_getLightness(terrainID);
			float specularFactor = _fe3d.terrainEntity_getSpecularLightingFactor(terrainID);
			float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(terrainID);
			float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(terrainID);
			float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(terrainID);
			float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(terrainID);
			bool isBlendMapped = _fe3d.terrainEntity_isBlendMapped(terrainID);
			bool isNormalMapped = _fe3d.terrainEntity_isNormalMapped(terrainID);
			bool isNormalMappedR = _fe3d.terrainEntity_isNormalMappedR(terrainID);
			bool isNormalMappedG = _fe3d.terrainEntity_isNormalMappedG(terrainID);
			bool isNormalMappedB = _fe3d.terrainEntity_isNormalMappedB(terrainID);
			bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(terrainID);

			// Perform empty string & space conversions
			heightMapPath = (heightMapPath == "") ? "?" : heightMapPath;
			diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
			normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
			blendMapPath = (blendMapPath == "") ? "?" : blendMapPath;
			blendMapPathR = (blendMapPathR == "") ? "?" : blendMapPathR;
			blendMapPathG = (blendMapPathG == "") ? "?" : blendMapPathG;
			blendMapPathB = (blendMapPathB == "") ? "?" : blendMapPathB;
			normalMapPathR = (normalMapPathR == "") ? "?" : normalMapPathR;
			normalMapPathG = (normalMapPathG == "") ? "?" : normalMapPathG;
			normalMapPathB = (normalMapPathB == "") ? "?" : normalMapPathB;
			std::replace(heightMapPath.begin(), heightMapPath.end(), ' ', '?');
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
			std::replace(blendMapPath.begin(), blendMapPath.end(), ' ', '?');
			std::replace(blendMapPathR.begin(), blendMapPathR.end(), ' ', '?');
			std::replace(blendMapPathG.begin(), blendMapPathG.end(), ' ', '?');
			std::replace(blendMapPathB.begin(), blendMapPathB.end(), ' ', '?');
			std::replace(normalMapPathR.begin(), normalMapPathR.end(), ' ', '?');
			std::replace(normalMapPathG.begin(), normalMapPathG.end(), ' ', '?');
			std::replace(normalMapPathB.begin(), normalMapPathB.end(), ' ', '?');

			// Write terrain data to file
			file <<
				"TERRAIN " <<
				terrainID << " " <<
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
				isNormalMapped << " " <<
				isNormalMappedR << " " <<
				isNormalMappedG << " " <<
				isNormalMappedB << " " <<
				normalMapPath << " " <<
				normalMapPathR << " " <<
				normalMapPathG << " " <<
				normalMapPathB << " " <<
				isSpecular << " " <<
				specularFactor << " " <<
				specularIntensity << std::endl;
		}

		// Write WATER entity data into file
		string waterID = _fe3d.waterEntity_getSelectedID();
		if (!waterID.empty())
		{
			// Values
			string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(waterID);
			string normalMapPath = _fe3d.waterEntity_getNormalMapPath(waterID);
			string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(waterID);
			bool isWaving = _fe3d.waterEntity_isWaving(waterID);
			bool isRippling = _fe3d.waterEntity_isRippling(waterID);
			bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(waterID);
			bool isReflective = _fe3d.waterEntity_isReflective(waterID);
			bool isRefractive = _fe3d.waterEntity_isRefractive(waterID);
			Vec3 color = _fe3d.waterEntity_getColor(waterID);
			float size = _fe3d.waterEntity_getSize(waterID);
			Vec3 position = _fe3d.waterEntity_getPosition(waterID);
			float uvRepeat = _fe3d.waterEntity_getUvRepeat(waterID);
			float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(waterID);
			Vec2 speed = _fe3d.waterEntity_getSpeed(waterID);
			float transparency = _fe3d.waterEntity_getTransparency(waterID);
			float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(waterID);
			float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(waterID);

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
				waterID << " " <<
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
		for (auto& modelID : _fe3d.gameEntity_getAllIDs())
		{
			// Check if not a preview model or an LOD entity
			if (modelID[0] != '@' || std::find(lodIDs.begin(), lodIDs.end(), modelID) != lodIDs.end())
			{
				// Check if model has bound animation
				if (!_animationEditor.getPlayingAnimationNames(modelID).empty())
				{
					// Reset main transformation
					_fe3d.gameEntity_setPosition(modelID, _initialModelPosition[modelID]);
					_fe3d.gameEntity_setRotationOrigin(modelID, Vec3(0.0f));
					_fe3d.gameEntity_setRotation(modelID, _initialModelRotation[modelID]);
					_fe3d.gameEntity_setSize(modelID, _initialModelSize[modelID]);

					// Reset part transformations
					for (auto& partName : _fe3d.gameEntity_getPartNames(modelID))
					{
						// Only named parts
						if (!partName.empty())
						{
							_fe3d.gameEntity_setPosition(modelID, Vec3(0.0f), partName);
							_fe3d.gameEntity_setRotationOrigin(modelID, Vec3(0.0f), partName);
							_fe3d.gameEntity_setRotation(modelID, Vec3(0.0f), partName);
							_fe3d.gameEntity_setSize(modelID, Vec3(1.0f), partName);
						}
					}
				}

				// General data
				auto position = _fe3d.gameEntity_getPosition(modelID);
				auto rotation = _fe3d.gameEntity_getRotation(modelID);
				auto size = _fe3d.gameEntity_getSize(modelID);
				auto meshPath = _fe3d.gameEntity_getMeshPath(modelID);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(modelID);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(modelID);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(modelID);
				auto normalMapPath = _fe3d.gameEntity_getNormalMapPath(modelID);
				auto isFrozen = _fe3d.gameEntity_isStaticToCamera(modelID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(modelID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(modelID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(modelID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(modelID);
				auto specularFactor = _fe3d.gameEntity_getSpecularFactor(modelID);
				auto specularIntensity = _fe3d.gameEntity_getSpecularIntensity(modelID);
				auto lightness = _initialModelLightness[modelID];
				auto color = _fe3d.gameEntity_getColor(modelID);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(modelID);
				auto lodID = _fe3d.gameEntity_getLevelOfDetailEntityID(modelID);
				auto isInstanced = _fe3d.gameEntity_isInstanced(modelID);
				auto instancedOffsets = _fe3d.gameEntity_getInstancedOffsets(modelID);
				auto animationID = _animationEditor.getPlayingAnimationNames(modelID).empty() ? "" :
					_animationEditor.getPlayingAnimationNames(modelID).front();

				// Reflection type
				int reflectionType;
				if (_fe3d.gameEntity_isSceneReflective(modelID))
				{
					reflectionType = 2;
				}
				else if (_fe3d.gameEntity_isSkyReflective(modelID))
				{
					reflectionType = 1;
				}
				else
				{
					reflectionType = 0;
				}

				// AABB data
				vector<string> aabbNames;
				vector<Vec3> aabbPositions;
				vector<Vec3> aabbSizes;
				for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(modelID, true, false))
				{
					aabbNames.push_back(aabbID.substr(string(modelID + "_").size()));
					aabbPositions.push_back(_fe3d.aabbEntity_getPosition(aabbID));
					aabbSizes.push_back(_fe3d.aabbEntity_getSize(aabbID));
				}

				// Perform empty string & space conversions
				diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "?" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "?" : reflectionMapPath;
				normalMapPath = (normalMapPath == "") ? "?" : normalMapPath;
				lodID = (lodID == "") ? "?" : lodID;
				animationID = (animationID == "") ? "?" : animationID;
				std::replace(meshPath.begin(), meshPath.end(), ' ', '?');
				std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
				std::replace(lightMapPath.begin(), lightMapPath.end(), ' ', '?');
				std::replace(reflectionMapPath.begin(), reflectionMapPath.end(), ' ', '?');
				std::replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
				std::replace(lodID.begin(), lodID.end(), ' ', '?');
				std::replace(animationID.begin(), animationID.end(), ' ', '?');

				// 1 model -> 1 line in file
				file <<
					"MODEL " <<
					modelID << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					rotation.x << " " <<
					rotation.y << " " <<
					rotation.z << " " <<
					size.x << " " <<
					size.y << " " <<
					size.z << " " <<
					meshPath << " " <<
					diffuseMapPath << " " <<
					lightMapPath << " " <<
					reflectionMapPath << " " <<
					normalMapPath << " " <<
					isFrozen << " " <<
					isFaceCulled << " " <<
					isShadowed << " " <<
					isTransparent << " " <<
					reflectionType << " " <<
					isSpecular << " " <<
					specularFactor << " " <<
					specularIntensity << " " <<
					lightness << " " <<
					color.r << " " <<
					color.g << " " <<
					color.b << " " <<
					uvRepeat << " " <<
					lodID << " " <<
					isInstanced << " " <<
					animationID;

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
		for (auto& billboardID : _fe3d.billboardEntity_getAllIDs())
		{
			// Check if not a preview entity
			if (billboardID[0] != '@')
			{
				// Retrieve all valus
				auto position = _fe3d.billboardEntity_getPosition(billboardID);
				auto rotation = _fe3d.billboardEntity_getRotation(billboardID);
				auto size = _fe3d.billboardEntity_getSize(billboardID);
				auto color = _fe3d.billboardEntity_getColor(billboardID);
				auto diffusePath = _fe3d.billboardEntity_getDiffuseMapPath(billboardID);
				auto fontPath = _fe3d.billboardEntity_getFontPath(billboardID);
				auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
				auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
				auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
				auto isTransparent = _fe3d.billboardEntity_isTransparent(billboardID);
				auto isAnimated = _fe3d.billboardEntity_isAnimationPlaying(billboardID);
				auto animationRows = _fe3d.billboardEntity_getAnimationRows(billboardID);
				auto animationColumns = _fe3d.billboardEntity_getAnimationColumns(billboardID);
				auto animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(billboardID);
				auto lightness = _initialBillboardLightness[billboardID];

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
					billboardID << " " <<
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
					animationFramestep << " " <<
					lightness << std::endl;
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
		float billboardLightness = _fe3d.billboardEntity_getLightness("@@lightSource");

		file <<
			"DIRECTIONAL_LIGHT " <<
			directionalLightingPosition.x << " " <<
			directionalLightingPosition.y << " " <<
			directionalLightingPosition.z << " " <<
			directionalLightingColor.r << " " <<
			directionalLightingColor.g << " " <<
			directionalLightingColor.b << " " <<
			directionalLightingIntensity << " " <<
			billboardSize << " " <<
			billboardLightness << std::endl;

		// Point lights
		for (auto& lightID : _fe3d.lightEntity_getAllIDs())
		{
			// Check if not preview light
			if (lightID[0] != '@')
			{
				auto position = _fe3d.lightEntity_getPosition(lightID);
				auto color = _fe3d.lightEntity_getColor(lightID);
				auto intensity = _fe3d.lightEntity_getIntensity(lightID);
				auto distance = _fe3d.lightEntity_getDistanceFactor(lightID);

				// Write line to file
				file <<
					"POINT_LIGHT " <<
					lightID << " " <<
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

		// Audio casters
		for (auto& audioID : _fe3d.audioEntity_getAllIDs())
		{
			// Check if not preview audio
			if (audioID[0] != '@')
			{
				string audioPath = _fe3d.audioEntity_getFilePath(audioID);
				auto position = _fe3d.audioEntity_getPosition(audioID);
				auto volume = _fe3d.audioEntity_getMaxVolume(audioID);
				auto distance = _fe3d.audioEntity_getMaxDistance(audioID);

				// Perform empty string & space conversions
				audioPath = (audioPath == "") ? "?" : audioPath;
				std::replace(audioPath.begin(), audioPath.end(), ' ', '?');

				// Write line to file
				file <<
					"AUDIO " <<
					audioID << " " <<
					audioPath << " " <<
					position.x << " " <<
					position.y << " " <<
					position.z << " " <<
					volume << " " <<
					distance << std::endl;
			}
		}

		// LOD distance
		file << "LOD_DISTANCE " << _fe3d.gameEntity_getLevelOfDetailDistance() << std::endl;

		// Editor properties
		if (_isEditorLoaded)
		{
			// Editor camera speed
			file << "EDITOR_SPEED " << _customEditorSpeed << std::endl;

			// Editor camera position
			Vec3 position = _fe3d.camera_getPosition();
			file << "EDITOR_POSITION " << position.x << " " << position.y << " " << position.z << std::endl;

			// Editor camera yaw
			file << "EDITOR_YAW " << _fe3d.camera_getYaw() << std::endl;

			// Editor camera pitch
			file << "EDITOR_PITCH " << _fe3d.camera_getPitch() << std::endl;
		}

		// Shadow settings
		bool enabled = _fe3d.gfx_isShadowsEnabled();
		if (enabled)
		{
			float size = _fe3d.gfx_getShadowSize();
			float lightness = _fe3d.gfx_getShadowLightness();
			Vec3 position = _fe3d.gfx_getShadowEyePosition();
			Vec3 center = _fe3d.gfx_getShadowCenter();
			bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
			bool isSoftShadowed = _fe3d.gfx_isSoftShadowingEnabled();
			int interval = _fe3d.gfx_getShadowInterval();
			file << "GRAPHICS_SHADOWS " << enabled << " " << size << " " << lightness << " " << _fe3d.misc_vec2str(position) << " " <<
				_fe3d.misc_vec2str(center) << " " << isFollowingCamera << " " << isSoftShadowed << " " << interval << std::endl;
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
			float maxDistance = _fe3d.gfx_getaMaxDofDistance();
			file << "GRAPHICS_DOF " << enabled << " " << dynamic << " " << blurDistance << " " << maxDistance << std::endl;
		}

		// Fog settings
		enabled = _fe3d.gfx_isFogEnabled();
		if (enabled)
		{
			float minDistance = _fe3d.gfx_getFogMinDistance();
			float maxDistance = _fe3d.gfx_getFogMaxDistance();
			float thickness = _fe3d.gfx_getFogThickness();
			Vec3 color = _fe3d.gfx_getFogColor();
			file << "GRAPHICS_FOG " << enabled << " " << minDistance << " " << maxDistance << " " << thickness << " " << _fe3d.misc_vec2str(color) << std::endl;
		}

		// Lens flare settings
		enabled = _fe3d.gfx_isLensFlareEnabled();
		if (enabled)
		{
			string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
			float intensity = _fe3d.gfx_getLensFlareIntensity();
			float multiplier = _fe3d.gfx_getLensFlareMultiplier();
			flareMapPath = (flareMapPath == "") ? "?" : flareMapPath;
			std::replace(flareMapPath.begin(), flareMapPath.end(), ' ', '?');
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
		if (_isEditorLoaded)
		{
			_fe3d.logger_throwInfo("Scene data from project \"" + _currentProjectID + "\" saved!");
		}
	}
}