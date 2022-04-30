#include "engine_core.hpp"
#include "engine_controller.hpp"

EngineCore::EngineCore()
{
	_renderWindow = make_shared<RenderWindow>();
	_timer = make_shared<Timer>();
	_inputHandler = make_shared<InputHandler>();
	_meshLoader = make_shared<MeshLoader>();
	_imageLoader = make_shared<ImageLoader>();
	_audioLoader = make_shared<AudioLoader>();
	_skyManager = make_shared<SkyManager>();
	_terrainManager = make_shared<TerrainManager>();
	_waterManager = make_shared<WaterManager>();
	_modelManager = make_shared<ModelManager>();
	_quad3dManager = make_shared<Quad3dManager>();
	_text3dManager = make_shared<Text3dManager>();
	_aabbManager = make_shared<AabbManager>();
	_quad2dManager = make_shared<Quad2dManager>();
	_text2dManager = make_shared<Text2dManager>();
	_pointlightManager = make_shared<PointlightManager>();
	_spotlightManager = make_shared<SpotlightManager>();
	_captorManager = make_shared<CaptorManager>();
	_animation3dManager = make_shared<Animation3dManager>();
	_animation2dManager = make_shared<Animation2dManager>();
	_sound3dManager = make_shared<Sound3dManager>();
	_sound2dManager = make_shared<Sound2dManager>();
	_vertexBufferCache = make_shared<VertexBufferCache>();
	_textureBufferCache = make_shared<TextureBufferCache>();
	_waveBufferCache = make_shared<WaveBufferCache>();
	_renderStorage = make_shared<RenderStorage>();
	_masterRenderer = make_shared<MasterRenderer>();
	_camera = make_shared<Camera>();
	_raycastCalculator = make_shared<RaycastCalculator>();
	_raycastIntersector = make_shared<RaycastIntersector>();
	_cameraCollisionResponder = make_shared<CameraCollisionResponder>();
	_cameraCollisionDetector = make_shared<CameraCollisionDetector>();
	_animation3dPlayer = make_shared<Animation3dPlayer>();
	_animation2dPlayer = make_shared<Animation2dPlayer>();
	_sound3dPlayer = make_shared<Sound3dPlayer>();
	_sound2dPlayer = make_shared<Sound2dPlayer>();
	_networkingHelper = make_shared<NetworkingHelper>();
	_networkingServer = make_shared<NetworkingServer>();
	_networkingClient = make_shared<NetworkingClient>();

	_renderWindow->inject(_inputHandler);
	_skyManager->inject(_renderStorage);
	_terrainManager->inject(_imageLoader);
	_modelManager->inject(_renderStorage);
	_modelManager->inject(_camera);
	_modelManager->inject(_timer);
	_modelManager->inject(_captorManager);
	_modelManager->inject(_meshLoader);
	_modelManager->inject(_vertexBufferCache);
	_quad3dManager->inject(_renderStorage);
	_quad3dManager->inject(_camera);
	_text3dManager->inject(_renderStorage);
	_text3dManager->inject(_imageLoader);
	_text3dManager->inject(_textureBufferCache);
	_text3dManager->inject(_camera);
	_quad2dManager->inject(_renderStorage);
	_text2dManager->inject(_renderStorage);
	_text2dManager->inject(_imageLoader);
	_text2dManager->inject(_textureBufferCache);
	_aabbManager->inject(_modelManager);
	_aabbManager->inject(_quad3dManager);
	_aabbManager->inject(_text3dManager);
	_sound3dManager->inject(_audioLoader);
	_sound3dManager->inject(_waveBufferCache);
	_sound2dManager->inject(_audioLoader);
	_sound2dManager->inject(_waveBufferCache);
	_masterRenderer->inject(_renderStorage);
	_masterRenderer->inject(_camera);
	_masterRenderer->inject(_timer);
	_masterRenderer->inject(_skyManager);
	_masterRenderer->inject(_terrainManager);
	_masterRenderer->inject(_waterManager);
	_masterRenderer->inject(_modelManager);
	_masterRenderer->inject(_quad3dManager);
	_masterRenderer->inject(_text3dManager);
	_masterRenderer->inject(_aabbManager);
	_masterRenderer->inject(_quad2dManager);
	_masterRenderer->inject(_text2dManager);
	_masterRenderer->inject(_pointlightManager);
	_masterRenderer->inject(_spotlightManager);
	_masterRenderer->inject(_captorManager);
	_camera->inject(_renderWindow);
	_raycastCalculator->inject(_camera);
	_raycastIntersector->inject(_raycastCalculator);
	_raycastIntersector->inject(_terrainManager);
	_raycastIntersector->inject(_aabbManager);
	_cameraCollisionResponder->inject(_terrainManager);
	_cameraCollisionResponder->inject(_aabbManager);
	_cameraCollisionResponder->inject(_camera);
	_cameraCollisionResponder->inject(_cameraCollisionDetector);
	_animation3dPlayer->inject(_animation3dManager);
	_animation3dPlayer->inject(_modelManager);
	_animation2dPlayer->inject(_animation2dManager);
	_animation2dPlayer->inject(_quad3dManager);
	_animation2dPlayer->inject(_quad2dManager);
	_sound3dPlayer->inject(_sound3dManager);
	_sound3dPlayer->inject(_camera);
	_sound2dPlayer->inject(_sound2dManager);

	_timer->createClock("total");
	_timer->createClock("mainUpdate");
	_timer->createClock("physicsUpdate");
	_timer->createClock("environmentUpdate");
	_timer->createClock("modelUpdate");
	_timer->createClock("quadUpdate");
	_timer->createClock("textUpdate");
	_timer->createClock("aabbUpdate");
	_timer->createClock("lightUpdate");
	_timer->createClock("captorUpdate");
	_timer->createClock("renderUpdate");
	_timer->createClock("animationUpdate");
	_timer->createClock("soundUpdate");
	_timer->createClock("networkUpdate");
	_timer->createClock("depthPreRender");
	_timer->createClock("shadowPreRender");
	_timer->createClock("reflectionPreRender");
	_timer->createClock("refractionPreRender");
	_timer->createClock("waterPreRender");
	_timer->createClock("3dRender");
	_timer->createClock("antiAliasingPostRender");
	_timer->createClock("bloomPreRender");
	_timer->createClock("dofPreRender");
	_timer->createClock("lensFlarePreRender");
	_timer->createClock("motionBlurPreRender");
	_timer->createClock("2dRender");
	_timer->createClock("bufferSwap");

	_updateDeltaTimes.push_back({"mainUpdate", 0.0f});
	_updateDeltaTimes.push_back({"physicsUpdate", 0.0f});
	_updateDeltaTimes.push_back({"environmentUpdate", 0.0f});
	_updateDeltaTimes.push_back({"modelUpdate", 0.0f});
	_updateDeltaTimes.push_back({"quadUpdate", 0.0f});
	_updateDeltaTimes.push_back({"textUpdate", 0.0f});
	_updateDeltaTimes.push_back({"aabbUpdate", 0.0f});
	_updateDeltaTimes.push_back({"lightUpdate", 0.0f});
	_updateDeltaTimes.push_back({"captorUpdate", 0.0f});
	_updateDeltaTimes.push_back({"renderUpdate", 0.0f});
	_updateDeltaTimes.push_back({"animationUpdate", 0.0f});
	_updateDeltaTimes.push_back({"soundUpdate", 0.0f});
	_updateDeltaTimes.push_back({"networkUpdate", 0.0f});

	_renderDeltaTimes.push_back({"depthPreRender", 0.0f});
	_renderDeltaTimes.push_back({"shadowPreRender", 0.0f});
	_renderDeltaTimes.push_back({"reflectionPreRender", 0.0f});
	_renderDeltaTimes.push_back({"refractionPreRender", 0.0f});
	_renderDeltaTimes.push_back({"waterPreRender", 0.0f});
	_renderDeltaTimes.push_back({"3dRender", 0.0f});
	_renderDeltaTimes.push_back({"antiAliasingPostRender", 0.0f});
	_renderDeltaTimes.push_back({"bloomPreRender", 0.0f});
	_renderDeltaTimes.push_back({"dofPreRender", 0.0f});
	_renderDeltaTimes.push_back({"lensFlarePreRender", 0.0f});
	_renderDeltaTimes.push_back({"motionBlurPreRender", 0.0f});
	_renderDeltaTimes.push_back({"2dRender", 0.0f});
	_renderDeltaTimes.push_back({"bufferSwap", 0.0f});
}

void EngineCore::start()
{
	if(_isRunning)
	{
		abort();
	}

	_isRunning = true;

	_initialize();

	float renderLag = 0.0f;

	while(_isRunning)
	{
		_timer->startClock("total");

		if(_networkingServer->isRunning())
		{
			_engineController->update();

			_networkingServer->update();

			_timer->increasePassedUpdateCount();
		}
		else
		{
			const auto millisecondsPerUpdate = (1000.0f / _timer->getUpdateCountPerSecond());

			renderLag += _totalDeltaTime;

			if(renderLag > (millisecondsPerUpdate * 100.0f))
			{
				renderLag = millisecondsPerUpdate;
			}

			while(renderLag >= millisecondsPerUpdate)
			{
				_update();

				renderLag -= millisecondsPerUpdate;
				renderLag = max(0.0f, renderLag);
			}

			_render();
		}

		_timer->stopClock("total");

		_totalDeltaTime = _timer->getClockDeltaTime("total");
	}

	_engineController->terminate();
}

void EngineCore::stop()
{
	if(!_isRunning)
	{
		abort();
	}

	_isRunning = false;
}