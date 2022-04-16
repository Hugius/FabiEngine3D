#include "engine_interface.hpp"
#include "engine_core.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <chrono>
#include <filesystem>

void EngineInterface::misc_setWindowTitle(const string & value)
{
	_core->getRenderWindow()->setTitle(value);
}

void EngineInterface::misc_setVsyncEnabled(bool value)
{
	_core->getRenderWindow()->setVsyncEnabled(value);
}

void EngineInterface::misc_setCursorEntityId(const string & value)
{
	_core->getRenderStorage()->setCursorEntityId(value);
}

void EngineInterface::misc_cacheMesh(const string & filePath, bool isCrucial)
{
	_core->getMeshLoader()->cacheMesh(filePath, isCrucial);
}

void EngineInterface::misc_cacheImage(const string & filePath, bool isCrucial)
{
	_core->getImageLoader()->cacheImage(filePath, isCrucial);
}

void EngineInterface::misc_cacheAudio(const string & filePath, bool isCrucial)
{
	_core->getAudioLoader()->cacheAudio(filePath, isCrucial);
}

void EngineInterface::misc_clearMeshCache(const string & filePath)
{
	_core->getMeshLoader()->clearMeshCache(filePath);

	for(const auto & partId : _core->getVertexBufferCache()->getPartIds(filePath))
	{
		_core->getVertexBufferCache()->deleteBuffer(filePath, partId);
	}
}

void EngineInterface::misc_clearImageCache(const string & filePath)
{
	_core->getImageLoader()->clearImageCache(filePath);

	for(const auto & mergedId : _core->getTextureBufferCache()->get2dFilePaths())
	{
		if(filePath == mergedId)
		{
			_core->getTextureBufferCache()->delete2dBuffer(mergedId);
		}
	}

	for(const auto & mergedId : _core->getTextureBufferCache()->get3dFilePaths())
	{
		if(find(mergedId.begin(), mergedId.end(), filePath) != mergedId.end())
		{
			_core->getTextureBufferCache()->delete3dBuffer(mergedId);
		}
	}
}

void EngineInterface::misc_clearAudioCache(const string & filePath)
{
	_core->getAudioLoader()->clearAudioCache(filePath);
}

void EngineInterface::misc_clearMeshesCache()
{
	_core->getMeshLoader()->clearMeshesCache();

	_core->getVertexBufferCache()->clearBuffers();
}

void EngineInterface::misc_clearImagesCache()
{
	_core->getImageLoader()->clearImagesCache();

	_core->getTextureBufferCache()->clear2dBuffers();
	_core->getTextureBufferCache()->clear3dBuffers();
}

void EngineInterface::misc_clearAudiosCache()
{
	_core->getAudioLoader()->clearAudiosCache();
}

void EngineInterface::misc_cacheMeshes(const vector<string> & filePaths, bool isCrucial)
{
	_core->getMeshLoader()->cacheMeshes(filePaths, isCrucial);
}

void EngineInterface::misc_cacheImages(const vector<string> & filePaths, bool isCrucial)
{
	_core->getImageLoader()->cacheImages(filePaths, isCrucial);
}

void EngineInterface::misc_cacheAudios(const vector<string> & filePaths, bool isCrucial)
{
	_core->getAudioLoader()->cacheAudios(filePaths, isCrucial);
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

const bool EngineInterface::misc_isVsyncEnabled() const
{
	return _core->getRenderWindow()->isVsyncEnabled();
}

const float EngineInterface::misc_getTotalDeltaTime() const
{
	return _core->getTotalDeltaTime();
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

const unordered_map<string, float> & EngineInterface::misc_getUpdateDeltaTimes() const
{
	return _core->getUpdateDeltaTimes();
}

const unordered_map<string, float> & EngineInterface::misc_getRenderDeltaTimes() const
{
	return _core->getRenderDeltaTimes();
}

const string EngineInterface::misc_getWindowTitle() const
{
	return _core->getRenderWindow()->getTitle();
}

const string EngineInterface::misc_getCursorEntityId() const
{
	return _core->getRenderStorage()->getCursorEntityId();
}