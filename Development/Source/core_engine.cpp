#include "core_engine.hpp"
#include "configuration.hpp"
#include <ctime>
#include <ratio>
#include <chrono>

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
	// Setup
	_setupApplication();
	_isRunning = true;

	// Variables
	std::chrono::high_resolution_clock::time_point previous = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	// Main game-loop
	while (_isRunning)
	{
		// Calculate timing values
		std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(current - previous);
		float elapsedMS = static_cast<float>(timeDifference.count()) * 1000.0f;
		previous = current;
		lag += elapsedMS;

		// Update 144 times per second
		while (lag >= Config::getInst().getUpdateMsPerFrame())
		{
			_inputHandler.f_checkInput();
			_updateApplication();
			lag -= Config::getInst().getUpdateMsPerFrame();
		}

		// Render at full speed
		_renderApplication();
	}

	_fe3d.FE3D_CONTROLLER_DESTROY();
}

void CoreEngine::_stop()
{
	_isRunning = false;
}