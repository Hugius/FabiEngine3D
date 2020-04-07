#include <fstream>

#include "CoreEngine.hpp"
#include "Configuration.hpp"
#include "ShaderBus.hpp"

void CoreEngine::_setupApplication()
{
	// Engine intro
	_displayIntroScene();

	// Window properties
	_initWindow();

	// Setup selected engine state
	//switch (_engineState)
	//{
	//	case(EngineState::STATE_GAME): // Setup game
	//	{
	//		_initGame();
	//		break;
	//	}
	//	
	//	case(EngineState::STATE_MODEL_EDITOR): // Setup model editor
	//	{
	//		_initModelEditor();
	//		break;
	//	}

	//	case(EngineState::STATE_WORLD_EDITOR): // Setup world editor
	//	{
	//		_initWorldEditor();
	//		break;
	//	}
	//}
}

void CoreEngine::_updateApplication()
{
	// Exit application
	if (_inputHandler.getKeyDown(Input::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// Update selected engine state
	switch (_engineState)
	{
		case(EngineState::STATE_GAME): // Update game
		{
			if (_isPaused)
			{
				_fe3d.WE3D_UPDATE_GAME(_timer.getDeltaTime());
			}
			else
			{
				_updateGame();
			}
			break;
		}
	
		case(EngineState::STATE_MODEL_EDITOR): // Update model editor
		{
			_updateModelEditor();
			break;
		}

		case(EngineState::STATE_WORLD_EDITOR): // Update world editor
		{
			if (_isPaused)
			{
				_fe3d.WE3D_UPDATE_EDITOR(_timer.getDeltaTime());
			}
			else
			{
				_updateWorldEditor();
			}
			break;
		}
	}
}

void CoreEngine::_renderApplication()
{
	_timer.start("entityBus");
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedSky(), _terrainEntityManager.getSelectedTerrain(), _waterEntityManager.getSelectedWater(), 
		_engineState == EngineState::STATE_MODEL_EDITOR ? vector<GameEntity*>{_modelEditor.getSelectedModel()} : _gameEntityManager.getEntities(),
		_billboardEntityManager.getEntities(), _aabbEntityManager.getEntities(),
		_lightEntityManager.getEntities(), _guiEntityManager.getEntities(), _textEntityManager.getEntities()
	);
	_timer.stop();

	// Render entities
	_renderEngine.renderScene(&entityBus, _cameraManager, _isPaused ? ivec2(0) : _windowManager.getMousePos());

	// Swap GPU buffer
	_timer.start("renderSwap");
	_windowManager.swapBackBuffer();
	_timer.stop();
}

void CoreEngine::_displayIntroScene()
{
	GuiEntity intro;
	intro.load("intro");
	intro.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	intro.setDiffuseMap(_texLoader.getTexture("../Engine/Textures/intro", true, true));
	_windowManager.setSize(ivec2(720, 480));
	_windowManager.showWindow();
	_renderEngine.renderEngineIntro(&intro, ivec2(720, 480));
	_windowManager.swapBackBuffer();
}

void CoreEngine::_initWindow()
{
	_windowManager.setSize(Config::getInst().getWindowSize());
	_windowManager.showBorder();
}

void CoreEngine::_initGame()
{
	_fe3d.WE3D_INIT_GAME();
}

void CoreEngine::_initModelEditor()
{
	_modelEditor.loadModels(_gameEntityManager);
	_fe3d.camera_load(90.0f, 0.1f, 100.0f, vec3(-1.5f, 5.0f, 15.0f), 0.0f);
	_cameraManager.setYaw(-90.0f);
	_cameraManager.updateMatrices();
	_fe3d.gfx_addAmbientLighting(1.0f);
	_fe3d.gfx_addDirectionalLighting(vec3(1000.0f), 1.0f);
	_fe3d.gfx_addMSAA();
	_fe3d.gfx_addBloom(0.975f, 0.0f, 10);
	_fe3d.gfx_addLightMapping();
	_fe3d.gfx_addShadows(vec3(15.0f), vec3(0.0f), 40.0f, 40.0f);
	_fe3d.gfx_addSkyReflections(0.5f);
	_fe3d.gfx_addSpecularLighting(32.0f);
	_shaderBus.setDayReflectionCubeMap(_texLoader.getCubeMap("../Engine/Textures/Skybox/"));
	_modelEditor.loadGUI(_guiEntityManager, _textEntityManager);
}

void CoreEngine::_initWorldEditor()
{
	_fe3d.WE3D_INIT_EDITOR();
	_modelEditor.loadModels(_gameEntityManager);

	// Check if a terrain selected
	if (_terrainEntityManager.getSelectedTerrain() == nullptr)
	{
		Logger::getInst().throwError("No terrain selected while in world editor state!");
	}
}

void CoreEngine::_updateGame()
{
	// Delta time problems
	if (_timer.getDeltaTime() >= 100.0f)
	{
		// Correct delta after resource loading
		if (_timer.getDeltaTime() >= 500.0f)
		{
			_timer.setCustomDeltaTime(1.0f);
		}
		else // Lag warning
		{
			Logger::getInst().throwWarning("FabiEngine3D is lagging, possible causes:");
			Logger::getInst().throwWarning("	- GFX settings too high in Config.we3d");
			Logger::getInst().throwWarning("	- Too much game entities");
			Logger::getInst().throwWarning("	- Too high poly OBJ models");
			Logger::getInst().throwWarning("	- Ingame resource loading");
		}
	}

	// Camera updates
	_timer.start("cameraUpdates");
	_cameraManager.update(_windowManager, _timer.getDeltaTime());
	_timer.stop();

	// User updates
	_timer.start("gameUpdates");
	_fe3d.WE3D_UPDATE_GAME(_timer.getDeltaTime());
	_timer.stop();

	// Physics updates
	_timer.start("raycastUpdates");
	_mousePicker.update(_windowManager.getMousePos(), _terrainEntityManager);
	_timer.stop();
	_timer.start("physicsUpdates");
	_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager, _timer.getDeltaTime());
	_timer.stop();

	// 3D entity updates
	_timer.start("entityUpdates");
	if (!_entitiesPaused)
	{
		_skyEntityManager.update(_timer.getDeltaTime());
		_waterEntityManager.update(_timer.getDeltaTime());
		_gameEntityManager.update(_timer.getDeltaTime());
		_billboardEntityManager.update(_timer.getDeltaTime());
		_aabbEntityManager.update(_gameEntityManager.getEntities());
	}

	// 2D entity updates
	_guiEntityManager.update(_timer.getDeltaTime());
	_textEntityManager.update(_timer.getDeltaTime());
	_timer.stop();

	// Miscellaneous updates
	_timer.start("shadowUpdates");
	_shadowManager.update(_shaderBus);
	_cameraManager.updateMatrices();
	_timer.stop();
	_timer.start("audioUpdates");
	_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic(), _timer.getDeltaTime());
	_timer.stop();

	// Performance profiling updates
	_updatePerformanceProfiler();
}

void CoreEngine::_updateModelEditor()
{
	_modelEditor.update(_windowManager.getMousePos(), _inputHandler, _timer.getDeltaTime());
	_textEntityManager.addTextEntity("modelName", "Model: " + _modelEditor.getSelectedModel()->getModelName(), "font", vec3(1.0f), vec2(0.3f, -0.75f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	_shadowManager.update(_shaderBus);
	_guiEntityManager.update(_timer.getDeltaTime());
	_textEntityManager.update(_timer.getDeltaTime());
}

void CoreEngine::_updateWorldEditor()
{
	_timer.start("worldEditor");
	if (_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		bool placementMode;
		if (_inputHandler.getMouseToggled(Input::MOUSE_BUTTON_MIDDLE)) // Mouse picker
		{
			_windowManager.showMouseCursor();
			_cameraManager.disableFirstPersonView();
			placementMode = true;
		}
		else // Free movement
		{
			_windowManager.hideMouseCursor();
			_cameraManager.enableFirstPersonView();
			placementMode = false;
		}

		// Update
		_fe3d.WE3D_UPDATE_EDITOR(_timer.getDeltaTime());
		_mousePicker.update(_windowManager.getMousePos(), _terrainEntityManager);
		_skyEntityManager.update(_timer.getDeltaTime());
		_waterEntityManager.update(_timer.getDeltaTime());
		_gameEntityManager.update(_timer.getDeltaTime());
		_guiEntityManager.update(_timer.getDeltaTime());
		_shadowManager.update(_shaderBus);
		_worldEditor.update(_windowManager.getMousePos(), _mousePicker.getTerrainPoint(), placementMode,
			_modelEditor.getModels(), _cameraManager, _textEntityManager, _inputHandler, _timer.getDeltaTime());
		_cameraManager.update(_windowManager, _timer.getDeltaTime());
		_textEntityManager.update(_timer.getDeltaTime());
	}
	else
	{
		Logger::getInst().throwInfo("No terrain selected for editing!");
	}
	_timer.stop();
}

void CoreEngine::_updatePerformanceProfiler()
{
	// Update statistics GUI
	_timer.start("stats");
	if (_showStats)
	{
		static int steps = 0;
		const float x = 0.6f;
		const float y = 0.95f;
		const float width = 0.015f;
		const float height = 0.05f;

		if (steps == 50) // Update interval
		{
			// FPS
			auto fps = 1000.0f / _timer.getDeltaTime();
			auto fpsText = "FPS: " + std::to_string(fps);
			_textEntityManager.addTextEntity("fps", fpsText, "font", vec3(1.0f), vec2(x, y), 0.0f, vec2(width * fpsText.size(), height), true, true, false);
			steps = 0;

			// Performance profiling
			vector<string> elements =
			{
				"inputHandle", "gameUpdates", "raycastUpdates", "physicsUpdates", "cameraUpdates", "entityUpdates", "shadowUpdates", "audioUpdates",
				"renderSwap", "SSRPreRender", "waterPreRender", "shadowPreRender", "depthPreRender", "skyEntity", "terrainEntity", "waterEntity",
				"gameEntities", "bBoardEntities", "aabbEntities", "postProcessing", "guiRender", "textRender"
			};

			// Add new text entities
			for (size_t i = 0; i < elements.size(); i++)
			{
				auto nameText = elements[i];
				nameText[0] = toupper(nameText[0]);
				auto percentage = std::to_string((_timer.getDeltaPart(elements[i]) / _timer.getDeltaTime()) * 100.0f);
				auto pcText = nameText + ": " + percentage + "%";
				_textEntityManager.addTextEntity(elements[i], pcText, "font", vec3(1.0f), vec2(x, y - height - (height * float(int(i)))), 0.0f, vec2(width * pcText.size(), height), true, true, false);
			}

			// Other percentage
			float percentage = 0.0f;
			percentage += (_timer.getDeltaPart("entityBus") / _timer.getDeltaTime()) * 100.0f;
			percentage += (_timer.getDeltaPart("aaBind") / _timer.getDeltaTime()) * 100.0f;
			percentage += (_timer.getDeltaPart("aaUnbind") / _timer.getDeltaTime()) * 100.0f;
			percentage += (_timer.getDeltaPart("stats") / _timer.getDeltaTime()) * 100.0f;
			auto pcText = "Misc: " + std::to_string(percentage) + "%";
			_textEntityManager.addTextEntity("misc", pcText, "font", vec3(1.0f), vec2(x, y - height - (height * float(int(elements.size())))), 0.0f, vec2(width * pcText.size(), height), true, true, false);
		}
		else
		{
			steps++;
		}
	}
	_timer.stop();
}