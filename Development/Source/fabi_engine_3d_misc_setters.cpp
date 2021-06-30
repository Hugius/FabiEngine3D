#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

void FabiEngine3D::misc_showCursor()
{
	_core->_window.showCursor();
}

void FabiEngine3D::misc_hideCursor()
{
	_core->_window.hideCursor();
}

void FabiEngine3D::misc_setCustomCursor(const string& imageEntityID)
{
	_core->_renderBus.setCursorEntityID(imageEntityID);
}

void FabiEngine3D::misc_enableWireframeRendering()
{
	_core->_renderBus.setWireframeRenderingEnabled(true);
}

void FabiEngine3D::misc_disableWireframeRendering()
{
	_core->_renderBus.setWireframeRenderingEnabled(false);
}

void FabiEngine3D::misc_enableShadowFrameRendering()
{
	_core->_renderBus.setShadowFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_disableShadowFrameRendering()
{
	_core->_renderBus.setShadowFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_enableAabbFrameRendering()
{
	_core->_renderBus.setAabbFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_disableAabbFrameRendering()
{
	_core->_renderBus.setAabbFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_enableDebugRendering()
{
	_core->_renderBus.setDebugRenderingEnabled(true);
}

void FabiEngine3D::misc_disableDebugRendering()
{
	_core->_renderBus.setDebugRenderingEnabled(false);
}

void FabiEngine3D::misc_enableTerrainRaycasting(float distance, float precision)
{
	_core->_rayCaster.setTerrainPointingEnabled(true);
	_core->_rayCaster.setTerrainPointingDistance(distance);
	_core->_rayCaster.setTerrainPointingPrecision(precision);
}

void FabiEngine3D::misc_disableTerrainRaycasting()
{
	_core->_rayCaster.setTerrainPointingEnabled(false);
}

void FabiEngine3D::misc_centerCursor()
{
	// Center the cursor
	Ivec2 currenCursorPosition = _core->_window.getCursorPosition();
	const int left = Config::getInst().getVpPos().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
	const int xMiddle = left + (Config::getInst().getVpSize().x / 2);
	const int yMiddle = bottom + (Config::getInst().getVpSize().y / 2);
	_core->_window.setCursorPosition({ xMiddle, yMiddle });

	// Notify camera of centering
	_core->_camera.notifyCursorCenter();
}

void FabiEngine3D::misc_setCursorPosition(Ivec2 pos)
{
	_core->_rayCaster.update(pos);
	_core->_window.setCursorPosition(pos);
}

void FabiEngine3D::misc_enableVsync()
{
	_core->_window.enableVsync();
}

void FabiEngine3D::misc_disableVsync()
{
	_core->_window.disableVsync();
}

void FabiEngine3D::misc_enableSounds()
{
	_core->_audioPlayer.setSoundsEnabled(true);
}

void FabiEngine3D::misc_disableSounds()
{
	_core->_audioPlayer.setSoundsEnabled(false);
}

void FabiEngine3D::misc_enableMusic()
{
	_core->_audioPlayer.setMusicEnabled(true);
}

void FabiEngine3D::misc_disableMusic()
{
	_core->_audioPlayer.setMusicEnabled(false);
}

void FabiEngine3D::misc_setMainRenderingColor(Vec3 color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void FabiEngine3D::misc_setWindowTitle(const string& title)
{
	_core->_window.setTitle(title);
}

void FabiEngine3D::misc_clearMeshCache(const string& filePath)
{
	_core->_meshLoader.clearMeshCache(filePath);
}

void FabiEngine3D::misc_clearTextCache(const string& textContent, const string& fontPath)
{
	_core->_textureLoader.clearTextCache(textContent, fontPath);
}

void FabiEngine3D::misc_clearFontCache(const string& filePath)
{
	_core->_textureLoader.clearFontCache(filePath);
}

void FabiEngine3D::misc_clearTextureCache2D(const string& filePath)
{
	_core->_textureLoader.clearTextureCache2D(filePath);
}

void FabiEngine3D::misc_clearTextureCache3D(const array<string, 6>& filePaths)
{
	_core->_textureLoader.clearTextureCache3D(filePaths);
}

void FabiEngine3D::misc_clearBitmapCache(const string& filePath)
{
	_core->_textureLoader.clearBitmapCache(filePath);
}

void FabiEngine3D::misc_clearAudioChunkCache(const string& filePath)
{
	_core->_audioLoader.clearChunkCache(filePath);
}

void FabiEngine3D::misc_clearAudioMusicCache(const string& filePath)
{
	_core->_audioLoader.clearMusicCache(filePath);
}

void FabiEngine3D::misc_cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths)
{
	_core->_meshLoader.cacheMeshesMultiThreaded(meshPaths, resultingTexturePaths);
}

void FabiEngine3D::misc_cacheTexturesMultiThreaded2D(const vector<string>& filePaths)
{
	_core->_textureLoader.cacheTexturesMultiThreaded2D(filePaths);
}

void FabiEngine3D::misc_cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePaths)
{
	_core->_textureLoader.cacheTexturesMultiThreaded3D(filePaths);
}

void FabiEngine3D::misc_cacheAudioMultiThreaded(const vector<string>& filePaths)
{
	_core->_audioLoader.cacheChunksMultiThreaded(filePaths);
}

void FabiEngine3D::misc_startMillisecondTimer()
{
	_core->_timer.start();
}

void FabiEngine3D::misc_setLevelOfDetailDistance(float distance)
{
	_core->_modelEntityManager.setLodDistance(distance);
}

void FabiEngine3D::misc_setMaxAudioChannels(unsigned int count)
{
	_core->_audioPlayer.allocateChannels(count);
}