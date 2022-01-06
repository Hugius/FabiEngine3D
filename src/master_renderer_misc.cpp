#include "master_renderer.hpp"

void MasterRenderer::setBackgroundColor(fvec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
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

void MasterRenderer::inject(shared_ptr<ShadowGenerator> shadowGenerator)
{
	_shadowGenerator = shadowGenerator;
}

void MasterRenderer::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void MasterRenderer::inject(shared_ptr<BufferCache> bufferCache)
{
	_bufferCache = bufferCache;
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

void MasterRenderer::inject(shared_ptr<BillboardEntityManager> billboardEntityManager)
{
	_billboardEntityManager = billboardEntityManager;
}

void MasterRenderer::inject(shared_ptr<AabbEntityManager> aabbEntityManager)
{
	_aabbEntityManager = aabbEntityManager;
}

void MasterRenderer::inject(shared_ptr<QuadEntityManager> quadEntityManager)
{
	_quadEntityManager = quadEntityManager;
}

void MasterRenderer::inject(shared_ptr<TextEntityManager> textEntityManager)
{
	_textEntityManager = textEntityManager;
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
	_billboardEntityColorRenderer.inject(renderBus);
	_billboardEntityDepthRenderer.inject(renderBus);
	_billboardEntityShadowRenderer.inject(renderBus);
	_aabbEntityColorRenderer.inject(renderBus);
	_quadEntityColorRenderer.inject(renderBus);
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