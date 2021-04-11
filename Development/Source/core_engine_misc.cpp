#include "core_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <fstream>

CoreEngine::CoreEngine(FabiEngine3D& fe3d) :
	_fe3d(fe3d),
	_windowManager(),
	_meshLoader(),
	_textureLoader(),
	_audioLoader(),
	_inputHandler(),
	_renderBus(),
	_cameraManager(_renderBus, _windowManager),
	_renderManager(_renderBus, _timer, _textureLoader),
	_skyEntityManager(_meshLoader, _textureLoader, _renderBus),
	_terrainEntityManager(_meshLoader, _textureLoader, _renderBus),
	_waterEntityManager(_meshLoader, _textureLoader, _renderBus),
	_modelEntityManager(_meshLoader, _textureLoader, _renderBus),
	_billboardEntityManager(_meshLoader, _textureLoader, _renderBus, _cameraManager),
	_aabbEntityManager(_meshLoader, _textureLoader, _renderBus),
	_lightEntityManager(_meshLoader, _textureLoader, _renderBus),
	_imageEntityManager(_meshLoader, _textureLoader, _renderBus),
	_textEntityManager(_meshLoader, _textureLoader, _renderBus),
	_shadowManager(),
	_rayCaster(_renderBus, _terrainEntityManager),
	_collisionDetector(),
	_collisionResolver(_collisionDetector),
	_timer(),
	_audioManager(_audioLoader),
	_audioPlayer()
{

}

CoreEngine::~CoreEngine()
{

}

void CoreEngine::_updateWindowFading()
{
	// Only if in engine preview
	if (!Config::getInst().isGameExported())
	{
		static float opacity = 0.0f;

		// Stop if window is 100% visible
		if (opacity < 1.0f)
		{
			_windowManager.setOpacity(opacity);
			opacity += 0.01f;
		}
		else
		{
			_windowManager.setOpacity(1.0f);
		}
	}
}

void CoreEngine::_pause()
{
	_isPaused = true;
}

void CoreEngine::_resume()
{
	_isPaused = false;
}

void CoreEngine::_stop()
{
	_isRunning = false;
}