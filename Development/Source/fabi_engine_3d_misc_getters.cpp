#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <chrono>
#include <direct.h>

using namespace std::chrono;

const int FabiEngine3D::misc_getRandomInteger(int min, int max)
{
	return Tools::getRandomInt(min, max);
}

const int FabiEngine3D::misc_getMsTimeSinceEpoch()
{
	return static_cast<int>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

const int FabiEngine3D::misc_getTriangleCount()
{
	return _core->_renderBus.getTriangleCount();
}

const float FabiEngine3D::misc_getRandomFloat(float min, float max)
{
	return Tools::getRandomFloat(min, max);
}

const float FabiEngine3D::misc_getAspectRatio()
{
	return static_cast<float>(misc_getWindowSize().x) / static_cast<float>(misc_getWindowSize().y);
}

const float FabiEngine3D::misc_getFPS()
{
	return 1000.0f / _core->_deltaTimeMS;
}

const float FabiEngine3D::misc_getPI()
{
	return Math::getPI();
}

const float FabiEngine3D::misc_degreesToRadians(float angle)
{
	return Math::degreesToRadians(angle);
}

const float FabiEngine3D::misc_radiansToDegrees(float angle)
{
	return Math::radiansToDegrees(angle);
}

const float FabiEngine3D::misc_stopMillisecondTimer()
{
	return _core->_timer.stop();
}

const float FabiEngine3D::misc_getLevelOfDetailDistance()
{
	return _core->_modelEntityManager.getLodDistance();
}

const string FabiEngine3D::misc_getWinExplorerFilename(const string& startingDirectory, const string& fileType)
{
	// Prepare filter C-string
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';
	auto startingDirectoryString = string(misc_getRootDirectory() + startingDirectory);
	auto startingDirectoryStringC = startingDirectoryString.c_str();

	// Open file explorer
	OPENFILENAME ofn;
	char pathBuffer[256] = {};
	char titleBuffer[100] = {};
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = pathBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(pathBuffer);
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = titleBuffer;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(titleBuffer);
	ofn.lpstrInitialDir = startingDirectoryStringC;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	// Return chosen filename or nothing if cancelled
	string filePath = ofn.lpstrFile;
	return filePath;
}

const string FabiEngine3D::misc_vec2str(Ivec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

const string FabiEngine3D::misc_vec2str(Vec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

const string FabiEngine3D::misc_vec2str(Vec3 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z);
}

const string FabiEngine3D::misc_vec2str(Vec4 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w);
}

const string FabiEngine3D::misc_getRootDirectory()
{
	return Tools::getRootDirectory();
}

const string FabiEngine3D::misc_getCpuName() // https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine
{
	// Temporary values
	int CPUInfo[4];
	char name[48];

	// Retrieve full CPU name string
	__cpuid(CPUInfo, 0x80000002);
	memcpy(name, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(name + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(name + 32, CPUInfo, sizeof(CPUInfo));

	// Convert to string
	string nameString;
	for (unsigned int i = 0; i < 48; i++)
	{
		nameString.push_back(name[i]);
	}

	// Remove trailing spaces
	string result;
	std::reverse(nameString.begin(), nameString.end());
	for (unsigned int i = 0; i < nameString.size(); i++)
	{
		// Check if end of whitespace found
		if (nameString[i] != 0)
		{
			result = nameString.substr(i);
			break;
		}
	}

	// Return
	std::reverse(result.begin(), result.end());
	return result;
}

const string FabiEngine3D::misc_getGpuName()
{
	return _core->_libraryLoader.getGpuName();
}

const string FabiEngine3D::misc_getOpenglVersion()
{
	return _core->_libraryLoader.getOpenglVersion();
}

const Vec2 FabiEngine3D::misc_convertToNDC(Vec2 position)
{
	position.x = (position.x * 2.0f) - 1.0f;
	position.y = (position.y * 2.0f) - 1.0f;

	return Vec2(position.x, position.y);
}

const Vec2 FabiEngine3D::misc_convertFromNDC(Vec2 position)
{
	position.x += 1.0f;
	position.x /= 2.0f;
	position.y += 1.0f;
	position.y /= 2.0f;

	return Vec2(position.x, position.y);
}

const Ivec2 FabiEngine3D::misc_convertToScreenCoords(Vec2 position)
{
	const float x = static_cast<float>(position.x) * static_cast<float>(misc_getWindowSize().x);
	const float y = static_cast<float>(position.y) * static_cast<float>(misc_getWindowSize().y);

	return Ivec2(static_cast<int>(x), static_cast<int>(y));
}

const Ivec2 FabiEngine3D::misc_getCursorPosition()
{
	Ivec2 mousePosition = _core->_window.getCursorPosition();

	return Ivec2(mousePosition.x, misc_getWindowSize().y - mousePosition.y);
}

const Ivec2 FabiEngine3D::misc_getCursorPositionRelativeToViewport()
{
	if (application_isExported())
	{
		return misc_getCursorPosition();
	}
	else
	{
		// Temporary values
		auto windowSize = Config::getInst().getWindowSize();
		auto viewportPosition = Config::getInst().getVpPos();
		auto viewportSize = Config::getInst().getVpSize();

		// Calculate viewport position Y offset, because GUI borders are not all of the same size
		Ivec2 offset = Ivec2(viewportPosition.x, windowSize.y - (viewportPosition.y + viewportSize.y));

		// Apply Y offset to cursor position
		Vec2 relativeCursorPosition = Vec2(_core->_window.getCursorPosition()) - Vec2(offset);

		// Convert fullscreen coords to viewport coords
		relativeCursorPosition = (relativeCursorPosition / Vec2(viewportSize)) * Vec2(windowSize);

		// Return
		Ivec2 result = Ivec2(relativeCursorPosition);
		return Ivec2(result.x, misc_getWindowSize().y - result.y);
	}
}

const Vec2 FabiEngine3D::misc_convertFromScreenCoords(Ivec2 position)
{
	const float x = static_cast<float>(position.x) / static_cast<float>(misc_getWindowSize().x);
	const float y = static_cast<float>(position.y) / static_cast<float>(misc_getWindowSize().y);

	return Vec2(x, y);
}

const Vec3 FabiEngine3D::misc_getRaycastVector()
{
	return _core->_rayCaster.getRay();
}

const Vec3 FabiEngine3D::misc_getRaycastPointOnTerrain()
{
	return _core->_rayCaster.getTerrainPoint();
}

const bool FabiEngine3D::misc_isRaycastPointOnTerrainValid()
{
	return (_core->_rayCaster.getTerrainPoint() != Vec3(-1.0f));
}

const bool FabiEngine3D::misc_isMillisecondTimerStarted()
{
	return _core->_timer.isStarted();
}

const Ivec2 FabiEngine3D::misc_getWindowSize()
{
	return Config::getInst().getWindowSize();
}

const Ivec2 FabiEngine3D::misc_getViewportPosition()
{
	return Config::getInst().getVpPos();
}

const Ivec2 FabiEngine3D::misc_getViewportSize()
{
	return Config::getInst().getVpSize();
}

const bool FabiEngine3D::misc_isCursorVisible()
{
	return _core->_window.isCursorVisible();
}

const bool FabiEngine3D::misc_isCursorInsideViewport()
{
	// Temporary values
	auto mousePosition = misc_getCursorPosition();
	auto viewportPosition = misc_getViewportPosition();
	auto viewportSize = misc_getViewportSize();

	// Checking if cursor is inside viewport
	if (mousePosition.x > viewportPosition.x && mousePosition.x < viewportPosition.x + viewportSize.x)
	{
		if (mousePosition.y > viewportPosition.y && mousePosition.y < viewportPosition.y + viewportSize.y)
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::misc_isCursorInsideWindow()
{
	// Temporary values
	auto mousePosition = misc_getCursorPosition();
	auto windowSize = misc_getWindowSize();
	
	// Checking if cursor is inside viewport
	if (mousePosition.x > 1 && mousePosition.x < windowSize.x - 1)
	{
		if (mousePosition.y > 1 && mousePosition.y < windowSize.y - 1)
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::misc_isDirectoryExisting(const string& filePath)
{
	struct stat fileInfo;
	int result = stat(filePath.c_str(), &fileInfo);
	return (result == 0 && (fileInfo.st_mode & S_IFDIR));
}

const bool FabiEngine3D::misc_isFileExisting(const string& filePath)
{
	struct stat fileInfo;
	bool isExisting = stat(filePath.c_str(), &fileInfo) == 0;
	return (isExisting && !misc_isDirectoryExisting(filePath));
}

const bool FabiEngine3D::misc_checkInterval(unsigned int frames)
{
	return ((_core->_timer.getPassedFrameCount() % frames) == 0);
}

const vector<pair<string, int>> FabiEngine3D::misc_getUpdateProfilingStatistics()
{
	// Final list of timer IDs
	vector<pair<string, int>> result =
	{
		pair<string, int>("coreUpdate", 0),
		pair<string, int>("cameraUpdate", 0),
		pair<string, int>("raycastUpdate", 0),
		pair<string, int>("collisionUpdate", 0),
		pair<string, int>("skyEntityUpdate", 0),
		pair<string, int>("waterEntityUpdate", 0),
		pair<string, int>("modelEntityUpdate", 0),
		pair<string, int>("billboardEntityUpdate", 0),
		pair<string, int>("aabbEntityUpdate", 0),
		pair<string, int>("guiEntityUpdate", 0),
		pair<string, int>("shadowUpdate", 0),
		pair<string, int>("audioUpdate", 0),
		pair<string, int>("networkUpdate", 0)
	};

	// Calculate percentages
	for (auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const vector<pair<string, int>> FabiEngine3D::misc_getRenderProfilingStatistics()
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
	for (auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

const bool FabiEngine3D::misc_createNewDirectory(const string& directoryPath)
{
	return (_mkdir(directoryPath.c_str()) != -1);
}

const bool FabiEngine3D::misc_isVsyncEnabled()
{
	return _core->_window.isVsyncEnabled();
}

const bool FabiEngine3D::misc_isWireframeRenderingEnabled()
{
	return _core->_renderBus.isWireframeRenderingEnabled();
}

const bool FabiEngine3D::misc_isShadowFrameRenderingEnabled()
{
	return _core->_renderBus.isShadowFrameRenderingEnabled();
}

const bool FabiEngine3D::misc_isAabbFrameRenderingEnabled()
{
	return _core->_renderBus.isAabbFrameRenderingEnabled();
}

const bool FabiEngine3D::misc_isDebugRenderingEnabled()
{
	return _core->_renderBus.isDebugRenderingEnabled();
}

const bool FabiEngine3D::misc_isTerrainRaycastPointingEnabled()
{
	return _core->_rayCaster.isTerrainPointingEnabled();
}

const bool FabiEngine3D::misc_isSoundsEnabled()
{
	return _core->_audioPlayer.isSoundsEnabled();
}

const bool FabiEngine3D::misc_isMusicEnabled()
{
	return _core->_audioPlayer.isMusicEnabled();
}

const unsigned int FabiEngine3D::misc_getMaxAudioChannelCount()
{
	return _core->_audioPlayer.getAllocatedChannelCount();
}