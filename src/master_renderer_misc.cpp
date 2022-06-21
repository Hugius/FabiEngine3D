#include "master_renderer.hpp"

#include <intrin.h>

using std::make_shared;

void MasterRenderer::setBackgroundColor(const fvec3 & color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

const string MasterRenderer::getCpuName() const
{
	/* https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine */

	int CPUInfo[4];
	char model[48];

	__cpuid(CPUInfo, 0x80000002);
	memcpy(model, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(model + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(model + 32, CPUInfo, sizeof(CPUInfo));

	string nameString = "";
	for(int index = 0; index < 48; index++)
	{
		nameString.push_back(model[index]);
	}

	reverse(nameString.begin(), nameString.end());

	string result;
	for(int index = 0; index < static_cast<int>(nameString.size()); index++)
	{
		if(nameString[index] != 0)
		{
			result = nameString.substr(index);

			break;
		}
	}

	reverse(result.begin(), result.end());

	return result;
}

const string MasterRenderer::getGpuName() const
{
	const auto rawString = glGetString(GL_RENDERER);

	if(rawString == nullptr)
	{
		return "";
	}

	return (reinterpret_cast<char *>(const_cast<GLubyte *>(rawString)));
}

const string MasterRenderer::getOpenglVersion() const
{
	const auto rawString = glGetString(GL_VERSION);

	if(rawString == nullptr)
	{
		return "";
	}

	return string(reinterpret_cast<char *>(const_cast<GLubyte *>(rawString))).substr(0, 3);
}

void MasterRenderer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;

	_skyColorRenderer->inject(_camera);
	_terrainColorRenderer->inject(_camera);
	_terrainDepthRenderer->inject(_camera);
	_terrainShadowRenderer->inject(_camera);
	_waterColorRenderer->inject(_camera);
	_waterDepthRenderer->inject(_camera);
	_modelColorRenderer->inject(_camera);
	_modelDepthRenderer->inject(_camera);
	_modelShadowRenderer->inject(_camera);
	_quad3dColorRenderer->inject(_camera);
	_quad3dDepthRenderer->inject(_camera);
	_quad3dShadowRenderer->inject(_camera);
	_aabbColorRenderer->inject(_camera);
	_aabbDepthRenderer->inject(_camera);
	_quad2dColorRenderer->inject(_camera);
	_antiAliasingRenderer->inject(_camera);
	_bloomRenderer->inject(_camera);
	_dofRenderer->inject(_camera);
	_lensFlareRenderer->inject(_camera);
	_motionBlurRenderer->inject(_camera);
	_bloomBlurRendererHighQuality->inject(_camera);
	_bloomBlurRendererLowQuality->inject(_camera);
	_dofBlurRenderer->inject(_camera);
	_motionBlurBlurRenderer->inject(_camera);
}

void MasterRenderer::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void MasterRenderer::inject(shared_ptr<SkyManager> skyManager)
{
	_skyManager = skyManager;
}

void MasterRenderer::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void MasterRenderer::inject(shared_ptr<WaterManager> waterManager)
{
	_waterManager = waterManager;
}

void MasterRenderer::inject(shared_ptr<ModelManager> modelManager)
{
	_modelManager = modelManager;
}

void MasterRenderer::inject(shared_ptr<Quad3dManager> quad3dManager)
{
	_quad3dManager = quad3dManager;
}

void MasterRenderer::inject(shared_ptr<Text3dManager> text3dManager)
{
	_text3dManager = text3dManager;
}

void MasterRenderer::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void MasterRenderer::inject(shared_ptr<Quad2dManager> quad2dManager)
{
	_quad2dManager = quad2dManager;
}

void MasterRenderer::inject(shared_ptr<Text2dManager> text2dManager)
{
	_text2dManager = text2dManager;
}

void MasterRenderer::inject(shared_ptr<PointlightManager> pointlightManager)
{
	_pointlightManager = pointlightManager;
}

void MasterRenderer::inject(shared_ptr<SpotlightManager> spotlightManager)
{
	_spotlightManager = spotlightManager;
}

void MasterRenderer::inject(shared_ptr<CaptorManager> captorManager)
{
	_captorManager = captorManager;
}

void MasterRenderer::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;

	_skyColorRenderer->inject(_renderStorage);
	_terrainColorRenderer->inject(_renderStorage);
	_terrainDepthRenderer->inject(_renderStorage);
	_terrainShadowRenderer->inject(_renderStorage);
	_waterColorRenderer->inject(_renderStorage);
	_waterDepthRenderer->inject(_renderStorage);
	_modelColorRenderer->inject(_renderStorage);
	_modelDepthRenderer->inject(_renderStorage);
	_modelShadowRenderer->inject(_renderStorage);
	_quad3dColorRenderer->inject(_renderStorage);
	_quad3dDepthRenderer->inject(_renderStorage);
	_quad3dShadowRenderer->inject(_renderStorage);
	_aabbColorRenderer->inject(_renderStorage);
	_aabbDepthRenderer->inject(_renderStorage);
	_quad2dColorRenderer->inject(_renderStorage);
	_antiAliasingRenderer->inject(_renderStorage);
	_bloomRenderer->inject(_renderStorage);
	_dofRenderer->inject(_renderStorage);
	_lensFlareRenderer->inject(_renderStorage);
	_motionBlurRenderer->inject(_renderStorage);
	_bloomBlurRendererHighQuality->inject(_renderStorage);
	_bloomBlurRendererLowQuality->inject(_renderStorage);
	_dofBlurRenderer->inject(_renderStorage);
	_motionBlurBlurRenderer->inject(_renderStorage);

	loadShadowQuality();
	loadBloomBlurQuality();
	loadDofBlurQuality();
	loadMotionBlurBlurQuality();
	loadPlanarReflectionQuality();
	loadPlanarRefractionQuality();
	loadWaterReflectionQuality();
	loadWaterRefractionQuality();
}

void MasterRenderer::loadBloomBlurQuality()
{
	const auto viewportSize = Tools::getDisplaySize();

	_bloomBlurHighQualityCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getBloomQuality()), 1, true);
	_bloomBlurLowQualityCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (_renderStorage->getBloomQuality() * 2)), 1, true);

	_bloomBlurRendererHighQuality->inject(_bloomBlurHighQualityCaptureBuffer);
	_bloomBlurRendererLowQuality->inject(_bloomBlurLowQualityCaptureBuffer);
}

void MasterRenderer::loadDofBlurQuality()
{
	const auto viewportSize = Tools::getDisplaySize();

	_dofBlurCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getDofQuality()), 1, true);

	_dofBlurRenderer->inject(_dofBlurCaptureBuffer);
}

void MasterRenderer::loadMotionBlurBlurQuality()
{
	const auto viewportSize = Tools::getDisplaySize();

	_motionBlurBlurCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderStorage->getMotionBlurQuality()), 1, true);

	_motionBlurBlurRenderer->inject(_motionBlurBlurCaptureBuffer);
}

void MasterRenderer::loadPlanarReflectionQuality()
{
	_planarReflectionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::loadPlanarRefractionQuality()
{
	_planarRefractionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::loadWaterReflectionQuality()
{
	_waterReflectionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::loadWaterRefractionQuality()
{
	_waterRefractionCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::loadShadowQuality()
{
	_shadowCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderStorage->getShadowQuality()));
}