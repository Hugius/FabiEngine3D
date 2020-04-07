#include <WE3D/CoreEngine.hpp>
#include <WE3D/Configuration.hpp>

CoreEngine::CoreEngine(WoodEngine3D & we3d, EngineState engineState) :
	p_we3d(we3d),
	p_engineState(engineState),
	p_objLoader(),
	p_texLoader(),
	p_audioLoader(),
	p_inputHandler(p_timer),
	p_shaderBus(),
	p_windowManager(),
	p_cameraManager(p_shaderBus),
	p_renderEngine(p_shaderBus, p_timer),
	p_skyEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_terrainEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_waterEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_gameEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_billboardEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_aabbEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_lightEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_guiEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_textEntityManager(p_objLoader, p_texLoader, p_shaderBus),
	p_shadowManager(),
	p_mousePicker(p_shaderBus),
	p_modelEditor(p_objLoader, p_texLoader),
	p_worldEditor(p_modelEditor.getModelNames(), p_gameEntityManager),
	p_collisionDetector(),
	p_collisionResolver(p_collisionDetector),
	p_timer(),
	p_audioManager(p_audioLoader),
	p_audioPlayer()
{
	
}

void CoreEngine::p_start()
{
	p_setupApplication();
	p_isRunning = true;

	while (p_isRunning)
	{
		p_timer.calculateDeltaTime();
		p_inputHandler.f_checkInput();
		p_updateApplication();
		p_renderApplication();
	}

	p_we3d.WE3D_DESTROY();
}

void CoreEngine::p_stop()
{
	p_isRunning = false;
}