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

void EngineInterface::misc_setCursorPosition(const ivec2& value)
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

const unsigned int EngineInterface::misc_getTriangleCount() const
{
	return _core->getRenderBus()->getTriangleCount();
}

const float EngineInterface::misc_getFPS() const
{
	return (1000.0f / _core->getDeltaTimeMS());
}

const float EngineInterface::misc_stopMillisecondTimer() const
{
	if(!_core->getTimer()->isStarted())
	{
		Logger::throwWarning("Tried to stop milliseconds timer: not started!");
		return 0.0f;
	}

	return _core->getTimer()->stop();
}

const string EngineInterface::misc_getCpuName() const
{
	return _core->getMasterRenderer()->getCpuName();
}

const string EngineInterface::misc_getGpuName() const
{
	return _core->getMasterRenderer()->getGpuName();
}

const string EngineInterface::misc_getOpenglVersion() const
{
	return _core->getMasterRenderer()->getOpenglVersion();
}

const ivec2 EngineInterface::misc_getCursorPosition() const
{
	ivec2 cursorPosition = _core->getRenderWindow()->getCursorPosition();

	return ivec2(cursorPosition.x, (Config::getInst().getWindowSize().y - cursorPosition.y));
}

const ivec2 EngineInterface::misc_getCursorPositionRelativeToViewport() const
{
	if(Config::getInst().isApplicationExported())
	{
		return misc_getCursorPosition();
	}
	else
	{
		auto windowSize = Config::getInst().getWindowSize();
		auto viewportPosition = Config::getInst().getViewportPosition();
		auto viewportSize = Config::getInst().getViewportSize();

		ivec2 offset = ivec2(viewportPosition.x, windowSize.y - (viewportPosition.y + viewportSize.y));

		fvec2 relativeCursorPosition = fvec2(_core->getRenderWindow()->getCursorPosition()) - fvec2(offset);

		relativeCursorPosition = (relativeCursorPosition / fvec2(viewportSize)) * fvec2(windowSize);

		ivec2 result = ivec2(relativeCursorPosition);
		return ivec2(result.x, (Config::getInst().getWindowSize().y - result.y));
	}
}

const bool EngineInterface::misc_isMillisecondTimerStarted() const
{
	return _core->getTimer()->isStarted();
}

const bool EngineInterface::misc_isCursorVisible() const
{
	return _core->getRenderWindow()->isCursorVisible();
}

const bool EngineInterface::misc_isCursorInsideViewport() const
{
	auto cursorPosition = misc_getCursorPosition();
	auto viewportPosition = Config::getInst().getViewportPosition();
	auto viewportSize = Config::getInst().getViewportSize();

	if((cursorPosition.x > viewportPosition.x) && (cursorPosition.x < (viewportPosition.x + viewportSize.x)))
	{
		if((cursorPosition.y > viewportPosition.y) && (cursorPosition.y < (viewportPosition.y + viewportSize.y)))
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::misc_isCursorInsideWindow() const
{
	auto cursorPosition = misc_getCursorPosition();
	auto windowSize = Config::getInst().getWindowSize();

	if((cursorPosition.x > 1) && (cursorPosition.x < (windowSize.x - 1)))
	{
		if((cursorPosition.y > 1) && (cursorPosition.y < (windowSize.y - 1)))
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::misc_checkInterval(unsigned int ticks) const
{
	return ((_core->getTimer()->getPassedTickCount() % ticks) == 0);
}

const vector<pair<string, int>> EngineInterface::misc_getUpdateProfilingStatistics() const
{
	vector<pair<string, int>> result =
	{
		pair<string, int>("coreUpdate", 0),
		pair<string, int>("physicsUpdate", 0),
		pair<string, int>("3dEntityUpdate", 0),
		pair<string, int>("2dEntityUpdate", 0),
		pair<string, int>("renderUpdate", 0),
		pair<string, int>("soundUpdate", 0),
		pair<string, int>("networkUpdate", 0),
		pair<string, int>("miscUpdate", 0)
	};

	for(auto& [key, percentage] : result)
	{
		percentage = static_cast<int>((_core->getTimer()->getDeltaPart(key) / _core->getTimer()->getDeltaPartSum()) * 100.0f);
	}

	return result;
}

const vector<pair<string, int>> EngineInterface::misc_getRenderProfilingStatistics() const
{
	vector<pair<string, int>> result =
	{
		pair<string, int>("depthPreRender", 0),
		pair<string, int>("shadowPreRender", 0),
		pair<string, int>("reflectionPreRender", 0),
		pair<string, int>("refractionPreRender", 0),
		pair<string, int>("3dEntityRender", 0),
		pair<string, int>("postProcessing", 0),
		pair<string, int>("2dEntityRender", 0),
		pair<string, int>("bufferSwap", 0)
	};

	for(auto& [key, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->getTimer()->getDeltaPart(key) / _core->getTimer()->getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const string EngineInterface::misc_getCursorEntityID() const
{
	return _core->getRenderBus()->getCursorEntityID();
}

const bool EngineInterface::misc_isVsyncEnabled() const
{
	return _core->getRenderWindow()->isVsyncEnabled();
}

const bool EngineInterface::misc_isWireframeRenderingEnabled() const
{
	return _core->getRenderBus()->isWireframeRenderingEnabled();
}

const bool EngineInterface::misc_isShadowFrameRenderingEnabled() const
{
	return _core->getRenderBus()->isShadowFrameRenderingEnabled();
}

const bool EngineInterface::misc_isAabbFrameRenderingEnabled() const
{
	return _core->getRenderBus()->isAabbFrameRenderingEnabled();
}