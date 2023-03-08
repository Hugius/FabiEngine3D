#include "engine_core.hpp"
#include "engine_controller.hpp"

void EngineCore::_update()
{
	_timer->startClock("mainUpdate");
	_inputHandler->update();
	_engineController->update();
	_timer->stopClock("mainUpdate");

	_timer->startClock("cameraUpdate");
	_camera->update();
	_timer->stopClock("cameraUpdate");

	_timer->startClock("environmentUpdate");
	_skyManager->update();
	_waterManager->update();
	_timer->stopClock("environmentUpdate");

	_timer->startClock("modelUpdate");
	_modelManager->update();
	_timer->stopClock("modelUpdate");

	_timer->startClock("quadUpdate");
	_quad3dManager->update();
	_quad2dManager->update();
	_timer->stopClock("quadUpdate");

	_timer->startClock("textUpdate");
	_text3dManager->update();
	_text2dManager->update();
	_timer->stopClock("textUpdate");

	_timer->startClock("aabbUpdate");
	_aabbManager->update();
	_timer->stopClock("aabbUpdate");

	_timer->startClock("lightUpdate");
	_pointlightManager->update();
	_spotlightManager->update();
	_timer->stopClock("lightUpdate");

	_timer->startClock("captorUpdate");
	_captorManager->update();
	_timer->stopClock("captorUpdate");

	_timer->startClock("renderUpdate");
	_renderWindow->update();
	if(!_renderWindow->isExisting())
	{
		return stop();
	}
	_masterRenderer->update();
	_timer->stopClock("renderUpdate");

	_timer->startClock("animationUpdate");
	_animation3dPlayer->update();
	_animation2dPlayer->update();
	_timer->stopClock("animationUpdate");

	_timer->startClock("soundUpdate");
	_sound3dManager->update();
	_sound3dPlayer->update();
	_sound2dPlayer->update();
	_timer->stopClock("soundUpdate");

	_timer->startClock("networkUpdate");
	_networkingServer->update();
	_networkingClient->update();
	_timer->stopClock("networkUpdate");

	for(auto & [clockId, deltaTime] : _updateDeltaTimes)
	{
		deltaTime = _timer->getClockDeltaTime(clockId);
	}

	_timer->increasePassedUpdateCount();
}

void EngineCore::_render()
{
	_renderStorage->resetTriangleCount();

	_timer->startClock("depthPreRender");
	_masterRenderer->captureWorldDepth();
	_timer->stopClock("depthPreRender");

	_timer->startClock("shadowPreRender");
	_masterRenderer->captureShadows();
	_timer->stopClock("shadowPreRender");

	_timer->startClock("reflectionPreRender");
	_masterRenderer->captureCubeReflections();
	_masterRenderer->capturePlanarReflections();
	_timer->stopClock("reflectionPreRender");

	_timer->startClock("refractionPreRender");
	_masterRenderer->captureCubeRefractions();
	_masterRenderer->capturePlanarRefractions();
	_timer->stopClock("refractionPreRender");

	_timer->startClock("waterPreRender");
	_masterRenderer->captureWaterReflections();
	_masterRenderer->captureWaterRefractions();
	_masterRenderer->captureWaterEdges();
	_timer->stopClock("waterPreRender");

	_timer->startClock("3dRender");
	_masterRenderer->render3d();
	_timer->stopClock("3dRender");

	_timer->startClock("antiAliasingPreRender");
	_masterRenderer->captureAntiAliasing();
	_timer->stopClock("antiAliasingPreRender");

	_timer->startClock("bloomPreRender");
	_masterRenderer->captureBloom();
	_timer->stopClock("bloomPreRender");

	_timer->startClock("dofPreRender");
	_masterRenderer->captureDof();
	_timer->stopClock("dofPreRender");

	_timer->startClock("lensFlarePreRender");
	_masterRenderer->captureLensFlare();
	_timer->stopClock("lensFlarePreRender");

	_timer->startClock("motionBlurPreRender");
	_masterRenderer->captureMotionBlur();
	_timer->stopClock("motionBlurPreRender");

	_timer->startClock("2dRender");
	_masterRenderer->render2d();
	_timer->stopClock("2dRender");

	_timer->startClock("bufferSwap");
	_renderWindow->swapBuffer();
	_timer->stopClock("bufferSwap");

	for(auto & [clockId, deltaTime] : _renderDeltaTimes)
	{
		deltaTime = _timer->getClockDeltaTime(clockId);
	}
}