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
	_quad3dEntityManager = make_shared<Quad3dEntityManager>();
	_text3dEntityManager = make_shared<Text3dEntityManager>();
	_quad2dEntityManager = make_shared<Quad2dEntityManager>();
	_text2dEntityManager = make_shared<Text2dEntityManager>();
	_aabbEntityManager = make_shared<AabbEntityManager>();
	_pointlightEntityManager = make_shared<PointlightEntityManager>();
	_spotlightEntityManager = make_shared<SpotlightEntityManager>();
	_reflectionEntityManager = make_shared<ReflectionEntityManager>();
	_renderWindow = make_shared<RenderWindow>(_libraryLoader->getWindowPointer());
	_masterRenderer = make_shared<MasterRenderer>();
	_vertexBufferCache = make_shared<VertexBufferCache>();
	_textureBufferCache = make_shared<TextureBufferCache>();
	_renderStorage = make_shared<RenderStorage>();
	_camera = make_shared<Camera>();
	_raycastCalculator = make_shared<RaycastCalculator>();
	_raycastIntersector = make_shared<RaycastIntersector>();
	_cameraCollisionResponder = make_shared<CameraCollisionResponder>();
	_cameraCollisionDetector = make_shared<CameraCollisionDetector>();
	_networkingServer = make_shared<NetworkingServer>();
	_networkingClient = make_shared<NetworkingClient>();
	_sound2dManager = make_shared<Sound2dManager>();
	_sound3dManager = make_shared<Sound3dManager>();
	_sound2dPlayer = make_shared<Sound2dPlayer>();
	_sound3dPlayer = make_shared<Sound3dPlayer>();
	_timer = make_shared<Timer>();

	_skyEntityManager->inject(_renderStorage);
	_terrainEntityManager->inject(_imageLoader);
	_modelEntityManager->inject(_renderStorage);
	_modelEntityManager->inject(_camera);
	_modelEntityManager->inject(_timer);
	_modelEntityManager->inject(_reflectionEntityManager);
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
	_masterRenderer->inject(_renderStorage);
	_masterRenderer->inject(_camera);
	_masterRenderer->inject(_timer);
	_masterRenderer->inject(_skyEntityManager);
	_masterRenderer->inject(_terrainEntityManager);
	_masterRenderer->inject(_waterEntityManager);
	_masterRenderer->inject(_modelEntityManager);
	_masterRenderer->inject(_quad3dEntityManager);
	_masterRenderer->inject(_text3dEntityManager);
	_masterRenderer->inject(_quad2dEntityManager);
	_masterRenderer->inject(_text2dEntityManager);
	_masterRenderer->inject(_aabbEntityManager);
	_masterRenderer->inject(_pointlightEntityManager);
	_masterRenderer->inject(_spotlightEntityManager);
	_masterRenderer->inject(_reflectionEntityManager);
	_camera->inject(_renderWindow);
	_raycastCalculator->inject(_camera);
	_raycastIntersector->inject(_raycastCalculator);
	_raycastIntersector->inject(_terrainEntityManager);
	_raycastIntersector->inject(_aabbEntityManager);
	_cameraCollisionResponder->inject(_terrainEntityManager);
	_cameraCollisionResponder->inject(_aabbEntityManager);
	_cameraCollisionResponder->inject(_camera);
	_cameraCollisionResponder->inject(_cameraCollisionDetector);
	_sound2dManager->inject(_audioLoader);
	_sound3dManager->inject(_audioLoader);
	_sound2dPlayer->inject(_sound2dManager);
	_sound3dPlayer->inject(_sound3dManager);
	_sound3dPlayer->inject(_camera);
}

void EngineCore::start()
{
	if(_isRunning)
	{
		abort();
	}

	_isRunning = true;

	string logoDirectoryPath;
	if(Config::getInst().isApplicationExported())
	{
		logoDirectoryPath = "logo\\";
	}
	else
	{
		logoDirectoryPath = "engine\\assets\\image\\diffuse_map\\";
	}

	_imageLoader->cacheImage(logoDirectoryPath + "logo.tga", true);

	shared_ptr<Quad2dEntity> logo = make_shared<Quad2dEntity>("logo");
	logo->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(make_shared<TextureBuffer>(_imageLoader->loadImage(logoDirectoryPath + "logo.tga")));
	logo->setCentered(true);

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	const auto width = static_cast<float>(DM.w);
	const auto height = static_cast<float>(DM.h);
	const auto logoResolution = ivec2(static_cast<int>(width * 0.4f), static_cast<int>(height * 0.2f));

	const auto keyingColor = fvec3(0.2f);
	_masterRenderer->setBackgroundColor(fvec4(keyingColor.r, keyingColor.g, keyingColor.b, 0.0f));
	_renderWindow->enableColorKeying(keyingColor);
	_renderWindow->setSize(logoResolution);
	_renderWindow->showWindow();
	_masterRenderer->renderLogo(logo, logoResolution);
	_renderWindow->swapBackBuffer();

	_engineController->initialize();

	if(_isRunning)
	{
		_renderWindow->disableColorKeying(keyingColor);

		_masterRenderer->setBackgroundColor(fvec4(0.0f, 0.0f, 0.0f, 1.0f));

		if(!_networkingServer->isRunning())
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

	const auto millisecondsPerUpdate = (1000.0f / static_cast<float>(_timer->getUpdateCountPerSecond()));
	float renderLag = 0.0f;

	while(_isRunning)
	{
		const auto previousTime = high_resolution_clock::now();

		if(_networkingServer->isRunning())
		{
			if(!Config::getInst().isApplicationExported())
			{
				_inputHandler->update();
			}

			_timer->increasePassedUpdateCount();

			_engineController->update();
			_networkingServer->update();
			_networkingClient->update();

			if(!Config::getInst().isApplicationExported())
			{
				_renderStorage->resetTriangleCount();

				_masterRenderer->renderApplication();

				_timer->startDeltaPart("bufferSwap");
				_renderWindow->swapBackBuffer();
				_timer->stopDeltaPart();
			}
		}
		else
		{
			renderLag += _deltaTime;

			if(renderLag > (millisecondsPerUpdate * 10.0f))
			{
				renderLag = millisecondsPerUpdate;
			}

			while(renderLag >= millisecondsPerUpdate)
			{
				_timer->increasePassedUpdateCount();

				_inputHandler->update();

				update();

				renderLag -= millisecondsPerUpdate;
				renderLag = max(0.0f, renderLag);
			}

			_renderStorage->resetTriangleCount();

			_masterRenderer->renderApplication();

			_timer->startDeltaPart("bufferSwap");
			_renderWindow->swapBackBuffer();
			_timer->stopDeltaPart();
		}

		const auto currentTime = high_resolution_clock::now();
		const auto timeDifference = duration_cast<nanoseconds>(currentTime - previousTime);
		_deltaTime = static_cast<float>(timeDifference.count()) / 1000000.0f;
	}

	_engineController->terminate();
}

void EngineCore::update()
{
	static ivec2 lastCursorPosition = _renderWindow->getCursorPosition();

	_timer->startDeltaPart("coreUpdate");
	if(_inputHandler->isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		stop();
		return;
	}
	_engineController->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("physicsUpdate");
	_camera->update(lastCursorPosition);
	_raycastCalculator->update(_renderWindow->getCursorPosition());
	_raycastIntersector->update();
	_cameraCollisionResponder->update();
	_camera->updateMatrices();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("3dEntityUpdate");
	_skyEntityManager->update();
	_waterEntityManager->update();
	_modelEntityManager->update();
	_quad3dEntityManager->update();
	_text3dEntityManager->update();
	_aabbEntityManager->update();
	_pointlightEntityManager->update();
	_spotlightEntityManager->update();
	_reflectionEntityManager->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("2dEntityUpdate");
	_quad2dEntityManager->update();
	_text2dEntityManager->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("renderUpdate");
	_masterRenderer->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("soundUpdate");
	_sound2dManager->update();
	_sound3dManager->update();
	_sound2dPlayer->update();
	_sound3dPlayer->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("networkUpdate");
	_networkingServer->update();
	_networkingClient->update();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("miscUpdate");
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
	_timer->stopDeltaPart();
}

void EngineCore::stop()
{
	if(!_isRunning)
	{
		abort();
	}

	_isRunning = false;
}