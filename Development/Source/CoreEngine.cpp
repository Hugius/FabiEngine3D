#include "CoreEngine.hpp"
#include "Configuration.hpp"

CoreEngine::CoreEngine(FabiEngine3D & fe3d) :
	_fe3d(fe3d),
	_windowManager(),
	_objLoader(),
	_texLoader(),
	_audioLoader(),
	_inputHandler(_timer),
	_shaderBus(),
	_cameraManager(_shaderBus),
	_renderEngine(_shaderBus, _timer),
	_skyEntityManager(_objLoader, _texLoader, _shaderBus),
	_terrainEntityManager(_objLoader, _texLoader, _shaderBus),
	_waterEntityManager(_objLoader, _texLoader, _shaderBus),
	_gameEntityManager(_objLoader, _texLoader, _shaderBus),
	_billboardEntityManager(_objLoader, _texLoader, _shaderBus),
	_aabbEntityManager(_objLoader, _texLoader, _shaderBus),
	_lightEntityManager(_objLoader, _texLoader, _shaderBus),
	_guiEntityManager(_objLoader, _texLoader, _shaderBus),
	_textEntityManager(_objLoader, _texLoader, _shaderBus),
	_shadowManager(),
	_mousePicker(_shaderBus),
	_modelEditor(_objLoader, _texLoader),
	_worldEditor(_modelEditor.getModelNames(), _gameEntityManager),
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

void CoreEngine::_start()
{
	_setupApplication();
	_isRunning = true;

	while (_isRunning)
	{
		_timer.calculateDeltaTime();
		_inputHandler.f_checkInput();
		_updateApplication();
		_renderApplication();
	}

	_fe3d.FE3D_CONTROLLER_DESTROY();
}

void CoreEngine::_stop()
{
	_isRunning = false;
}