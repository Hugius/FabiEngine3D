#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

void FabiEngine3D::misc_setCustomCursor(const string& imageEntityID)
{
	_core->_renderBus.setCursorEntityID(imageEntityID);
}

void FabiEngine3D::misc_enableWireFrameRendering()
{
	if (_core->_renderBus.isWireFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable wire frame rendering: already enabled!");
		return;
	}

	_core->_renderBus.setWireFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_enableShadowFrameRendering()
{
	if (_core->_renderBus.isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable shadow frame rendering: already enabled!");
		return;
	}

	_core->_renderBus.setShadowFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_enableAabbFrameRendering()
{
	if (_core->_renderBus.isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable AABB frame rendering: already enabled!");
		return;
	}

	_core->_renderBus.setAabbFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_enableDebugRendering()
{
	if (_core->_renderBus.isDebugRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable debug rendering: already enabled!");
		return;
	}

	_core->_renderBus.setDebugRenderingEnabled(true);
}

void FabiEngine3D::misc_enableTerrainRaycastPointing(float distance, float precision)
{
	if (_core->_rayCaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to enable terrain raycast pointing: already enabled!");
		return;
	}

	_core->_rayCaster.setTerrainPointingEnabled(true);
	_core->_rayCaster.setTerrainPointingDistance(distance);
	_core->_rayCaster.setTerrainPointingPrecision(precision);
}

void FabiEngine3D::misc_enableVsync()
{
	if (_core->_window.isVsyncEnabled())
	{
		Logger::throwWarning("Tried to enable Vsync: already enabled!");
		return;
	}

	_core->_window.enableVsync();
}

void FabiEngine3D::misc_enableSounds()
{
	if (_core->_audioPlayer.isSoundsEnabled())
	{
		Logger::throwWarning("Tried to enable sounds: already enabled!");
		return;
	}
	
	_core->_audioPlayer.setSoundsEnabled(true);
}

void FabiEngine3D::misc_enableMusic()
{
	if (_core->_audioPlayer.isMusicEnabled())
	{
		Logger::throwWarning("Tried to enable music: already enabled!");
		return;
	}

	_core->_audioPlayer.setMusicEnabled(true);
}

void FabiEngine3D::misc_disableWireFrameRendering()
{
	if (!_core->_renderBus.isWireFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable wire frame rendering: not enabled!");
		return;
	}

	_core->_renderBus.setWireFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_disableShadowFrameRendering()
{
	if (!_core->_renderBus.isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable shadow frame rendering: not enabled!");
		return;
	}

	_core->_renderBus.setShadowFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_disableAabbFrameRendering()
{
	if (!_core->_renderBus.isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable AABB frame rendering: not enabled!");
		return;
	}

	_core->_renderBus.setAabbFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_disableDebugRendering()
{
	if (!_core->_renderBus.isDebugRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable debug rendering: not enabled!");
		return;
	}

	_core->_renderBus.setDebugRenderingEnabled(false);
}

void FabiEngine3D::misc_disableTerrainRaycastPointing()
{
	if (!_core->_rayCaster.isTerrainPointingEnabled())
	{
		Logger::throwWarning("Tried to disable terrain raycast pointing: not enabled!");
		return;
	}

	_core->_rayCaster.setTerrainPointingEnabled(false);
}

void FabiEngine3D::misc_disableVsync()
{
	if (!_core->_window.isVsyncEnabled())
	{
		Logger::throwWarning("Tried to disable Vsync: not enabled!");
		return;
	}

	_core->_window.disableVsync();
}

void FabiEngine3D::misc_disableSounds()
{
	if (!_core->_audioPlayer.isSoundsEnabled())
	{
		Logger::throwWarning("Tried to disable sounds: not enabled!");
		return;
	}

	_core->_audioPlayer.setSoundsEnabled(false);
}

void FabiEngine3D::misc_disableMusic()
{
	if (!_core->_audioPlayer.isMusicEnabled())
	{
		Logger::throwWarning("Tried to disable music: not enabled!");
		return;
	}

	_core->_audioPlayer.setMusicEnabled(false);
}

void FabiEngine3D::misc_setCursorVisible(bool isVisible)
{
	if (isVisible)
	{
		_core->_window.showCursor();
	}
	else
	{
		_core->_window.hideCursor();
	}
}

void FabiEngine3D::misc_centerCursor()
{
	// Center the cursor
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
	_core->_window.setCursorPosition(pos);
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

void FabiEngine3D::misc_clearAudioCache(const string& filePath)
{
	_core->_audioLoader.clearChunkCache(filePath);
	_core->_audioLoader.clearMusicCache(filePath);
}

void FabiEngine3D::misc_cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths)
{
	_core->_meshLoader.cacheMeshesMultiThreaded(meshPaths, resultingTexturePaths);
}

void FabiEngine3D::misc_cacheTexturesMultiThreaded2D(const vector<string>& filePaths)
{
	_core->_textureLoader.cacheTexturesMultiThreaded2D(filePaths, true, true);
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
	if (_core->_timer.isStarted())
	{
		Logger::throwWarning("Tried to start milliseconds timer: already started!");
		return;
	}

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