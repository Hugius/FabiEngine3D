#include "master_renderer.hpp"

void MasterRenderer::setBackgroundColor(const fvec3& color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

/* https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine */
const string MasterRenderer::getCpuName() const
{
	int CPUInfo[4];
	char model[48];

	__cpuid(CPUInfo, 0x80000002);
	memcpy(model, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(model + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(model + 32, CPUInfo, sizeof(CPUInfo));

	string nameString;
	for(unsigned int i = 0; i < 48; i++)
	{
		nameString.push_back(model[i]);
	}

	string result;
	reverse(nameString.begin(), nameString.end());
	for(size_t i = 0; i < nameString.size(); i++)
	{
		if(nameString[i] != 0)
		{
			result = nameString.substr(i);
			break;
		}
	}

	reverse(result.begin(), result.end());
	return result;
}

const string MasterRenderer::getGpuName() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER))));
}

const string MasterRenderer::getOpenglVersion() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))).substr(0, 3);
}

void MasterRenderer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void MasterRenderer::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void MasterRenderer::inject(shared_ptr<SkyEntityManager> skyEntityManager)
{
	_skyEntityManager = skyEntityManager;
}

void MasterRenderer::inject(shared_ptr<TerrainEntityManager> terrainEntityManager)
{
	_terrainEntityManager = terrainEntityManager;
}

void MasterRenderer::inject(shared_ptr<WaterEntityManager> waterEntityManager)
{
	_waterEntityManager = waterEntityManager;
}

void MasterRenderer::inject(shared_ptr<ModelEntityManager> modelEntityManager)
{
	_modelEntityManager = modelEntityManager;
}

void MasterRenderer::inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager)
{
	_quad3dEntityManager = quad3dEntityManager;
}

void MasterRenderer::inject(shared_ptr<Text3dEntityManager> text3dEntityManager)
{
	_text3dEntityManager = text3dEntityManager;
}

void MasterRenderer::inject(shared_ptr<AabbEntityManager> aabbEntityManager)
{
	_aabbEntityManager = aabbEntityManager;
}

void MasterRenderer::inject(shared_ptr<Quad2dEntityManager> quad2dEntityManager)
{
	_quad2dEntityManager = quad2dEntityManager;
}

void MasterRenderer::inject(shared_ptr<Text2dEntityManager> text2dEntityManager)
{
	_text2dEntityManager = text2dEntityManager;
}

void MasterRenderer::inject(shared_ptr<PointlightEntityManager> pointlightEntityManager)
{
	_pointlightEntityManager = pointlightEntityManager;
}

void MasterRenderer::inject(shared_ptr<SpotlightEntityManager> spotlightEntityManager)
{
	_spotlightEntityManager = spotlightEntityManager;
}

void MasterRenderer::inject(shared_ptr<ReflectionEntityManager> reflectionEntityManager)
{
	_reflectionEntityManager = reflectionEntityManager;
}

void MasterRenderer::inject(shared_ptr<RenderBus> renderBus)
{
	_skyEntityColorRenderer.inject(renderBus);
	_terrainEntityColorRenderer.inject(renderBus);
	_terrainEntityDepthRenderer.inject(renderBus);
	_waterEntityColorRenderer.inject(renderBus);
	_modelEntityColorRenderer.inject(renderBus);
	_modelEntityDepthRenderer.inject(renderBus);
	_modelEntityShadowRenderer.inject(renderBus);
	_quad3dEntityColorRenderer.inject(renderBus);
	_quad3dEntityDepthRenderer.inject(renderBus);
	_quad3dEntityShadowRenderer.inject(renderBus);
	_aabbEntityColorRenderer.inject(renderBus);
	_quad2dEntityColorRenderer.inject(renderBus);
	_antiAliasingRenderer.inject(renderBus);
	_bloomRenderer.inject(renderBus);
	_dofRenderer.inject(renderBus);
	_lensFlareRenderer.inject(renderBus);
	_motionBlurRenderer.inject(renderBus);
	_bloomBlurRendererHighQuality.inject(renderBus);
	_bloomBlurRendererLowQuality.inject(renderBus);
	_dofBlurRenderer.inject(renderBus);
	_motionBlurBlurRenderer.inject(renderBus);

	_renderBus = renderBus;
}

void MasterRenderer::reloadBloomBlurQuality()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_bloomBlurCaptorHighQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getBloomQuality()), 1, true);
	_bloomBlurCaptorLowQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (_renderBus->getBloomQuality() * 2)), 1, true);

	_bloomBlurRendererHighQuality.inject(_bloomBlurCaptorHighQuality);
	_bloomBlurRendererLowQuality.inject(_bloomBlurCaptorLowQuality);
}

void MasterRenderer::reloadDofBlurQuality()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_dofBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getDofQuality()), 1, true);

	_dofBlurRenderer.inject(_dofBlurCaptor);
}

void MasterRenderer::reloadMotionBlurBlurQuality()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_motionBlurBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getMotionBlurQuality()), 1, true);

	_motionBlurBlurRenderer.inject(_motionBlurBlurCaptor);
}

void MasterRenderer::reloadCubeReflectionQuality()
{
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionQuality()
{
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionQuality()
{
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionQuality()
{
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowQuality()
{
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getShadowQuality()));
}