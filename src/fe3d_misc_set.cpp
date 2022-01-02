#include "fe3d.hpp"
#include "core.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

void FabiEngine3D::misc_setCursorEntityID(const string& value)
{
	_core->_renderBus.setCursorEntityID(value);
}

void FabiEngine3D::misc_enableWireframeRendering()
{
	if(_core->_renderBus.isWireframeRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable wireframe rendering: already enabled!");
		return;
	}

	_core->_renderBus.setWireframeRenderingEnabled(true);
}

void FabiEngine3D::misc_enableShadowFrameRendering()
{
	if(_core->_renderBus.isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable shadow frame rendering: already enabled!");
		return;
	}

	_core->_renderBus.setShadowFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_enableAabbFrameRendering()
{
	if(_core->_renderBus.isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable AABB frame rendering: already enabled!");
		return;
	}

	_core->_renderBus.setAabbFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_enableDebugRendering()
{
	if(_core->_renderBus.isDebugRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable debug rendering: already enabled!");
		return;
	}

	_core->_renderBus.setDebugRenderingEnabled(true);
}

void FabiEngine3D::misc_enableVsync()
{
	if(_core->_window.isVsyncEnabled())
	{
		Logger::throwWarning("Tried to enable Vsync: already enabled!");
		return;
	}

	_core->_window.enableVsync();
}

void FabiEngine3D::misc_disableWireframeRendering()
{
	if(!_core->_renderBus.isWireframeRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable wireframe rendering: not enabled!");
		return;
	}

	_core->_renderBus.setWireframeRenderingEnabled(false);
}

void FabiEngine3D::misc_disableShadowFrameRendering()
{
	if(!_core->_renderBus.isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable shadow frame rendering: not enabled!");
		return;
	}

	_core->_renderBus.setShadowFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_disableAabbFrameRendering()
{
	if(!_core->_renderBus.isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable AABB frame rendering: not enabled!");
		return;
	}

	_core->_renderBus.setAabbFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_disableDebugRendering()
{
	if(!_core->_renderBus.isDebugRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable debug rendering: not enabled!");
		return;
	}

	_core->_renderBus.setDebugRenderingEnabled(false);
}

void FabiEngine3D::misc_disableVsync()
{
	if(!_core->_window.isVsyncEnabled())
	{
		Logger::throwWarning("Tried to disable Vsync: not enabled!");
		return;
	}

	_core->_window.disableVsync();
}

void FabiEngine3D::misc_setCursorVisible(bool value)
{
	if(value)
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
	const int left = Config::getInst().getViewportPosition().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getViewportPosition().y + Config::getInst().getViewportSize().y);
	const int xMiddle = left + (Config::getInst().getViewportSize().x / 2);
	const int yMiddle = bottom + (Config::getInst().getViewportSize().y / 2);
	_core->_window.setCursorPosition({xMiddle, yMiddle});

	_core->_camera.notifyCursorCenter();
}

void FabiEngine3D::misc_setCursorPosition(ivec2 value)
{
	_core->_window.setCursorPosition(value);
}

void FabiEngine3D::misc_setWindowTitle(const string& value)
{
	_core->_window.setTitle(value);
}

void FabiEngine3D::misc_cacheMesh(const string& filePath)
{
	_core->_meshLoader.cacheMesh(filePath);
}

void FabiEngine3D::misc_cache2dTexture(const string& filePath)
{
	_core->_textureLoader.cache2dTexture(filePath, true, true);
}

void FabiEngine3D::misc_cache3dTexture(const array<string, 6>& filePaths)
{
	_core->_textureLoader.cache3dTexture(filePaths);
}

void FabiEngine3D::misc_cacheImage(const string& filePath)
{
	_core->_textureLoader.cacheImage(filePath);
}

void FabiEngine3D::misc_cacheAudio(const string& filePath)
{
	_core->_audioLoader.cacheChunk(filePath);
}

void FabiEngine3D::misc_clearMeshCache(const string& filePath)
{
	_core->_meshLoader.clearMeshCache(filePath);
}

void FabiEngine3D::misc_clear2dTextureCache(const string& filePath)
{
	_core->_textureLoader.clear2dTextureCache(filePath);
}

void FabiEngine3D::misc_clear3dTextureCache(const array<string, 6>& filePaths)
{
	_core->_textureLoader.clear3dTextureCache(filePaths);
}

void FabiEngine3D::misc_clearImageCache(const string& filePath)
{
	_core->_textureLoader.clearImageCache(filePath);
}

void FabiEngine3D::misc_clearAudioCache(const string& filePath)
{
	_core->_audioLoader.clearChunkCache(filePath);
}

void FabiEngine3D::misc_clearMeshesCache()
{
	_core->_meshLoader.clearMeshesCache();
}

void FabiEngine3D::misc_clear2dTexturesCache()
{
	_core->_textureLoader.clear2dTexturesCache();
}

void FabiEngine3D::misc_clear3dTexturesCache()
{
	_core->_textureLoader.clear3dTexturesCache();
}

void FabiEngine3D::misc_clearImagesCache()
{
	_core->_textureLoader.clearImagesCache();
}

void FabiEngine3D::misc_clearAudiosCache()
{
	_core->_audioLoader.clearChunksCache();
}

void FabiEngine3D::misc_cacheMeshes(const vector<string>& filePaths)
{
	_core->_meshLoader.cacheMeshes(filePaths);
}

void FabiEngine3D::misc_cache2dTextures(const vector<string>& filePaths)
{
	_core->_textureLoader.cache2dTextures(filePaths, true, true);
}

void FabiEngine3D::misc_cache3dTextures(const vector<array<string, 6>>& filePathsList)
{
	_core->_textureLoader.cache3dTextures(filePathsList);
}

void FabiEngine3D::misc_cacheImages(const vector<string>& filePaths)
{
	_core->_textureLoader.cacheImages(filePaths);
}

void FabiEngine3D::misc_cacheAudios(const vector<string>& filePaths)
{
	_core->_audioLoader.cacheChunks(filePaths);
}

void FabiEngine3D::misc_startMillisecondTimer()
{
	if(_core->_timer.isStarted())
	{
		Logger::throwWarning("Tried to start milliseconds timer: already started!");
		return;
	}

	_core->_timer.start();
}