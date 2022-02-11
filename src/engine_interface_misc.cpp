#include "engine_interface.hpp"
#include "engine_core.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <chrono>
#include <filesystem>

void EngineInterface::misc_setCursorEntityId(const string& value)
{
	_core->getRenderStorage()->setCursorEntityId(value);
}

void EngineInterface::misc_setVsyncEnabled(bool value)
{
	_core->getRenderWindow()->setVsyncEnabled(value);
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
	_core->getRenderWindow()->setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

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

void EngineInterface::misc_cacheMesh(const string& filePath, bool isCrucial)
{
	_core->getMeshLoader()->cacheMesh(filePath, isCrucial);
}

void EngineInterface::misc_cacheImage(const string& filePath, bool isCrucial)
{
	_core->getImageLoader()->cacheImage(filePath, isCrucial);
}

void EngineInterface::misc_cacheAudio(const string& filePath, bool isCrucial)
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

void EngineInterface::misc_cacheMeshes(const vector<string>& filePaths, bool isCrucial)
{
	_core->getMeshLoader()->cacheMeshes(filePaths, isCrucial);
}

void EngineInterface::misc_cacheImages(const vector<string>& filePaths, bool isCrucial)
{
	_core->getImageLoader()->cacheImages(filePaths, isCrucial);
}

void EngineInterface::misc_cacheAudios(const vector<string>& filePaths, bool isCrucial)
{
	_core->getAudioLoader()->cacheChunks(filePaths);
}

void EngineInterface::misc_startMillisecondTimer()
{
	_core->getTimer()->start();
}

const unsigned int EngineInterface::misc_getTriangleCount() const
{
	return _core->getRenderStorage()->getTriangleCount();
}

const unsigned int EngineInterface::misc_getUpdateCountPerSecond() const
{
	return _core->getTimer()->getUpdateCountPerSecond();
}

const unsigned int EngineInterface::misc_getPassedUpdateCount() const
{
	return _core->getTimer()->getPassedUpdateCount();
}

const float EngineInterface::misc_getFPS() const
{
	return (1000.0f / _core->getDeltaTime());
}

const float EngineInterface::misc_stopMillisecondTimer() const
{
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
	return _core->getRenderWindow()->getCursorPosition();
}

const bool EngineInterface::misc_isMillisecondTimerStarted() const
{
	return _core->getTimer()->isStarted();
}

const bool EngineInterface::misc_isCursorVisible() const
{
	return _core->getRenderWindow()->isCursorVisible();
}

const bool EngineInterface::misc_isCursorInsideDisplay() const
{
	auto cursorPosition = misc_getCursorPosition();
	auto viewportPosition = Config::getInst().getDisplayPosition();
	auto viewportSize = Config::getInst().getDisplaySize();

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

const vector<pair<string, int>> EngineInterface::misc_getUpdateProfilingStatistics() const
{
	vector<pair<string, int>> result =
	{
		pair<string, int>("coreUpdate", 0),
		pair<string, int>("physicsUpdate", 0),
		pair<string, int>("3dEntityUpdate", 0),
		pair<string, int>("2dEntityUpdate", 0),
		pair<string, int>("renderUpdate", 0),
		pair<string, int>("animationUpdate", 0),
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
		pair<string, int>("waterPreRender", 0),
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

const string EngineInterface::misc_getCursorEntityId() const
{
	return _core->getRenderStorage()->getCursorEntityId();
}

const bool EngineInterface::misc_isVsyncEnabled() const
{
	return _core->getRenderWindow()->isVsyncEnabled();
}