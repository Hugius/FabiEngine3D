#include "fe3d.hpp"
#include "core.hpp"
#include "configuration.hpp"

const unsigned int FabiEngine3D::misc_getTriangleCount() const
{
	return _core->_renderBus->getTriangleCount();
}

const float FabiEngine3D::misc_getFPS() const
{
	return (1000.0f / _core->_deltaTimeMS);
}

const float FabiEngine3D::misc_stopMillisecondTimer() const
{
	if(!_core->_timer->isStarted())
	{
		Logger::throwWarning("Tried to stop milliseconds timer: not started!");
		return 0.0f;
	}

	return _core->_timer->stop();
}

const string FabiEngine3D::misc_getCpuName() const
{
	return _core->_masterRenderer->getCpuName();
}

const string FabiEngine3D::misc_getGpuName() const
{
	return _core->_masterRenderer->getGpuName();
}

const string FabiEngine3D::misc_getOpenglVersion() const
{
	return _core->_masterRenderer->getOpenglVersion();
}

const ivec2 FabiEngine3D::misc_getCursorPosition() const
{
	ivec2 cursorPosition = _core->_renderWindow->getCursorPosition();

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
		auto windowSize = Config::getInst().getWindowSize();
		auto viewportPosition = Config::getInst().getViewportPosition();
		auto viewportSize = Config::getInst().getViewportSize();

		ivec2 offset = ivec2(viewportPosition.x, windowSize.y - (viewportPosition.y + viewportSize.y));

		fvec2 relativeCursorPosition = fvec2(_core->_renderWindow->getCursorPosition()) - fvec2(offset);

		relativeCursorPosition = (relativeCursorPosition / fvec2(viewportSize)) * fvec2(windowSize);

		ivec2 result = ivec2(relativeCursorPosition);
		return ivec2(result.x, (Config::getInst().getWindowSize().y - result.y));
	}
}

const bool FabiEngine3D::misc_isMillisecondTimerStarted() const
{
	return _core->_timer->isStarted();
}

const bool FabiEngine3D::misc_isCursorVisible() const
{
	return _core->_renderWindow->isCursorVisible();
}

const bool FabiEngine3D::misc_isCursorInsideViewport() const
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

const bool FabiEngine3D::misc_isCursorInsideWindow() const
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

const bool FabiEngine3D::misc_checkInterval(unsigned int ticks) const
{
	return ((_core->_timer->getPassedTickCount() % ticks) == 0);
}

const vector<pair<string, int>> FabiEngine3D::misc_getUpdateProfilingStatistics() const
{
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
		pair<string, int>("soundUpdate", 0),
		pair<string, int>("networkUpdate", 0)
	};

	for(auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer->getDeltaPart(ID) / _core->_timer->getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const vector<pair<string, int>> FabiEngine3D::misc_getRenderProfilingStatistics() const
{
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

	for(auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer->getDeltaPart(ID) / _core->_timer->getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const string FabiEngine3D::misc_getCursorEntityID() const
{
	return _core->_renderBus->getCursorEntityID();
}

const bool FabiEngine3D::misc_isVsyncEnabled() const
{
	return _core->_renderWindow->isVsyncEnabled();
}

const bool FabiEngine3D::misc_isWireframeRenderingEnabled() const
{
	return _core->_renderBus->isWireframeRenderingEnabled();
}

const bool FabiEngine3D::misc_isShadowFrameRenderingEnabled() const
{
	return _core->_renderBus->isShadowFrameRenderingEnabled();
}

const bool FabiEngine3D::misc_isAabbFrameRenderingEnabled() const
{
	return _core->_renderBus->isAabbFrameRenderingEnabled();
}