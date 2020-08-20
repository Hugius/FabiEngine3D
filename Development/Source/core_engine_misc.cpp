#include "core_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <fstream>

CoreEngine::CoreEngine(FabiEngine3D& fe3d) :
	_fe3d(fe3d),
	_windowManager(),
	_objLoader(),
	_texLoader(),
	_audioLoader(),
	_inputHandler(_timer),
	_renderBus(),
	_cameraManager(_renderBus),
	_renderEngine(_renderBus, _timer),
	_skyEntityManager(_objLoader, _texLoader, _renderBus),
	_terrainEntityManager(_objLoader, _texLoader, _renderBus),
	_waterEntityManager(_objLoader, _texLoader, _renderBus),
	_gameEntityManager(_objLoader, _texLoader, _renderBus),
	_billboardEntityManager(_objLoader, _texLoader, _renderBus, _cameraManager),
	_aabbEntityManager(_objLoader, _texLoader, _renderBus),
	_lightEntityManager(_objLoader, _texLoader, _renderBus),
	_guiEntityManager(_objLoader, _texLoader, _renderBus),
	_textEntityManager(_objLoader, _texLoader, _renderBus),
	_shadowManager(),
	_mousePicker(_renderBus),
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