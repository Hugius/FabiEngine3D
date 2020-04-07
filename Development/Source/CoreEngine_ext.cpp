#include <fstream>

#include <WE3D/CoreEngine.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>

void CoreEngine::p_setupApplication()
{
	// Engine intro
	p_displayIntroScene();

	// Setup selected engine state
	switch (p_engineState)
	{
		case(EngineState::STATE_GAME): // Setup game
		{
			p_initGame();
			break;
		}
		
		case(EngineState::STATE_MODEL_EDITOR): // Setup model editor
		{
			p_initModelEditor();
			break;
		}

		case(EngineState::STATE_WORLD_EDITOR): // Setup world editor
		{
			p_initWorldEditor();
			break;
		}
	}

	// Window properties
	p_initWindow();
}

void CoreEngine::p_updateApplication()
{
	// Exit application
	if (p_inputHandler.getKeyDown(Input::WINDOW_X_BUTTON))
	{
		p_stop();
	}

	// Update selected engine state
	switch (p_engineState)
	{
		case(EngineState::STATE_GAME): // Update game
		{
			if (p_isPaused)
			{
				p_we3d.WE3D_UPDATE_GAME(p_timer.getDeltaTime());
			}
			else
			{
				p_updateGame();
			}
			break;
		}
	
		case(EngineState::STATE_MODEL_EDITOR): // Update model editor
		{
			p_updateModelEditor();
			break;
		}

		case(EngineState::STATE_WORLD_EDITOR): // Update world editor
		{
			if (p_isPaused)
			{
				p_we3d.WE3D_UPDATE_EDITOR(p_timer.getDeltaTime());
			}
			else
			{
				p_updateWorldEditor();
			}
			break;
		}
	}
}

void CoreEngine::p_renderApplication()
{
	p_timer.start("entityBus");
	EntityBus entityBus
	(
		p_skyEntityManager.getSelectedSky(), p_terrainEntityManager.getSelectedTerrain(), p_waterEntityManager.getSelectedWater(), 
		p_engineState == EngineState::STATE_MODEL_EDITOR ? vector<GameEntity*>{p_modelEditor.getSelectedModel()} : p_gameEntityManager.getEntities(),
		p_billboardEntityManager.getEntities(), p_aabbEntityManager.getEntities(),
		p_lightEntityManager.getEntities(), p_guiEntityManager.getEntities(), p_textEntityManager.getEntities()
	);
	p_timer.stop();

	// Render entities
	p_renderEngine.renderScene(&entityBus, p_cameraManager, p_isPaused ? ivec2(0) : p_windowManager.getMousePos());

	// Swap GPU buffer
	p_timer.start("renderSwap");
	p_windowManager.swapBackBuffer();
	p_timer.stop();
}

void CoreEngine::p_displayIntroScene()
{
	// Update intro index
	std::fstream file;
	file.open("../Engine/IntroIndex.we3d", std::ios::in | std::ios::out);
	string temp;
	std::getline(file, temp);
	int index = std::stoi(temp);
	int newIndex = index == 6 ? 1 : index + 1;
	file.seekg(0);
	file << newIndex;
	file.flush();
	file.close();

	// Prepare intro screen
	GuiEntity intro;
	intro.load("intro");
	intro.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	intro.setDiffuseMap(p_texLoader.getTexture("../Engine/Textures/intro" + std::to_string(index), true, true));
	p_windowManager.showWindow();
	p_windowManager.setSize(ivec2(720, 480));
	p_renderEngine.renderEngineIntro(&intro, ivec2(720, 480));
	p_windowManager.swapBackBuffer();
}

void CoreEngine::p_initWindow()
{
	// Window size
	p_windowManager.setSize(Config::getInst().getWindowSize());

	// Window borderless option
	if (!Config::getInst().isWindowBorderless())
	{
		p_windowManager.showBorder();
	}

	// Window fullscreen option
	if (Config::getInst().isWindowFullscreen())
	{
		p_windowManager.enableFullscreen();
	}
}

void CoreEngine::p_initGame()
{
	p_we3d.WE3D_INIT_GAME();
}

void CoreEngine::p_initModelEditor()
{
	p_modelEditor.loadModels(p_gameEntityManager);
	p_we3d.camera_load(90.0f, 0.1f, 100.0f, vec3(-1.5f, 5.0f, 15.0f), 0.0f);
	p_cameraManager.setYaw(-90.0f);
	p_cameraManager.updateMatrices();
	p_we3d.gfx_addAmbientLighting(1.0f);
	p_we3d.gfx_addDirectionalLighting(vec3(1000.0f), 1.0f);
	p_we3d.gfx_addMSAA();
	p_we3d.gfx_addBloom(0.975f, 0.0f, 10);
	p_we3d.gfx_addLightMapping();
	p_we3d.gfx_addShadows(vec3(15.0f), vec3(0.0f), 40.0f, 40.0f);
	p_we3d.gfx_addSkyReflections(0.5f);
	p_we3d.gfx_addSpecularLighting(32.0f);
	p_shaderBus.setDayReflectionCubeMap(p_texLoader.getCubeMap("../Engine/Textures/Skybox/"));
	p_modelEditor.loadGUI(p_guiEntityManager, p_textEntityManager);
}

void CoreEngine::p_initWorldEditor()
{
	p_we3d.WE3D_INIT_EDITOR();
	p_modelEditor.loadModels(p_gameEntityManager);

	// Check if a terrain selected
	if (p_terrainEntityManager.getSelectedTerrain() == nullptr)
	{
		Logger::getInst().throwError("No terrain selected while in world editor state!");
	}
}

void CoreEngine::p_updateGame()
{
	// Delta time problems
	if (p_timer.getDeltaTime() >= 100.0f)
	{
		// Correct delta after resource loading
		if (p_timer.getDeltaTime() >= 500.0f)
		{
			p_timer.setCustomDeltaTime(1.0f);
		}
		else // Lag warning
		{
			Logger::getInst().throwWarning("WoodEngine3D is lagging, possible causes:");
			Logger::getInst().throwWarning("	- GFX settings too high in Config.we3d");
			Logger::getInst().throwWarning("	- Too much game entities");
			Logger::getInst().throwWarning("	- Too high poly OBJ models");
			Logger::getInst().throwWarning("	- Ingame resource loading");
		}
	}

	// Camera updates
	p_timer.start("cameraUpdates");
	p_cameraManager.update(p_windowManager, p_timer.getDeltaTime());
	p_timer.stop();

	// User updates
	p_timer.start("gameUpdates");
	p_we3d.WE3D_UPDATE_GAME(p_timer.getDeltaTime());
	p_timer.stop();

	// Physics updates
	p_timer.start("raycastUpdates");
	p_mousePicker.update(p_windowManager.getMousePos(), p_terrainEntityManager);
	p_timer.stop();
	p_timer.start("physicsUpdates");
	p_collisionResolver.update(p_aabbEntityManager.getEntities(), p_terrainEntityManager, p_cameraManager, p_timer.getDeltaTime());
	p_timer.stop();

	// 3D entity updates
	p_timer.start("entityUpdates");
	if (!p_entitiesPaused)
	{
		p_skyEntityManager.update(p_timer.getDeltaTime());
		p_waterEntityManager.update(p_timer.getDeltaTime());
		p_gameEntityManager.update(p_timer.getDeltaTime());
		p_billboardEntityManager.update(p_timer.getDeltaTime());
		p_aabbEntityManager.update(p_gameEntityManager.getEntities());
	}

	// 2D entity updates
	p_guiEntityManager.update(p_timer.getDeltaTime());
	p_textEntityManager.update(p_timer.getDeltaTime());
	p_timer.stop();

	// Miscellaneous updates
	p_timer.start("shadowUpdates");
	p_shadowManager.update(p_shaderBus);
	p_cameraManager.updateMatrices();
	p_timer.stop();
	p_timer.start("audioUpdates");
	p_audioPlayer.update(p_cameraManager, p_audioManager.getChunks(), p_audioManager.getMusic(), p_timer.getDeltaTime());
	p_timer.stop();

	// Performance profiling updates
	p_updatePerformanceProfiler();
}

void CoreEngine::p_updateModelEditor()
{
	p_modelEditor.update(p_windowManager.getMousePos(), p_inputHandler, p_timer.getDeltaTime());
	p_textEntityManager.addTextEntity("modelName", "Model: " + p_modelEditor.getSelectedModel()->getModelName(), "font", vec3(1.0f), vec2(0.3f, -0.75f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
	p_shadowManager.update(p_shaderBus);
	p_guiEntityManager.update(p_timer.getDeltaTime());
	p_textEntityManager.update(p_timer.getDeltaTime());
}

void CoreEngine::p_updateWorldEditor()
{
	p_timer.start("worldEditor");
	if (p_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		bool placementMode;
		if (p_inputHandler.getMouseToggled(Input::MOUSE_BUTTON_MIDDLE)) // Mouse picker
		{
			p_windowManager.showMouseCursor();
			p_cameraManager.disableFirstPersonView();
			placementMode = true;
		}
		else // Free movement
		{
			p_windowManager.hideMouseCursor();
			p_cameraManager.enableFirstPersonView();
			placementMode = false;
		}

		// Update
		p_we3d.WE3D_UPDATE_EDITOR(p_timer.getDeltaTime());
		p_mousePicker.update(p_windowManager.getMousePos(), p_terrainEntityManager);
		p_skyEntityManager.update(p_timer.getDeltaTime());
		p_waterEntityManager.update(p_timer.getDeltaTime());
		p_gameEntityManager.update(p_timer.getDeltaTime());
		p_guiEntityManager.update(p_timer.getDeltaTime());
		p_shadowManager.update(p_shaderBus);
		p_worldEditor.update(p_windowManager.getMousePos(), p_mousePicker.getTerrainPoint(), placementMode,
			p_modelEditor.getModels(), p_cameraManager, p_textEntityManager, p_inputHandler, p_timer.getDeltaTime());
		p_cameraManager.update(p_windowManager, p_timer.getDeltaTime());
		p_textEntityManager.update(p_timer.getDeltaTime());
	}
	else
	{
		Logger::getInst().throwInfo("No terrain selected for editing!");
	}
	p_timer.stop();
}

void CoreEngine::p_updatePerformanceProfiler()
{
	// Update statistics GUI
	p_timer.start("stats");
	if (p_showStats)
	{
		static int steps = 0;
		const float x = 0.6f;
		const float y = 0.95f;
		const float width = 0.015f;
		const float height = 0.05f;

		if (steps == 50) // Update interval
		{
			// FPS
			auto fps = 1000.0f / p_timer.getDeltaTime();
			auto fpsText = "FPS: " + std::to_string(fps);
			p_textEntityManager.addTextEntity("fps", fpsText, "font", vec3(1.0f), vec2(x, y), 0.0f, vec2(width * fpsText.size(), height), true, true, false);
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
				auto percentage = std::to_string((p_timer.getDeltaPart(elements[i]) / p_timer.getDeltaTime()) * 100.0f);
				auto pcText = nameText + ": " + percentage + "%";
				p_textEntityManager.addTextEntity(elements[i], pcText, "font", vec3(1.0f), vec2(x, y - height - (height * float(int(i)))), 0.0f, vec2(width * pcText.size(), height), true, true, false);
			}

			// Other percentage
			float percentage = 0.0f;
			percentage += (p_timer.getDeltaPart("entityBus") / p_timer.getDeltaTime()) * 100.0f;
			percentage += (p_timer.getDeltaPart("aaBind") / p_timer.getDeltaTime()) * 100.0f;
			percentage += (p_timer.getDeltaPart("aaUnbind") / p_timer.getDeltaTime()) * 100.0f;
			percentage += (p_timer.getDeltaPart("stats") / p_timer.getDeltaTime()) * 100.0f;
			auto pcText = "Misc: " + std::to_string(percentage) + "%";
			p_textEntityManager.addTextEntity("misc", pcText, "font", vec3(1.0f), vec2(x, y - height - (height * float(int(elements.size())))), 0.0f, vec2(width * pcText.size(), height), true, true, false);
		}
		else
		{
			steps++;
		}
	}
	p_timer.stop();
}