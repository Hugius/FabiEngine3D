#include "core_engine.hpp"
#include "configuration.hpp"
#include "shader_bus.hpp"

#include <fstream>

CoreEngine::CoreEngine(FabiEngine3D& fe3d) :
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
	_billboardEntityManager(_objLoader, _texLoader, _shaderBus, _cameraManager),
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

void CoreEngine::_updateWindowFading()
{
	static float opacity = 0.0f;

	// Stop if window is 100% visible
	if (opacity < 1.0f)
	{
		_windowManager.setOpacity(opacity);
		opacity += 0.005f;
	}
}