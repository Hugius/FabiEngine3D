#include "engine_core.hpp"
#include "engine_interface.hpp"
#include "engine_controller.hpp"
#include "tools.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;

EngineCore::EngineCore()
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
	_vertexBufferCache = make_shared<VertexBufferCache>();
	_textureBufferCache = make_shared<TextureBufferCache>();
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
	_modelEntityManager->inject(_vertexBufferCache);
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

void EngineCore::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void EngineCore::inject(shared_ptr<EngineController> engineController)
{
	_engineController = engineController;
}

void EngineCore::start()
{
	if(_isRunning)
	{
		Logger::throwError("Tried to start engine: already running!");
	}

	_isRunning = true;

	const auto rootPath = Tools::getRootDirectoryPath();
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";

	if
		(
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "camera.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "box.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "lamp.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "plane.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "speaker.obj") ||
		!Tools::isFileExisting(rootPath + meshDirectoryPath + "torch.obj") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "box.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "color.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_default.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_pointing.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "cursor_text.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "debug.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "grid.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "light_source.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "logo.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "minus.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "pause.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "plus.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "position.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "radius.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "restart.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "rotation.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "settings.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "shape_circle.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "shape_square.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "size.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "start.tga") ||
		!Tools::isFileExisting(rootPath + diffuseMapDirectoryPath + "stop.tga") ||
		!Tools::isFileExisting(rootPath + fontMapDirectoryPath + "font.tga")
		)
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	shared_ptr<QuadEntity> logo = make_shared<QuadEntity>("logo");
	logo->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(make_shared<TextureBuffer>(_imageLoader->loadImage("engine\\assets\\image\\diffuse_map\\logo.tga")));
	logo->setCentered(true);

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float width = static_cast<float>(DM.w);
	float height = static_cast<float>(DM.h);
	ivec2 logoResolution = ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	fvec3 keyingColor = fvec3(0.2f);
	if(Config::getInst().isApplicationExported())
	{
		_masterRenderer->setBackgroundColor(fvec4(0.0f));
	}
	else
	{
		_masterRenderer->setBackgroundColor(fvec4(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f));
		_renderWindow->enableColorKeying(keyingColor);
		_renderWindow->setSize(logoResolution);
		_renderWindow->showWindow();
		_masterRenderer->renderLogo(logo, logoResolution);
		_renderWindow->swapBackBuffer();
	}

	_engineController->initialize();

	if(_isRunning)
	{
		if(!Config::getInst().isApplicationExported())
		{
			_renderWindow->disableColorKeying(keyingColor);
		}

		if(!Config::getInst().isApplicationExported() || (Config::getInst().isApplicationExported() && !_networkingServer->isRunning()))
		{
			_renderWindow->showWindow();
			_renderWindow->setSize(Config::getInst().getWindowSize());
			if(Config::getInst().isWindowFullscreen())
			{
				_renderWindow->enableFullscreen();
			}
			if(!Config::getInst().isWindowBorderless())
			{
				_renderWindow->showBorder();
			}
			if(Config::getInst().isApplicationExported())
			{
				_renderWindow->setTitle(Config::getInst().getWindowTitle());
			}

			if(Config::getInst().isApplicationExported())
			{
				_renderWindow->setOpacity(1.0f);
			}
			else
			{
				_renderWindow->setOpacity(0.0f);
			}
		}
	}

	float renderLag = 0.0f;

	while(_isRunning)
	{
		auto previousTime = high_resolution_clock::now();

		if(_networkingServer->isRunning())
		{
			if(!Config::getInst().isApplicationExported())
			{
				_inputHandler->update();
			}

			update();
			_timer->increasePassedFrameCount();

			if(!Config::getInst().isApplicationExported())
			{
				render();
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

				update();

				renderLag -= Config::MS_PER_UPDATE;
				renderLag = max(renderLag, 0.0f);
				_timer->increasePassedFrameCount();
			}

			render();
		}

		auto currentTime = high_resolution_clock::now();
		auto timeDifference = duration_cast<nanoseconds>(currentTime - previousTime);
		_deltaTimeMS = static_cast<float>(timeDifference.count()) / 1000000.0f;
	}

	_engineController->terminate();
}

void EngineCore::update()
{
	static ivec2 lastCursorPosition = _renderWindow->getCursorPosition();

	if(_inputHandler->isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		stop();
		return;
	}

	_timer->startDeltaPart("coreUpdate");
	_fe3d->_isRaycastUpdated = false;
	_fe3d->_hoveredAabbID = "";
	_engineController->update();
	_timer->stopDeltaPart();

	if(!(Config::getInst().isApplicationExported() && _networkingServer->isRunning()))
	{
		if(!_isPaused)
		{
			_timer->startDeltaPart("physicsUpdate");
			_camera->update(lastCursorPosition);
			_raycaster->update(_fe3d->misc_getCursorPositionRelativeToViewport());
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

void EngineCore::render()
{
	_renderBus->resetTriangleCount();

	_masterRenderer->renderApplication();

	_timer->startDeltaPart("bufferSwap");
	_renderWindow->swapBackBuffer();
	_timer->stopDeltaPart();
}

void EngineCore::pause()
{
	if(_isPaused)
	{
		Logger::throwError("Tried to resume engine: already paused!");
	}

	_isPaused = true;
}

void EngineCore::resume()
{
	if(!_isPaused)
	{
		Logger::throwError("Tried to resume engine: not paused!");
	}

	_isPaused = false;
}

void EngineCore::stop()
{
	if(!_isRunning)
	{
		Logger::throwError("Tried to stop engine: not running!");
	}

	_isRunning = false;
}

const float EngineCore::getDeltaTimeMS() const
{
	return _deltaTimeMS;
}

const bool EngineCore::isPaused() const
{
	return _isPaused;
}

const bool EngineCore::isRunning() const
{
	return _isRunning;
}

const shared_ptr<LibraryLoader> EngineCore::getLibraryLoader() const
{
	return _libraryLoader;
}

const shared_ptr<InputHandler> EngineCore::getInputHandler() const
{
	return _inputHandler;
}

const shared_ptr<MeshLoader> EngineCore::getMeshLoader() const
{
	return _meshLoader;
}

const shared_ptr<ImageLoader> EngineCore::getImageLoader() const
{
	return _imageLoader;
}

const shared_ptr<AudioLoader> EngineCore::getAudioLoader() const
{
	return _audioLoader;
}

const shared_ptr<SkyEntityManager> EngineCore::getSkyEntityManager() const
{
	return _skyEntityManager;
}

const shared_ptr<TerrainEntityManager> EngineCore::getTerrainEntityManager() const
{
	return _terrainEntityManager;
}

const shared_ptr<WaterEntityManager> EngineCore::getWaterEntityManager() const
{
	return _waterEntityManager;
}

const shared_ptr<ModelEntityManager> EngineCore::getModelEntityManager() const
{
	return _modelEntityManager;
}

const shared_ptr<BillboardEntityManager> EngineCore::getBillboardEntityManager() const
{
	return _billboardEntityManager;
}

const shared_ptr<AabbEntityManager> EngineCore::getAabbEntityManager() const
{
	return _aabbEntityManager;
}

const shared_ptr<QuadEntityManager> EngineCore::getQuadEntityManager() const
{
	return _quadEntityManager;
}

const shared_ptr<TextEntityManager> EngineCore::getTextEntityManager() const
{
	return _textEntityManager;
}

const shared_ptr<PointlightEntityManager> EngineCore::getPointlightEntityManager() const
{
	return _pointlightEntityManager;
}

const shared_ptr<SpotlightEntityManager> EngineCore::getSpotlightEntityManager() const
{
	return _spotlightEntityManager;
}

const shared_ptr<ReflectionEntityManager> EngineCore::getReflectionEntityManager() const
{
	return _reflectionEntityManager;
}

const shared_ptr<RenderWindow> EngineCore::getRenderWindow() const
{
	return _renderWindow;
}

const shared_ptr<MasterRenderer> EngineCore::getMasterRenderer() const
{
	return _masterRenderer;
}

const shared_ptr<VertexBufferCache> EngineCore::getVertexBufferCache() const
{
	return _vertexBufferCache;
}

const shared_ptr<TextureBufferCache> EngineCore::getTextureBufferCache() const
{
	return _textureBufferCache;
}

const shared_ptr<RenderBus> EngineCore::getRenderBus() const
{
	return _renderBus;
}

const shared_ptr<ShadowGenerator> EngineCore::getShadowGenerator() const
{
	return _shadowGenerator;
}

const shared_ptr<Camera> EngineCore::getCamera() const
{
	return _camera;
}

const shared_ptr<Raycaster> EngineCore::getRaycaster() const
{
	return _raycaster;
}

const shared_ptr<CameraCollisionDetector> EngineCore::getCameraCollisionDetector() const
{
	return _cameraCollisionDetector;
}

const shared_ptr<CameraCollisionHandler> EngineCore::getCameraCollisionHandler() const
{
	return _cameraCollisionHandler;
}

const shared_ptr<Sound2dManager> EngineCore::getSound2dManager() const
{
	return _sound2dManager;
}

const shared_ptr<Sound3dManager> EngineCore::getSound3dManager() const
{
	return _sound3dManager;
}

const shared_ptr<Sound2dPlayer> EngineCore::getSound2dPlayer() const
{
	return _sound2dPlayer;
}

const shared_ptr<Sound3dPlayer> EngineCore::getSound3dPlayer() const
{
	return _sound3dPlayer;
}

const shared_ptr<NetworkingServer> EngineCore::getNetworkingServer() const
{
	return _networkingServer;
}

const shared_ptr<NetworkingClient> EngineCore::getNetworkingClient() const
{
	return _networkingClient;
}

const shared_ptr<Timer> EngineCore::getTimer() const
{
	return _timer;
}