#include "fe3d.hpp"
#include "core_engine.hpp"
#include "configuration.hpp"

const unsigned int FabiEngine3D::misc_getTriangleCount() const
{
	return _core->_renderBus.getTriangleCount();
}

const float FabiEngine3D::misc_getFPS() const
{
	return (1000.0f / _core->_deltaTimeMS);
}

const float FabiEngine3D::misc_stopMillisecondTimer() const
{
	if(!_core->_timer.isStarted())
	{
		Logger::throwWarning("Tried to stop milliseconds timer: not started!");
		return 0.0f;
	}

	return _core->_timer.stop();
}

const string FabiEngine3D::misc_getCpuModel() const
{
	return _core->_libraryLoader.getCpuModel();
}

const string FabiEngine3D::misc_getGpuModel() const
{
	return _core->_libraryLoader.getGpuModel();
}

const string FabiEngine3D::misc_getOpenglVersion() const
{
	return _core->_libraryLoader.getOpenglVersion();
}

const ivec2 FabiEngine3D::misc_getCursorPosition() const
{
	ivec2 cursorPosition = _core->_window.getCursorPosition();

	return ivec2(cursorPosition.x, (Config::getInst().getWindowSize().y - cursorPosition.y));
}

const ivec2 FabiEngine3D::misc_getCursorPositionRelativeToViewport() const
{
	if(Config::getInst().isApplicationExported())
	{
		return misc_getCursorPosition();
	}
	else
	{
		// Temporary values
		auto windowSize = Config::getInst().getWindowSize();
		auto viewportPosition = Config::getInst().getViewportPosition();
		auto viewportSize = Config::getInst().getViewportSize();

		// Calculate viewport position Y offset, because GUI borders are not all of the same size
		ivec2 offset = ivec2(viewportPosition.x, windowSize.y - (viewportPosition.y + viewportSize.y));

		// Apply Y offset to cursor position
		fvec2 relativeCursorPosition = fvec2(_core->_window.getCursorPosition()) - fvec2(offset);

		// Convert fullscreen coords to viewport coords
		relativeCursorPosition = (relativeCursorPosition / fvec2(viewportSize)) * fvec2(windowSize);

		// Return
		ivec2 result = ivec2(relativeCursorPosition);
		return ivec2(result.x, (Config::getInst().getWindowSize().y - result.y));
	}
}

const bool FabiEngine3D::misc_isMillisecondTimerStarted() const
{
	return _core->_timer.isStarted();
}

const bool FabiEngine3D::misc_isCursorVisible() const
{
	return _core->_window.isCursorVisible();
}

const bool FabiEngine3D::misc_isCursorInsideViewport() const
{
	// Temporary values
	auto cursorPosition = misc_getCursorPosition();
	auto viewportPosition = Config::getInst().getViewportPosition();
	auto viewportSize = Config::getInst().getViewportSize();

	// Checking if cursor is inside viewport
	if((cursorPosition.x > viewportPosition.x) && (cursorPosition.x < (viewportPosition.x + viewportSize.x)))
	{
		if((cursorPosition.y > viewportPosition.y) && (cursorPosition.y < (viewportPosition.y + viewportSize.y)))
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::misc_isCursorInsideWindow() const
{
	// Temporary values
	auto cursorPosition = misc_getCursorPosition();
	auto windowSize = Config::getInst().getWindowSize();

	// Checking if cursor is inside viewport
	if((cursorPosition.x > 1) && (cursorPosition.x < (windowSize.x - 1)))
	{
		if((cursorPosition.y > 1) && (cursorPosition.y < (windowSize.y - 1)))
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::misc_checkInterval(unsigned int ticks) const
{
	return ((_core->_timer.getPassedTickCount() % ticks) == 0);
}

const vector<pair<string, int>> FabiEngine3D::misc_getUpdateProfilingStatistics() const
{
	// Final list of timer IDs
	vector<pair<string, int>> result =
	{
		pair<string, int>("coreUpdate", 0),
		pair<string, int>("physicsUpdate", 0),
		pair<string, int>("skyEntityUpdate", 0),
		pair<string, int>("waterEntityUpdate", 0),
		pair<string, int>("modelEntityUpdate", 0),
		pair<string, int>("billboardEntityUpdate", 0),
		pair<string, int>("aabbEntityUpdate", 0),
		pair<string, int>("lightEntityUpdate", 0),
		pair<string, int>("reflectionEntityUpdate", 0),
		pair<string, int>("guiEntityUpdate", 0),
		pair<string, int>("shadowUpdate", 0),
		pair<string, int>("audioUpdate", 0),
		pair<string, int>("networkUpdate", 0)
	};

	// Calculate percentages
	for(auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const vector<pair<string, int>> FabiEngine3D::misc_getRenderProfilingStatistics() const
{
	// Final list of timer IDs
	vector<pair<string, int>> result =
	{
		pair<string, int>("reflectionPreRender", 0),
		pair<string, int>("refractionPreRender", 0),
		pair<string, int>("shadowPreRender", 0),
		pair<string, int>("depthPreRender", 0),
		pair<string, int>("skyEntityRender", 0),
		pair<string, int>("terrainEntityRender", 0),
		pair<string, int>("waterEntityRender", 0),
		pair<string, int>("modelEntityRender", 0),
		pair<string, int>("billboardEntityRender", 0),
		pair<string, int>("aabbEntityRender", 0),
		pair<string, int>("guiEntityRender", 0),
		pair<string, int>("postProcessing", 0),
		pair<string, int>("bufferSwap", 0)
	};

	// Calculate percentages
	for(auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const bool FabiEngine3D::misc_isVsyncEnabled() const
{
	return _core->_window.isVsyncEnabled();
}

const bool FabiEngine3D::misc_isWireframeRenderingEnabled() const
{
	return _core->_renderBus.isWireframeRenderingEnabled();
}

const bool FabiEngine3D::misc_isShadowFrameRenderingEnabled() const
{
	return _core->_renderBus.isShadowFrameRenderingEnabled();
}

const bool FabiEngine3D::misc_isAabbFrameRenderingEnabled() const
{
	return _core->_renderBus.isAabbFrameRenderingEnabled();
}

const bool FabiEngine3D::misc_isDebugRenderingEnabled() const
{
	return _core->_renderBus.isDebugRenderingEnabled();
}

const unsigned int FabiEngine3D::misc_getMaxAudioChannelCount() const
{
	return _core->_audioPlayer.getAllocatedChannelCount();
}

const unsigned int FabiEngine3D::misc_getUsedAudioChannelCount() const
{
	return _core->_audioPlayer.getUsedChannelCount();
}