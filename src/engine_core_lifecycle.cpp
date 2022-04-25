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
	_skyEntityManager = make_shared<SkyEntityManager>();
	_terrainEntityManager = make_shared<TerrainEntityManager>();
	_waterEntityManager = make_shared<WaterEntityManager>();
	_modelEntityManager = make_shared<ModelEntityManager>();
	_quad3dEntityManager = make_shared<Quad3dEntityManager>();
	_text3dEntityManager = make_shared<Text3dEntityManager>();
	_aabbEntityManager = make_shared<AabbEntityManager>();
	_quad2dEntityManager = make_shared<Quad2dEntityManager>();
	_text2dEntityManager = make_shared<Text2dEntityManager>();
	_pointlightEntityManager = make_shared<PointlightEntityManager>();
	_spotlightEntityManager = make_shared<SpotlightEntityManager>();
	_captorEntityManager = make_shared<CaptorEntityManager>();
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
	_skyEntityManager->inject(_renderStorage);
	_terrainEntityManager->inject(_imageLoader);
	_modelEntityManager->inject(_renderStorage);
	_modelEntityManager->inject(_camera);
	_modelEntityManager->inject(_timer);
	_modelEntityManager->inject(_captorEntityManager);
	_modelEntityManager->inject(_meshLoader);
	_modelEntityManager->inject(_vertexBufferCache);
	_quad3dEntityManager->inject(_renderStorage);
	_quad3dEntityManager->inject(_camera);
	_text3dEntityManager->inject(_renderStorage);
	_text3dEntityManager->inject(_imageLoader);
	_text3dEntityManager->inject(_textureBufferCache);
	_text3dEntityManager->inject(_camera);
	_quad2dEntityManager->inject(_renderStorage);
	_text2dEntityManager->inject(_renderStorage);
	_text2dEntityManager->inject(_imageLoader);
	_text2dEntityManager->inject(_textureBufferCache);
	_aabbEntityManager->inject(_modelEntityManager);
	_aabbEntityManager->inject(_quad3dEntityManager);
	_aabbEntityManager->inject(_text3dEntityManager);
	_sound3dManager->inject(_audioLoader);
	_sound3dManager->inject(_waveBufferCache);
	_sound2dManager->inject(_audioLoader);
	_sound2dManager->inject(_waveBufferCache);
	_masterRenderer->inject(_renderStorage);
	_masterRenderer->inject(_camera);
	_masterRenderer->inject(_timer);
	_masterRenderer->inject(_skyEntityManager);
	_masterRenderer->inject(_terrainEntityManager);
	_masterRenderer->inject(_waterEntityManager);
	_masterRenderer->inject(_modelEntityManager);
	_masterRenderer->inject(_quad3dEntityManager);
	_masterRenderer->inject(_text3dEntityManager);
	_masterRenderer->inject(_aabbEntityManager);
	_masterRenderer->inject(_quad2dEntityManager);
	_masterRenderer->inject(_text2dEntityManager);
	_masterRenderer->inject(_pointlightEntityManager);
	_masterRenderer->inject(_spotlightEntityManager);
	_masterRenderer->inject(_captorEntityManager);
	_camera->inject(_renderWindow);
	_raycastCalculator->inject(_camera);
	_raycastIntersector->inject(_raycastCalculator);
	_raycastIntersector->inject(_terrainEntityManager);
	_raycastIntersector->inject(_aabbEntityManager);
	_cameraCollisionResponder->inject(_terrainEntityManager);
	_cameraCollisionResponder->inject(_aabbEntityManager);
	_cameraCollisionResponder->inject(_camera);
	_cameraCollisionResponder->inject(_cameraCollisionDetector);
	_animation3dPlayer->inject(_animation3dManager);
	_animation3dPlayer->inject(_modelEntityManager);
	_animation2dPlayer->inject(_animation2dManager);
	_animation2dPlayer->inject(_quad3dEntityManager);
	_animation2dPlayer->inject(_quad2dEntityManager);
	_sound3dPlayer->inject(_sound3dManager);
	_sound3dPlayer->inject(_camera);
	_sound2dPlayer->inject(_sound2dManager);

	_timer->createClock("total");
	_timer->createClock("mainUpdate");
	_timer->createClock("physicsUpdate");
	_timer->createClock("3dEntityUpdate");
	_timer->createClock("2dEntityUpdate");
	_timer->createClock("renderUpdate");
	_timer->createClock("animationUpdate");
	_timer->createClock("soundUpdate");
	_timer->createClock("networkUpdate");
	_timer->createClock("miscUpdate");
	_timer->createClock("depthPreRender");
	_timer->createClock("shadowPreRender");
	_timer->createClock("reflectionPreRender");
	_timer->createClock("refractionPreRender");
	_timer->createClock("waterPreRender");
	_timer->createClock("3dEntityRender");
	_timer->createClock("antiAliasingPostRender");
	_timer->createClock("bloomPreRender");
	_timer->createClock("dofPreRender");
	_timer->createClock("lensFlarePreRender");
	_timer->createClock("motionBlurPreRender");
	_timer->createClock("2dEntityRender");
	_timer->createClock("bufferSwap");

	_updateDeltaTimes.insert({"mainUpdate", 0.0f});
	_updateDeltaTimes.insert({"physicsUpdate", 0.0f});
	_updateDeltaTimes.insert({"3dEntityUpdate", 0.0f});
	_updateDeltaTimes.insert({"2dEntityUpdate", 0.0f});
	_updateDeltaTimes.insert({"renderUpdate", 0.0f});
	_updateDeltaTimes.insert({"animationUpdate", 0.0f});
	_updateDeltaTimes.insert({"soundUpdate", 0.0f});
	_updateDeltaTimes.insert({"networkUpdate", 0.0f});
	_updateDeltaTimes.insert({"miscUpdate", 0.0f});

	_renderDeltaTimes.insert({"depthPreRender", 0.0f});
	_renderDeltaTimes.insert({"shadowPreRender", 0.0f});
	_renderDeltaTimes.insert({"reflectionPreRender", 0.0f});
	_renderDeltaTimes.insert({"refractionPreRender", 0.0f});
	_renderDeltaTimes.insert({"waterPreRender", 0.0f});
	_renderDeltaTimes.insert({"3dEntityRender", 0.0f});
	_renderDeltaTimes.insert({"antiAliasingPostRender", 0.0f});
	_renderDeltaTimes.insert({"bloomPreRender", 0.0f});
	_renderDeltaTimes.insert({"dofPreRender", 0.0f});
	_renderDeltaTimes.insert({"lensFlarePreRender", 0.0f});
	_renderDeltaTimes.insert({"motionBlurPreRender", 0.0f});
	_renderDeltaTimes.insert({"2dEntityRender", 0.0f});
	_renderDeltaTimes.insert({"bufferSwap", 0.0f});
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