#include "core.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;

Core::Core(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{
	_libraryLoader = make_shared<LibraryLoader>();
	_inputHandler = make_shared<InputHandler>();
	_meshLoader = make_shared<MeshLoader>();
	_imageLoader = make_shared<ImageLoader>();
	_audioLoader = make_shared<AudioLoader>();
	_skyEntityManager = make_shared<SkyEntityManager>();
	_terrainEntityManager = make_shared<TerrainEntityManager>();
	_waterEntityManager = make_shared<WaterEntityManager>();
	_modelEntityManager = make_shared<ModelEntityManager>();
	_billboardEntityManager = make_shared<BillboardEntityManager>();
	_aabbEntityManager = make_shared<AabbEntityManager>();
	_quadEntityManager = make_shared<QuadEntityManager>();
	_textEntityManager = make_shared<TextEntityManager>();
	_pointlightEntityManager = make_shared<PointlightEntityManager>();
	_spotlightEntityManager = make_shared<SpotlightEntityManager>();
	_reflectionEntityManager = make_shared<ReflectionEntityManager>();
	_renderWindow = make_shared<RenderWindow>(_libraryLoader->getWindowPointer());
	_masterRenderer = make_shared<MasterRenderer>();
	_bufferCache = make_shared<BufferCache>();
	_renderBus = make_shared<RenderBus>();
	_shadowGenerator = make_shared<ShadowGenerator>();
	_camera = make_shared<Camera>();
	_raycaster = make_shared<Raycaster>();
	_cameraCollisionHandler = make_shared<CameraCollisionHandler>();
	_cameraCollisionDetector = make_shared<CameraCollisionDetector>();
	_networkingServer = make_shared<NetworkingServer>();
	_networkingClient = make_shared<NetworkingClient>();
	_sound2dManager = make_shared<Sound2dManager>();
	_sound3dManager = make_shared<Sound3dManager>();
	_sound2dPlayer = make_shared<Sound2dPlayer>();
	_sound3dPlayer = make_shared<Sound3dPlayer>();
	_timer = make_shared<Timer>();

	_skyEntityManager->inject(_renderBus);
	_terrainEntityManager->inject(_imageLoader);
	_modelEntityManager->inject(_renderBus);
	_modelEntityManager->inject(_timer);
	_modelEntityManager->inject(_reflectionEntityManager);
	_modelEntityManager->inject(_meshLoader);
	_billboardEntityManager->inject(_renderBus);
	_aabbEntityManager->inject(_modelEntityManager);
	_aabbEntityManager->inject(_billboardEntityManager);
	_quadEntityManager->inject(_renderBus);
	_textEntityManager->inject(_renderBus);
	_masterRenderer->inject(_renderBus);
	_masterRenderer->inject(_camera);
	_masterRenderer->inject(_shadowGenerator);
	_masterRenderer->inject(_timer);
	_masterRenderer->inject(_skyEntityManager);
	_masterRenderer->inject(_terrainEntityManager);
	_masterRenderer->inject(_waterEntityManager);
	_masterRenderer->inject(_modelEntityManager);
	_masterRenderer->inject(_billboardEntityManager);
	_masterRenderer->inject(_aabbEntityManager);
	_masterRenderer->inject(_quadEntityManager);
	_masterRenderer->inject(_textEntityManager);
	_masterRenderer->inject(_pointlightEntityManager);
	_masterRenderer->inject(_spotlightEntityManager);
	_masterRenderer->inject(_reflectionEntityManager);
	_shadowGenerator->inject(_renderBus);
	_camera->inject(_renderBus);
	_camera->inject(_renderWindow);
	_raycaster->inject(_terrainEntityManager);
	_raycaster->inject(_renderBus);
	_cameraCollisionHandler->inject(_terrainEntityManager);
	_cameraCollisionHandler->inject(_aabbEntityManager);
	_cameraCollisionHandler->inject(_camera);
	_cameraCollisionHandler->inject(_cameraCollisionDetector);
	_sound2dManager->inject(_audioLoader);
	_sound3dManager->inject(_audioLoader);
	_sound2dPlayer->inject(_sound2dManager);
	_sound3dPlayer->inject(_sound3dManager);
	_sound3dPlayer->inject(_camera);
}

void Core::_start()
{
	if(_isRunning)
	{
		Logger::throwError("Tried to start engine: already running!");
	}

	_isRunning = true;

	_prepare();

	float renderLag = 0.0f;

	while(_isRunning)
	{
		auto previousTime = high_resolution_clock::now();

		if(_fe3d.server_isRunning())
		{
			if(!Config::getInst().isApplicationExported())
			{
				_inputHandler->update();
			}

			_update();
			_timer->increasePassedFrameCount();

			if(!Config::getInst().isApplicationExported())
			{
				_render();
			}
		}
		else
		{
			renderLag += _deltaTimeMS;

			if(renderLag > (Config::MS_PER_UPDATE * 10.0f))
			{
				renderLag = Config::MS_PER_UPDATE;
			}

			while(renderLag >= Config::MS_PER_UPDATE)
			{
				_inputHandler->update();

				_update();

				renderLag -= Config::MS_PER_UPDATE;
				renderLag = max(renderLag, 0.0f);
				_timer->increasePassedFrameCount();
			}

			_render();
		}

		auto currentTime = high_resolution_clock::now();
		auto timeDifference = duration_cast<nanoseconds>(currentTime - previousTime);
		_deltaTimeMS = static_cast<float>(timeDifference.count()) / 1000000.0f;
	}

	_fe3d.FE3D_CONTROLLER_TERMINATE();
}

void Core::_pause()
{
	if(_isPaused)
	{
		Logger::throwError("Tried to resume engine: already paused!");
	}

	_isPaused = true;
}

void Core::_resume()
{
	if(!_isPaused)
	{
		Logger::throwError("Tried to resume engine: not paused!");
	}

	_isPaused = false;
}

void Core::_stop()
{
	if(!_isRunning)
	{
		Logger::throwError("Tried to stop engine: not running!");
	}

	_isRunning = false;
}

void Core::_update()
{
	static ivec2 lastCursorPosition = _renderWindow->getCursorPosition();

	if(_inputHandler->isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		_stop();
		return;
	}

	_timer->startDeltaPart("coreUpdate");
	_fe3d._isRaycastUpdated = false;
	_fe3d._hoveredAabbID = "";
	_fe3d.FE3D_CONTROLLER_UPDATE();
	_timer->stopDeltaPart();

	if(!(Config::getInst().isApplicationExported() && _fe3d.server_isRunning()))
	{
		if(!_isPaused)
		{
			_timer->startDeltaPart("physicsUpdate");
			_camera->update(lastCursorPosition);
			_raycaster->update(_fe3d.misc_getCursorPositionRelativeToViewport());
			_cameraCollisionHandler->update();
			_camera->updateMatrices();
			_timer->stopDeltaPart();

			_timer->startDeltaPart("skyEntityUpdate");
			_skyEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("waterEntityUpdate");
			_waterEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("modelEntityUpdate");
			_modelEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("billboardEntityUpdate");
			_billboardEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("aabbEntityUpdate");
			_aabbEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("lightEntityUpdate");
			_pointlightEntityManager->update();
			_spotlightEntityManager->update();
			_timer->stopDeltaPart();
			_timer->startDeltaPart("reflectionEntityUpdate");
			_reflectionEntityManager->update();
			_timer->stopDeltaPart();

			_timer->startDeltaPart("shadowUpdate");
			_shadowGenerator->update();
			_timer->stopDeltaPart();

			_timer->startDeltaPart("soundUpdate");
			_sound2dManager->update();
			_sound3dManager->update();
			_sound2dPlayer->update();
			_sound3dPlayer->update();
			_timer->stopDeltaPart();
		}

		_timer->startDeltaPart("guiEntityUpdate");
		_quadEntityManager->update();
		_textEntityManager->update();
		_timer->stopDeltaPart();
	}

	_timer->startDeltaPart("networkUpdate");
	_networkingServer->update();
	_networkingClient->update();
	_timer->stopDeltaPart();

	_masterRenderer->update();

	if(!Config::getInst().isApplicationExported())
	{
		static float opacity = 0.0f;

		if(opacity < 1.0f)
		{
			_renderWindow->setOpacity(opacity);
			opacity += 0.01f;
		}
		if(opacity > 1.0f)
		{
			opacity = 1.0f;
			_renderWindow->setOpacity(opacity);
		}
	}

	lastCursorPosition = _renderWindow->getCursorPosition();
}