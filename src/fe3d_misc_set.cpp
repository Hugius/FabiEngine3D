#include "engine_interface.hpp"
#include "engine_core.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

void EngineInterface::misc_setCursorEntityID(const string& value)
{
	_core->getRenderBus()->setCursorEntityID(value);
}

void EngineInterface::misc_enableWireframeRendering()
{
	if(_core->getRenderBus()->isWireframeRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable wireframe rendering: already enabled!");
		return;
	}

	_core->getRenderBus()->setWireframeRenderingEnabled(true);
}

void EngineInterface::misc_enableShadowFrameRendering()
{
	if(_core->getRenderBus()->isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable shadow frame rendering: already enabled!");
		return;
	}

	_core->getRenderBus()->setShadowFrameRenderingEnabled(true);
}

void EngineInterface::misc_enableAabbFrameRendering()
{
	if(_core->getRenderBus()->isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to enable AABB frame rendering: already enabled!");
		return;
	}

	_core->getRenderBus()->setAabbFrameRenderingEnabled(true);
}

void EngineInterface::misc_enableVsync()
{
	if(_core->getRenderWindow()->isVsyncEnabled())
	{
		Logger::throwWarning("Tried to enable Vsync: already enabled!");
		return;
	}

	_core->getRenderWindow()->enableVsync();
}

void EngineInterface::misc_disableWireframeRendering()
{
	if(!_core->getRenderBus()->isWireframeRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable wireframe rendering: not enabled!");
		return;
	}

	_core->getRenderBus()->setWireframeRenderingEnabled(false);
}

void EngineInterface::misc_disableShadowFrameRendering()
{
	if(!_core->getRenderBus()->isShadowFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable shadow frame rendering: not enabled!");
		return;
	}

	_core->getRenderBus()->setShadowFrameRenderingEnabled(false);
}

void EngineInterface::misc_disableAabbFrameRendering()
{
	if(!_core->getRenderBus()->isAabbFrameRenderingEnabled())
	{
		Logger::throwWarning("Tried to disable AABB frame rendering: not enabled!");
		return;
	}

	_core->getRenderBus()->setAabbFrameRenderingEnabled(false);
}

void EngineInterface::misc_disableVsync()
{
	if(!_core->getRenderWindow()->isVsyncEnabled())
	{
		Logger::throwWarning("Tried to disable Vsync: not enabled!");
		return;
	}

	_core->getRenderWindow()->disableVsync();
}

void EngineInterface::misc_setCursorVisible(bool value)
{
	if(value)
	{
		_core->getRenderWindow()->showCursor();
	}
	else
	{
		_core->getRenderWindow()->hideCursor();
	}
}

void EngineInterface::misc_centerCursor()
{
	const int left = Config::getInst().getViewportPosition().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getViewportPosition().y + Config::getInst().getViewportSize().y);
	const int xMiddle = left + (Config::getInst().getViewportSize().x / 2);
	const int yMiddle = bottom + (Config::getInst().getViewportSize().y / 2);
	_core->getRenderWindow()->setCursorPosition({xMiddle, yMiddle});

	_core->getCamera()->notifyCursorCenter();
}

void EngineInterface::misc_setCursorPosition(ivec2 value)
{
	_core->getRenderWindow()->setCursorPosition(value);
}

void EngineInterface::misc_setWindowTitle(const string& value)
{
	_core->getRenderWindow()->setTitle(value);
}

void EngineInterface::misc_cacheMesh(const string& filePath)
{
	_core->getMeshLoader()->cacheMesh(filePath);
}

void EngineInterface::misc_cacheImage(const string& filePath)
{
	_core->getImageLoader()->cacheImage(filePath);
}

void EngineInterface::misc_cacheAudio(const string& filePath)
{
	_core->getAudioLoader()->cacheChunk(filePath);
}

void EngineInterface::misc_clearMeshCache(const string& filePath)
{
	_core->getMeshLoader()->clearMeshCache(filePath);

	for(const auto& [key, texture] : _core->getVertexBufferCache()->getBuffers())
	{
		if(key.first == filePath)
		{
			_core->getVertexBufferCache()->deleteBuffer(key.first, key.second);
		}
	}
}

void EngineInterface::misc_clearImageCache(const string& filePath)
{
	_core->getImageLoader()->clearImageCache(filePath);

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get2dBuffers())
	{
		if(key == filePath)
		{
			_core->getTextureBufferCache()->delete2dBuffer(key);
		}
	}

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get3dBuffers())
	{
		if(find(key.begin(), key.end(), filePath) != key.end())
		{
			_core->getTextureBufferCache()->delete3dBuffer(key);
		}
	}
}

void EngineInterface::misc_clearAudioCache(const string& filePath)
{
	_core->getAudioLoader()->clearChunkCache(filePath);
}

void EngineInterface::misc_clearMeshesCache()
{
	_core->getMeshLoader()->clearMeshesCache();

	_core->getVertexBufferCache()->clear();
}

void EngineInterface::misc_clearImagesCache()
{
	_core->getImageLoader()->clearImagesCache();

	_core->getTextureBufferCache()->clear2dBuffers();
	_core->getTextureBufferCache()->clear3dBuffers();
}

void EngineInterface::misc_clearAudiosCache()
{
	_core->getAudioLoader()->clearChunksCache();
}

void EngineInterface::misc_cacheMeshes(const vector<string>& filePaths)
{
	_core->getMeshLoader()->cacheMeshes(filePaths);
}

void EngineInterface::misc_cacheImages(const vector<string>& filePaths)
{
	_core->getImageLoader()->cacheImages(filePaths);
}

void EngineInterface::misc_cacheAudios(const vector<string>& filePaths)
{
	_core->getAudioLoader()->cacheChunks(filePaths);
}

void EngineInterface::misc_startMillisecondTimer()
{
	if(_core->getTimer()->isStarted())
	{
		Logger::throwWarning("Tried to start milliseconds timer: already started!");
		return;
	}

	_core->getTimer()->start();
}