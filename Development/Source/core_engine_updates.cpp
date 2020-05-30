#include <fstream>

#include "core_engine.hpp"
#include "configuration.hpp"
#include "shader_bus.hpp"

void CoreEngine::_setupApplication()
{
	// Display engine intro
	GuiEntity intro;
	intro.load("intro");
	intro.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	intro.setDiffuseMap(_texLoader.getTexture("Engine\\Textures\\intro.png", true, true));

	// Get intro resolution
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = float(DM.w);
	float height = float(DM.h);
	ivec2 introResolution = ivec2(int(width * 0.4f), int(height * 0.4f));
	_windowManager.setSize(introResolution);
	_windowManager.showWindow();
	_renderEngine.renderEngineIntro(&intro, introResolution);
	_windowManager.swapBackBuffer();

	// Initialize engine controller
	_fe3d.FE3D_CONTROLLER_INIT();

	// Set new window properties
	_windowManager.setSize(Config::getInst().getWindowSize());
	_windowManager.showBorder();
}

void CoreEngine::_updateApplication()
{
	// Exit application
	if (_inputHandler.getKeyDown(Input::WINDOW_X_BUTTON))
	{
		_stop();
	}

	// User updates
	_fe3d.FE3D_CONTROLLER_UPDATE();

	// Camera updates
	_cameraManager.update(_windowManager);

	// Physics updates
	_mousePicker.update(_windowManager.getMousePos(), _terrainEntityManager);
	_collisionResolver.update(_aabbEntityManager.getEntities(), _terrainEntityManager, _cameraManager);

	// 3D entity updates
	_skyEntityManager.update();
	_waterEntityManager.update();
	_gameEntityManager.update();
	_billboardEntityManager.update();
	_aabbEntityManager.update(_gameEntityManager.getEntities());

	// 2D entity updates
	_guiEntityManager.update();
	_textEntityManager.update();

	// Miscellaneous updates
	_shadowManager.update(_shaderBus);
	_cameraManager.updateMatrices();
	_audioPlayer.update(_cameraManager, _audioManager.getChunks(), _audioManager.getMusic());

	// Performance profiling updates
	_updatePerformanceProfiler();
}

void CoreEngine::_renderApplication()
{
	EntityBus entityBus
	(
		_skyEntityManager.getSelectedSky(), _terrainEntityManager.getSelectedTerrain(), _waterEntityManager.getSelectedWater(), 
		_gameEntityManager.getEntities(), _billboardEntityManager.getEntities(), _aabbEntityManager.getEntities(),
		_lightEntityManager.getEntities(), _guiEntityManager.getEntities(), _textEntityManager.getEntities()
	);

	// Render entities
	_renderEngine.renderScene(&entityBus, _cameraManager, _windowManager.getMousePos());

	// Swap GPU buffer
	_windowManager.swapBackBuffer();
}

//void CoreEngine::_initWorldEditor()
//{
//	_fe3d.WE3D_INIT_EDITOR();
//	_modelEditor.loadModels(_gameEntityManager);
//
//	// Check if a terrain selected
//	if (_terrainEntityManager.getSelectedTerrain() == nullptr)
//	{
//		Logger::getInst().throwError("No terrain selected while in world editor state!");
//	}
//}

//void CoreEngine::_updateModelEditor()
//{
//	_modelEditor.update(_windowManager.getMousePos(), _inputHandler);
//	_textEntityManager.addTextEntity("modelName", "Model: " + _modelEditor.getSelectedModel()->getModelName(), "font", vec3(1.0f), vec2(0.3f, -0.75f), 0.0f, vec2(0.5f, 0.15f), true, true, true);
//	_shadowManager.update(_shaderBus);
//	_guiEntityManager.update();
//	_textEntityManager.update();
//}

//void CoreEngine::_updateWorldEditor()
//{
//	_timer.start("worldEditor");
//	if (_terrainEntityManager.getSelectedTerrain() != nullptr)
//	{
//		bool placementMode;
//		if (_inputHandler.getMouseToggled(Input::MOUSE_BUTTON_MIDDLE)) // Mouse picker
//		{
//			_windowManager.showMouseCursor();
//			_cameraManager.disableFirstPersonView();
//			placementMode = true;
//		}
//		else // Free movement
//		{
//			_windowManager.hideMouseCursor();
//			_cameraManager.enableFirstPersonView();
//			placementMode = false;
//		}
//
//		// Update
//		_fe3d.WE3D_UPDATE_EDITOR();
//		_mousePicker.update(_windowManager.getMousePos(), _terrainEntityManager);
//		_skyEntityManager.update();
//		_waterEntityManager.update();
//		_gameEntityManager.update();
//		_guiEntityManager.update();
//		_shadowManager.update(_shaderBus);
//		_worldEditor.update(_windowManager.getMousePos(), _mousePicker.getTerrainPoint(), placementMode,
//			_modelEditor.getModels(), _cameraManager, _textEntityManager, _inputHandler);
//		_cameraManager.update(_windowManager);
//		_textEntityManager.update();
//	}
//	else
//	{
//		Logger::getInst().throwInfo("No terrain selected for editing!");
//	}
//	_timer.stop();
//}

void CoreEngine::_updatePerformanceProfiler()
{
	// Update statistics GUI
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
			auto fps = 1000.0f;
			auto fpsText = "FPS: " + std::to_string(fps);
			_textEntityManager.addTextEntity("fps", fpsText, "font", vec3(1.0f), vec2(x, y), 0.0f, vec2(width * fpsText.size(), height), true, true);
			steps = 0;

			// Performance profiling
			vector<string> elementNames =
			{
				"reflectionPreRender", "refractionPreRender", "shadowPreRender", "depthPreRender", "skyEntityRender", "terrainEntityRender", "waterEntityRender",
				"gameEntityRender", "billboardEntityRender", "aabbEntityRender", "antiAliasing", "postProcessing", "guiEntityRender", "textEntityRender"
			};

			// Add new text entities
			for (size_t i = 0; i < elementNames.size(); i++)
			{
				auto percentage = std::to_string((_timer.getDeltaPart(elementNames[i]) / _timer.getDeltaPartSum()) * 100.0f);
				auto text = elementNames[i] + ": " + percentage + "%";
				_textEntityManager.addTextEntity(elementNames[i], text, "font", vec3(1.0f), vec2(x, y - height - (height * float(int(i)))), 0.0f, vec2(width * text.size(), height), true, true);
			}
		}
		else
		{
			steps++;
		}
	}
}