#include "engine_core.hpp"
#include "engine_controller.hpp"

void EngineCore::_update()
{
	_timer->startClock("mainUpdate");
	_inputHandler->update();
	_engineController->update();
	_timer->stopClock("mainUpdate");

	_timer->startClock("physicsUpdate");
	_camera->update();
	_cameraCollisionResponder->update();
	_raycastCalculator->update();
	_raycastIntersector->update();
	_camera->updateMatrices();
	_timer->stopClock("physicsUpdate");

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
	if(_renderWindow->isClosed())
	{
		stop();
	}
	_masterRenderer->update();
	_timer->stopClock("renderUpdate");

	_timer->startClock("animationUpdate");
	_animation3dPlayer->update();
	_animation2dPlayer->update();
	_timer->stopClock("animationUpdate");

	_timer->startClock("soundUpdate");
	_sound3dPlayer->update();
	_sound2dPlayer->update();
	_timer->stopClock("soundUpdate");

	_timer->startClock("networkUpdate");
	_networkingServer->update();
	_networkingClient->update();
	_timer->stopClock("networkUpdate");

	_updateDeltaTimes.at("mainUpdate") = _timer->getClockDeltaTime("mainUpdate");
	_updateDeltaTimes.at("physicsUpdate") = _timer->getClockDeltaTime("physicsUpdate");
	_updateDeltaTimes.at("environmentUpdate") = _timer->getClockDeltaTime("environmentUpdate");
	_updateDeltaTimes.at("modelUpdate") = _timer->getClockDeltaTime("modelUpdate");
	_updateDeltaTimes.at("quadUpdate") = _timer->getClockDeltaTime("quadUpdate");
	_updateDeltaTimes.at("textUpdate") = _timer->getClockDeltaTime("textUpdate");
	_updateDeltaTimes.at("aabbUpdate") = _timer->getClockDeltaTime("aabbUpdate");
	_updateDeltaTimes.at("lightUpdate") = _timer->getClockDeltaTime("lightUpdate");
	_updateDeltaTimes.at("captorUpdate") = _timer->getClockDeltaTime("captorUpdate");
	_updateDeltaTimes.at("renderUpdate") = _timer->getClockDeltaTime("renderUpdate");
	_updateDeltaTimes.at("animationUpdate") = _timer->getClockDeltaTime("animationUpdate");
	_updateDeltaTimes.at("soundUpdate") = _timer->getClockDeltaTime("soundUpdate");
	_updateDeltaTimes.at("networkUpdate") = _timer->getClockDeltaTime("networkUpdate");

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
	// insert capture cube/planar refractions here
	_timer->stopClock("refractionPreRender");
	_timer->startClock("waterPreRender");
	_masterRenderer->captureWaterReflections();
	_masterRenderer->captureWaterRefractions();
	_masterRenderer->captureWaterEdges();
	_timer->stopClock("waterPreRender");

	_timer->startClock("3dRender");
	_masterRenderer->render3d();
	_timer->stopClock("3dRender");

	_timer->startClock("antiAliasingPostRender");
	_masterRenderer->captureAntiAliasing();
	_timer->stopClock("antiAliasingPostRender");
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

	_renderDeltaTimes.at("depthPreRender") = _timer->getClockDeltaTime("depthPreRender");
	_renderDeltaTimes.at("shadowPreRender") = _timer->getClockDeltaTime("shadowPreRender");
	_renderDeltaTimes.at("reflectionPreRender") = _timer->getClockDeltaTime("reflectionPreRender");
	_renderDeltaTimes.at("refractionPreRender") = _timer->getClockDeltaTime("refractionPreRender");
	_renderDeltaTimes.at("waterPreRender") = _timer->getClockDeltaTime("waterPreRender");
	_renderDeltaTimes.at("3dRender") = _timer->getClockDeltaTime("3dRender");
	_renderDeltaTimes.at("antiAliasingPostRender") = _timer->getClockDeltaTime("antiAliasingPostRender");
	_renderDeltaTimes.at("bloomPreRender") = _timer->getClockDeltaTime("bloomPreRender");
	_renderDeltaTimes.at("dofPreRender") = _timer->getClockDeltaTime("dofPreRender");
	_renderDeltaTimes.at("lensFlarePreRender") = _timer->getClockDeltaTime("lensFlarePreRender");
	_renderDeltaTimes.at("motionBlurPreRender") = _timer->getClockDeltaTime("motionBlurPreRender");
	_renderDeltaTimes.at("2dRender") = _timer->getClockDeltaTime("2dRender");
	_renderDeltaTimes.at("bufferSwap") = _timer->getClockDeltaTime("bufferSwap");
}